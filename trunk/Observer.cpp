/*
 *  Observer.cpp
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "Observer.h"

const int Observer::NL = 100;
const int Observer::NP = 100;
const double alpha = M_PI/180.0;

void Observer::initMatrix(void){
	Vector u, w, up(0,1,0);
	
	w = *sight ^ up;
	u = *sight ^ w;
	
	view = new Matrix(u, *sight, w, *eye);
	*view = view->t();
}

Vector& Observer::ray(Point *sp){
	Point eye2( (*view)*(*eye) );
	Point sp2( (*view) * (*sp));
	
	Vector *r = new Vector(eye2, sp2);
	
	return *r;
}

void Observer::rayTracing(void){
	for(int x = -NP/2; x<NP/2; x++){
		for(int y = NL/2; y>-NL/2; y--){
			ray(new Point(x, y, focal()));
		}
	}
}

double Observer::focal(void){
	return (NP/2.0) / tan(alpha/2.0);
}
