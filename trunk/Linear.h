/*
 *  Linear.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LINEAR_H
#define LINEAR_H

#include "Enlightment.h"

class Linear : public Enlightment{
	
	Color *color;

public:
	
	Linear(Color *_color){
		color = _color;
	}
	
	Linear(Linear &linear) {}
	virtual ~Linear(void) {}
	virtual Color &getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const;
	virtual Enlightment *getCopy() {return new Linear(*this);}
};

#endif //LINEAR_H
