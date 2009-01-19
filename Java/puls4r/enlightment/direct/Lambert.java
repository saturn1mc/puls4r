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
public class Lambert extends Enlightment {

	Color3f od;
	double kd;
	
	public Lambert(Color3f od, double kd) {
		this.od = od;
		this.kd = kd;
	}

	@Override
	public Color3f getColor(Point3d point, Vector3d norm, Ray ray,
			Vector<Light> lights) {
		
		Color3f color = new Color3f();
		
		for(Light light : lights){
			Vector3d L = getL(point, light);
			
			Color3f diffuse = new Color3f(light.getColor());
			diffuse.scale((float) (kd * L.dot(norm)) );
			
			color.set(od.x * diffuse.x, od.y * diffuse.y, od.z * diffuse.z);
			Enlightment.normalize(color);
		}
		
		return color;
	}

}
