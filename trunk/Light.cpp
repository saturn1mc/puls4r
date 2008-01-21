/*
 *  Light.cpp
 *  RayTracing
 *
 *  Created by Camille on 21/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Light.h"

void Light::initMatrix(void){
	
	Vector up(0,1,0);
	up.normalize();
	
	Vector &w = *direction ^ up;
	w.normalize();
	
	Vector &u = *direction ^ w;
	u.normalize();
	
	reference = new Matrix(w, u, *direction, *source);
	*reference = reference->t();
}
