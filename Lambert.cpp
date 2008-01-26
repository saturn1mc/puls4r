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
	
	Color &color = (*od);
	double coeff = 0;
	
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector &L = getL(point, *(*iter));
		coeff += (L * norm);
	}
	
	color = (*od) * coeff;
	
	return color;
}
