/**
 * 
 */
package puls4r.scene.objects;

import java.awt.Color;

import javax.vecmath.Point3d;

/**
 * @author cmaurice2
 * 
 */
public class Light {
	private Point3d source;
	private Color color;
	private double radius;
	private double power;

	public Point3d getSource() {
		return source;
	}

	public void setSource(Point3d source) {
		this.source = source;
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
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
