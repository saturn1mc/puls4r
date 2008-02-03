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
	
	Vector* norm;
	double d;
	
	bool monoface;

public:

	Plan(Enlightment* _enlightment, Vector* _norm, double _d, bool _monoface) : norm(_norm), d(_d), monoface(_monoface) {
		reflect = false;
		enlightment = _enlightment;
		norm->normalize();
	}
	
	Plan(const Plan& plan) : norm(new Vector(plan.norm)), d(plan.d), monoface(plan.monoface){
		reflect = plan.reflect;
		enlightment = plan.enlightment->clone();
		norm->normalize();
	}
	
	Plan(const Plan* plan) : norm(new Vector(plan->norm)), d(plan->d), monoface(plan->monoface){
		reflect = plan->reflect;
		enlightment = plan->enlightment->clone();
		norm->normalize();
	}

	virtual ~Plan(void) {}
	virtual Intersection* intersection(Ray* ray);
	virtual std::string toString(void) const;
	
	Plan& operator=(const Plan& plan){
		
		delete(enlightment);
		delete(norm);
		
		reflect = plan.reflect;
		enlightment = plan.enlightment->clone();
		norm = new Vector(plan.norm);
		d = plan.d;
		monoface = plan.monoface;
		
		return *this;
	}
};

#endif //PLAN_H
