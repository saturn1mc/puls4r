/*
 *  Box.cpp
 *  Pulsar
 *
 *  Created by Camille on 02/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Box.h"

Intersection* Box::intersection(Ray* ray){
	
	double tnear = -std::numeric_limits<double>::infinity();
	double tfar = std::numeric_limits<double>::infinity();
	
	double t1 = 0;
	double t2 = 0;
	
	//X Planes
	if(ray->getDirection()->getX() == 0){
		if(ray->getOrigin()->getX() < min->getX() || ray->getOrigin()->getX() > max->getX()){
			return 0;
		}
	}
	else{
		t1 = (min->getX() - ray->getOrigin()->getX()) / ray->getDirection()->getX();
		t2 = (max->getX() - ray->getOrigin()->getX()) / ray->getDirection()->getX();
		
		if(t1 > t2){
			swap(t1, t2);
		}
		
		if(t1 > tnear){
			tnear = t1;
		}
		
		if(t2 > tfar){
			tfar = t2;
		}
		
		if(tnear > tfar || tfar < 0){
			return 0;
		}
	}
	
	//Y Planes
	if(ray->getDirection()->getY() == 0){
		if(ray->getOrigin()->getY() < min->getY() || ray->getOrigin()->getY() > max->getY()){
			return 0;
		}
	}
	else{
		t1 = (min->getY() - ray->getOrigin()->getY()) / ray->getDirection()->getY();
		t2 = (max->getY() - ray->getOrigin()->getY()) / ray->getDirection()->getY();
		
		if(t1 > t2){
			swap(t1, t2);
		}
		
		if(t1 > tnear){
			tnear = t1;
		}
		
		if(t2 > tfar){
			tfar = t2;
		}
		
		if(tnear > tfar || tfar < 0){
			return 0;
		}
	}
	
	//Z Planes
	if(ray->getDirection()->getZ() == 0){
		if(ray->getOrigin()->getZ() < min->getZ() || ray->getOrigin()->getZ() > max->getZ()){
			return 0;
		}
	}
	else{
		t1 = (min->getZ() - ray->getOrigin()->getZ()) / ray->getDirection()->getZ();
		t2 = (max->getZ() - ray->getOrigin()->getZ()) / ray->getDirection()->getZ();
		
		if(t1 > t2){
			swap(t1, t2);
		}
		
		if(t1 > tnear){
			tnear = t1;
		}
		
		if(t2 > tfar){
			tfar = t2;
		}
		
		if(tnear > tfar || tfar < 0){
			return 0;
		}
	}
	
	//Result
	ray->setT(tnear);
	
	-9
	
	return 0;
}

std::string Box::toString(void) const{
	
	std::stringstream ss;
	
	ss << "---------------------------" << std::endl;
	ss << "Box :" << std::endl;
	ss << "---------------------------" << std::endl;
	
	return ss.str();
}
