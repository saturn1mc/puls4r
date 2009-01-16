/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

/**
 * @author Camille
 *
 */
public class PhotonMap {
	int stored_photons;
	int half_stored_photons;
	int max_photons;
	int prev_scale;
	
	float costheta[] = new float[256];
	float sintheta[] = new float[256];
	float cosphi[] = new float[256];
	float sinphi[] = new float[256];
	
	float bbox_min[] = new float[3]; // use bbox_min;
	float bbox_max[] = new float[3]; // use bbox_max;
	
	PhotonMap( int max_phot )
	{
		stored_photons = 0;
		prev_scale = 1;
		max_photons = max_phot;
		
		photons = (Photon*)malloc( sizeof( Photon ) * ( max_photons+1 ) );
		
		if (photons == NULL) {
			fprintf(stderr,"Out of memory initializing photon map\n");
			exit(-1);
		}
		
		bbox_min[0] = bbox_min[1] = bbox_min[2] = 1e8f;
		bbox_max[0] = bbox_max[1] = bbox_max[2] = -1e8f;
		
		//----------------------------------------
		// initialize direction conversion tables
		//----------------------------------------
		
		for (int i=0; i<256; i++) {
			double angle = double(i)*(1.0/256.0)*M_PI;
			costheta[i] = cos( angle );
			sintheta[i] = sin( angle );
			cosphi[i]   = cos( 2.0*angle );
			sinphi[i]   = sin( 2.0*angle );
		}
	}
}
