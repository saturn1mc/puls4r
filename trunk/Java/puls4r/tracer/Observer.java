/**
 * 
 */
package puls4r.tracer;

import javax.vecmath.Matrix4d;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

/**
 * @author cmaurice2
 * 
 */
public class Observer {
	private Point3d eye;
	private Vector3d sight;
	private Matrix4d view;
	private double alpha;

	public Observer(Point3d eye, Vector3d sight, double alpha) {
		this.eye = eye;
		
		this.sight = sight;
		this.sight.normalize();
		
		this.alpha = alpha;

		initMatrix();
	}
	
	public Observer(Point3d eye, Point3d sight, double alpha) {
		this.eye = eye;
		
		this.sight = new Vector3d(sight.x - eye.x, sight.y - eye.y, sight.z - eye.z);
		this.sight.normalize();
		
		this.alpha = alpha;

		initMatrix();
	}

	public Ray ray(Point3d sp) {
		Point3d np = new Point3d(sp);
		view.transform(np);

		Vector3d dir = new Vector3d(np.x - eye.x, np.y - eye.y, np.z - eye.z);
		Ray ray = new Ray(eye, dir);

		return ray;
	}

	void initMatrix() {
		Vector3d up = new Vector3d(0, 1, 0);
		up.normalize();

		Vector3d w = new Vector3d();
		w.cross(sight, up);
		w.normalize();

		Vector3d u = new Vector3d();
		u.cross(sight, w);
		u.normalize();

		view = new Matrix4d(w.x, w.y, w.z, 0, u.x, u.y, u.z, 0, sight.x, sight.y, sight.z, 0, eye.x, eye.y, eye.z, 1);
		view.transpose();
	}

	public Point3d getEye() {
		return eye;
	}

	public void setEye(Point3d eye) {
		this.eye = eye;
	}

	public Vector3d getSight() {
		return sight;
	}

	public void setSight(Vector3d sight) {
		this.sight = sight;
	}

	public Matrix4d getView() {
		return view;
	}

	public void setView(Matrix4d view) {
		this.view = view;
	}

	public double getAlpha() {
		return alpha;
	}

	public void setAlpha(double alpha) {
		this.alpha = alpha;
	}
}
