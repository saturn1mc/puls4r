/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

/**
 * @author cmaurice2
 *
 */
public class Photon {
	public float pos[] = new float[3];		// photon position
	public short plane;						// splitting plane for kd-tree
	public byte theta, phi;					// incoming direction
	public float power[] = new float[3];	// photon power (uncompressed)
}
