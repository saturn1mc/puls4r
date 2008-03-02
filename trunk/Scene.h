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
#include "Image.h"
#include "Color.h"
#include "Object.h"
#include "Light.h"
#include "Intersection.h"
#include "Enlightment.h"

class Scene{
private:
	
	static const int MAX_RECURSIONS = 1000;
	int currentRecursions;
	
	Observer* observer;
	Image* img;
	Color* background;
	std::list<Object* > objects;
	std::list<Light* > lights;
	double focal;
	
	Intersection* getNearestIntersection(Ray* ray, double epsilon = 0.000001);
	
	double calcFocal(void) const;
	
	Color* colorAt(double l, double p);
	Color* antialiasedColor(double l, double p);
	Color* observedColor(Ray* ray);
	Color* glossyReflection(Ray* ray, Intersection* intersection, double smoothing = 2.0);
	
	Ray* reflectedRay(Ray* ray, Intersection* intersection);
	Ray* refractedRay(Ray* ray, Intersection* intersection);
	Ray* refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon = 0.000001);
	
	void shadow(Color* color, Intersection* intersection, double smoothing = 3.0);
	
public:
	
	Scene(Observer* _observer, Image* _img, Color* _background) : observer(new Observer(_observer)), img(new Image(_img)), background(new Color(_background)), objects(0), lights(0), focal(calcFocal()) {}
	Scene(const Scene& scene) : observer(new Observer(scene.observer)), img(new Image(scene.img)), background(new Color(scene.background)), objects(scene.objects), lights(scene.lights), focal(scene.focal) {}
	
	~Scene(){
		delete(observer);
		delete(img);
		delete(background);
		objects.clear();
		lights.clear();
	}
	
	int getH(void) const {return img->getH();}
	int getW(void) const {return img->getW();}
	double getFocal(void) const {return focal;}
	Observer* getObserver(void) const {return observer;}
	Image* getImage(void) const {return img;}
	Color* getBackground(void) const {return background;}
	std::list<Object* >& getObjects(void) {return objects;}
	std::list<Light* >& getLights(void) {return lights;}
	
	void setImage(Image* _img){
		delete(img);
		img = new Image(_img);
	}
	
	void setObserver(Observer* _observer){
		delete(observer);
		observer = new Observer(_observer);
	}
	
	void addObject(Object* obj);
	void addLight(Light* light);
	void rayTrace(void);
	
	Scene& operator=(const Scene& scene){
		objects.clear();
		lights.clear();
		delete(observer);
		delete(img);
		delete(background);
		
		objects = scene.objects;
		lights = scene.lights;
		observer = new Observer(scene.observer);
		img = new Image(scene.img);
		background = new Color(scene.background);
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& strm, Scene& scene){
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
	s << "Focal : " << scene.getFocal() << std::endl;
	s << "Background color : " << scene.getBackground() << std::endl;
	s << "********************************" << std::endl;
	s << "Lights :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Light *>::iterator iter = scene.getLights().begin(); iter != scene.getLights().end(); ++iter){
		s << (*iter) << std::endl;
	}
	s << "********************************" << std::endl;
	s << "********************************" << std::endl;
	s << "Objects :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Object *>::iterator iter = scene.getObjects().begin(); iter != scene.getObjects().end(); ++iter){
		s << (*iter) << std::endl;
	}
	s << "********************************" << std::endl;
	s << "##########################################" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& strm, Scene* scene){
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
	s << scene->getObserver() << std::endl;
	s << scene->getImage() << std::endl;
	s << "Focal : " << scene->getFocal() << std::endl;
	s << "Background color : " << scene->getBackground() << std::endl;
	s << "********************************" << std::endl;
	s << "Lights :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Light *>::iterator iter = scene->getLights().begin(); iter != scene->getLights().end(); ++iter){
		s << (*iter) << std::endl;
	}
	s << "********************************" << std::endl;
	s << "********************************" << std::endl;
	s << "Objects :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Object *>::iterator iter = scene->getObjects().begin(); iter != scene->getObjects().end(); ++iter){
		s << (*iter) << std::endl;
	}
	s << "********************************" << std::endl;
	s << "##########################################" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //SCENE_H
