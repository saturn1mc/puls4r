/*
 *  Linear.h
 *  puls4r
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LINEAR_H
#define LINEAR_H

#include "Enlightment.h"

class Linear : public Enlightment{
	
	Color* color;

public:
	
	Linear(Color* _color): color(new Color(_color)) {}
	Linear(const Linear& linear) : color(new Color(linear.color)) {}
	Linear(const Linear* linear) : color(new Color(linear->color)) {}
	
	virtual ~Linear(void) {
		delete(color);
	}
	
	virtual Color getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const;
	virtual Enlightment* clone(void) {return new Linear(*this);}
	
	Linear& operator=(const Linear& linear){
		delete(color);
		
		reflect = linear.reflect;
		kr = linear.kr;
		
		color = new Color(linear.color);
		
		return *this;
	}
};

#endif //LINEAR_H
