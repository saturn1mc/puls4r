package puls4r.enlightment.direct;

import java.util.Vector;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import puls4r.enlightment.Enlightment;
import puls4r.scene.objects.Light;
import puls4r.tracer.Ray;

public class Linear extends Enlightment {

	Color3f color;
	
	public Linear(Color3f color) {
		this.color = color;
	}
	
	@Override
	public Color3f getColor(Point3d point, Vector3d norm, Ray ray,
			Vector<Light> lights) {

		return color;
	}

}
