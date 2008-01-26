/*
 *  Linear.cpp
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Linear.h"

Color &Linear::getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const{
	return *color;
}
