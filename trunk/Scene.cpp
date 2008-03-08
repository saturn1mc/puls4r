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

void Scene::addBox(Box* box){
	boxes.push_front(box);
}

double Scene::calcFocal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}

void Scene::rayTrace(void){
	
	std::cout << "---> Photon Tracing..." << std::endl;
	shooter = new PhotonShooter(lights.size(), 1000000);
	
	shooter->shoot(lights, objects);
	
	std::cout << std::endl;
	std::cout << "---> Balancing photon map..." << std::endl;
	shooter->getPhotonMap()->balance();
	std::cout << "---> End of photon tracing" << std::endl;
	
	std::cout << "---> Rendering..." << std::endl;
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
	
	currentRecursions = 0;
	Color* oc = observedColor(ray);
	
	delete(target);
	delete(ray);
	
	return oc;
}

Color* Scene::antialiasedColor(double l, double p){
	
	Color* finalColor = 0;
	double cpt = 0;
	double aa = 1.0 / ((double)img->getAntialiasing());
	
	for(double l2 = (l - 1); l2 <= (l + 1); l2+=aa){
		for(double p2 = (p - 1); p2 <= (p + 1); p2+=aa){
			
			cpt++;
			
			if(finalColor == 0){
				finalColor = colorAt(l2, p2);
			}
			else{
				Color* nearColor = colorAt(l2, p2);
				
				*finalColor = (*finalColor) + nearColor;
				
				delete(nearColor);
			}
		}
	}
	
	*finalColor = (*finalColor) * (1.0 / cpt);
	finalColor->normalize();
	
	return finalColor;
}

