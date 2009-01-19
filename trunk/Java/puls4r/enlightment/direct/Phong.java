/**
 * 
 */
package puls4r.enlightment.direct;

import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.enlightment.Enlightment;
import puls4r.scene.objects.Light;
import puls4r.tracer.Ray;

/**
 * @author cmaurice2
 *
 */
public class Phong extends Enlightment {

	Color3f oa; //ambient color
	Color3f od; //diffuse color
	Color3f os; //specular color
	
	double ia;
	
	double ka; //ambient reflection constant
	double kd; //diffuse reflection constant
	double ks; //specular reflection constant
	
	int n; //rugosity constant
	
	public Phong(Color3f od){
		this.od = od;
		
		this.ia = 1.0d;
		
		this.oa = new Color3f(od);
		this.oa.scale((float) ia);
		
		this.ka = 1.0;
	}
	
	public Phong(Color3f oa, Color3f od, Color3f os, double ia, double ka,
			double kd, double ks, int n) {
		super();
		this.oa = oa;
		this.od = od;
		this.os = os;
		this.ia = ia;
		this.ka = ka;
		this.kd = kd;
		this.ks = ks;
		this.n = n;
	}



	/* (non-Javadoc)
	 * @see puls4r.enlightment.Enlightment#getColor(javax.vecmath.Point3d, javax.vecmath.Vector3d, puls4r.tracer.Ray, java.util.Vector)
	 */
	@Override
	public Color3f getColor(Point3d point, Vector3d norm, Ray ray,
			Vector<Light> lights) {

		Color3f color = new Color3f();
		Vector3d V = getV(ray);
		
		for(Light light : lights){
			Vector3d L = getL(point, light);
			Vector3d R = getR(L, norm);
			
			Color3f diffuse = new Color3f(od);
			diffuse.scale((float) (L.dot(norm) * kd));
			
			
			Color3f specular = new Color3f();
			
			if((R.dot(V)) > 0){
				specular = new Color3f(os);
				specular.scale((float) (ks * Math.pow(R.dot(V), n)));
			}
			
			Enlightment.normalize(diffuse);
			Enlightment.normalize(specular);
			
			color.add(diffuse);
			color.add(specular);
			color.set(color.x * light.getColor().x, color.y * light.getColor().y, color.z * light.getColor().z);
		}
		
		Enlightment.normalize(color);
		
		return color;
	}

}
