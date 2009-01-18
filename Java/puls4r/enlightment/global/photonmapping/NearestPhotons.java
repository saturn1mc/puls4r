/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

/**
 * @author Camille
 * 
 */
public class NearestPhotons {
	int max;
	int found;
	int got_heap;
	float pos[];
	float dist2[];
	Photon index[];

	public NearestPhotons() {
		max = 0;
		found = 0;
		got_heap = 0;

		pos = new float[3];
	}
}
