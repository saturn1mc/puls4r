/*
 *  Ray.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <sstream>

#include "Point.h"
#include "Vector.h"

class Ray{
private:
	
	Point *origin;
	Vector *direction;
	double t;
	
public:
		
	Ray(Point *_origin, Vector *_direction) : origin(new Point(_origin)), direction(new Vector(_direction)), t(0) {
		direction->normalize();
	}
	
	Ray(const Ray& ray) : origin(new Point(ray.origin)), direction(new Vector(ray.direction)), t(ray.t) {}
	Ray(const Ray* ray) : origin(new Point(ray->origin)), direction(new Vector(ray->direction)), t(ray->t) {}
	
	~Ray(){
		delete(origin);
		delete(direction);
	}
	
	Point *getOrigin(void) const {return origin;}
	
	Vector *getDirection(void) const {return direction;}
	
	double getT(void) const {return t;}
	
	void setOrigin(Point *_origin){
		origin = _origin;
	}
	
	void setDirection(Vector *_direction){
		direction = _direction;
		direction->normalize();
	}
	
	void setT(double _t){
		t = _t;
	}
	
	Ray& operator=(const Ray& ray){
		
		delete(origin);
		delete(direction);
		
		origin = new Point(ray.origin);
		direction = new Vector(ray.direction);
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Ray &ray){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "---------------------------" << std::endl;
	s << "Ray :" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Origin : " << ray.getOrigin() << std::endl;
	s << "Direction : " << ray.getDirection() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //RAY_H
