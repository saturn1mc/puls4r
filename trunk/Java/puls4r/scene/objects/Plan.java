/**
 * 
 */
package puls4r.scene.objects;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.enlightment.Enlightment;
import puls4r.texture.Perlin;
import puls4r.tracer.Intersection;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 * 
 */
public class Plan extends Shape {

	private Vector3d norm;
	private double d;

	private boolean monoface;

	public Plan(Enlightment enlightment, Vector3d norm, double d,
			boolean monoface, boolean perlinNoised) {
		this.enlightment = enlightment;

		this.norm = norm;
		norm.normalize();

		this.d = d;
		this.monoface = monoface;

		if (perlinNoised) {
			this.perlin = Perlin.getInstance();
		}
	}

	@Override
	public Intersection intersection(Ray ray) {
		double vd = (norm.getX() * ray.getDirection().getX())
				+ (norm.getY() * ray.getDirection().getY())
				+ (norm.getZ() * ray.getDirection().getZ());
		double t = -((norm.getX() * ray.getOrigin().getX())
				+ (norm.getY() * ray.getOrigin().getY())
				+ (norm.getZ() * ray.getOrigin().getZ()) + d)
				/ vd;

		if (vd == 0 || (vd > 0 && monoface)) {
			return null;
		} else {
			if (t < 0) {
				return null;
			} else {

				ray.setT(t);

				Point3d m = new Point3d(ray.getOrigin().getX()
						+ (ray.getDirection().getX() * ray.getT()), ray
						.getOrigin().getY()
						+ (ray.getDirection().getY() * ray.getT()), ray
						.getOrigin().getZ()
						+ (ray.getDirection().getZ() * ray.getT()));

				Vector3d nm = new Vector3d(norm);

				if (perlin != null) {
					perlin.disruptNormal(nm, m, epsilon);
				}

				return new Intersection(m, nm, this, ray.getT());
			}
		}
	}
}
