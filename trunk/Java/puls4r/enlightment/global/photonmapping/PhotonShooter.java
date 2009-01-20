/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.enlightment.Enlightment;
import puls4r.scene.Scene;
import puls4r.scene.objects.Light;
import puls4r.tracer.Intersection;
import puls4r.tracer.Ray;

/**
 * @author Camille
 *
 */
public class PhotonShooter {
	private static int MAX_RECURSIONS = 500;
	private static double IRRADIANCE_AREA = 1.5;
	private static int IRRADIANCE_PHOTON_NUMBER = 1000000;
	
	private int currentRecursions;
	
	private int storedDirect;
	private int storedIndirect;
	private int storedCaustic;
	
	private int maxPhotons;
	
	private PhotonMap directEnlightment;
	private PhotonMap indirectEnlightment;
	private PhotonMap caustics;
	
	private Scene scene;
	
	public PhotonShooter(Scene scene, int maxPhotons) {
		this.scene = scene;
		this.maxPhotons = maxPhotons;
		
		directEnlightment = new PhotonMap(maxPhotons);
		indirectEnlightment = new PhotonMap(maxPhotons);
		caustics = new PhotonMap(maxPhotons);
	}
	
	private Vector3d randomDirection(){
		double x, y, z;
		
		do{
			x = Math.random();
			y = Math.random();
			z = Math.random();
		}while( (x*x)+(y*y)+(z*z) > 1);
		
		Vector3d randDir = new Vector3d(x, y, z);
		
		return randDir;
	}
	
	private boolean russianRoulette(double d){
		double e = Math.random();
		
		if(e < d){
			//Photon continues course
			return false;
		}
		else{
			//Photon absorbed
			return true;
		}
	}
	
	private void storePhoton(Point3d position, Vector3d direction, float energy[], boolean direct, boolean indirect, boolean caustic){
		float pos[] = {(float) position.x, (float) position.y, (float) position.z};
		float dir[] = {(float) direction.x, (float) direction.y, (float) direction.z};
		
		if(direct){
			storedDirect++;
			directEnlightment.store(energy, pos, dir);
		}
		
		if(indirect){
			storedIndirect++;
			indirectEnlightment.store(energy, pos, dir);
		}
		
		if(caustic){
			storedCaustic++;
			caustics.store(energy, pos, dir);
		}
	}
	
	private void scaleEnergy(float energy[], Color3f color){
		energy[0] *= (float)color.x;
		energy[1] *= (float)color.y;
		energy[2] *= (float)color.z;
	}
	
	private void shootPhoton(Ray ray, float energy[], boolean direct, boolean indirect, boolean caustic){
		//TODO split refraction coeff for all waves (r, g and b)
		currentRecursions++;
		
		Intersection photonIntersection = scene.getNearestIntersection(ray);
		
		if(photonIntersection != null){
			if(photonIntersection.getObject().isReflecting()){
				
				if(russianRoulette(photonIntersection.getObject().getKR()) || (currentRecursions >= MAX_RECURSIONS)){
					storePhoton(photonIntersection.getPoint(), ray.getDirection(), energy, direct, indirect, caustic);
				}
				else{
					Ray reflected = scene.reflectedRay(ray, photonIntersection);
					shootPhoton(reflected, energy, false, true, false);
				}
			}
			
			if(photonIntersection.getObject().isRefracting()){
				
				if(russianRoulette(photonIntersection.getObject().getKT()) || (currentRecursions >= MAX_RECURSIONS)){
					storePhoton(photonIntersection.getPoint(), ray.getDirection(), energy, direct, indirect, caustic);
				}
				else{
					Ray refracted = scene.refractedRay(ray, photonIntersection);
					shootPhoton(refracted, energy, false, false, true);
				}
				
			}
			
			if(!photonIntersection.getObject().isReflecting() && !photonIntersection.getObject().isRefracting()){
				
				Color3f objectColor = photonIntersection.getObject().getEnlightment().getColor(photonIntersection.getPoint(), photonIntersection.getNormal(), ray, scene.getLights());
				scaleEnergy(energy, objectColor);
				
				storePhoton(photonIntersection.getPoint(), ray.getDirection(), energy, direct, indirect, caustic);
				
				if(!russianRoulette(photonIntersection.getObject().getKR()) && !(currentRecursions >= MAX_RECURSIONS)){
					Vector3d randDir = randomDirection();
					Ray reflected =  new Ray(photonIntersection.getPoint(), randDir);
					shootPhoton(reflected, energy, false, true, false);
				}
			}
		}
	}
	
