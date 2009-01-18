/**
 * 
 */
package puls4r.scene;

import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;

import puls4r.enlightment.global.photonmapping.PhotonShooter;
import puls4r.output.Output;
import puls4r.scene.objects.Light;
import puls4r.scene.objects.Shape;
import puls4r.tracer.Intersection;
import puls4r.tracer.Observer;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 * 
 */
public class Scene {

	private static final int RAYCASTING_MODE = 0;
	private static final int PHOTONMAPPING_MODE = 1;

	private double EPSILON = 0.000001;
	private int PHOTONS = 1000000;
	private int MAX_RECURSIONS = 1000;

	private boolean RANDOMIZE = false;
	private double SMOOTHING = 4.0;

	private int currentRecursions;

	private PhotonShooter shooter;
	private Observer observer;
	private Output output;
	private Color3f background;
	private Vector<Shape> shapes;
	private Vector<Light> lights;
	private double focal;

	private double calcFocal() {
		return ((output.getW() / 2.0) / Math.tan(observer.getAlpha() / 2.0));
	}

	private Color3f observedColor(Ray ray, int mode) {
		Color3f oc = new Color3f(background);
		Intersection nearestIntersection = getNearestIntersection(ray);

		currentRecursions++;

		if (nearestIntersection == null) {
			return oc;
		} else {

			Color3f objectColor = nearestIntersection.getObject().getEnlightment().getColor(nearestIntersection.getPoint(), nearestIntersection.getNormal(), ray, lights);

			if ((currentRecursions >= MAX_RECURSIONS) || (!nearestIntersection.getObject().isReflecting() && !nearestIntersection.getObject().isRefracting())) {

				switch (mode) {
				case RAYCASTING_MODE:
					oc = new Color3f(objectColor);
					shadow(oc, nearestIntersection);

					break;

				case PHOTONMAPPING_MODE:

					oc = shooter.irradianceEstimate(nearestIntersection);

					break;

				default:
					System.err.println("Unknown mode " + mode + " for tracing");
				}
			} else {
				Color3f reflectedColor = new Color3f();
				Color3f refractedColor = new Color3f();

				if (nearestIntersection.getObject().isReflecting()) {

					if (nearestIntersection.getObject().getGlossyFocal() == 0) {
						Ray reflected = reflectedRay(ray, nearestIntersection);
						reflectedColor = observedColor(reflected, mode);
					} else {
						reflectedColor = glossyReflection(ray, nearestIntersection, mode);
					}

					reflectedColor.set((float) (objectColor.x * (1.0 - nearestIntersection.getObject().getKR()) + (reflectedColor.x * nearestIntersection.getObject().getKR())), (float) (objectColor.y * (1.0 - nearestIntersection.getObject().getKR()) + (reflectedColor.y * nearestIntersection.getObject().getKR())), (float) (objectColor.z * (1.0 - nearestIntersection.getObject().getKR()) + (reflectedColor.z * nearestIntersection.getObject().getKR())));

					oc.set(oc.x + reflectedColor.x, oc.y + reflectedColor.y, oc.z + reflectedColor.z);
				}

				if (nearestIntersection.getObject().isRefracting()) {
					Ray refracted = refractedRay(ray, nearestIntersection);

					refractedColor = observedColor(refracted, mode);

					refractedColor.set((float) (objectColor.x * (1.0 - nearestIntersection.getObject().getKR()) + (refractedColor.x * nearestIntersection.getObject().getKR())), (float) (objectColor.y * (1.0 - nearestIntersection.getObject().getKR()) + (refractedColor.y * nearestIntersection.getObject().getKR())), (float) (objectColor.z * (1.0 - nearestIntersection.getObject().getKR()) + (refractedColor.z * nearestIntersection.getObject().getKR())));
					oc.set(oc.x + refractedColor.x, oc.y + refractedColor.y, oc.z + refractedColor.z);
				}

				if (nearestIntersection.getObject().isReflecting() && nearestIntersection.getObject().isRefracting()) {
					oc.scale(0.5f);
				}
			}

			return oc;
		}
	}

	private Color3f colorAt(double l, double p, int mode) {
		Point3d target = new Point3d(p, l, focal);
		Ray ray = observer.ray(target);

		currentRecursions = 0;

		return observedColor(ray, mode);
	}

	private Color3f antialiasedColor(double l, double p, int mode) {
		Color3f finalColor = new Color3f();
		double cpt = 0;
		double aa = 1.0 / ((double) output.getAntialiasing());

		for (double l2 = (l - 1); l2 <= (l + 1); l2 += aa) {
			for (double p2 = (p - 1); p2 <= (p + 1); p2 += aa) {
				finalColor.add(colorAt(l2, p2, mode));
				cpt++;
			}
		}

		finalColor.scale((float) (1.0 / cpt));

		return finalColor;
	}

	private Color3f glossyReflection(Ray ray, Intersection intersection, int mode) {
		// TODO
	}

	private void shadow(Color3f color, Intersection intersection) {
		// TODO
	}

	/* Ray Casting Function */
	private void rayCasting() {
		// TODO
	}

	/* Photon Mapping Functions */
	private void photonMapping() {
		// TODO
	}

	public Ray reflectedRay(Ray ray, Intersection intersection) {
		// TODO
	}

	public Ray refractedRay(Ray ray, Intersection intersection) {
		// TODO
	}

	public Ray refractRay(Ray ray, Intersection intersection, double n1, double n2) {
		// TODO
	}

	public Intersection getNearestIntersection(Ray ray) {
		// TODO
	}

	public Intersection getNearestShadowIntersection(Ray ray) {
		// TODO
	}

	public void addShape(Shape obj) {
		// TODO
	}

	public void addLight(Light light) {
		// TODO
	}

	public Vector<Shape> getShapes() {
		return shapes;
	}

	public Vector<Light> getLights() {
		return lights;
	}

	public void trace(int mode) {
		if (observer != null && output != null && background != null) {
			switch (mode) {
			case RAYCASTING_MODE:
				rayCasting();

				break;

			case PHOTONMAPPING_MODE:
				photonMapping();

				break;

			default:
				System.err.println("Unknown mode " + mode + " for tracing");
			}
		} else {
			System.err.println("Can't trace Scene : attributes uninitialized (check observer, image and background color)");
		}
	}
}
