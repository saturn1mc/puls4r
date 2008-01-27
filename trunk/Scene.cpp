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
			
			Intersection *current_intersection = 0;
			Point *pix = new Point(p, l, focal);
			Ray &ray = observer->ray(pix);
			
			for(list<Object *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
				Intersection *candidate = (*iter)->intersection(ray);
				
				if(candidate != 0){
					if(current_intersection == 0 || current_intersection->getT() > candidate->getT()){
						current_intersection = candidate;
					}
				}
			}
			
			if(current_intersection != 0){
				Color *color = new Color(current_intersection->getObject().getEnlightment().getColor(current_intersection->getPoint(), current_intersection->getNorm(), ray, lights));
				img->writePixel(*color);
				delete(color);
			}
			else{
				img->writePixel(*background);
			}
		}
	}
	
	img->writeBitmap();
}

double Scene::calcFocal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}
