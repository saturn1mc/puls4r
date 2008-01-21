/*
 *  Scene.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <cmath>

#include "Observer.h"
#include "Object.h"
#include "Color.h"
#include "Image.h"

class Scene{
private:
	
	Observer *observer;
	std::list<Object *> objects;
	Image *img;
	Color *background;
	
public:
	
	Scene(Observer *_observer, Image *_img, Color *_background) : objects(0) {
		observer = _observer;
		img = _img;
		background = _background;
	}
	
	int getH() {return img->getH();}
	int getW() {return img->getW();}
	
	void add(Object *obj);
	void rayTrace(void);
	double focal(void);
};

#endif //SCENE_H
