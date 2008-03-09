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

#include "PhotonShooter.h"
#include "Observer.h"
#include "Image.h"
#include "Color.h"
#include "Object.h"
#include "Light.h"
#include "Box.h"
#include "Intersection.h"
#include "Enlightment.h"

class Scene{
private:
	
	static const int MAX_RECURSIONS = 1000;
	int currentRecursions;
	
	PhotonShooter* shooter;
	Observer* observer;
	Image* img;
	Color* background;
	std::list<Object* > objects;
	std::list<Light* > lights;
	std::list<Box* > boxes;
	double focal;
	
	/* Global Functions */
	double calcFocal(void) const;
	Intersection* getNearestIntersection(Ray* ray, double epsilon = 0.000001);
	Color* antialiasedColor(double l, double p, int mode);
	
	Color* colorAt(double l, double p, int mode);
	Color* observedColor(Ray* ray, int mode);
	Color* glossyReflection(Ray* ray, Intersection* intersection, int mode, bool random = false, double smoothing = 1);
	
	Ray* reflectedRay(Ray* ray, Intersection* intersection);
	Ray* refractedRay(Ray* ray, Intersection* intersection);
	Ray* refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon = 0.000001);
	
	void shadow(Color* color, Intersection* intersection, bool random = false, double smoothing = 1);
	
	/* Ray Casting Function */
	void rayCasting(void);
	
	/* Photon Mapping Functions */
	void photonMapping(void);
	
public:
	
	static const int RAYCASTING_MODE = 0;
	static const int PHOTONMAPPING_MODE = 1;
	
	Scene(Observer* _observer, Image* _img, Color* _background) : shooter(0), observer(new Observer(_observer)), img(new Image(_img)), background(new Color(_background)), objects(0), lights(0), boxes(0), focal(calcFocal()) {
		std::srand(std::time(0));
	}
	
	Scene(const Scene& scene) : shooter(new PhotonShooter(scene.shooter)), observer(new Observer(scene.observer)), img(new Image(scene.img)), background(new Color(scene.background)), objects(scene.objects), lights(scene.lights), boxes(scene.boxes), focal(scene.focal) {
		std::srand(std::time(0));
	}
	
	~Scene(){
		delete(shooter);
		delete(observer);
		delete(img);
		delete(background);
		objects.clear();
		lights.clear();
		boxes.clear();
	}
	
	int getH(void) const {return img->getH();}
	int getW(void) const {return img->getW();}
	double getFocal(void) const {return focal;}
	Observer* getObserver(void) const {return observer;}
	Image* getImage(void) const {return img;}
	Color* getBackground(void) const {return background;}
	
	std::list<Object* >& getObjects(void) {return objects;}
	std::list<Light* >& getLights(void) {return lights;}
	std::list<Box* >& getBoxes(void) {return boxes;}
	
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
	void addBox(Box* box);
	void trace(int mode = RAYCASTING_MODE);
	
	Scene& operator=(const Scene& scene){
		objects.clear();
		lights.clear();
		boxes.clear();
		
		delete(shooter);
		delete(observer);
		delete(img);
		delete(background);
		
		objects = scene.objects;
		lights = scene.lights;
		boxes = scene.boxes;
		
		shooter = new PhotonShooter(scene.shooter);
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
	s << "********************************" << std::endl;
	s << "Boxes :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Box *>::iterator iter = scene.getBoxes().begin(); iter != scene.getBoxes().end(); ++iter){
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
	s << "********************************" << std::endl;
	s << "Boxes :" << std::endl;
	s << "********************************" << std::endl;
	for(std::list<Box *>::iterator iter = scene->getBoxes().begin(); iter != scene->getBoxes().end(); ++iter){
		s << (*iter) << std::endl;
	}
	s << "********************************" << std::endl;
	s << "##########################################" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //SCENE_H
