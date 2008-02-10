/*
 *  Plan.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plan.h"

Intersection* Plan::intersection(Ray* ray){
	
	double vd = (norm->getX() * ray->getDirection()->getX()) + (norm->getY() * ray->getDirection()->getY()) + (norm->getZ() * ray->getDirection()->getZ());
	double t = -((norm->getX() * ray->getOrigin()->getX()) + (norm->getY() * ray->getOrigin()->getY()) + (norm->getZ() * ray->getOrigin()->getZ()) + d) / vd;
	
	if(vd == 0 || (vd > 0 && monoface)){
		return 0;
	}
	else{
		if(t < 0){
			return 0;
		}
		else{
			
			ray->setT(t);
		
			Point* m = new Point(	ray->getOrigin()->getX() + (ray->getDirection()->getX() * ray->getT()),
									ray->getOrigin()->getY() + (ray->getDirection()->getY() * ray->getT()),
									ray->getOrigin()->getZ() + (ray->getDirection()->getZ() * ray->getT())
								);
		
			Intersection* intersection = new Intersection(m, norm, this, ray->getT());
			
			delete(m);
			
			return intersection;
		}
	}
}

std::string Plan::toString(void) const{
	
	std::stringstream ss;
	
	ss << "---------------------------" << std::endl;
	ss << "Plan :" << std::endl;
	ss << "---------------------------" << std::endl;
	ss << "Norm : " << norm << std::endl;
	ss << "D : " << d << std::endl;
	ss << "---------------------------" << std::endl;
	
	return ss.str();
}
