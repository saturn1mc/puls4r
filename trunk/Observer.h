/*
 *  Observer.h
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <cmath>

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"

class Observer{
private:
	
	static const int NL;
	static const int NP;
	static const double alpha;
	
	Point *eye;
	Vector *sight;
	Matrix *view;
	
	void initMatrix(void);
	
public:
	Observer(Point *_eye, Point *_sight){
		eye = _eye;
		sight = new Vector(*eye, *_sight);
		
		initMatrix();
	}
	
	Observer(Point *_eye, Vector *_sight){
		eye = _eye;
		sight = _sight;
		
		initMatrix();
	}
	
	double focal(void);
	Vector &ray(Point *sp);
	void rayTracing(void);
};

#endif //OBSERVER_H
