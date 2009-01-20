package puls4r;

import puls4r.output.Puls4rFrame;
import puls4r.scene.Scene;
import puls4r.scene.parser.SceneParser;

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
		Puls4rFrame output = new Puls4rFrame(400, 300, 0);
		output.setVisible(true);
		
		try {
			
			Scene scene = SceneParser.parse("D://Mes Documents/Workspace/Puls4r/C++/scenes/waterScene.xml");
			scene.setOutput(output);
			scene.trace(Scene.PHOTONMAPPING_MODE);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
