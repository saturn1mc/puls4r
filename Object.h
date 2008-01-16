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

#include "Color.h"
#include "Intersection.h"
#include "Ray.h"

class Object{

protected:
	Color *color;
	Object(void) {}
	
public:
	
	virtual ~Object(void) {}
	virtual Intersection *intersection(Ray ray) = 0;
};

#endif //OBJECT_H
