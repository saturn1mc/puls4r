/*
 *  Perlin.h
 *  puls4r
 *
 *  Created by Camille on 05/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

/*
 * From Ken Perlin http://mrl.nyu.edu/~perlin/
 */

#ifndef PERLIN_H
#define PERLIN_H

#include <math.h>
#include "Vector.h"

class Perlin{
	
private:
	
	static Perlin* singleton;
	
	int p[512];
	
	static const int permutation[];
	
	Perlin(void) 
	{ 
		for (int i=0; i < 256 ; i++) {
			p[256+i] = p[i] = permutation[i];
		}
	}
	
	Perlin(Perlin& perlin);

	static double fade(double t) 
	{ 
		return t * t * t * (t * (t * 6 - 15) + 10); 
	}
	
	static double lerp(double t, double a, double b) { 
		return a + t * (b - a); 
	}
	
	static double grad(int hash, double x, double y, double z) {
		int h = hash & 15;                      
		double	u = h<8||h==12||h==13 ? x : y,
				v = h<4||h==12||h==13 ? y : z;
		return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	}

	double noise(double x, double y, double z) {
	
		int X = (int)floor(x) & 255,                  
			Y = (int)floor(y) & 255,                  
			Z = (int)floor(z) & 255;
			
			x -= floor(x);
			y -= floor(y);
			z -= floor(z);
		
		double	u = fade(x),
				v = fade(y),
				w = fade(z);
		
		int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,
			B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;
		
		return lerp(w, lerp(v,	lerp(u, grad(p[AA  ], x  , y  , z   ),
								grad(p[BA  ], x-1, y  , z   )),
								lerp(u, grad(p[AB  ], x  , y-1, z   ),
								grad(p[BB  ], x-1, y-1, z   ))),
								lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),
								grad(p[BA+1], x-1, y  , z-1 )),
								lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
								grad(p[BB+1], x-1, y-1, z-1 ))));
	}


public:
		
	static Perlin& getInstance(void){
		if(singleton == 0){
			singleton = new Perlin();
		}
		
		return *singleton;
	}

	void disruptNormal(Vector* n, double e)
	{
		double x,y,z;
		
		x = noise(10.0 * n->getX() - e, 10.0 * n->getY(), 10.0 * n->getZ()) - noise(10.0 * n->getX()+e, 10.0*n->getY(), 10.0 * n->getZ());
		y = noise(10.0 * n->getX(), 10.0 * n->getY() - e, 10.0 * n->getZ()) - noise(10.0 * n->getX(), 10.0 * n->getY() + e, 10.0 * n->getZ());
		z = noise(10.0 * n->getX(), 10.0 * n->getY(), 10.0 * n->getZ()-e) - noise(10.0 * n->getX(), 10.0 * n->getY(), 10 * n->getZ() + e);
		
		n->setX(n->getX() + x);
		n->setY(n->getY() + y);
		n->setZ(n->getZ() + z);
		
		n->normalize();
	}

	void disruptNormal(Vector* n, Point* p, double e)
	{
		double x,y,z;
		double X,Y,Z;
		
		X = n->getX() + p->getX();
		Y = 50.0 * n->getY() + 10.0 * p->getY();
		Z = n->getZ() + p->getZ();
		
		x = noise(X - e, Y, Z) - noise(X + e, Y, Z);
		y = noise(X, Y - e, Z) - noise(X, Y + e, Z);
		z = noise(X, Y, Z - e) - noise(X, Y, Z + e);
		
		n->setX(n->getX() + x);
		n->setY(n->getY() + y);
		n->setZ(n->getZ() + z);
		
		n->normalize();
	}

};

#endif //PERLIN_H
