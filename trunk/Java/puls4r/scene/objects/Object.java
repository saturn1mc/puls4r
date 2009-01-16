/**
 * 
 */
package puls4r.scene.objects;

import puls4r.enlightment.Enlightment;
import puls4r.texture.Perlin;
import puls4r.tracer.Intersection;
import puls4r.tracer.Ray;

/**
 * @author Camille
 *
 */
public abstract class Object {
	
	private Enlightment enlightment;
	private Perlin perlin;
	private double epsilon;
	
	public abstract Intersection intersection(Ray ray);

	public Enlightment getEnlightment() {
		return enlightment;
	}

	public void setEnlightment(Enlightment enlightment) {
		this.enlightment = enlightment;
	}

	public Perlin getPerlin() {
		return perlin;
	}

	public void setPerlin(Perlin perlin) {
		this.perlin = perlin;
	}

	public double getEpsilon() {
		return epsilon;
	}

	public void setEpsilon(double epsilon) {
		this.epsilon = epsilon;
	}
}
