/*
 *  Plan.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plan.h"

Intersection *Plan::intersection(Ray ray){
	
	double vd = (norm->getX() * ray.getDirection().getX()) + (norm->getY() * ray.getDirection().getY()) + (norm->getZ() * ray.getDirection().getZ());
	double t = -((norm->getX() * ray.getOrigin().getX()) + (norm->getY() * ray.getOrigin().getY()) + (norm->getZ() * ray.getOrigin().getZ()) + d) / vd;
	
	if(vd == 0 || (vd > 0 && monoface)){
		return 0;
	}
	else{
		if(t < 0){
			return 0;
		}
		else{
			
			ray.setT(t);
		
			Point m;
		
			m.setX(ray.getOrigin().getX() + (ray.getDirection().getX() * ray.getT()));
			m.setY(ray.getOrigin().getY() + (ray.getDirection().getY() * ray.getT()));
			m.setZ(ray.getOrigin().getZ() + (ray.getDirection().getZ() * ray.getT()));
		
			return new Intersection(&m, norm, color, ray.getT());
		}
	}
}
