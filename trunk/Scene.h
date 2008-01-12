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

#include "Observer.h"
#include "Object.h"
#include "Image.h"
#include "Color.h"

class Scene{
private:
	
	Observer *obs;
	Object *obj;
	Image *img;
	Color *background;
	
public:
	
	Scene(Observer *_obs, Object *_obj, Image *_img, Color *_background){
		obs = _obs;
		obj = _obj;
		img = _img;
		background = _background;
	}
};

#endif //SCENE_H
