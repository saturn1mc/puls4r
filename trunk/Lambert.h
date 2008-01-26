/*
 *  Lambert.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef LAMBERT_H
#define LAMBERT_H

#include "Enlightment.h"

class Lambert : public Enlightment{
	
	Color *od;
	Color *os;
	double kd;
	
public:
	
	Lambert(Color *_od){
		od = _od;
		os = new Color(1.0, 1.0, 1.0);
		kd = 1.0;
	}
	
	Lambert(Color *_od, Color *_os, double _kd){
		od = _od;
		os = _os;
		kd = _kd;
	}
	
	virtual ~Lambert(void) {}
	
	virtual Color &getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const;
};

#endif //LINEAR_H
