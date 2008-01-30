/*
 *  C3dsParser.cpp
 *  puls4r
 *
 *  Created by Camille on 27/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "C3dsParser.h"

void C3dsParser::User3dVert(float x, float y, float z){
	
	Point *p = new Point((double)x, (double)y, (double)z);
	std::cout << *p << std::endl;
	points.push_back(p);
	
	if(points.size() >= 3){
		
		Point *a = points.front();
		points.pop_front();
		
		Point *b = points.front();
		points.pop_front();
		
		Point *c = points.front();
		points.pop_front();
		
		Triangle *triangle = new Triangle(enlightment, a, b, c);
		scene->addObject(triangle);
		cout << *triangle << endl;
	}
}
