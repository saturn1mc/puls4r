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
	points.push_back(new Point(x, y, z));
	
	if(points.size() >= 3){
		//TODO create triangles
		points.pop_front();
	}
}
