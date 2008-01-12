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
	virtual ~Plan(void) {}
	virtual void intersection(Ray ray);

};

#endif //PLAN_H
