/**
 * 
 */
package puls4r.output;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.image.BufferStrategy;

import javax.swing.JFrame;
import javax.vecmath.Color3f;

/**
 * @author cmaurice2
 * 
 */
public class Puls4rFrame extends JFrame implements Output {

	/**
	 * Auto-generated SVUID
	 */
	private static final long serialVersionUID = -6121291203518030848L;

	protected int w;
	protected int h;
	protected int antialiasing;

	protected Color3f pixels[][];

	public Puls4rFrame(int width, int height, int antialiasing) {
		
		super("Puls4r");
		
		pixels = new Color3f[width][height];

		this.w = width;
		this.h = height;
		this.antialiasing = antialiasing;
		
		this.setPreferredSize(new Dimension(w, h));
		this.pack();
		//this.setResizable(false);
		this.setLocationRelativeTo(null);
	}

	@Override
	public void setVisible(boolean b) {
		super.setVisible(b);

		if (b) {
			this.setSize(this.getWidth(), this.getHeight()+this.getInsets().top);
			this.createBufferStrategy(2); // Buffering
		}
	}

	private void drawOutput() {

		BufferStrategy bf = this.getBufferStrategy();

		if (bf != null) {
			Graphics g = bf.getDrawGraphics();
			g.clearRect(0, 0, WIDTH, HEIGHT);

			for (int i = 0; i < w; i++) {
				for (int j = 0; j < h; j++) {
					if (pixels[i][j] != null) {
						g.setColor(pixels[i][j].get());
					} else {
						g.setColor(Color.BLACK);
					}
					
					g.drawLine(i, j+this.getInsets().top, i, j+this.getInsets().top);
				}
			}

			bf.show();

			// Tell the System to do the Drawing now, otherwise it can take a
			// few extra ms until drawing is done
			Toolkit.getDefaultToolkit().sync();

			g.dispose();
		}
	}

	@Override
	public void finalize() {
		drawOutput();
	}

	@Override
	public void writePixel(Color3f color, int w, int h) {
		pixels[w][h] = color;

		/*
		BufferStrategy bf = this.getBufferStrategy();
		if (bf != null) {
			Graphics g = bf.getDrawGraphics();
			g.setColor(color.get());
			g.drawLine(w, h, w, h);
			
			bf.show();

			// Tell the System to do the Drawing now, otherwise it can take a
			// few extra ms until drawing is done
			Toolkit.getDefaultToolkit().sync();

			g.dispose();
		}
		*/
	}

	@Override
	public int getAntialiasing() {
		return antialiasing;
	}

	@Override
	public int getH() {
		return h;
	}

	@Override
	public int getW() {
		return w;
	}

}
