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
#include "Point.h"

class Sphere : public Object{
private:
	
	Point *center;
	double radius;
	
public:

	Sphere(Point *_center, double _radius) {
		center = _center;
		radius = _radius;
	}
	
	virtual ~Sphere(void) {}
	virtual void intersection(Ray ray);
		
};

#endif //SPHERE_H
