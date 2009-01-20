package puls4r;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;

import puls4r.enlightment.direct.Phong;
import puls4r.output.Puls4rFrame;
import puls4r.scene.Scene;
import puls4r.scene.objects.Light;
import puls4r.scene.objects.Sphere;
import puls4r.scene.parser.SceneParser;
import puls4r.texture.Perlin;
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
		Puls4rFrame output = new Puls4rFrame(800, 600, 0);
		output.setVisible(true);
		
		try {
			
			Scene scene = SceneParser.parse("D:\\Mes Documents\\Workspace\\Puls4r\\C++\\scenes\\allShapes.xml");
			scene.trace(Scene.RAYCASTING_MODE);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
