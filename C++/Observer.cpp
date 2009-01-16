/*
 *  Observer.cpp
 *  puls4r
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Observer.h"

void Observer::initMatrix(void){
	
	Vector up(0,1,0);
	up.normalize();
	
	Vector w = (*sight) ^ up;
	w.normalize();
	
	Vector u = (*sight) ^ w;
	u.normalize();
	
	view = new Matrix(w, u, *sight, *eye);
	*view = view->t();
}

Ray Observer::ray(Point *sp){
	Vector dir(*eye, (*view) * sp);
	Ray ray(eye, &dir);
	
	return ray;
}
