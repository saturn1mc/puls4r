/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.color.Color;
import puls4r.enlightment.Enlightment;
import puls4r.math.Point3;
import puls4r.math.Vector3;
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
	private static float IRRADIANCE_AREA = 0.5f;
	private static int IRRADIANCE_GATHER = 50;
	
	private int currentRecursions;
	
	private int storedDirect;
	private int storedIndirect;
	private int storedCaustic;
	
	private int maxPhotons;
	
	private PhotonMap directEnlightment;
	//private GlobalPhotonMap indirectEnlightment;
	//private GlobalPhotonMap caustics;
	
	private Scene scene;
	
	public PhotonShooter(Scene scene, int maxPhotons) {
		this.scene = scene;
		this.maxPhotons = maxPhotons;
		
		directEnlightment = new PhotonMap(maxPhotons, IRRADIANCE_GATHER, IRRADIANCE_AREA);
		//indirectEnlightment = new GlobalPhotonMap(maxPhotons, (int)(maxPhotons*IRRADIANCE_PHOTON_RATIO), IRRADIANCE_AREA);
		//caustics = new GlobalPhotonMap(maxPhotons, (int)(maxPhotons*IRRADIANCE_PHOTON_RATIO), IRRADIANCE_AREA);
		
		directEnlightment.prepare();
		//indirectEnlightment.prepare();
		//caustics.prepare();
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
	
	private void storePhoton(Point3d position, Vector3d norm, Vector3d direction, float energy[], Color3f diffColor, boolean direct, boolean indirect, boolean caustic){
		Point3 point = new Point3((float)position.x, (float)position.y, (float)position.z);
		Vector3 dir = new Vector3((float)direction.x, (float)direction.y, (float)direction.z);
		Vector3 normal = new Vector3((float)norm.x, (float)norm.y, (float)norm.z);;
		
		Color power = new Color(energy[0], energy[1], energy[2]);
		Color diffuse = new Color((float)diffColor.x, (float)diffColor.y, (float)diffColor.z);
		
		//if(direct){
			storedDirect++;
			directEnlightment.store(point, normal, dir, power, diffuse);
		//}
		
		//else if(indirect){
		//	storedIndirect++;
		//	indirectEnlightment.store(point, normal, dir, power, diffuse);
		//}
		
		//else if(caustic){
		//	storedCaustic++;
		//	caustics.store(point, normal, dir, power, diffuse);
		//}
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
		Color3f objectColor = photonIntersection.getObject().getEnlightment().getColor(photonIntersection.getPoint(), photonIntersection.getNormal(), ray, scene.getLights());
		
		if(photonIntersection != null){
			if(photonIntersection.getObject().isReflecting()){
				
				if(russianRoulette(photonIntersection.getObject().getKR()) || (currentRecursions >= MAX_RECURSIONS)){
					storePhoton(photonIntersection.getPoint(), photonIntersection.getNormal(), ray.getDirection(), energy, objectColor, direct, indirect, caustic);
				}
				else{
					Ray reflected = scene.reflectedRay(ray, photonIntersection);
					shootPhoton(reflected, energy, false, true, false);
				}
			}
			
			if(photonIntersection.getObject().isRefracting()){
				
				if(russianRoulette(photonIntersection.getObject().getKT()) || (currentRecursions >= MAX_RECURSIONS)){
					storePhoton(photonIntersection.getPoint(), photonIntersection.getNormal(), ray.getDirection(), energy, objectColor, direct, indirect, caustic);
				}
				else{
					Ray refracted = scene.refractedRay(ray, photonIntersection);
					shootPhoton(refracted, energy, false, false, true);
				}
				
			}
			
			if(!photonIntersection.getObject().isReflecting() && !photonIntersection.getObject().isRefracting()){
				
				scaleEnergy(energy, objectColor);
				
				storePhoton(photonIntersection.getPoint(), photonIntersection.getNormal(), ray.getDirection(), energy, objectColor, direct, indirect, caustic);
				
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
				
				float energy[] = {	l.getColor().x / maxPhotons, 
									l.getColor().y / maxPhotons, 
									l.getColor().z / maxPhotons};
				
				currentRecursions = 0;
				shootPhoton(ray, energy, true, false, false);
			}
		}
		
		System.out.println("--> Balancing direct photon map...");
		directEnlightment.init();
		
		System.out.println("--> Balancing indirect photon map...");
		//indirectEnlightment.init();
		
		System.out.println("--> Balancing caustic photon map...");
		//caustics.init();
	}
	
	public Color3f irradianceEstimate(Intersection intersection){
		Color3f color = new Color3f();
		Point3 point = new Point3((float)intersection.getPoint().x, (float)intersection.getPoint().y, (float)intersection.getPoint().z);
		Vector3 norm = new Vector3((float)intersection.getNormal().x, (float)intersection.getNormal().y, (float)intersection.getNormal().z);
		
		//Direct enlightment component
		Color radiance = directEnlightment.getRadiance(point, norm);
		color.set(color.x + radiance.getR(), color.y + radiance.getG(), color.z + radiance.getB());			
		
		//Indirect enlightment component
		//radiance = indirectEnlightment.getRadiance(point, norm);
		//color.set(color.x + radiance.getR(), color.y + radiance.getG(), color.z + radiance.getB());	
		
		//Caustics component
		//radiance = indirectEnlightment.getRadiance(point, norm);
		//color.set(color.x + radiance.getR(), color.y + radiance.getG(), color.z + radiance.getB());	
		
		Enlightment.normalize(color);
		
		return color;
	}
}
