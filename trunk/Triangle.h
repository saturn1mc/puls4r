/*
 *  Triangle.h
 *  Pulsar
 *
 *  Created by Camille on 27/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Plan.h"

class Triangle : public Object{
private:
	
	Point *points[3];
	Plan *plan;
	
public:

	Triangle(Enlightment *_enlightment, Point *a, Point *b, Point *c) {
		enlightment = _enlightment;
		points[0] = a;
		points[1] = b;
		points[2] = c;
		
		Vector *AB = new Vector(*a, *b);
		Vector *AC = new Vector(*a, *c);
	
		Vector *norm = new Vector((*AB) ^ (*AC));
		norm->normalize();
		double d = - (norm->get(0) * getPoint(0)->getX())  - (norm->get(1) * getPoint(0)->getY()) - (norm->get(2) * getPoint(0)->getZ());
	
		plan = new Plan(enlightment, norm, d, true);
	}
	
	virtual ~Triangle(void) {}
	virtual Intersection *intersection(Ray &ray);
	virtual std::string toString(void) const;

	Point *getPoint(int index) const{
		if(index < 0 || index > 2){
			return 0;
		}
		else{
			return points[index];
		}
	}
};

#endif //TRIANGLE_H
