/*
 *  Phong.cpp
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Phong.h"

Color &Phong::getColor(Point &point, Vector &norm, Ray &ray, std::list<Light *> lights) const{
	
	Color *color = new Color((*oa) * ka);
	
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector &L = getL(point, *(*iter));
		Vector &R = getR(L, norm);
		Vector &V = getV(ray);
		
		*color = *color + ((*od) * (kd * (L * norm))) + ((*os) * (ks * pow(R*V, n)));
	}
	
	return *color;
}
