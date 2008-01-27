/*
 *  C3dsParser.h
 *  puls4r
 *
 *  Created by Camille on 27/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef C3DSPARSER_H
#define C3DSPARSER_H

#include <list>

#include "C3dsFileLoader.h"
#include "Triangle.h"

class C3dsParser : public C3dsFileLoader{
private:
	
	Enlightment *enlightment;
	std::list<Point*> points;
	
protected:
	void User3dVert(float x, float y, float z);
	
public:
	C3dsParser(Enlightment *_enlightment) : C3dsFileLoader(), points(0){
		enlightment = _enlightment;
	} 
};

#endif //C3DSPARSER_H