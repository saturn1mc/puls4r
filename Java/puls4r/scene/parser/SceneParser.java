/**
 *
 **/
package puls4r.scene.parser;

import java.io.File;
import java.util.List;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

import puls4r.enlightment.Enlightment;
import puls4r.enlightment.direct.Lambert;
import puls4r.enlightment.direct.Linear;
import puls4r.enlightment.direct.Phong;
import puls4r.scene.Scene;
import puls4r.scene.objects.Light;
import puls4r.scene.objects.Plan;
import puls4r.scene.objects.Quadric;
import puls4r.scene.objects.Sphere;
import puls4r.scene.objects.Triangle;
import puls4r.tracer.Observer;

/**
 * @author cmaurice2
 * 
 */
public class SceneParser {
	public static final String ROOT_NODE = "scene";

	public static final String BACKGROUND_NODE = "background";

	public static final String OBSERVER_NODE = "observer";
	public static final String EYE_NODE = "eye";
	public static final String SIGHT_NODE = "sight";

	public static final String IMAGE_NODE = "image";

	public static final String LIGHT_LIST_NODE = "lights";
	public static final String LIGHT_NODE = "light";

	public static final String SHAPE_LIST_NODE = "objects";
	public static final String SPHERE_NODE = "sphere";
	public static final String PLAN_NODE = "plan";
	public static final String TRIANGLE_NODE = "triangle";
	public static final String QUADRIC_NODE = "quadric";

	public static final String TARGET_ATTR = "target";
	public static final String WIDTH_ATTR = "width";
	public static final String HEIGHT_ATTR = "height";
	public static final String ANTIALIASING_ATTR = "antialiasing";

	public static final String X_ATTR = "x";
	public static final String Y_ATTR = "y";
	public static final String Z_ATTR = "z";

	public static final String AX_ATTR = "ax";
	public static final String AY_ATTR = "ay";
	public static final String AZ_ATTR = "az";

	public static final String BX_ATTR = "bx";
	public static final String BY_ATTR = "by";
	public static final String BZ_ATTR = "bz";

	public static final String CX_ATTR = "cx";
	public static final String CY_ATTR = "cy";
	public static final String CZ_ATTR = "cz";

	public static final String R_ATTR = "r";
	public static final String G_ATTR = "g";
	public static final String B_ATTR = "b";

	public static final String QA_ATTR = "qa";
	public static final String QB_ATTR = "qb";
	public static final String QC_ATTR = "qc";
	public static final String QD_ATTR = "qd";
	public static final String QE_ATTR = "qe";
	public static final String QF_ATTR = "qf";
	public static final String QG_ATTR = "qg";
	public static final String QH_ATTR = "qh";
	public static final String QI_ATTR = "qi";
	public static final String QJ_ATTR = "qj";

	public static final String D_ATTR = "d";
	public static final String MONOFACE_ATTR = "monoface";

	public static final String RADIUS_ATTR = "radius";

	public static final String POWER_ATTR = "power";

	public static final String ENLIGHTMENT_ATTR = "enlightment";
	public static final String ENL_PHONG = "phong";
	public static final String ENL_LINEAR = "linear";
	public static final String ENL_LAMBERT = "lambert";

	public static final String REFLECTING_ATTR = "reflecting";
	public static final String KR_ATTR = "kr";
	public static final String GLOSSY_FOCAL_ATTR = "glossyFocal";
	public static final String GLOSSY_WIDTH_ATTR = "glossyWidth";
	public static final String REFRACTING_ATTR = "refracting";
	public static final String N_ATTR = "n";
	public static final String KT_ATTR = "kt";

	public static final String PERLIN_ATTR = "perlin";
	public static final String EPSILON_ATTR = "epsilon";

	public static Scene parse(String filePath) throws Exception {

		System.out.println("-- Parsing " + filePath + " ... ");

		Scene scene = new Scene();

		SAXReader reader = new SAXReader();
		Document doc = reader.read(new File(filePath).toURI().toURL());

		Element root = doc.getRootElement();

		// Background color parsing
		System.out.println("\tParsing background ... ");
		Node node = root.selectSingleNode("//" + BACKGROUND_NODE);
		parseBackgroundNode(node, scene);

		// Observer parsing
		System.out.println("\tParsing observer ... ");
		node = root.selectSingleNode("//" + OBSERVER_NODE);
		parseObserverNode(node, scene);

		// Light list parsing
		System.out.println("\tParsing lights ... ");
		node = root.selectSingleNode("//" + LIGHT_LIST_NODE);
		parseLightList(node, scene);

		// Object list parsing
		System.out.println("\tParsing objects ... ");
		node = root.selectSingleNode("//" + SHAPE_LIST_NODE);
		parseShapeList(node, scene);

		System.out.println("-- End of parsing.");

		return scene;
	}

