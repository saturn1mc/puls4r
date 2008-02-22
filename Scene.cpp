/*
 *  Scene.cpp
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
		
		Color* color = new Color();
		
		if(nearestIntersection->getObject()->isReflecting() || nearestIntersection->getObject()->isRefracting()){
			
			Color* reflectionColor;
			Color* refractionColor;
			
			if(nearestIntersection->getObject()->isReflecting()){
				
				if(nearestIntersection->getObject()->getGlossyFocal() > 0.0){
					reflectionColor = reflectionGlossy(ray, nearestIntersection);
				}
				else{
					reflectionColor = reflection(ray, nearestIntersection);
				}
			}
			else{
				reflectionColor = new Color(); //black
			}
			
			if(nearestIntersection->getObject()->isRefracting()){
				refractionColor = refraction(ray, nearestIntersection, 1.0, nearestIntersection->getObject()->getN());
			}
			else{
				refractionColor = new Color(); //black
			}
			
			*color = (*refractionColor) + reflectionColor;
			if(nearestIntersection->getObject()->isReflecting() && nearestIntersection->getObject()->isRefracting()){
				*color = (*color) * 0.5;
			}
			
			delete(reflectionColor);
			delete(refractionColor);
		}
		else{
			Color* objectColor = nearestIntersection->getObject()->getEnlightment()->getColor(nearestIntersection->getPoint(), nearestIntersection->getNormal(), ray, lights);
			*color = *objectColor;
			
			shadow(color, nearestIntersection);
			
			delete(objectColor);
		}
		
		delete(nearestIntersection);
		delete(ray);
		delete(target);
		
		return color;
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
				if(nearestIntersection != 0){
					delete(nearestIntersection);
				}
				
				nearestIntersection = candidate;
			}
			else{
				delete(candidate);
			}
		}
	}
	
	return nearestIntersection;
}

Intersection* Scene::getNearestIntersection(Ray* ray, double epsilon){
	
	Intersection* nearestIntersection = 0;
	
	for(std::list<Object* >::iterator iter = objects.begin(); iter != objects.end(); ++iter){
		
		Intersection* candidate = (*iter)->intersection(ray);
		
		if(candidate != 0){
			if((nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()) && (candidate->getT() > epsilon)){
				if(nearestIntersection != 0){
					delete(nearestIntersection);
				}
				
				nearestIntersection = candidate;
			}
			else{
				delete(candidate);
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
					if(nearestIntersection != 0){
						delete(nearestIntersection);
					}
					
					nearestIntersection = candidate;
				}
				else{
					delete(candidate);
				}
			}
		}
	}
	
	return nearestIntersection;
}

void Scene::shadow(Color* color, Intersection* intersection, double smoothing){
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		
		double enlighted = 0;
		double shadowed = 0;
		double radius = (*iter)->getRadius();
		double step = radius / smoothing;
		
		Vector* distanceTolight = new Vector(intersection->getPoint(), (*iter)->getSource());
		Observer* virtualObs = new Observer(intersection->getPoint(), (*iter)->getSource(), M_PI / 4.0);
		double f = distanceTolight->norm();
		
		for(double i=-radius; i<radius; i+= step){
			for(double j=-radius; j<radius; j+= step){
				Point* target = new Point(i, j, f);
				Ray* ray = virtualObs->ray(target);
				Intersection* shadowIntersection = getNearestIntersectionExcluding(ray, intersection->getObject());
				
				if(shadowIntersection != 0){
					
					Vector *shadowVect = new Vector(intersection->getPoint(), shadowIntersection->getPoint());
					
					if(shadowVect->norm() <= f){
						shadowed++;
					}
					else{
						enlighted++;
					}
					
					delete(shadowVect);
				}
				else{
					enlighted++;
				}
				
				delete(ray);
				delete(shadowIntersection);
				delete(target);
			}
		}
		
		color->darken(enlighted / (shadowed + enlighted));
		
		delete(virtualObs);
		delete(distanceTolight);
	}
	
	color->normalize();
}

Color* Scene::reflection(Ray* ray, Intersection* intersection){
	
	Color* color = new Color();
	
	if(intersection == 0){
		*color = background;
	}
	else{
		
		Color* objectColor = intersection->getObject()->getEnlightment()->getColor(intersection->getPoint(), intersection->getNormal(), ray, lights);
		
		if(intersection->getObject()->isReflecting()){
			
			Vector *reflectDirection = new Vector( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
			reflectDirection->normalize();
			
			Ray* reflected = new Ray(intersection->getPoint(), reflectDirection);
			
			Intersection* reflectionIntersection = getNearestIntersectionExcluding(reflected, intersection->getObject());
			
			Color* reflectedColor = reflection(reflected, reflectionIntersection);
			
			*color = ((*objectColor) * (1.0 - intersection->getObject()->getKR())) + ((*reflectedColor) * intersection->getObject()->getKR());
			
			delete(reflectDirection);
			delete(reflected);
			delete(reflectionIntersection);
			delete(reflectedColor);
		}
		
		if(intersection->getObject()->isRefracting() && !intersection->getObject()->isReflecting()){
			Color* refractedColor = refraction(ray, intersection, 1.0, intersection->getObject()->getN());
			*color = (*color) + refractedColor;
			delete(refractedColor);
		}
		
		if(!intersection->getObject()->isReflecting() && !intersection->getObject()->isRefracting()){
			*color = objectColor;
			shadow(color, intersection);
		}
		
		delete(objectColor);
	}
	
	return color;
}

Color* Scene::reflectionGlossy(Ray* ray, Intersection* intersection, double smoothing){
	
	Color* color = new Color();
	double f = intersection->getObject()->getGlossyFocal();
	double radius = intersection->getObject()->getGlossyWidth();
	double step = intersection->getObject()->getGlossyWidth() / smoothing;
	
	Vector *reflectDirection = new Vector( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	reflectDirection->normalize();
	
	Ray* reflected = new Ray(intersection->getPoint(), reflectDirection);
	
	delete(reflectDirection);
	
	Point* sight = new Point(((*reflected->getDirection()) * f) + intersection->getPoint());
	Observer* virtualObs = new Observer(intersection->getPoint(), sight, M_PI / 4.0);
	
	for(double i=-radius; i<radius; i+= step){
		for(double j=-radius; j<radius; j+= step){
			Point* target = new Point(i, j, f);
			Ray* glossyRay = virtualObs->ray(target);
			Intersection* glossyIntersection = getNearestIntersectionExcluding(glossyRay, intersection->getObject());
			
			if(glossyIntersection != 0){
				
				Color* glossyColor = glossyIntersection->getObject()->getEnlightment()->getColor(glossyIntersection->getPoint(), glossyIntersection->getNormal(), glossyRay, lights);
				
				//TODO take into account multiple reflections && refractions
				
				
				*color = (*color) + glossyColor;
				*color = (*color) * 0.5;
				
				delete(glossyColor);
			}
		}
	}
	
	delete(reflected);
	delete(virtualObs);

	return color;
}

Ray* Scene::getRefractedRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon){
	
	double n = n2 / n1;
	double cosT = (*intersection->getNormal()) * ray->getDirection();
	double sinT2 = 1.0 - ((1.0  - cosT * cosT ) / ( n * n ));
	
	Ray* refracted;
	Vector* refractDirection;
	Point* origin;
	
	if(sinT2 > 0){
		//refraction
		refractDirection = new Vector( (( (*ray->getDirection()) - ( (*intersection->getNormal()) * cosT ) ) * (1.0 / n)) - ( (*intersection->getNormal()) * sqrt(sinT2) ));
	}
	else{
		//reflexion
		refractDirection = new Vector( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	}
	
	origin = new Point(((*refractDirection) * epsilon) + intersection->getPoint());
	refracted = new Ray(origin, refractDirection);
	
	delete(origin);
	delete(refractDirection);
	
	return refracted;
}


Color* Scene::refraction(Ray* ray, Intersection* intersection, double n1, double n2){
	Color* color = new Color();
	
	if(intersection == 0){
		*color = background;
	}
	else{
		Color* objectColor = intersection->getObject()->getEnlightment()->getColor(intersection->getPoint(), intersection->getNormal(), ray, lights);
		
		if(intersection->getObject()->isRefracting()){
			Ray* refracted = getRefractedRay(ray, intersection, n1, n2);
			Color* refractedColor;
			Intersection* refractionIntersection = getNearestIntersection(refracted, 0.0001);
			
			if(refractionIntersection != 0){
				if(refractionIntersection->getObject() == intersection->getObject()){
					refractionIntersection->getNormal()->invert();
					Ray* refracted2 = getRefractedRay(refracted, refractionIntersection, n2, n1);
					
					Intersection* refractionIntersection2 = getNearestIntersection(refracted2, 0.0001);
					
					if(refractionIntersection2 != 0){
						refractedColor = refraction(refracted2, refractionIntersection2, 1.0, refractionIntersection2->getObject()->getN());
					}
					else{
						refractedColor = new Color(background);
					}
					
					delete(refracted2);
					delete(refractionIntersection2);
				}
				else{
					refractedColor = refraction(refracted, refractionIntersection, 1.0, refractionIntersection->getObject()->getN());
				}
			}
			else{
				refractedColor = new Color(background);
			}	
			
			*color = ((*objectColor) * (1.0 - intersection->getObject()->getKT())) + ((*refractedColor) * intersection->getObject()->getKT());;
			
			delete(refractedColor);
			delete(refractionIntersection);
			delete(refracted);
		}
		
		if(intersection->getObject()->isReflecting() && !intersection->getObject()->isRefracting()){
			Color* reflectedColor = reflection(ray, intersection);
			*color = (*color) + reflectedColor;
			delete(reflectedColor);
		}
		
		if(!intersection->getObject()->isReflecting() && !intersection->getObject()->isRefracting()){
			*color = objectColor;
			shadow(color, intersection);
		}
		
		delete(objectColor);
	}
	
	return color;
}
