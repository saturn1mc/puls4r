/*
 *  Object.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <sstream>

#include "Enlightment.h"
#include "Intersection.h"
#include "Ray.h"

class Object{

protected:
	
	Object(void) {}
	Enlightment *enlightment;
	
public:
	
	Enlightment &getEnlightment(void) const {
		return *enlightment;
	}
	
	virtual ~Object(void) {}
	virtual Intersection *intersection(Ray &ray) = 0;
	virtual std::string toString(void) const = 0;
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Object &obj){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << obj.toString();
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //OBJECT_H
