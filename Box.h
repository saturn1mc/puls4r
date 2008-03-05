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

#include "Point.h"
#include "Ray.h"

class Box{
private:
	
	Point* min;
	Point* max;
	
	void swap(double& a, double& b);
	
public:

	Box(Point* _min, Point* _max) : min(_min), max(_max) {}
	
	virtual ~Box(void) {
		delete(min);
		delete(max);
	}
	
	virtual bool intersection(Ray* ray);
	virtual std::string toString(void) const;
	
	Box& operator=(const Box& box){
		
		*min = box.min;
		*max = box.max;
		
		return *this;
	}
};

#endif //BOX_H
