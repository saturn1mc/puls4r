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

#include <cmath>

#include "Object.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"

class Intersection{
private:
	
	Point *point;
	Vector *norm;
	Color *color;
	
public:
	
	Intersection(Point *_point, Vector *_norm, Color *_color){
		point = _point;
		norm = _norm;
		color = _color;
	}
};

#endif //INTERSECTION_H

