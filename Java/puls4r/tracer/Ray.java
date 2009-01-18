/**
 * 
 */
package puls4r.tracer;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

/**
 * @author cmaurice2
 * 
 */
public class Ray {
	private Point3d origin;
	private Vector3d direction;
	private double t;
	
	public Ray(Point3d origin, Vector3d direction, double t) {
		this.origin = origin;
		this.direction = direction;
		this.t = t;
	}
	
	public Ray(Point3d origin, Vector3d direction) {
		this.origin = origin;
		this.direction = direction;
		this.t = 0;
	}

	public Point3d getOrigin() {
		return origin;
	}

	public void setOrigin(Point3d origin) {
		this.origin = origin;
	}

	public Vector3d getDirection() {
		return direction;
	}

	public void setDirection(Vector3d direction) {
		this.direction = direction;
	}

	public double getT() {
		return t;
	}

	public void setT(double t) {
		this.t = t;
	}
}
