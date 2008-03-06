/*
 *  Sphere.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sphere.h"

Intersection* Sphere::createIntersection(Ray* ray){
	Point* m =  new Point(	ray->getOrigin()->getX() + (ray->getDirection()->getX() * ray->getT()),
							ray->getOrigin()->getY() + (ray->getDirection()->getY() * ray->getT()),
							ray->getOrigin()->getZ() + (ray->getDirection()->getZ() * ray->getT())
						);
	
	Vector* nm = new Vector(	(m->getX() - center->getX()) / radius,
								(m->getY() - center->getY()) / radius,
								(m->getZ() - center->getZ()) / radius
							);
	
	nm->normalize();
	
	if(perlin != 0){
		perlin->disruptNormal(nm, epsilon);
	}
	
	Intersection *intersection = new Intersection(m, nm, this, ray->getT());
	
	delete(nm);
	delete(m);
	
	return intersection;
}

Intersection* Sphere::intersection(Ray* ray){
	
	double A = pow(ray->getDirection()->getX(), 2.0) + pow(ray->getDirection()->getY(), 2.0) + pow(ray->getDirection()->getZ(), 2.0);
	double B = 2.0 * ( (ray->getDirection()->getX() * (ray->getOrigin()->getX() - center->getX())) + (ray->getDirection()->getY() * (ray->getOrigin()->getY() - center->getY())) + (ray->getDirection()->getZ() * (ray->getOrigin()->getZ() - center->getZ())));
	double C = pow(ray->getOrigin()->getX() - center->getX(), 2.0) + pow(ray->getOrigin()->getY() - center->getY(), 2.0) + pow(ray->getOrigin()->getZ() - center->getZ(), 2.0) - pow(radius, 2.0);
	
	double t0 = (-B - sqrt((B*B) - (4*A*C))) / (2.0*A);
	double t1 = (-B + sqrt((B*B) - (4*A*C))) / (2.0*A);
	
	if(t0 > 0 && t1 > 0){
		
		ray->setT(std::min(t0, t1));
		return createIntersection(ray);
	}
	else{
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


std::string Sphere::toString(void) const{

	std::stringstream ss;
	
	ss << "---------------------------" << std::endl;
	ss << "Sphere :" << std::endl;
	ss << "---------------------------" << std::endl;
	ss << "Center : " << center << std::endl;
	ss << "Radius : " << radius << std::endl;
	ss << "---------------------------" << std::endl;
	
	return ss.str();
}
