/*
 *  Triangle.h
 *  Pulsar
 *
 *  Created by Camille on 27/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Plan.h"

class Triangle : public Object{
private:
	
	Point* points[3];
	Plan* plan;
	
public:

	Triangle(Enlightment* _enlightment, Point* a, Point* b, Point* c) : plan(0){
		
		enlightment = _enlightment->clone();
		points[0] = new Point(a);
		points[1] = new Point(b);
		points[2] = new Point(c);
		
		Vector *AB = new Vector(a, b);
		Vector *AC = new Vector(a, c);
	
		Vector *norm = new Vector((*AB) ^ (AC));
		norm->normalize();
		double d = - (norm->get(0) * points[0]->getX())  - (norm->get(1) * points[0]->getY()) - (norm->get(2) * points[0]->getZ());
	
		plan = new Plan(enlightment, norm, d, false);
		
		delete(AB);
		delete(AC);
		delete(norm);
	}
	
	Triangle(const Triangle& triangle) : plan(0){
		
		enlightment = triangle.enlightment->clone();
		points[0] = new Point(triangle.points[0]);
		points[1] = new Point(triangle.points[1]);
		points[2] = new Point(triangle.points[2]);
		
		plan = new Plan(triangle.plan);
	}
	
	Triangle(const Triangle* triangle) : plan(0){
		
		enlightment = triangle->enlightment->clone();
		points[0] = new Point(triangle->points[0]);
		points[1] = new Point(triangle->points[1]);
		points[2] = new Point(triangle->points[2]);
		
		plan = new Plan(triangle->plan);
	}
	
	virtual ~Triangle(void) {
		delete(enlightment);
		delete(plan);
		delete(points[0]);
		delete(points[1]);
		delete(points[2]);		
	}
	virtual Intersection *intersection(Ray *ray);
	virtual std::string toString(void) const;

	Point* getPoint(int index) const{
		if(index < 0 || index > 2){
			return 0;
		}
		else{
			return points[index];
		}
	}
	
	Triangle& operator=(const Triangle& triangle){
		
		delete(plan);
		delete(points[0]);
		delete(points[1]);
		delete(points[2]);
		
		enlightment = triangle.enlightment->clone();
		points[0] = new Point(triangle.points[0]);
		points[1] = new Point(triangle.points[1]);
		points[2] = new Point(triangle.points[2]);
		
		plan = new Plan(triangle.plan);
		
		return *this;
	}
};

#endif //TRIANGLE_H
