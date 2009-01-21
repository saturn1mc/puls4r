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
public class Quadric extends Shape {

	private double A;
	private double B;
	private double C;
	private double D;
	private double E;
	private double F;
	private double G;
	private double H;
	private double I;
	private double J;

	public Quadric(Enlightment enlightment, double a, double b, double c,
			double d, double e, double f, double g, double h, double i,
			double j, boolean perlinNoised) {

		this.enlightment = enlightment;

		this.A = a;
		this.B = b;
		this.C = c;
		this.D = d;
		this.E = e;
		this.F = f;
		this.G = g;
		this.H = h;
		this.I = i;
		this.J = j;

		if (perlinNoised) {
			this.perlin = Perlin.getInstance();
		}
	}

	private Intersection createIntersection(Ray ray) {
		Point3d m = new Point3d(ray.getOrigin().x
				+ (ray.getDirection().x * ray.getT()), ray.getOrigin()
				.y
				+ (ray.getDirection().y * ray.getT()), ray.getOrigin()
				.z
				+ (ray.getDirection().z * ray.getT()));

		Vector3d nm = new Vector3d(2.0 * A * m.x + D * m.y + E
				* m.z + G, 2.0 * B * m.y + D * m.x + F
				* m.z + H, 2.0 * C * m.z + E * m.x + F
				* m.y + I);

		nm.normalize();

		if (nm.dot(ray.getDirection()) > 0) {
			nm.negate();
		}

		if (perlin != null) {
			perlin.disruptNormal(nm, epsilon);
		}

		Intersection intersection = new Intersection(m, nm, this, ray.getT());

		return intersection;
	}

	@Override
	public Intersection intersection(Ray ray) {
		double Aq = A * (ray.getDirection().x)
				* (ray.getDirection().x) + B * (ray.getDirection().y)
				* (ray.getDirection().y) + C * (ray.getDirection().z)
				* (ray.getDirection().z) + D * (ray.getDirection().x)
				* (ray.getDirection().y) + E * (ray.getDirection().x)
				* (ray.getDirection().z) + F * (ray.getDirection().y)
				* (ray.getDirection().z);

		double Bq = 2.0
				* A
				* (ray.getOrigin().x)
				* (ray.getDirection().x)
				+ 2.0
				* B
				* (ray.getOrigin().y)
				* (ray.getDirection().y)
				+ 2.0
				* C
				* (ray.getOrigin().z)
				* (ray.getDirection().z)
				+ D
				* (((ray.getOrigin().x) * (ray.getDirection().y)) + ((ray
						.getOrigin().y) * (ray.getDirection().x)))
				+ E
				* ((ray.getOrigin().x) * (ray.getDirection().z))
				+ F
				* (((ray.getOrigin().y) * (ray.getDirection().z)) + ((ray
						.getOrigin().z) * (ray.getDirection().y)))
				+ G * (ray.getDirection().x) + H
				* (ray.getDirection().y) + I * (ray.getDirection().z);

		double Cq = A * (ray.getOrigin().x) * (ray.getOrigin().x) + B
				* (ray.getOrigin().y) * (ray.getOrigin().y) + C
				* (ray.getOrigin().z) * (ray.getOrigin().z) + D
				* (ray.getOrigin().x) * (ray.getOrigin().y) + E
				* (ray.getOrigin().x) * (ray.getOrigin().z) + F
				* (ray.getOrigin().y) * (ray.getOrigin().z) + H
				* (ray.getOrigin().y) + I * (ray.getOrigin().z) + J;

		if (Aq == 0) {
			ray.setT((-Cq / Bq));
			return createIntersection(ray);
		} else {

			if (((Bq * Bq) - (4 * Aq * Cq)) < 0) {
				return null;
			} else {
				double t0 = (-Bq - Math.sqrt((Bq * Bq) - (4 * Aq * Cq)))
						/ (2.0 * Aq);
				double t1 = (-Bq + Math.sqrt((Bq * Bq) - (4 * Aq * Cq)))
						/ (2.0 * Aq);

				if (t0 > 0) {
					ray.setT(t0);
					return createIntersection(ray);
				} else {
					if (t1 > 0) {
						ray.setT(t1);
						return createIntersection(ray);
					} else {
						return null;
					}
				}

			}

		}
	}

}
