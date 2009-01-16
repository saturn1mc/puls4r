/**
 * 
 */
package puls4r.enlightment.global.photonmapping;

import java.awt.Point;
import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Vector3d;

import puls4r.scene.objects.Light;
import puls4r.tracer.Intersection;
import puls4r.tracer.Ray;

/**
 * @author Camille
 *
 */
public class PhotonShooter {
	private static int MAX_RECURSIONS = 500;
	private static double IRRADIANCE_AREA;
	private static int IRRADIANCE_PHOTON_NUMBER = 1000000;
	
	private int currentRecursions;
	
	private static double EPSILON;
	
	private int storedDirect;
	private int storedIndirect;
	private int storedCaustic;
	
	private int nbLights;
	private int maxPhotons;
	
	private PhotonMap directEnlightment;
	private PhotonMap indirectEnlightment;
	private PhotonMap caustics;
	
	private void shootPhoton(Ray ray, Vector<Light> lights, Vector<Object> objects, float energy[], boolean direct, boolean indirect, boolean caustic){
		//TODO
	}
	
	Intersection getNearestIntersection(Ray ray, Vector<Object> objects, double epsilon){
		//TODO
	}
	
	private Ray reflectedRay(Ray ray, Intersection intersection){
		//TODO
	}
	
	private Ray refractedRay(Ray ray, Intersection intersection, Vector<Object> objects){
		//TODO
	}
	
	private Ray refractRay(Ray ray, Intersection intersection, double n1, double n2, double epsilon){
		//TODO
	}
	
	private Vector3d randomDirection(){
		//TODO
	}
	
	private boolean russianRoulette(double d){
		//TODO
	}
	
	private void storePhoton(Point position, Vector3d direction, float energy[], boolean direct, boolean indirect, boolean caustic){
		//TODO
	}
	
	private void scaleEnergy(float energy[], Color3f color){
		//TODO
	}
}
