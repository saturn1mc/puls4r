/*
 *  Observer.cpp
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Observer.h"

void Observer::initMatrix(void){
	Vector u, w, up(0,1,0);
	
	w = *sight ^ up;
	u = *sight ^ w;
	
	view = new Matrix(u, *sight, w, *eye);
	*view = view->t();
}

Ray& Observer::ray(Point *sp){
	Point eye2( (*view)*(*eye) );
	Point sp2( (*view) * (*sp));
	
	Ray *r = new Ray(eye, new Vector(eye2, sp2));
	
	return *r;
}
