/*
 *  Triangle.cpp
 *  Pulsar
 *
 *  Created by Camille on 27/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Triangle.h"

Intersection* Triangle::intersection(Ray* ray){
	
	Intersection* intersection = plan->intersection(ray);
	
	if(intersection == 0){
		return 0;
	}
	else{
		Point* b = new Point(*points[1] - points[0]);
		Point* c = new Point(*points[2] - points[0]);
		Point* p = new Point(*intersection->getPoint() - points[0]);
		
		double u = ((p->getY() * c->getX()) - (p->getX() * c->getY())) / ((b->getY() * c->getX()) - (b->getX() * c->getY()));
		double v = ((p->getY() * b->getX()) - (p->getX() * b->getY())) / ((c->getY() * b->getX()) - (c->getX() * b->getY()));
		
		delete(b);
		delete(c);
		delete(p);
		
		if(u>=0 && v >= 0 && (u+v) <= 1){
			intersection->setObject(this);
			return intersection;
		}
		else{
			return 0;
		}
	}
}


std::string Triangle::toString(void) const{

	std::stringstream ss;
	
	ss << "---------------------------" << std::endl;
	ss << "Triangle :" << std::endl;
	ss << "---------------------------" << std::endl;
	ss << "Points : " << points[0] << ","<< points[1] << "," << points[2] << std::endl;
	ss << "---------------------------" << std::endl;
	
	return ss.str();
}
