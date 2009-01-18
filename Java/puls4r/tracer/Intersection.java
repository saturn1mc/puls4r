/**
 * 
 */
package puls4r.tracer;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

/**
 * @author Camille
 * 
 */
public class Intersection {
	private Point3d point;
	private Vector3d normal;
	private puls4r.scene.objects.Shape object;
	private double t;

	public Intersection(Point3d point, Vector3d normal, puls4r.scene.objects.Shape object, double t) {
		super();
		this.point = point;
		this.normal = normal;
		this.object = object;
		this.t = t;
	}

	public Point3d getPoint() {
		return point;
	}

	public void setPoint(Point3d point) {
		this.point = point;
	}

	public Vector3d getNormal() {
		return normal;
	}

	public void setNormal(Vector3d normal) {
		this.normal = normal;
	}

	public puls4r.scene.objects.Shape getObject() {
		return object;
	}

	public void setObject(puls4r.scene.objects.Shape object) {
		this.object = object;
	}

	public double getT() {
		return t;
	}

	public void setT(double t) {
		this.t = t;
	}
}
