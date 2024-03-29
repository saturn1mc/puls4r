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
public class Triangle extends Shape{
	private Point3d points[];
	private Plan plan;
	
	public Triangle(Enlightment enlightment, Point3d a, Point3d b, Point3d c, boolean perlinNoised){
		this.enlightment = enlightment;
		
		this.points = new Point3d[3];
		this.points[0] = a;
		this.points[1] = b;
		this.points[2] = c;
		
		Vector3d AB = new Vector3d(b.x - a.x, b.y - a.y, b.z - a.z);
		Vector3d AC = new Vector3d(c.x - a.x, c.y - a.y, c.z - a.z);
	
		Vector3d norm = new Vector3d();
		norm.cross(AB, AC);
		norm.normalize();
		
		double d = - (norm.x * points[0].x)  - (norm.y * points[0].y) - (norm.z * points[0].z);
	
		this.plan = new Plan(enlightment, norm, d, false, perlinNoised);
		
		if(perlinNoised){
			perlin = Perlin.getInstance();
		}
	}
	
	@Override
	public Intersection intersection(Ray ray) {
		Intersection intersection = plan.intersection(ray);
		
		if(intersection == null){
			return null;
		}
		else{
			Point3d b = new Point3d(points[1]);
			b.sub(points[0]);
			
			Point3d c = new Point3d(points[2]);
			c.sub(points[0]);
			
			Point3d p = new Point3d(intersection.getPoint());
			p.sub(points[0]);
			
			double u = ((p.y * c.x) - (p.x * c.y)) / ((b.y * c.x) - (b.x * c.y));
			double v = ((p.y * b.x) - (p.x * b.y)) / ((c.y * b.x) - (c.x * b.y));
			
			if((u>=0) && (v >= 0) && ((u+v) <= 1)){
				intersection.setObject(this);
				
				if(perlin != null){
					perlin.disruptNormal(intersection.getNormal(), epsilon);
				}
				
				return intersection;
			}
			else{
				return null;
			}
		}
	}
}
