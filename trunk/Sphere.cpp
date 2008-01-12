/*
 *  Sphere.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sphere.h"

void Sphere::intersection(Ray ray){
	
	double A = ( ray.getDirection().getX() * ray.getDirection().getX() ) + ( ray.getDirection().getY() * ray.getDirection().getY() ) + ( ray.getDirection().getZ() * ray.getDirection().getZ() );
	double B = 2.0 * ( ray.getDirection().getX() * ( ray.getOrigin().getX() - center->getX() ) + ray.getDirection().getY() * ( ray.getOrigin().getY() - center->getY() ) + ray.getDirection().getZ() * ( ray.getOrigin().getZ() - center->getZ() ));
	double C = ( (ray.getOrigin().getX() - center->getX()) * (ray.getOrigin().getX() - center->getX()) ) + ( (ray.getOrigin().getY() - center->getY()) * (ray.getOrigin().getY() - center->getY()) ) + ( (ray.getOrigin().getZ() - center->getX()) * (ray.getOrigin().getZ() - center->getZ()) ) + (radius * radius);
	
	
	double t0 = (-B - sqrt((B*B) - (4*A*C))) / 2.0;
	double t1 = (-B + sqrt((B*B) - (4*A*C))) / 2.0;
	
	if(t0 > 0 && t1 > 0){
		
		ray.setT(min(t0, t1));
		
		Point m;
		
		m.setX(ray.getOrigin().getX() + (ray.getDirection().getX() * ray.getT()));
		m.setY(ray.getOrigin().getY() + (ray.getDirection().getY() * ray.getT()));
		m.setZ(ray.getOrigin().getZ() + (ray.getDirection().getZ() * ray.getT()));
		
		Vector nm;
		
		nm.setX((m.getX() - center->getX()) / radius);
		nm.setY((m.getY() - center->getY()) / radius);
		nm.setZ((m.getZ() - center->getZ()) / radius);
		
		//TODO intersection
	}
	else{
		if(t0 < 0 && t1 < 0){
			//TODO no intersection
		}
	}
}
