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
	
	Object(void) : reflect(false) {}
	bool reflect;
	Enlightment *enlightment;
	
public:
		
	bool isReflecting(void) const{
		return reflect;
	}
	
	void setReflectance(bool _reflect){
		reflect = _reflect;
	}
		
	Enlightment *getEnlightment(void) const {
		return enlightment;
	}
	
	void setEnlightment(Enlightment *_enlightment){
		enlightment = _enlightment;
	}
	
	Object(const Object& object) : reflect(object.reflect) {}
	virtual ~Object(void) {}
	virtual Object& operator=(const Object& object){

		//delete(enlightment);
		
		reflect = object.reflect;
		enlightment = object.enlightment->clone();
		
		return *this;
	}
	
	virtual Intersection *intersection(Ray *ray) = 0;
	virtual std::string toString(void) const = 0;
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Object *obj){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << obj->toString();
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //OBJECT_H
