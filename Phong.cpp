/*
 *  Phong.cpp
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Phong.h"

Color *Phong::getColor(Point *point, Vector *norm, Ray *ray, std::list<Light *> lights) const{
	
	Color *color = new Color();
	
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector *L = getL(point, (*iter));
		Vector *R = getR(L, norm);
		Vector *V = getV(ray);
		
		Color *diffuse = new Color( (*od) * (kd * ((*L) * norm)) );
		
		Color *specular;
		
		if((*R)*V < 0){
			specular = new Color();
		}
		else{
			specular = new Color( (*os) * (ks * pow((*R)*V, n)) );
		}
		
		
		diffuse->normalize();
		specular->normalize();
		
		*color = *color + ((*(*iter)->getColor()) * ((*diffuse) + specular));
		
		delete(diffuse);
		delete(specular);
	}
	
	color->normalize();
	
	return color;
}
