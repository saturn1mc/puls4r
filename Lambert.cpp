/*
 *  Lambert.cpp
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Lambert.h"


Color Lambert::getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const{
	
	Color color(od);
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector L = getL(point, (*iter));
		
		Color diffuse = ((*(*iter)->getColor()) * (kd * (L * norm)));
		
		color = color * diffuse;
	}
	
	color.normalize();
	
	return color;
}
