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
#include "Perlin.h"
#include "Ray.h"

class Object{

protected:
	
	Enlightment *enlightment;
	Perlin* perlin;
	double epsilon;
	
	Object(void) : enlightment(0), perlin(0), epsilon(0.5){}
	
public:
		
	bool isReflecting(void) const{
		return enlightment->isReflecting();
	}
	
	double getKR(void) const{
		return enlightment->getKR();
	}
	
	void setGlossy(double _glossyFocal, double _glossyWidth){
		enlightment->setGlossy(_glossyFocal, _glossyWidth);
	}
	
	double getGlossyFocal(void) const{
		return enlightment->getGlossyFocal();
	}
	
	double getGlossyWidth(void) const{
		return enlightment->getGlossyWidth();
	}
	
	bool isRefracting(void) const{
		return enlightment->isRefracting();
	}
	
	double getN(void) const{
		return enlightment->getN();
	}
	
	double getKT(void) const{
		return enlightment->getKT();
	}
	
	void setReflecting(bool _reflect, double _kr = 1.0){
		enlightment->setReflecting(_reflect, _kr);
	}
	
	void setRefracting(bool _refract, double _n = 1.0, double _kt = 1.0){
		enlightment->setRefracting(_refract, _n, _kt);
	}
		
	Enlightment* getEnlightment(void) const {
		return enlightment;
	}
	
	void setEnlightment(Enlightment* _enlightment){
		enlightment = _enlightment;
	}
	
	void setEpsilon(double _epsilon){
		epsilon = _epsilon;
	}
	
	Object(const Object& object) : enlightment(0) {}
	
	virtual ~Object(void) {}
	
	virtual Object& operator=(const Object& object){

		delete(enlightment);
		
		enlightment = object.enlightment->clone();
		
		return *this;
	}
	
	virtual Intersection* intersection(Ray* ray) = 0;
	virtual std::string toString(void) const = 0;
};

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& strm, const Object* obj){
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
