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
	
	bool reflect;
	double kr;
	
	Enlightment(void) : reflect(false), kr(0.0){}
	
	Vector* getV(Ray* ray) const{
		Vector* v = new Vector((*ray->getDirection()) * -1.0);
		v->normalize();
		return v;
	}
	
	Vector* getR(Vector* light, Vector* norm) const{
		Vector* r = new Vector( ( ( (*norm) * 2.0 ) * ( (*norm) * (light) ) ) - light );
		r->normalize();
		
		return r;
	}
	
	Vector* getL(Point* point, Light* light) const{
		Vector* l = new Vector(point, light->getSource());
		
		l->normalize();
		
		return l;
	}
	
public:
	Enlightment(Enlightment &enlightment) : reflect(enlightment.reflect), kr(enlightment.kr) {}
	virtual ~Enlightment(void) {}
	virtual Color* getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const = 0;
	virtual Enlightment *clone(void) = 0;
	
	bool isReflecting(void) const { return reflect; }
	double getKR(void) const { return kr; }
	
	void setReflecting(bool _reflect, double _kr = 1.0) { 
		
		if(kr < 0){
			kr = 0;
		}
		
		if(kr > 1.0){
			kr = 1.0;
		}
		
		reflect = _reflect; kr = _kr; 
	}
};

#endif //ENLIGHTMENT_H
