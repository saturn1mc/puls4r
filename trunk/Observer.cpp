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
	
	Vector up(0,1,0);
	up.normalize();
	
	Vector &w = *sight ^ up;
	w.normalize();
	
	Vector &u = *sight ^ w;
	u.normalize();
	
	view = new Matrix(w, u, *sight, *eye);
	*view = view->t();
}

Ray& Observer::ray(Point *sp){
	
	Point sp2( (*view) * (*sp));
	
	Ray *r = new Ray(eye, new Vector(*eye, sp2));
	
	return *r;
}
