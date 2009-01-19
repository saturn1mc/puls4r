/**
 * 
 */
package puls4r.output;

import javax.vecmath.Color3f;

/**
 * @author Camille
 * 
 */
public interface Output {
	public abstract void writePixel(Color3f color, int w, int h);
	public int getW();
	public int getH();
	public int getAntialiasing();
	public abstract void finalize();
}
