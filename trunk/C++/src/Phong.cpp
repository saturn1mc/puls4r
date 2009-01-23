/*
 *  Phong.cpp
 *  puls4r
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Phong.h"

Color Phong::getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const{
	
	Color color;
	Vector V = getV(ray);
	
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector L = getL(point, (*iter));
		Vector R = getR(&L, norm);
		
		Color diffuse( (*od) * (kd * (L * norm)) );
		Color specular;
		
		if((R*V) > 0){
			specular = ( (*os) * (ks * pow(R*V, n)) );
		}
		
		diffuse.normalize();
		specular.normalize();
		
		color = color + ((diffuse + specular) * (*iter)->getColor());
	}
	
	color.normalize();
	
	return color;
}
