/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

/**
 * @author cmaurice2
 *
 */
public class Photon {
	public float pos[];		// photon position
	public short plane;		// splitting plane for kd-tree
	public byte theta, phi;	// incoming direction
	public float power[];	// photon power (uncompressed)
	
	public Photon() {
		pos = new float[3];
		pos[0] = pos[1] = pos[2] = 0.0f;
		
		plane = 0;
		theta = phi = 0;
		
		power = new float[3];
		power[0] = power[1] = power[2] = 0.0f;
		
	}
	
	public void set(Photon p){
		this.pos[0] = p.pos[0];
		this.pos[1] = p.pos[1];
		this.pos[2] = p.pos[2];
		
		this.plane = p.plane;
		this.theta = p.theta;
		this.phi = p.phi;
		
		this.power[0] = p.power[0];
		this.power[1] = p.power[1];
		this.power[2] = p.power[2];
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof Photon){
			
			Photon p = (Photon)obj;
			
			return ((this.pos[0] == p.pos[0]) && (this.pos[1] == p.pos[1]) && (this.pos[2] == p.pos[2]) &&
					(this.plane == p.plane) && (this.theta == p.theta) && (this.phi == p.phi) &&
					(this.power[0] == p.power[0]) && (this.power[1] == p.power[1]) && (this.power[2] == p.power[2]));
		}
		else{
			return false;
		}
	}
}
