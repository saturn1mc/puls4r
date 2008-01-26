/*
 *  Intersection.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <sstream>

#include "Point.h"
#include "Vector.h"

class Object;

class Intersection{
private:
	
	Point *point;
	Vector *norm;
	Object *object;
	double t;
	
public:
	
	Intersection(Point *_point, Vector *_norm, Object *_object, double _t){
		point = _point;
		norm = _norm;
		object = _object;
		t = _t;
	}
	
	Intersection(Intersection &intersection){
		point = intersection.point;
		norm = intersection.norm;
		object = intersection.object;
		t = intersection.t;
	}
	
	~Intersection(){}
	
	Point &getPoint(void) const {return *point;}
	Vector &getNorm(void) const {return *norm;}
	Object &getObject() const {return *object;}
	double getT(void) const {return t;}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Intersection &inter){
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
	s << "Intersection :" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Point : " << inter.getPoint() << std::endl;
	s << "Norm : " << inter.getNorm() << std::endl;
	s << "t : " << inter.getT() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //INTERSECTION_H

