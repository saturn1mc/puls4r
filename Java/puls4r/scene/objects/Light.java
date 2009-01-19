/**
 * 
 */
package puls4r.scene.objects;

import javax.vecmath.Color3f;
import javax.vecmath.Point3d;

/**
 * @author cmaurice2
 * 
 */
public class Light {
	private Point3d source;
	private Color3f color;
	private double radius;
	private double power;

	public Light(Point3d source, Color3f color, double radius, double power) {
		this.source = source;
		this.color = color;
		this.radius = radius;
		this.power = power;
	}

	public Point3d getSource() {
		return source;
	}

	public void setSource(Point3d source) {
		this.source = source;
	}

	public Color3f getColor() {
		return color;
	}

	public void setColor(Color3f color) {
		this.color = color;
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double radius) {
		this.radius = radius;
	}

	public double getPower() {
		return power;
	}

	public void setPower(double power) {
		this.power = power;
	}
}
