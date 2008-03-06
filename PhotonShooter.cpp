/*
 *  PhotonShooter.cpp
 *  puls4r
 *
 *  Created by Camille on 06/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PhotonShooter.h"

void PhotonShooter::shootFrom(Light* light, std::list<Object * > objects){
	int shooted = 0;
	int progress = 0;
	double x, y, z;
	
	while(shooted < (maxPhotons / nbLights)){
			
		int done = (int)round(100 * (shooted+1) / (maxPhotons / nbLights));
			
		if(progress != done){
			progress = done;
			std::cout << "\r\tProgress " << progress << "%";
			std::cout.flush();
		}
		
		do{
			x = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
			y = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
			z = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
		}while( (x*x)+(y*y)+(z*z) > 1);
		
		Vector* d = new Vector(x, y, z);
		Ray* ray = new Ray(light->getSource(), d);
		
		//TODO replace "1.0" by light->totalEnergy
		float energy[3] = {(1.0 / ((float)maxPhotons / (float)nbLights)), (1.0 / ((float)maxPhotons / (float)nbLights)), (1.0 / ((float)maxPhotons / (float)nbLights))};
		//---
		
		shootPhoton(ray, objects, energy);
		
		delete(d);
		delete (ray);
		
		shooted++;
	}
}

void PhotonShooter::shootPhoton(Ray* ray, std::list<Object * > objects, float energy[3]){
	Intersection* photonIntersection = getNearestIntersection(ray, objects);
	
	if(photonIntersection != 0){
		if(photonIntersection->getObject()->isReflecting()){
			Ray* reflected = reflectedRay(ray, photonIntersection);
			//TODO take absorption into account
			shootPhoton(reflected, objects, energy);
			delete(reflected);
		}
		
		if(photonIntersection->getObject()->isRefracting()){
			Ray* refracted = refractedRay(ray, photonIntersection, objects);
			//TODO take absorption into account
			shootPhoton(refracted
						, objects, energy);
			delete(refracted);
		}
		
		if(!photonIntersection->getObject()->isReflecting() && !photonIntersection->getObject()->isRefracting()){
			
			float* pos = photonIntersection->getPoint()->toArray();
			
			//ray->getDirection()->invert();
			
			float* dir = ray->getDirection()->toArray();
			
			map->store(energy, pos, dir);
			
			free(pos);
			free(dir);
		}
	}
	
	delete(photonIntersection);
}

Intersection* PhotonShooter::getNearestIntersection(Ray* ray, std::list<Object * > objects, double epsilon){
	
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

Ray* PhotonShooter::reflectedRay(Ray* ray, Intersection* intersection){
	Vector *reflectDirection = new Vector( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	reflectDirection->normalize();
	
	Ray* reflected = new Ray(intersection->getPoint(), reflectDirection);
	
	delete(reflectDirection);
	
	return reflected;
}

Ray* PhotonShooter::refractedRay(Ray* ray, Intersection* intersection, std::list<Object * > objects){
	
	Ray* refracted = 0;
	
	Ray* r1 = refractRay(ray, intersection, 1.0, intersection->getObject()->getN());
	Intersection* refractionIntersection = getNearestIntersection(r1, objects, 0.0001);
	
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

Ray* PhotonShooter::refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon){
	
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
