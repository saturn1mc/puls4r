/**
 * 
 */
package puls4r.output;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JFrame;
import javax.vecmath.Color3f;

/**
 * @author cmaurice2
 *
 */
public class Puls4rFrame extends Output {

	protected JFrame frame;
	
	public Puls4rFrame(int width, int height) {
		
		pixels = new Color3f[width][height];
		
		this.w = width;
		this.h = height;
		
		frame = new JFrame(){
			@Override
			public void paintComponents(Graphics g) {
				super.paintComponents(g);
				
				Graphics2D g2 = (Graphics2D)g;
				
				for(int i = 0; i < w; i++){
					for(int j = 0; j < h; j++){
						g2.setPaint(pixels[i][j].get());
						g2.drawLine(i, j, i, j);
					}
				}
			}
		};
		
		frame.setPreferredSize(new Dimension(w, h));
		frame.pack();
		frame.setResizable(false);
		frame.setLocationRelativeTo(null);
		
		frame.setVisible(true);
	}
	
	@Override
	public void finalize() {
		frame.repaint();
	}

	@Override
	public void writePixel(Color3f color, int w, int h) {
		pixels[w][h] = color;
		frame.repaint();
	}

}
