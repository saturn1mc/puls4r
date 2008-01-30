/*
 *  Scene.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene.h"

void Scene::addObject(Object *obj){
	objects.push_front(obj);
}

void Scene::addLight(Light *light){
	lights.push_front(light);
}
	
void Scene::rayTrace(void){
	
	cout << "Tracing ... ";
	int progress = 0;
	
	for(int l=-getH()/2; l<getH()/2; l++){
		
		int done = round(100 * (float)(l+(getH()/2)+1) / (float)getH());
		
		if(progress != done){
			progress = done;
			cout << progress << "% ";
			cout.flush();
		}
		
		for(int p=-getW()/2; p<getW()/2; p++){
			
			Point *pix = new Point(p, l, focal);
			Ray &ray = observer->ray(pix);
			
			Intersection *nearestIntersection = getNearestIntersection(ray);
			
			if(nearestIntersection != 0){
				Color *color = new Color(nearestIntersection->getObject().getEnlightment().getColor(nearestIntersection->getPoint(), nearestIntersection->getNorm(), ray, lights));
				shadow(*color, nearestIntersection->getObject(), nearestIntersection->getPoint());
				
				img->writePixel(*color);
				
				delete(color);
			}
			else{
				img->writePixel(*background);
			}
			
			delete(pix);
		}
	}
	
	img->writeBitmap();
}

double Scene::calcFocal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}

Intersection *Scene::getNearestIntersection(Ray &ray){
	
	Intersection *nearestIntersection = 0;
	
	for(list<Object *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
		Intersection *candidate = (*iter)->intersection(ray);
		
		if(candidate != 0){
			if(nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()){
				nearestIntersection = candidate;
			}
		}
	}
	
	return nearestIntersection;
}

void Scene::shadow(Color &color, Object &object, Point &point){
	for(std::list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector *l = new Vector(point, (*iter)->getSource());
		l->normalize();
		
		Ray *ray = new Ray(&point, l);
		Intersection *intersection = getNearestIntersection(*ray);
		
		if(intersection != 0 && (&intersection->getObject() != &object)){
			color.darken(0.3);
		}
	}
	
	color.normalize();
}
