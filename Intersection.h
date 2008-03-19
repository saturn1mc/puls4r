/*
 *  Intersection.h
 *  puls4r
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
	Vector* normal;
	Object* object;
	double t;
	
public:
	
	Intersection(Point* _point, Vector* _normal, Object* _object, double _t) : point(new Point(_point)), normal(new Vector(_normal)), object(_object), t(_t) {
		normal->normalize();
	}
	
	Intersection(const Intersection& intersection) : point(new Point(intersection.point)), normal(new Vector(intersection.normal)), object(0), t(intersection.t) { object = intersection.object; }
	Intersection(const Intersection* intersection) : point(new Point(intersection->point)), normal(new Vector(intersection->normal)), object(0), t(intersection->t) { object = intersection->object; }
	
	~Intersection(){
		delete(point);
		delete(normal);
	}
	
	Point* getPoint(void) const {return point;}
	Vector* getNormal(void) const {return normal;}
	Object* getObject() const {return object;}
	void setObject(Object* _object) {object = _object;}
	double getT(void) const {return t;}
	
	Intersection& operator=(const Intersection& intersection){
		delete(point);
		delete(normal);
		
		point = new Point(intersection.point);
		normal = new Vector(intersection.normal);
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
	s << "Normal : " << inter.getNormal() << std::endl;
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
	s << "Normal : " << inter->getNormal() << std::endl;
	s << "t : " << inter->getT() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //INTERSECTION_H

