/*
 *  Lambert.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef LAMBERT_H
#define LAMBERT_H

#include "Enlightment.h"

class Lambert : public Enlightment{
	
	Color* od;
	double kd;
	
public:
	
	Lambert(Color* _od) : od(_od), kd(1.0){}
	Lambert(Color* _od, double _kd) : od(_od), kd(_kd) {}
	
	Lambert(const Lambert& lambert) : od(new Color(lambert.od)), kd(lambert.kd) {}
	Lambert(const Lambert* lambert) : od(new Color(lambert->od)), kd(lambert->kd) {}
	
	virtual ~Lambert(void) {}
	
	virtual Color* getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const;
	virtual Enlightment* clone(void) {return new Lambert(this);}
	
	Lambert& operator=(const Lambert& lambert){
		delete(od);
		
		od = new Color(lambert.od);
		kd = lambert.kd;
		
		return *this;
	}
};

#endif //LINEAR_H