	private static Color3f parseColor(Node node) {
		float r, g, b;
		
		r = Float.parseFloat(node.valueOf("@" + R_ATTR));
		g = Float.parseFloat(node.valueOf("@" + G_ATTR));
		b = Float.parseFloat(node.valueOf("@" + B_ATTR));

		return new Color3f(r, g, b);
	}

	private static Point3d parsePoint(Node node) {
		double x, y, z;

		x = Double.parseDouble(node.valueOf("@" + X_ATTR));
		y = Double.parseDouble(node.valueOf("@" + Y_ATTR));
		z = Double.parseDouble(node.valueOf("@" + Z_ATTR));

		return new Point3d(x, y, z);
	}

	private static Vector3d parseVector(Node node) {
		double x, y, z;

		x = Double.parseDouble(node.valueOf("@" + X_ATTR));
		y = Double.parseDouble(node.valueOf("@" + Y_ATTR));
		z = Double.parseDouble(node.valueOf("@" + Z_ATTR));

		return new Vector3d(x, y, z);
	}

	private static void parseBackgroundNode(Node backgroundNode, Scene scene)
			throws Exception {
		Color3f background = parseColor(backgroundNode);
		scene.setBackground(background);
	}

	private static void parseObserverNode(Node observerNode, Scene scene)
			throws Exception {
		Point3d eye = parseEyeNode(observerNode.selectSingleNode("//"
				+ EYE_NODE));
		Point3d sight = parseSightNode(observerNode.selectSingleNode("//"
				+ SIGHT_NODE));

		Observer observer = new Observer(eye, sight, Math.PI / 4.0d);
		scene.setObserver(observer);
	}

	private static Point3d parseEyeNode(Node eyeNode) throws Exception {
		Point3d eye = parsePoint(eyeNode);
		return eye;
	}

	private static Point3d parseSightNode(Node sightNode) throws Exception {
		Point3d sight = parsePoint(sightNode);
		return sight;
	}

	@SuppressWarnings("unchecked")
	private static void parseLightList(Node lightListNode, Scene scene)
			throws Exception {
		List<Node> lightNodes = lightListNode.selectNodes(LIGHT_NODE);

		for (Node lightNode : lightNodes) {
			parseLightNode(lightNode, scene);
		}
	}

	private static void parseLightNode(Node lightNode, Scene scene) throws Exception {

		// Position
		Point3d position = parsePoint(lightNode);

		// Color
		Color3f color = parseColor(lightNode);

		// Radius
		double radius = Double.parseDouble(lightNode.valueOf("@" + RADIUS_ATTR));

		// Power
		double power = Double.parseDouble(lightNode.valueOf("@" + POWER_ATTR));

		// Light
		Light light = new Light(position, color, radius, power);
		scene.addLight(light);
	}

	@SuppressWarnings("unchecked")
	private static void parseShapeList(Node shapeListNode, Scene scene)
			throws Exception {
		List<Node> shapeNodes = shapeListNode.selectNodes("//" + SHAPE_LIST_NODE + "/*");

		for (Node shapeNode : shapeNodes) {
			parseShapeNode(shapeNode, scene);
		}
	}

	private static void parseShapeNode(Node shapeNode, Scene scene) throws Exception {

		boolean handled = false;

		if (shapeNode.getName().equals(SPHERE_NODE)) {
			parseSphereNode(shapeNode, scene);
			handled = true;
		}

		else if (shapeNode.getName().equals(PLAN_NODE)) {
			parsePlanNode(shapeNode, scene);
			handled = true;
		}

		else if (shapeNode.getName().equals(TRIANGLE_NODE)) {
			parseTriangleNode(shapeNode, scene);
			handled = true;
		}

		else if (shapeNode.getName().equals(QUADRIC_NODE)) {
			parseQuadricNode(shapeNode, scene);
			handled = true;
		}

		if (!handled) {
			System.err.println("Unknown object " + shapeNode.getName());
		}
	}

