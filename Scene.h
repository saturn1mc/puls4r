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

#include <iostream>
#include <sstream>
#include <list>
#include <cmath>

#include "Observer.h"
#include "Object.h"
#include "Color.h"
#include "Image.h"

class Scene{
private:
	
	Observer *observer;
	Image *img;
	Color *background;
	std::list<Object *> objects;
	
public:
	
	Scene(Observer *_observer, Image *_img, Color *_background) : objects(0) {
		observer = _observer;
		img = _img;
		background = _background;
	}
	
	int getH(void) const {return img->getH();}
	int getW(void) const {return img->getW();}
	Observer &getObserver(void) const {return *observer;}
	Image &getImage(void) const {return *img;}
	Color &getBackground(void) const {return *background;}
	std::list<Object *> getObjects(void) const {return objects;}
	
	void add(Object *obj);
	void rayTrace(void);
	double focal(void);
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Scene &scene){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "##########################################" << std::endl;
	s << "Scene :" << std::endl;
	s << "##########################################" << std::endl;
	s << scene.getObserver() << std::endl;
	s << scene.getImage() << std::endl;
	s << "Background color :" << scene.getBackground() << std::endl;
	s << "********************************" << std::endl;
	s << "Objects :" << std::endl;
	s << "********************************" << std::endl;
	for(list<Object *>::iterator iter = scene.getObjects().begin(); iter != scene.getObjects().end(); ++iter){
		s << (*iter)->toString() << endl;
	}
	s << "********************************" << std::endl;
	s << "##########################################" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //SCENE_H
