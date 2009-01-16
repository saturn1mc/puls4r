/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

/**
 * @author Camille
 *
 */
public class Photon {
	float pos[] = new float[3];		// photon position
	short plane;					// splitting plane for kd-tree
	char theta, phi;				// incoming direction
	float power[] = new float[3];	// photon power (uncompressed)
}
