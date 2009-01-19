package puls4r;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;

import puls4r.enlightment.direct.Lambert;
import puls4r.output.Puls4rFrame;
import puls4r.scene.Scene;
import puls4r.scene.objects.Light;
import puls4r.scene.objects.Sphere;
import puls4r.tracer.Observer;

/**
 * 
 */

/**
 * @author cmaurice2
 *
 */
public class Puls4r {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Puls4rFrame output = new Puls4rFrame(800, 600);
		Scene scene = new Scene();
		
		scene.setOutput(output);
		scene.setObserver(new Observer(new Point3d(0,0,100), new Point3d(0,0,0), Math.PI/4.0));
		
		Sphere sphere = new Sphere(new Point3d(0,0,0), 20);
		sphere.setEnlightment(new Lambert(new Color3f(1, 0, 0), 0.8));
		
		scene.addShape(sphere);
		scene.addLight(new Light(new Point3d(10, 10, 0), new Color3f(1,1,1), 1.5d, 1500d));
		
		scene.trace(Scene.RAYCASTING_MODE);
	}

}
