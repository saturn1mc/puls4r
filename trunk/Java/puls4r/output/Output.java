/**
 * 
 */
package puls4r.output;

/**
 * @author Camille
 * 
 */
public abstract class Output {
	private int w;
	private int h;
	private int antialiasing;

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
}
