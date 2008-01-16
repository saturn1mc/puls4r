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
private:
	
	int nl;
	int np;
	double alpha;
	
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
	
	int getnl() {return nl;}
	int getnp() {return np;}
	double getAlpha() {return alpha;}
	
	void setnl(int _nl) {nl=_nl;}
	void setnp(int _np) {np=_np;}
	void setAlpha(int _alpha) {alpha=_alpha;}
	
	void add(Object *obj);
	void rayTrace(void);
	double focal(void);
};

#endif //SCENE_H
