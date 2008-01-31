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
#include <string>
#include <iostream>

#include "C3dsFileLoader.h"
#include "Scene.h"
#include "Triangle.h"

class C3dsParser : public C3dsFileLoader{
private:
	
	std::list<Point *> points;
	Scene *scene;
	Enlightment *enlightment;
	
protected:
	void User3dVert(float x, float y, float z);
	
public:
	C3dsParser(Scene *_scene, Enlightment *_enlightment) : C3dsFileLoader(), points(0){
		scene = _scene;
		enlightment = _enlightment;
	}
	
	Scene &getScene(void) const{
		return *scene;
	}
};

#endif //C3DSPARSER_H

