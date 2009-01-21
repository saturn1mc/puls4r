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
public abstract class Shape {
	
	protected Enlightment enlightment;
	protected Perlin perlin;
	protected double epsilon;
	
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
	
	public boolean isReflecting() {
		return enlightment.isReflecting();
	}

	public double getKR() {
		return enlightment.getKR();
	}

	public void setReflecting(boolean reflect, double kr) {
		enlightment.setReflecting(reflect, kr);
	}

	public boolean isRefracting() {
		return enlightment.isRefracting();
	}

	public double getN() {
		return enlightment.getN();
	}

	public double getKT() {
		return enlightment.getKT();
	}

	public void setRefracting(boolean refract, double n, double kt) {
		enlightment.setRefracting(refract, n, kt);
	}

	public double getGlossyFocal() {
		return enlightment.getGlossyFocal();
	}

	public double getGlossyWidth() {
		return enlightment.getGlossyWidth();
	}

	public void setGlossy(double glossyFocal, double glossyWidth) {
		enlightment.setGlossy(glossyFocal, glossyWidth);
	}
}