Color* Scene::observedColor(Ray* ray){
	Color* oc = new Color(background);
	Intersection* nearestIntersection = getNearestIntersection(ray, 0.0001);
	
	currentRecursions++;
	
	if(nearestIntersection == 0){
		return oc;
	}
	else{
	
		Color* objectColor = nearestIntersection->getObject()->getEnlightment()->getColor(nearestIntersection->getPoint(), nearestIntersection->getNormal(), ray, lights);
	
		if((currentRecursions >= MAX_RECURSIONS) || (!nearestIntersection->getObject()->isReflecting() && !nearestIntersection->getObject()->isRefracting())){
			*oc = *objectColor;
			//shadow(oc, nearestIntersection);
			
			/* ---- GLOBAL ILLUMINATION TEST ---- */
			
			float irradiance[3];
			float* pos = nearestIntersection->getPoint()->toArray();
			float* normal = nearestIntersection->getNormal()->toArray();
			
			shooter->getPhotonMap()->irradiance_estimate(irradiance, pos, normal, 10.0, 10.0);
			
			oc->setR(oc->getR() + irradiance[0] );
			oc->setG(oc->getG() + irradiance[1] );
			oc->setB(oc->getB() + irradiance[2] );
			
//			oc->setR( irradiance[0] );
//			oc->setG( irradiance[1] );
//			oc->setB( irradiance[2] );			
			
			oc->normalize();
			
			free(pos);
			free(normal);
			
			/* ------------------------------------- */
		}
		else{
			Color* reflectedColor = 0;
			Color* refractedColor = 0;
	
			if(nearestIntersection->getObject()->isReflecting()){
				
				if(nearestIntersection->getObject()->getGlossyFocal() == 0){
					Ray* reflected = reflectedRay(ray, nearestIntersection);
					reflectedColor = observedColor(reflected);
					
					delete(reflected);
				}
				else{
					reflectedColor = glossyReflection(ray, nearestIntersection);
				}
			
				*reflectedColor = ((*objectColor) * (1.0 - nearestIntersection->getObject()->getKR())) + ((*reflectedColor) * nearestIntersection->getObject()->getKR());
				*oc = (*oc) + reflectedColor;
			}
		
			if(nearestIntersection->getObject()->isRefracting()){
				Ray* refracted = refractedRay(ray, nearestIntersection);
			
				refractedColor = observedColor(refracted);
			
				*refractedColor = ((*objectColor) * (1.0 - nearestIntersection->getObject()->getKT())) + ((*refractedColor) * nearestIntersection->getObject()->getKT());
				*oc = (*oc) + refractedColor;
			
				delete(refracted);
			}
			
			if(nearestIntersection->getObject()->isReflecting() && nearestIntersection->getObject()->isRefracting()){
				*oc = (*oc) * 0.5;
			}

			
			delete(reflectedColor);
			delete(refractedColor);
		}
		
		delete(objectColor);
		
		return oc;
	}
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

Ray* Scene::reflectedRay(Ray* ray, Intersection* intersection){
	Vector *reflectDirection = new Vector( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	reflectDirection->normalize();
			
	Ray* reflected = new Ray(intersection->getPoint(), reflectDirection);
	
	delete(reflectDirection);
	
	return reflected;
}

Color* Scene::glossyReflection(Ray* ray, Intersection* intersection, bool random, double smoothing){
	
	Color* color = new Color();
	
	double cpt = 0;
	
	double f = intersection->getObject()->getGlossyFocal();
	double radius = intersection->getObject()->getGlossyWidth();
	double step = 1.0 / smoothing;
	
	Ray* reflected = reflectedRay(ray, intersection);
	Point* sight = new Point(((*reflected->getDirection()) * f) + intersection->getPoint());
	Observer* virtualObs = new Observer(intersection->getPoint(), sight, M_PI / 4.0);
	
	delete(sight);
	delete(reflected);
	
	for(double i=-radius/2.0; i<radius/2.0; i+= step){
		for(double j=-radius/2.0; j<radius/2.0; j+= step){
			
			Point* target;
			
			if(random){
				double ii = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
				double jj = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
				target = new Point(ii, jj, f);
			}
			else{
				target = new Point(i, j, f);
			}
			
			Ray* glossyRay = virtualObs->ray(target);
			Intersection* glossyIntersection = getNearestIntersection(glossyRay);
			
			if(glossyIntersection != 0){
				
				Color* glossyColor = observedColor(glossyRay);
				
				*color = (*color) + glossyColor;
				cpt++;
				
				delete(glossyColor);
			}
			
			delete(glossyIntersection);
			delete(glossyRay);
		}
	}
	
	delete(virtualObs);

	*color = (*color) * (1.0 / cpt);
	color->normalize();
	
	return color;
}

Ray* Scene::refractedRay(Ray* ray, Intersection* intersection){
	
	Ray* refracted = 0;
	
	Ray* r1 = refractRay(ray, intersection, 1.0, intersection->getObject()->getN());
	Intersection* refractionIntersection = getNearestIntersection(r1, 0.0001);
			
	if(refractionIntersection != 0){
		if(refractionIntersection->getObject() == intersection->getObject()){
			refractionIntersection->getNormal()->invert();
			Ray* r2 = refractRay(r1, refractionIntersection, intersection->getObject()->getN(), 1.0);
			refracted = new Ray(r2);
			
			delete(r2);
		}
		else{
			refracted = new Ray(r1);
		}
	}
	else{
		refracted = new Ray(r1);
	}
	
	delete(refractionIntersection);
	delete(r1);
	
	return refracted;
}

Ray* Scene::refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon){
	
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

void Scene::shadow(Color* color, Intersection* intersection, bool random, double smoothing){
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		
		double enlighted = 0;
		double shadowed = 0;
		double radius = (*iter)->getRadius();
		double step = 1.0 / smoothing;
		
		Vector* distanceTolight = new Vector(intersection->getPoint(), (*iter)->getSource());
		Observer* virtualObs = new Observer(intersection->getPoint(), (*iter)->getSource(), M_PI / 4.0);
		double f = distanceTolight->norm();
		
		delete(distanceTolight);
		
		for(double i=-radius/2.0; i<radius/2.0; i+= step){
			for(double j=-radius/2.0; j<radius/2.0; j+= step){
				
				Point* target;
				
				if(random){
					double ii = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
					double jj = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
					target = new Point(ii, jj, f);
				}
				else{
					target = new Point(i, j, f);
				}
				
				Ray* shadowRay = virtualObs->ray(target);
				Intersection* shadowIntersection = getNearestIntersection(shadowRay);
				
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
				
				delete(shadowRay);
				delete(shadowIntersection);
				delete(target);
			}
		}
		
		delete(virtualObs);
		
		if(shadowed > 0){
			color->scale(std::min(1.0, (enlighted / (shadowed + enlighted)) + 0.3));
			color->normalize();
		}
	}
	
	color->normalize();
}
