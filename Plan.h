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

	Plan(Enlightment *_enlightment, Vector *_norm, double _d, bool _monoface){
		
		reflect = false;
		
		enlightment = _enlightment;
		
		norm = _norm;
		norm->normalize();
		
		d = _d;
		monoface = _monoface;
	}

	virtual ~Plan(void) {}
	virtual Intersection *intersection(Ray *ray);
	virtual std::string toString(void) const;
};

#endif //PLAN_H
