/**
 * 
 */
package puls4r.output;

import javax.vecmath.Color3f;

/**
 * @author Camille
 * 
 */
public abstract class Output {
	protected int w;
	protected int h;
	protected int antialiasing;
	
	protected Color3f pixels[][];

	public abstract void writePixel(Color3f color, int w, int h);
	
	public int getW() {
		return w;
	}

	public void setW(int w) {
		this.w = w;
	}

	public int getH() {
		return h;
	}

	public void setH(int h) {
		this.h = h;
	}

	public int getAntialiasing() {
		return antialiasing;
	}

	public void setAntialiasing(int antialiasing) {
		this.antialiasing = antialiasing;
	}
	
	public abstract void finalize();
}
