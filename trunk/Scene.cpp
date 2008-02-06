/*
 *  Scene.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene.h"

void Scene::addObject(Object* obj){
	objects.push_front(obj);
}

void Scene::addLight(Light* light){
	lights.push_front(light);
}
	
void Scene::rayTrace(void){
	
	std::cout << "---> Tracing..." << std::endl;
	int progress = 0;
	
	for(int l=-getH()/2; l<getH()/2; l++){
		
		int done = (int)round(100 *  (float)(l+(getH()/2)+1) / (float)getH());
		
		if(progress != done){
			progress = done;
			std::cout << "\r\t" << progress << "%";
			std::cout.flush();
		}
		
		for(int p=-getW()/2; p<getW()/2; p++){
			
			Color* color = 0;
			
			if(img->getAntialiasing() > 1){
				color = antialiasedColor(l, p);
			}
			else{
				color = colorAt(l, p);
			}
			
			img->writePixel(color);
			
			delete(color);
		}
	}
	
	std::cout << std::endl;
	std::cout << "\tWriting image to " << img->getFilename() << std::endl;
	img->writeBitmap();
	std::cout << "---> End of tracing" << std::endl;
}

Color* Scene::colorAt(double l, double p){

	Point* target = new Point(p, l, focal);
	Ray* ray = observer->ray(target);
	
	Intersection* nearestIntersection = getNearestIntersection(ray);
	
	if(nearestIntersection != 0){
		Color* color = nearestIntersection->getObject()->getEnlightment()->getColor(nearestIntersection->getPoint(), nearestIntersection->getNorm(), ray, lights);
		
		if(!nearestIntersection->getObject()->isReflecting()){
			shadow(color, nearestIntersection);
		}
		
		Color *reflectedColor = new Color(reflection(color, ray, nearestIntersection));
		
		delete(color);
		delete(nearestIntersection);
		delete(ray);
		delete(target);
		
		return reflectedColor;
	}
	else{
		delete(ray);
		delete(target);
		return new Color(background);
	}
}

Color* Scene::antialiasedColor(double l, double p){
	
	Color* finalColor = 0;
	double aa = 1.0 / ((double)img->getAntialiasing());
	
	for(double l2 = (l - 1); l2 <= (l + 1); l2+=aa){
		for(double p2 = (p - 1); p2 <= (p + 1); p2+=aa){
			if(finalColor == 0){
				finalColor = colorAt(l2, p2);
			}
			else{
				Color* nearColor = colorAt(l2, p2);
				
				*finalColor = (*finalColor) + nearColor;
				*finalColor = (*finalColor) * 0.5;
				
				delete(nearColor);
			}
		}
	}
	
	return finalColor;
}

double Scene::calcFocal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}

Intersection* Scene::getNearestIntersection(Ray* ray){
	
	Intersection* nearestIntersection = 0;
	
	for(std::list<Object* >::iterator iter = objects.begin(); iter != objects.end(); ++iter){
		Intersection* candidate = (*iter)->intersection(ray);
		
		if(candidate != 0){
			if(nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()){
				if(nearestIntersection!=0){
					delete(nearestIntersection);
				}
				nearestIntersection = candidate;
			}
		}
	}
	
	return nearestIntersection;
}

Intersection* Scene::getNearestIntersectionExcluding(Ray* ray, Object* object){
	
	Intersection* nearestIntersection = 0;
	
	for(std::list<Object* >::iterator iter = objects.begin(); iter != objects.end(); ++iter){
		
		if((*iter) != object){
		
			Intersection* candidate = (*iter)->intersection(ray);
		
			if(candidate != 0){
				if(nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()){
					
					if(nearestIntersection!=0){
						delete(nearestIntersection);
					}
					
					nearestIntersection = candidate;
				}
			}
		
		}
	}
	
	return nearestIntersection;
}

void Scene::shadow(Color* color, Intersection* intersection){
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		Vector* l = new Vector(intersection->getPoint(), (*iter)->getSource());
		double distanceToLight = l->norm();
		l->normalize();
		
		Ray* ray = new Ray(intersection->getPoint(), l);
		Intersection* shadowIntersection = getNearestIntersectionExcluding(ray, intersection->getObject());
		
		if(shadowIntersection != 0 && (shadowIntersection->getObject() != intersection->getObject())){
			
			Vector *shadowVect = new Vector(intersection->getPoint(), shadowIntersection->getPoint());
			
			if(shadowVect->norm() <= distanceToLight){
				color->darken(0.3);
			}
			
			delete(shadowVect);
		}
		
		delete(l);
		delete(ray);
		delete(shadowIntersection);
	}
	
	color->normalize();
}

Color* Scene::reflection(Color* color, Ray* ray, Intersection* intersection){
	if(intersection->getObject()->isReflecting()){
		Vector* r = new Vector( (*ray->getDirection()) - ( ((*intersection->getNorm()) * 2.0) * ((*intersection->getNorm()) * ray->getDirection()) ) );
		r->normalize();
		
		Ray* reflected = new Ray(intersection->getPoint(), r);
		Intersection* reflectionIntersection = getNearestIntersectionExcluding(reflected, intersection->getObject());
		
		delete(r);
		
		if(reflectionIntersection != 0){
			
			Color* reflectedColor = reflection(reflectionIntersection->getObject()->getEnlightment()->getColor(reflectionIntersection->getPoint(), reflectionIntersection->getNorm(), reflected, lights), reflected, reflectionIntersection);
			
			delete(reflectionIntersection);
			delete(reflected);
			
			return reflectedColor;
		}
		else{
			
			delete(reflected);
			return background;
		}
	}
	else{
		shadow(color, intersection);
		return color;
	}
}