	private static void parseSphereNode(Node sphereNode, Scene scene) throws Exception {
		// Position
		Point3d position = parsePoint(sphereNode);

		// Radius
		double radius = Double.parseDouble(sphereNode.valueOf("@" + RADIUS_ATTR));

		// Enlightment
		Enlightment enl = parseEnlightment(sphereNode);

		// Relfection attributes
		int reflecting;
		double kr;
		double glossyFocal;
		double glossyWidth;

		reflecting = Integer.parseInt(sphereNode.valueOf("@" + REFLECTING_ATTR));
		kr = Double.parseDouble(sphereNode.valueOf("@" + KR_ATTR));
		glossyFocal = Double.parseDouble(sphereNode.valueOf("@" + GLOSSY_FOCAL_ATTR));
		glossyWidth = Double.parseDouble(sphereNode.valueOf("@" + GLOSSY_WIDTH_ATTR));

		// Refraction attributes
		int refracting;
		double n;
		double kt;

		refracting = Integer.parseInt(sphereNode.valueOf("@" + REFRACTING_ATTR));
		n = Double.parseDouble(sphereNode.valueOf("@" + N_ATTR));
		kt = Double.parseDouble(sphereNode.valueOf("@" + KT_ATTR));

		// Noise attributes
		int perlin;
		double epsilon;

		perlin = Integer.parseInt(sphereNode.valueOf("@" + PERLIN_ATTR));
		epsilon = Double.parseDouble(sphereNode.valueOf("@" + EPSILON_ATTR));

		// Creating and adding object
		Sphere sphere = new Sphere(enl, position, radius, perlin == 1);
		sphere.setReflecting(reflecting == 1, kr);
		sphere.setGlossy(glossyFocal, glossyWidth);
		sphere.setRefracting(refracting == 1, n, kt);
		sphere.setEpsilon(epsilon);

		scene.addShape(sphere);
	}

	private static void parsePlanNode(Node planNode, Scene scene) throws Exception {

		// Equation parameters
		double d = Double.parseDouble(planNode.valueOf("@" + D_ATTR));
		Vector3d normal = parseVector(planNode);

		// Monoface property
		int monoface = Integer.parseInt(planNode.valueOf("@" + MONOFACE_ATTR));

		// Enlightment
		Enlightment enl = parseEnlightment(planNode);

		// Relfection attributes
		int reflecting;
		double kr;
		double glossyFocal;
		double glossyWidth;

		reflecting = Integer.parseInt(planNode.valueOf("@" + REFLECTING_ATTR));
		kr = Double.parseDouble(planNode.valueOf("@" + KR_ATTR));
		glossyFocal = Double.parseDouble(planNode.valueOf("@" + GLOSSY_FOCAL_ATTR));
		glossyWidth = Double.parseDouble(planNode.valueOf("@" + GLOSSY_WIDTH_ATTR));

		// Refraction attributes
		int refracting;
		double n;
		double kt;

		refracting = Integer.parseInt(planNode.valueOf("@" + REFRACTING_ATTR));
		n = Double.parseDouble(planNode.valueOf("@" + N_ATTR));
		kt = Double.parseDouble(planNode.valueOf("@" + KT_ATTR));

		// Noise attributes
		int perlin;
		double epsilon;

		perlin = Integer.parseInt(planNode.valueOf("@" + PERLIN_ATTR));
		epsilon = Double.parseDouble(planNode.valueOf("@" + EPSILON_ATTR));

		// Creating and adding object
		Plan plan = new Plan(enl, normal, d, monoface == 1, perlin == 1);
		plan.setReflecting(reflecting == 1, kr);
		plan.setGlossy(glossyFocal, glossyWidth);
		plan.setRefracting(refracting == 1, n, kt);
		plan.setEpsilon(epsilon);

		scene.addShape(plan);
	}

	private static void parseTriangleNode(Node triangleNode, Scene scene)
			throws Exception {

		// Equation parameters
		double ax, ay, az, bx, by, bz, cx, cy, cz;

		ax = Double.parseDouble(triangleNode.valueOf("@" + AX_ATTR));
		ay = Double.parseDouble(triangleNode.valueOf("@" + AY_ATTR));
		az = Double.parseDouble(triangleNode.valueOf("@" + AZ_ATTR));
		Point3d a = new Point3d(ax, ay, az);

		bx = Double.parseDouble(triangleNode.valueOf("@" + BX_ATTR));
		by = Double.parseDouble(triangleNode.valueOf("@" + BY_ATTR));
		bz = Double.parseDouble(triangleNode.valueOf("@" + BZ_ATTR));
		Point3d b = new Point3d(bx, by, bz);

		cx = Double.parseDouble(triangleNode.valueOf("@" + CX_ATTR));
		cy = Double.parseDouble(triangleNode.valueOf("@" + CY_ATTR));
		cz = Double.parseDouble(triangleNode.valueOf("@" + CZ_ATTR));
		Point3d c = new Point3d(cx, cy, cz);

		// Enlightment
		Enlightment enl = parseEnlightment(triangleNode);

		// Relfection attributes
		int reflecting;
		double kr;
		double glossyFocal;
		double glossyWidth;

		reflecting = Integer.parseInt(triangleNode.valueOf("@" + REFLECTING_ATTR));
		kr = Double.parseDouble(triangleNode.valueOf("@" + KR_ATTR));
		glossyFocal = Double.parseDouble(triangleNode
				.valueOf("@" + GLOSSY_FOCAL_ATTR));
		glossyWidth = Double.parseDouble(triangleNode
				.valueOf("@" + GLOSSY_WIDTH_ATTR));

		// Refraction attributes
		int refracting;
		double n;
		double kt;

		refracting = Integer.parseInt(triangleNode.valueOf("@" + REFRACTING_ATTR));
		n = Double.parseDouble(triangleNode.valueOf("@" + N_ATTR));
		kt = Double.parseDouble(triangleNode.valueOf("@" + KT_ATTR));

		// Noise attributes
		int perlin;
		double epsilon;

		perlin = Integer.parseInt(triangleNode.valueOf("@" + PERLIN_ATTR));
		epsilon = Double.parseDouble(triangleNode.valueOf("@" + EPSILON_ATTR));

		// Creating and adding object
		Triangle triangle = new Triangle(enl, a, b, c, perlin == 1);
		triangle.setReflecting(reflecting == 1, kr);
		triangle.setGlossy(glossyFocal, glossyWidth);
		triangle.setRefracting(refracting == 1, n, kt);
		triangle.setEpsilon(epsilon);

		scene.addShape(triangle);
	}

