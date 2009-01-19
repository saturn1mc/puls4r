/**
 * 
 */
package puls4r.enlightment;

import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.scene.objects.Light;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 * 
 */
public abstract class Enlightment {
	// Reflection properties
	private boolean reflect;
	private double kr;
	private double glossyFocal;
	private double glossyWidth;

	// Refraction properties
	private boolean refract;
	private double n;
	private double kt;

	public Enlightment() {
		reflect = false;
		kr = 0;
		glossyFocal = 0.0;
		glossyWidth = 0.0;
		
		refract = false;
		n = 1.0d;
		kt = 0;
	}

	public Vector3d getV(Ray ray) {
		Vector3d v = new Vector3d(ray.getDirection());
		v.negate();
		v.normalize();
		
		return v;
	}

	Vector3d getR(Vector3d light, Vector3d norm) {
		// r = ( ( (norm) * 2.0 ) * ( norm * light ) ) - light

		Vector3d norm2 = new Vector3d(norm);
		norm2.scale(2.0d);

		Vector3d r = new Vector3d(norm2);
		r.scale(norm.dot(light));
		r.sub(light);

		r.normalize();
		
		return r;
	}

	public Vector3d getL(Point3d point, Light light) {

		// l point, light vector

		Vector3d l = new Vector3d(light.getSource());
		l.sub(point);

		l.normalize();

		return l;
	}

	public abstract Color3f getColor(Point3d point, Vector3d norm, Ray ray,
			Vector<Light> lights);

	public boolean isReflecting() {
		return reflect;
	}

	public double getKR() {
		return kr;
	}

	public void setReflecting(boolean reflect, double kr) {

		this.reflect = reflect;
		this.kr = kr;

		if (kr < 0) {
			this.kr = 0;
		}

		if (kr > 1.0) {
			this.kr = 1.0;
		}
	}

	public boolean isRefracting() {
		return refract;
	}

	public double getN() {
		return n;
	}

	public double getKT() {
		return kt;
	}

	public void setRefracting(boolean refract, double n, double kt) {
		this.refract = refract;
		this.n = n;
		this.kt = kt;

		if (n < 0) {
			this.n = 0;
		}

		if (kt < 0) {
			this.kt = 0;
		}

		if (kt > 1.0) {
			this.kt = 1.0;
		}
	}

	public double getGlossyFocal() {
		return glossyFocal;
	}

	public double getGlossyWidth() {
		return glossyWidth;
	}

	public void setGlossy(double glossyFocal, double glossyWidth) {
		this.glossyFocal = glossyFocal;
		this.glossyWidth = glossyWidth;
	}
	
	private static float normalizedComponent(float component){
		
		float normalizedComponent = component;
		
		if(component < 0.0f){
			normalizedComponent = 0.0f;
		}
		else if(component > 1.0f){
			normalizedComponent = 1.0f;
		}
		
		return normalizedComponent;
	}
	
	public static void normalize(Color3f color){
		color.set(normalizedComponent(color.x), normalizedComponent(color.y), normalizedComponent(color.z));
	}
}
