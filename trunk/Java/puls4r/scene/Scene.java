/**
 * 
 */
package puls4r.scene;

import java.util.Vector;

import javax.vecmath.Color3f;

import puls4r.enlightment.global.photonmapping.PhotonShooter;
import puls4r.output.Output;
import puls4r.scene.objects.Light;
import puls4r.tracer.Intersection;
import puls4r.tracer.Observer;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 *
 */
public class Scene {
	
	private static int RAYCASTING_MODE = 0;
	private static int PHOTONMAPPING_MODE = 1;
	
	
	private static double EPSILON;
	private static double SMOOTHING;
	private static int PHOTONS = 1000000;
	private static int MAX_RECURSIONS = 1000;
	
	int currentRecursions;
	
	private PhotonShooter shooter;
	private Observer observer;
	private Output output;
	private Color3f background;
	private Vector<Object> objects;
	private Vector<Light> lights;
	private double focal;
	
	private double calcFocal(){
		return ( (output.getW() / 2.0) / Math.tan(observer.getAlpha() / 2.0) );
	}
	
	Intersection getNearestIntersection(Ray ray, double epsilon){
		//TODO
	}
	
	Intersection getNearestShadowIntersection(Ray ray, double epsilon){
		//TODO
	}
	
	Color3f antialiasedColor(double l, double p, int mode){
		//TODO
	}
	
	Color3f colorAt(double l, double p, int mode){
		//TODO
	}
	
	Color3f observedColor(Ray ray, int mode){
		//TODO
	}
	
	Color3f glossyReflection(Ray ray, Intersection intersection, int mode, boolean random, double smoothing){
		//TODO
	}
	
	public Ray reflectedRay(Ray ray, Intersection intersection){
		//TODO
	}
	
	public Ray refractedRay(Ray ray, Intersection intersection){
		//TODO
	}
	
	public Ray refractRay(Ray ray, Intersection intersection, double n1, double n2, double epsilon){
		//TODO
	}
	
	void shadow(Color3f color, Intersection intersection, boolean random, double smoothing){
		//TODO
	}
	
	/* Ray Casting Function */
	void rayCasting(){
		//TODO
	}
	
	/* Photon Mapping Functions */
	void photonMapping(){
		//TODO
	}
	
	void addObject(Object obj){
		//TODO
	}
	
	void addLight(Light light){
		//TODO
	}
	
	void trace(int mode){
		//TODO
	}
}
