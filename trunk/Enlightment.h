/*
 *  Enlightment.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ENLIGHTMENT_H
#define ENLIGHTMENT_H

#include <iostream>

#include <list>

#include "Color.h"
#include "Point.h"
#include "Vector.h"
#include "Light.h"
#include "Ray.h"

class Enlightment{
	
protected:
	
	Enlightment(void) {}
	
	Vector &getV(Ray &ray) const{
		return (ray.getDirection() * -1.0);
	}
	
	Vector &getR(Vector &light, Vector &norm) const{
		Vector &r = ((norm * 2.0) * (norm * light)) - light;
		
		r.normalize();
		
		return r;
	}
	
	Vector &getL(Point &point, Light &light) const{
		Vector *l = new Vector(point, light.getSource());
		
		l->normalize();
		
		return *l;
	}
	
public:
	
	virtual ~Enlightment(void) {}
	virtual Color &getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const = 0;
};

#endif //ENLIGHTMENT_H
