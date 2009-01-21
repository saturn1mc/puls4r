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
public class Sphere extends Shape {

	Point3d center;
	double radius;

	public Sphere(Enlightment enlightment, Point3d center, double radius, boolean perlinNoised) {
		
		this.enlightment = enlightment;
		this.center = center;
		this.radius = radius;
		
		if(perlinNoised){
			this.perlin = Perlin.getInstance();
		}
	}
	
	protected Intersection createIntersection(Ray ray) {
		Point3d m = new Point3d(ray.getOrigin().x
				+ (ray.getDirection().x * ray.getT()), ray.getOrigin()
				.y
				+ (ray.getDirection().y * ray.getT()), ray.getOrigin()
				.z
				+ (ray.getDirection().z * ray.getT()));

		Vector3d nm = new Vector3d((m.x - center.x) / radius, (m
				.y - center.y)
				/ radius, (m.z - center.z) / radius);

		nm.normalize();

		if (perlin != null) {
			perlin.disruptNormal(nm, epsilon);
		}

		return new Intersection(m, nm, this, ray.getT());
	}

	@Override
	public Intersection intersection(Ray ray) {
		double A = Math.pow(ray.getDirection().x, 2.0) + Math.pow(ray.getDirection().y, 2.0) + Math.pow(ray.getDirection().z, 2.0);
		double B = 2.0 * ( (ray.getDirection().x * (ray.getOrigin().x - center.x)) + (ray.getDirection().y * (ray.getOrigin().y - center.y)) + (ray.getDirection().z * (ray.getOrigin().z - center.z)));
		double C = Math.pow(ray.getOrigin().x - center.x, 2.0) + Math.pow(ray.getOrigin().y - center.y, 2.0) + Math.pow(ray.getOrigin().z - center.z, 2.0) - Math.pow(radius, 2.0);
		
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
