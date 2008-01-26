/*
 *  Lambert.cpp
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Lambert.h"


Color &Lambert::getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const{
	
	Color *color = new Color(*od);
	
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector &L = getL(point, *(*iter));
		*color = (*color) * (kd *(L * norm));
	}
	
	return *color;
}
