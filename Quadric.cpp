/*
 *  Quadric.cpp
 *  puls4r
 *
 *  Created by Camille on 01/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Quadric.h"

Intersection* Quadric::createIntersection(Ray* ray){
	Point m	(	ray->getOrigin()->getX() + (ray->getDirection()->getX() * ray->getT()),
				ray->getOrigin()->getY() + (ray->getDirection()->getY() * ray->getT()),
				ray->getOrigin()->getZ() + (ray->getDirection()->getZ() * ray->getT())
			);
	
	Vector nm	(	2.0 * A * m.getX() + D * m.getY() + E * m.getZ() + G,
					2.0 * B * m.getY() + D * m.getX() + F * m.getZ() + H,
					2.0 * C * m.getZ() + E * m.getX() + F * m.getY() + I
				);
	
	nm.normalize();
	
	if((nm * ray->getDirection()) > 0){
		nm.invert();
	}
	
	if(perlin != 0){
		perlin->disruptNormal(&nm, epsilon);
	}
	
	Intersection *intersection = new Intersection(&m, &nm, this, ray->getT());
	
	return intersection;
}


Intersection* Quadric::intersection(Ray* ray){
	double Aq =	A * (ray->getDirection()->getX()) * (ray->getDirection()->getX()) +
	B * (ray->getDirection()->getY()) * (ray->getDirection()->getY()) +
	C * (ray->getDirection()->getZ()) * (ray->getDirection()->getZ()) +
	D * (ray->getDirection()->getX()) * (ray->getDirection()->getY()) +
	E * (ray->getDirection()->getX()) * (ray->getDirection()->getZ()) +
	F * (ray->getDirection()->getY()) * (ray->getDirection()->getZ());
	
	double Bq =	2.0 * A * (ray->getOrigin()->getX()) * (ray->getDirection()->getX()) +
	2.0 * B * (ray->getOrigin()->getY()) * (ray->getDirection()->getY()) +
	2.0 * C * (ray->getOrigin()->getZ()) * (ray->getDirection()->getZ()) +
	D * (((ray->getOrigin()->getX()) * (ray->getDirection()->getY())) + ((ray->getOrigin()->getY()) * (ray->getDirection()->getX()))) +
	E * ((ray->getOrigin()->getX()) * (ray->getDirection()->getZ())) +
	F * (((ray->getOrigin()->getY()) * (ray->getDirection()->getZ())) + ((ray->getOrigin()->getZ()) * (ray->getDirection()->getY()))) +
	G * (ray->getDirection()->getX()) +
	H * (ray->getDirection()->getY()) +
	I * (ray->getDirection()->getZ());
	
	double Cq =	A * (ray->getOrigin()->getX()) * (ray->getOrigin()->getX()) +
	B * (ray->getOrigin()->getY()) * (ray->getOrigin()->getY()) +
	C * (ray->getOrigin()->getZ()) * (ray->getOrigin()->getZ()) +
	D * (ray->getOrigin()->getX()) * (ray->getOrigin()->getY()) +
	E * (ray->getOrigin()->getX()) * (ray->getOrigin()->getZ()) +
	F * (ray->getOrigin()->getY()) * (ray->getOrigin()->getZ()) +
	H * (ray->getOrigin()->getY()) +
	I * (ray->getOrigin()->getZ()) +
	J;
	
	if(Aq == 0){
		ray->setT((-Cq / Bq));
		return createIntersection(ray);
	}
	else{
		
		if(((Bq*Bq) - (4*Aq*Cq)) < 0){
			return 0;
		}
		else{
			double t0 = (-Bq - sqrt((Bq*Bq) - (4*Aq*Cq))) / (2.0*Aq);
			double t1 = (-Bq + sqrt((Bq*Bq) - (4*Aq*Cq))) / (2.0*Aq);
			
			if(t0 > 0){
				ray->setT(t0);
				return createIntersection(ray);
			}
			else{
				if(t1 > 0){
					ray->setT(t1);
					return createIntersection(ray);
				}
				else{
					return 0;
				}
			}
			
		}
		
	}
}


std::string Quadric::toString(void) const{
	
	std::stringstream ss;
	
	ss << "---------------------------" << std::endl;
	ss << "Quadric :" << std::endl;
	ss << "---------------------------" << std::endl;
	
	return ss.str();
}