	public void shoot(){
		int lightNum = 0;
		
		for(Light l : scene.getLights()){
			lightNum++;
			
			int progress = 0;
			
			storedDirect = 0;
			storedIndirect = 0;
			storedCaustic = 0;
			
			while((storedDirect + storedIndirect + storedCaustic) < (maxPhotons / scene.getLights().size())){
				
				int done = (int)Math.round(100 * ((storedDirect + storedIndirect + storedCaustic)+1) / (maxPhotons / scene.getLights().size()));
				
				if(progress != done){
					progress = done;
					System.out.println("\r\tLight (" + lightNum + "/" + scene.getLights().size() + ") : " + progress + "%");
				}
				
				Vector3d randDir = randomDirection();
				Ray ray = new Ray(l.getSource(), randDir);
				
				float energy[] = {	(float) (l.getPower() * l.getColor().x), 
									(float) (l.getPower() * l.getColor().y), 
									(float) (l.getPower() * l.getColor().z)};
				
				currentRecursions = 0;
				shootPhoton(ray, energy, true, false, false);
			}
			
			/* Photons energy scaling */
			if(storedDirect != 0){
				directEnlightment.scale_photon_power(1.0f / storedDirect);
			}
			
			if(storedIndirect != 0){
				indirectEnlightment.scale_photon_power(1.0f / storedIndirect);
			}
			
			if(storedCaustic != 0){
				caustics.scale_photon_power(1.0f / storedCaustic);
			}
			
			System.out.println("");
		}
		
		System.out.println("--> Balancing direct photon map...");
		directEnlightment.balance();
		
		System.out.println("--> Balancing indirect photon map...");
		indirectEnlightment.balance();
		
		System.out.println("--> Balancing caustic photon map...");
		caustics.balance();
	}
	
	public Color3f irradianceEstimate(Intersection intersection){
		Color3f color = new Color3f();
		
		float irradiance[] = new float[3];
		float pos[] = {(float) intersection.getPoint().x, (float) intersection.getPoint().y, (float) intersection.getPoint().z};
		float normal[] = {(float) intersection.getNormal().x, (float) intersection.getNormal().y, (float) intersection.getNormal().z};
		
		//Direct enlightment component
		irradiance[0] = 0;
		irradiance[1] = 0;
		irradiance[2] = 0;
		
		directEnlightment.irradiance_estimate(irradiance, pos, normal, (float) IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
		
		color.set(color.x + irradiance[0], color.y + irradiance[1], color.z + irradiance[2]);			
		
		//Indirect enlightment component
		irradiance[0] = 0;
		irradiance[1] = 0;
		irradiance[2] = 0;
		
		indirectEnlightment.irradiance_estimate(irradiance, pos, normal, (float) IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
		
		color.set(color.x + irradiance[0], color.y + irradiance[1], color.z + irradiance[2]);	
		
		//Caustics component
		irradiance[0] = 0;
		irradiance[1] = 0;
		irradiance[2] = 0;
		
		caustics.irradiance_estimate(irradiance, pos, normal, (float) IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
		
		color.set(color.x + irradiance[0], color.y + irradiance[1], color.z + irradiance[2]);
		Enlightment.normalize(color);
		
		return color;
	}
}
