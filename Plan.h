/*
 *  Plan.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PLAN_H
#define PLAN_H

#include "Object.h"

class Plan : public Object{
private:
	
	Vector *norm;
	double d;
	
	bool monoface;

public:

	Plan(Vector *_norm, double _d, Color *_color, bool _monoface){
		norm = _norm;
		d = _d;
		color = _color;
		monoface = _monoface;
	}

	virtual ~Plan(void) {}
	virtual Intersection *intersection(Ray ray);

};

#endif //PLAN_H
