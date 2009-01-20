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
		Point3d m = new Point3d(ray.getOrigin().getX()
				+ (ray.getDirection().getX() * ray.getT()), ray.getOrigin()
				.getY()
				+ (ray.getDirection().getY() * ray.getT()), ray.getOrigin()
				.getZ()
				+ (ray.getDirection().getZ() * ray.getT()));

		Vector3d nm = new Vector3d(2.0 * A * m.getX() + D * m.getY() + E
				* m.getZ() + G, 2.0 * B * m.getY() + D * m.getX() + F
				* m.getZ() + H, 2.0 * C * m.getZ() + E * m.getX() + F
				* m.getY() + I);

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
		double Aq = A * (ray.getDirection().getX())
				* (ray.getDirection().getX()) + B * (ray.getDirection().getY())
				* (ray.getDirection().getY()) + C * (ray.getDirection().getZ())
				* (ray.getDirection().getZ()) + D * (ray.getDirection().getX())
				* (ray.getDirection().getY()) + E * (ray.getDirection().getX())
				* (ray.getDirection().getZ()) + F * (ray.getDirection().getY())
				* (ray.getDirection().getZ());

		double Bq = 2.0
				* A
				* (ray.getOrigin().getX())
				* (ray.getDirection().getX())
				+ 2.0
				* B
				* (ray.getOrigin().getY())
				* (ray.getDirection().getY())
				+ 2.0
				* C
				* (ray.getOrigin().getZ())
				* (ray.getDirection().getZ())
				+ D
				* (((ray.getOrigin().getX()) * (ray.getDirection().getY())) + ((ray
						.getOrigin().getY()) * (ray.getDirection().getX())))
				+ E
				* ((ray.getOrigin().getX()) * (ray.getDirection().getZ()))
				+ F
				* (((ray.getOrigin().getY()) * (ray.getDirection().getZ())) + ((ray
						.getOrigin().getZ()) * (ray.getDirection().getY())))
				+ G * (ray.getDirection().getX()) + H
				* (ray.getDirection().getY()) + I * (ray.getDirection().getZ());

		double Cq = A * (ray.getOrigin().getX()) * (ray.getOrigin().getX()) + B
				* (ray.getOrigin().getY()) * (ray.getOrigin().getY()) + C
				* (ray.getOrigin().getZ()) * (ray.getOrigin().getZ()) + D
				* (ray.getOrigin().getX()) * (ray.getOrigin().getY()) + E
				* (ray.getOrigin().getX()) * (ray.getOrigin().getZ()) + F
				* (ray.getOrigin().getY()) * (ray.getOrigin().getZ()) + H
				* (ray.getOrigin().getY()) + I * (ray.getOrigin().getZ()) + J;

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
