/*
 *  Plan.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plan.h"

void Plan::intersection(Ray ray){
	
	double vd = (norm->getX() * ray.getDirection().getX()) + (norm->getY() * ray.getDirection().getY()) + (norm->getZ() * ray.getDirection().getZ());
	double t = - ((norm->getX() * ray.getOrigin().getX()) + (norm->getY() * ray.getOrigin().getY()) + (norm->getZ() * ray.getOrigin().getZ()) + d) / vd;
	
	if(vd == 0 || (vd > 0 && monoface)){
		//TODO no intersection
	}
	else{
		if(t < 0){
			//TODO intersection behind ray origin
		}
	}
}
