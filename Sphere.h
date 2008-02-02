/*
 *  Sphere.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object{
private:
	
	Point *center;
	double radius;
	
	Intersection *Sphere::createIntersection(Ray *ray);
	
public:

	Sphere(Enlightment *_enlightment, Point *_center, double _radius) {
		reflect = false;
		enlightment = _enlightment;
		center = _center;
		radius = _radius;
	}
	
	virtual ~Sphere(void) {}
	virtual Intersection *intersection(Ray *ray);
	virtual std::string toString(void) const;
};

#endif //SPHERE_H
