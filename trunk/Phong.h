/*
 *  Phong.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PHONG_H
#define PHONG_H

#include <list>

#include "Enlightment.h"
#include "Light.h"

class Phong : public Enlightment{
private:
	
	Color *oa; //ambient color
	Color *od; //diffuse color
	Color *os; //specular color
	
	double ia;
	
	double ka; //ambient reflection constant
	double kd; //diffuse reflection constant
	double ks; //specular reflection constant
	
	int n; //rugosity constant

public:
		
	Phong(Color *_od){
		
		ia = 1.0;
		
		oa = new Color((*_od) * ia);
		od = _od;
		os = new Color(1.0, 1.0, 1.0);
		
		ka = 1.0;
		kd = 0.7;
		ks = 0.3;
		
		n = 10;
	}
	
	Phong(Color *_oa, Color *_od, Color *_os, double _ka, double _kd, double _ks, int _n){
		oa = oa;
		od = _od;
		os = _os;
		ka = _ka;
		kd = _kd;
		ks = _ks;
		n = _n;
	}
	
	Phong(Phong &phong) { 
		oa = new Color(*phong.oa);
		od = new Color(*phong.od);
		os = new Color(*phong.os);
		
		ka = phong.ka;
		kd = phong.kd;
		ks = phong.ks;
	}
	
	virtual ~Phong(void) {}
	
	virtual Color &getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const;
	
	virtual Enlightment *getCopy() {return new Phong(*this);}
};

#endif //PHONG_H
