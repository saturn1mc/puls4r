/**
 * 
 */
package puls4r.scene.objects;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.tracer.Intersection;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 * 
 */
public class Sphere extends Shape {

	Point3d center;
	double radius;

	public Sphere(Point3d center, double radius) {
		this.center = center;
		this.radius = radius;
	}

	@Override
	protected Intersection createIntersection(Ray ray) {
		Point3d m = new Point3d(ray.getOrigin().getX()
				+ (ray.getDirection().getX() * ray.getT()), ray.getOrigin()
				.getY()
				+ (ray.getDirection().getY() * ray.getT()), ray.getOrigin()
				.getZ()
				+ (ray.getDirection().getZ() * ray.getT()));

		Vector3d nm = new Vector3d((m.getX() - center.getX()) / radius, (m
				.getY() - center.getY())
				/ radius, (m.getZ() - center.getZ()) / radius);

		nm.normalize();

		if (perlin != null) {
			perlin.disruptNormal(nm, epsilon);
		}

		Intersection intersection = new Intersection(m, nm, this, ray.getT());

		return intersection;
	}

	@Override
	public Intersection intersection(Ray ray) {
		double A = Math.pow(ray.getDirection().getX(), 2.0) + Math.pow(ray.getDirection().getY(), 2.0) + Math.pow(ray.getDirection().getZ(), 2.0);
		double B = 2.0 * ( (ray.getDirection().getX() * (ray.getOrigin().getX() - center.getX())) + (ray.getDirection().getY() * (ray.getOrigin().getY() - center.getY())) + (ray.getDirection().getZ() * (ray.getOrigin().getZ() - center.getZ())));
		double C = Math.pow(ray.getOrigin().getX() - center.getX(), 2.0) + Math.pow(ray.getOrigin().getY() - center.getY(), 2.0) + Math.pow(ray.getOrigin().getZ() - center.getZ(), 2.0) - Math.pow(radius, 2.0);
		
		double t0 = (-B - Math.sqrt((B*B) - (4*A*C))) / (2.0*A);
		double t1 = (-B + Math.sqrt((B*B) - (4*A*C))) / (2.0*A);
		
		if(t0 > 0 && t1 > 0){
			
			ray.setT(Math.min(t0, t1));
			return createIntersection(ray);
		}
		else{
			if(t0 > 0){
				ray.setT(t0);
				return createIntersection(ray);
			}
			else{
				if(t1 > 0){
					ray.setT(t1);
					return createIntersection(ray);
				}
				else{
					return null;
				}
			}
		}
	}
}