	private static void parseQuadricNode(Node quadricNode, Scene scene)
			throws Exception {

		// Equation parameters
		double a, b, c, d, e, f, g, h, i, j;

		a = Double.parseDouble(quadricNode.valueOf("@" + QA_ATTR));
		b = Double.parseDouble(quadricNode.valueOf("@" + QB_ATTR));
		c = Double.parseDouble(quadricNode.valueOf("@" + QC_ATTR));
		d = Double.parseDouble(quadricNode.valueOf("@" + QD_ATTR));
		e = Double.parseDouble(quadricNode.valueOf("@" + QE_ATTR));
		f = Double.parseDouble(quadricNode.valueOf("@" + QF_ATTR));
		g = Double.parseDouble(quadricNode.valueOf("@" + QG_ATTR));
		h = Double.parseDouble(quadricNode.valueOf("@" + QH_ATTR));
		i = Double.parseDouble(quadricNode.valueOf("@" + QI_ATTR));
		j = Double.parseDouble(quadricNode.valueOf("@" + QJ_ATTR));

		// Enlightment
		Enlightment enl = parseEnlightment(quadricNode);

		// Relfection attributes
		int reflecting;
		double kr;
		double glossyFocal;
		double glossyWidth;

		reflecting = Integer.parseInt(quadricNode.valueOf("@" + REFLECTING_ATTR));
		kr = Double.parseDouble(quadricNode.valueOf("@" + KR_ATTR));
		glossyFocal = Double
				.parseDouble(quadricNode.valueOf("@" + GLOSSY_FOCAL_ATTR));
		glossyWidth = Double
				.parseDouble(quadricNode.valueOf("@" + GLOSSY_WIDTH_ATTR));

		// Refraction attributes
		int refracting;
		double n;
		double kt;

		refracting = Integer.parseInt(quadricNode.valueOf("@" + REFRACTING_ATTR));
		n = Double.parseDouble(quadricNode.valueOf("@" + N_ATTR));
		kt = Double.parseDouble(quadricNode.valueOf("@" + KT_ATTR));

		// Noise attributes
		int perlin;
		double epsilon;

		perlin = Integer.parseInt(quadricNode.valueOf("@" + PERLIN_ATTR));
		epsilon = Double.parseDouble(quadricNode.valueOf("@" + EPSILON_ATTR));

		// Creating and adding object
		Quadric quadric = new Quadric(enl, a, b, c, d, e, f, g, h, i, j,
				perlin == 1);
		quadric.setReflecting(reflecting == 1, kr);
		quadric.setGlossy(glossyFocal, glossyWidth);
		quadric.setRefracting(refracting == 1, n, kt);
		quadric.setEpsilon(epsilon);

		scene.addShape(quadric);
	}

	private static Enlightment parseEnlightment(Node objectNode) throws Exception {

		// Color
		Color3f color = parseColor(objectNode);

		// Type
		String enlName = objectNode.valueOf("@" + ENLIGHTMENT_ATTR);
		Enlightment enl = null;

		if (enlName.equals(ENL_PHONG)) {
			enl = new Phong(color);
		}

		else if (enlName.equals(ENL_LAMBERT)) {
			enl = new Lambert(color);
		}

		else if (enlName.equals(ENL_LINEAR)) {
			enl = new Linear(color);
		}

		if (enl == null) {
			System.err.println("Enlightment technique unknown : " + enlName);
			enl = new Linear(color);
		}

		return enl;
	}
}
