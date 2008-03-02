/*
 *  Box.h
 *  Pulsar
 *
 *  Created by Camille on 02/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BOX_H
#define BOX_H

#include <limits>

#include "Object.h"

class Box : public Object{
private:
	
	Point* min;
	Point* max;
	
public:

	Box(Enlightment* _enlightment, Point* _min, Point* _max) : min(_min), max(_max) {
		enlightment = _enlightment->clone();
	}
	
	virtual ~Box(void) {
		delete(enlightment);
	}
	
	virtual Intersection* intersection(Ray* ray);
	virtual std::string toString(void) const;
	
	Box& operator=(const Box& box){
		delete(enlightment);
		
		enlightment = box.enlightment->clone();
		
		return *this;
	}
};

#endif //BOX_H
