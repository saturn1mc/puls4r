/**
 * 
 */
package puls4r.scene;

import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

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

			Color3f objectColor = nearestIntersection.getObject()
					.getEnlightment().getColor(nearestIntersection.getPoint(),
							nearestIntersection.getNormal(), ray, lights);

			if ((currentRecursions >= MAX_RECURSIONS)
					|| (!nearestIntersection.getObject().isReflecting() && !nearestIntersection
							.getObject().isRefracting())) {

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
						reflectedColor = glossyReflection(ray,
								nearestIntersection, mode);
					}

					reflectedColor
							.set(
									(float) (objectColor.x
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (reflectedColor.x * nearestIntersection
											.getObject().getKR())),
									(float) (objectColor.y
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (reflectedColor.y * nearestIntersection
											.getObject().getKR())),
									(float) (objectColor.z
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (reflectedColor.z * nearestIntersection
											.getObject().getKR())));

					oc.set(oc.x + reflectedColor.x, oc.y + reflectedColor.y,
							oc.z + reflectedColor.z);
				}

				if (nearestIntersection.getObject().isRefracting()) {
					Ray refracted = refractedRay(ray, nearestIntersection);

					refractedColor = observedColor(refracted, mode);

					refractedColor
							.set(
									(float) (objectColor.x
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (refractedColor.x * nearestIntersection
											.getObject().getKR())),
									(float) (objectColor.y
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (refractedColor.y * nearestIntersection
											.getObject().getKR())),
									(float) (objectColor.z
											* (1.0 - nearestIntersection
													.getObject().getKR()) + (refractedColor.z * nearestIntersection
											.getObject().getKR())));
					oc.set(oc.x + refractedColor.x, oc.y + refractedColor.y,
							oc.z + refractedColor.z);
				}

				if (nearestIntersection.getObject().isReflecting()
						&& nearestIntersection.getObject().isRefracting()) {
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

	private Color3f glossyReflection(Ray ray, Intersection intersection,
			int mode) {

		Color3f color = new Color3f();
		
		double cpt = 0;
		
		double f = intersection.getObject().getGlossyFocal();
		double radius = intersection.getObject().getGlossyWidth();
		double step = 1.0 / SMOOTHING;
		
		Ray reflected = reflectedRay(ray, intersection);
		
		Vector3d scaledReflection = new Vector3d(reflected.getDirection());
		scaledReflection.scale(f);
		
		Point3d sight = new Point3d(intersection.getPoint());
		sight.add(scaledReflection);
		
		Observer virtualObs = new Observer(intersection.getPoint(), sight, Math.PI / 4.0);
		
		for(double i=-radius/2.0; i<radius/2.0; i+= step){
			for(double j=-radius/2.0; j<radius/2.0; j+= step){
				
				Point3d target;
				
				if(RANDOMIZE){
					double ii = (Math.random() * radius) - (radius/2.0);
					double jj = (Math.random() * radius) - (radius/2.0);
					target = new Point3d(ii, jj, f);
				}
				else{
					target = new Point3d(i, j, f);
				}
				
				Ray glossyRay = virtualObs.ray(target);
				Intersection glossyIntersection = getNearestIntersection(glossyRay);
				
				if(glossyIntersection != null){
					
					Color3f glossyColor = observedColor(glossyRay, mode);
					
					color.add(glossyColor);
					cpt++;
				}
			}
		}
		
		color.scale((float) (1.0 / cpt));
		
		return color;
	}

	private void shadow(Color3f color, Intersection intersection) {
		for (Light l : lights) {

			double enlighted = 0;
			double shadowed = 0;
			double radius = l.getRadius();
			double step = 1.0 / SMOOTHING;

			Vector3d shiftedNorm = new Vector3d(intersection.getNormal());
			shiftedNorm.scale(EPSILON);

			Point3d shadowedPoint = new Point3d(intersection.getPoint());
			shadowedPoint.add(shiftedNorm);

			Vector3d distanceTolight = new Vector3d(l.getSource().x
					- shadowedPoint.x, l.getSource().y - shadowedPoint.y, l
					.getSource().z
					- shadowedPoint.z);
			Observer virtualObs = new Observer(shadowedPoint, l.getSource(),
					(Math.PI / 4.0d));
			double f = distanceTolight.length();

			for (double i = -radius / 2.0; i < radius / 2.0; i += step) {
				for (double j = -radius / 2.0; j < radius / 2.0; j += step) {

					Point3d target;

					if (RANDOMIZE) {
						double ii = (Math.random() * radius) - (radius / 2.0);
						double jj = (Math.random() * radius) - (radius / 2.0);
						target = new Point3d(ii, jj, f);
					} else {
						target = new Point3d(i, j, f);
					}

					Ray shadowRay = virtualObs.ray(target);
					Intersection shadowIntersection = getNearestShadowIntersection(shadowRay);

					if (shadowIntersection != null) {

						Vector3d shadowVect = new Vector3d(shadowIntersection
								.getPoint().x
								- intersection.getPoint().x, shadowIntersection
								.getPoint().y
								- intersection.getPoint().y, shadowIntersection
								.getPoint().z
								- intersection.getPoint().z);

						if (shadowVect.length() < f) {
							shadowed++;
						} else {
							enlighted++;
						}
					} else {
						enlighted++;
					}
				}
			}

			if (shadowed > 0) {
				color.scale((float) Math.min(1.0,
						(enlighted / (shadowed + enlighted)) + 0.3));
			}
		}
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

		// reflect = rayDir - ( (intNorm * 2.0) * (interNorm * rayDir) )

		Vector3d toSub = new Vector3d(intersection.getNormal());
		toSub.scale(2.0);
		toSub.scale(intersection.getNormal().dot(ray.getDirection()));

		Vector3d reflectDirection = new Vector3d(ray.getDirection());
		reflectDirection.sub(toSub);
		reflectDirection.normalize();
		reflectDirection.scale(EPSILON);

		Point3d origin = new Point3d(intersection.getPoint());
		origin.add(reflectDirection);

		Ray reflected = new Ray(origin, reflectDirection);

		return reflected;
	}

	public Ray refractedRay(Ray ray, Intersection intersection) {
		Ray r1 = refractRay(ray, intersection, 1.0, intersection.getObject()
				.getN());
		Intersection refractionIntersection = getNearestIntersection(r1);

		if (refractionIntersection != null) {
			if (refractionIntersection.getObject() == intersection.getObject()) {
				refractionIntersection.getNormal().negate();

				Ray r2 = refractRay(r1, refractionIntersection, intersection
						.getObject().getN(), 1.0);
				return r2;
			} else {
				return r1;
			}
		} else {
			return r1;
		}
	}

	public Ray refractRay(Ray ray, Intersection intersection, double n1,
			double n2) {

		double n = n2 / n1;
		double cosT = intersection.getNormal().dot(ray.getDirection());
		double sinT2 = 1.0 - ((1.0 - cosT * cosT) / (n * n));

		Vector3d refractDirection;

		if (sinT2 > 0) {
			// refraction
			// refract = ( (rayDirection - (interNorm * cosT) ) * (1.0 / n) ) -
			// ( interNorm * sqrt(sinT2));

			Vector3d sub1 = new Vector3d(intersection.getNormal());
			sub1.scale(cosT);

			Vector3d firstMember = new Vector3d(ray.getDirection());
			firstMember.sub(sub1);
			firstMember.scale(1.0d / n);

			Vector3d secondMember = new Vector3d(intersection.getNormal());
			secondMember.scale(Math.sqrt(sinT2));

			refractDirection = new Vector3d(firstMember);
			refractDirection.sub(secondMember);
		} else {
			// reflexion
			// reflect = rayDir - ( (intNorm * 2.0) * (interNorm * rayDir) )
			Vector3d toSub = new Vector3d(intersection.getNormal());
			toSub.scale(2.0);
			toSub.scale(intersection.getNormal().dot(ray.getDirection()));

			refractDirection = new Vector3d(ray.getDirection());
			refractDirection.sub(toSub);
			refractDirection.normalize();
		}

		refractDirection.normalize();
		refractDirection.scale(EPSILON);

		Point3d origin = new Point3d(intersection.getPoint());
		origin.add(refractDirection);

		Ray refracted = new Ray(origin, refractDirection);

		return refracted;
	}

	public Intersection getNearestIntersection(Ray ray) {
		Intersection nearestIntersection = null;

		for (Shape s : shapes) {

			Intersection candidate = s.intersection(ray);

			if (candidate != null) {
				if ((nearestIntersection == null || nearestIntersection.getT() > candidate
						.getT())
						&& (candidate.getT() > EPSILON)) {
					nearestIntersection = candidate;
				}
			}

		}

		return nearestIntersection;
	}

	public Intersection getNearestShadowIntersection(Ray ray) {
		Intersection nearestIntersection = null;

		for (Shape s : shapes) {

			Intersection candidate = s.intersection(ray);

			if (candidate != null) {
				if ((nearestIntersection == null || nearestIntersection.getT() > candidate
						.getT())
						&& (!candidate.getObject().isRefracting())
						&& (candidate.getT() > EPSILON)) {
					nearestIntersection = candidate;
				}
			}
		}

		return nearestIntersection;
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
			System.err
					.println("Can't trace Scene : attributes uninitialized (check observer, image and background color)");
		}
	}
}
