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
#include "Perlin.h"

class Sphere : public Object{
private:
	
	Point* center;
	double radius;
	
	Intersection* createIntersection(Ray* ray);
	
public:

	Sphere(Enlightment* _enlightment, Point* _center, double _radius) : center(new Point(_center)), radius(_radius) {
		enlightment = _enlightment->clone();
	}
	
	Sphere(const Sphere& sphere) : center(new Point(sphere.center)), radius(sphere.radius){
		enlightment = sphere.enlightment->clone();
	}
	
	virtual ~Sphere(void) {
		delete(enlightment);
		delete(center);
	}
	virtual Intersection* intersection(Ray* ray);
	virtual std::string toString(void) const;
	
	Sphere& operator=(const Sphere& sphere){
		delete(enlightment);
		delete(center);
		
		enlightment = sphere.enlightment->clone();
		center = new Point(sphere.center);
		radius = sphere.radius;
		
		return *this;
	}
};

#endif //SPHERE_H
