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
	
	Point* point;
	Vector* norm;
	Object* object;
	double t;
	
public:
	
	Intersection(Point* _point, Vector* _norm, Object* _object, double _t) : point(new Point(_point)), norm(new Vector(_norm)), object(_object), t(_t) {
		norm->normalize();
	}
	Intersection(const Intersection& intersection) : point(new Point(intersection.point)), norm(new Vector(intersection.norm)), object(object), t(intersection.t) {}
	
	~Intersection(){
		delete(point);
		delete(norm);
	}
	
	Point* getPoint(void) const {return point;}
	Vector* getNorm(void) const {return norm;}
	Object* getObject() const {return object;}
	void setObject(Object* _object) {object = _object;}
	double getT(void) const {return t;}
	
	Intersection& operator=(const Intersection& intersection){
		delete(point);
		delete(norm);
		
		point = new Point(intersection.point);
		norm = new Vector(intersection.norm);
		object = intersection.object;
		t = intersection.t;
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits> &strm, const Intersection& inter){
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

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits> &strm, const Intersection* inter){
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
	s << "Point : " << inter->getPoint() << std::endl;
	s << "Norm : " << inter->getNorm() << std::endl;
	s << "t : " << inter->getT() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //INTERSECTION_H

