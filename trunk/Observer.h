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

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"

class Observer{
private:
	
	Point *eye;
	Vector *sight;
	Matrix *view;
	double alpha;
	
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
	
	Ray &ray(Point *sp);
	
	Point *getEye(void){
		return eye;
	}
	
	Vector *getSight(void){
		return sight;
	}
	
	Matrix *getView(void){
		return view;
	}
	
	double getAlpha() {return alpha;}
	
	void setAlpha(int _alpha) {alpha=_alpha;}
};

#endif //OBSERVER_H
