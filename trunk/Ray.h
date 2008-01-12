/*
 *  Ray.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray{
private:
	
	Point *origin;
	Vector *direction;
	double t;
	
public:
		
	Ray(Point *_origin, Vector *_direction){
		origin = _origin;
		direction = _direction;
	}
	
	Point &getOrigin() const{
		return *origin;
	}
	
	Vector &getDirection() const{
		return *direction;
	}
	
	double getT() const{
		return t;
	}
	
	void setOrigin(Point *_origin){
		origin = _origin;
	}
	
	void setDirection(Vector *_direction){
		direction = _direction;
	}
	
	void setT(double _t){
		t = _t;
	}
};

#endif //RAY_H
