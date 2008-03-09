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
	
	//Reflection properties
	bool reflect;
	double kr;
	double glossyFocal;
	double glossyWidth;
	
	//Refraction properties
	bool refract;
	double n;
	double kt;
	
	Enlightment(void) : reflect(false), kr(0), glossyFocal(0.0), glossyWidth(0.0), refract(false), n(1.0), kt(0){}
	
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
	
	Enlightment(Enlightment &enlightment) : reflect(enlightment.reflect), kr(enlightment.kr), glossyFocal(enlightment.glossyFocal), glossyWidth(enlightment.glossyWidth), refract(enlightment.refract), n(enlightment.n), kt(enlightment.kt) {}
	virtual ~Enlightment(void) {}
	virtual Color* getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const = 0;
	virtual Enlightment *clone(void) = 0;
	
	bool isReflecting(void) const { return reflect; }
	double getKR(void) const { return kr; }
	
	void setReflecting(bool _reflect, double _kr = 1.0) { 
		
		reflect = _reflect; 
		kr = _kr; 
		
		if(kr < 0){
			kr = 0;
		}
		
		if(kr > 1.0){
			kr = 1.0;
		}
	}
	
	bool isRefracting(void) const { return refract; }
	double getN(void) const { return n; }
	double getKT(void) const { return kt; }
	
	void setRefracting(bool _refract, double _n = 1.0, double _kt = 1.0){
		refract = _refract; 
		n = _n;
		kt = _kt;
		
		if(n < 0){
			n = 0;
		}
		
		if(kt < 0){
			kt = 0;
		}
		
		if(kt > 1.0){
			kt = 1.0;
		}
	}
	
	double getGlossyFocal(void) const{
		return glossyFocal;
	}
	
	double getGlossyWidth(void) const{
		return glossyWidth;
	}
	
	void setGlossy(double _glossyFocal, double _glossyWidth){
		glossyFocal = _glossyFocal;
		glossyWidth = _glossyWidth;
	}
};

#endif //ENLIGHTMENT_H
