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
#include "Image.h"
#include "Color.h"

class Scene{
public:
	static const int NL;
	static const int NP;
	static const double alpha;

private:
	
	Observer *obs;
	std::list<Object *> objects;
	Image *img;
	Color *background;
	
public:
	
	Scene(Observer *_obs, Image *_img, Color *_background) : objects(0) {
		obs = _obs;
		img = _img;
		background = _background;
	}
	
	void add(Object *obj);
	void rayTrace(void);
	double focal(void);
};

#endif //SCENE_H
