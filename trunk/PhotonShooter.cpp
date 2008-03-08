/*
 *  PhotonShooter.cpp
 *  puls4r
 *
 *  Created by Camille on 06/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PhotonShooter.h"

void PhotonShooter::shoot(std::list<Light* > lights, std::list<Object * > objects){
	
	int lightNum = 0;
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		lightNum++;
		
		int shooted = 0;
		int progress = 0;
		double x, y, z;
		
		stored = 0;
		
		while(shooted < (maxPhotons / nbLights)){
			
			int done = (int)round(100 * (shooted+1) / (maxPhotons / nbLights));
			
			if(progress != done){
				progress = done;
				std::cout << "\r\tLight (" << lightNum << "/" << lights.size() << ") : " << progress << "%";
				std::cout.flush();
			}
			
			/*
			 * Random emission from diffuse point light 
			 * As described by Henrik Wann Jensen
			 */
			do{
				x = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
				y = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
				z = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
			}while( (x*x)+(y*y)+(z*z) > 1);
			
			
			Vector* d = new Vector(x, y, z);
			Ray* ray = new Ray((*iter)->getSource(), d);
			
			//TODO replace initial energy by light->totalEnergy * color
			float energy[3] = {100.0, 100.0, 100.0};
			//---
			
			shootPhoton(ray, lights, objects, energy, false);
			shooted++;
			
			delete(d);
			delete (ray);
		}
		
		if(stored != 0){
			map->scale_photon_power(1.0 / stored);
		}
	}
}

bool PhotonShooter::russianRoulette(double d) const{
	double epsilon = ((double)std::rand() / (double)RAND_MAX); //epsilon is in [0, 1]
	
	if(epsilon < d){
		//Photon continues course
		return false;
	}
	else{
		//Absorption
		return true;
	}
}

void PhotonShooter::shootPhoton(Ray* ray, std::list<Light * > lights, std::list<Object * > objects, float energy[3], bool indirect){
	
	//TODO take object color into account for refraction
	//TODO split refraction coeff for all waves (r, g and b)
	
	Intersection* photonIntersection = getNearestIntersection(ray, objects);
	
	if(photonIntersection != 0){
		if(photonIntersection->getObject()->isReflecting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKR())){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
			}
			else{
				Ray* reflected = reflectedRay(ray, photonIntersection);
				shootPhoton(reflected, lights, objects, energy, true);
				delete(reflected);
			}
		}
		
		if(photonIntersection->getObject()->isRefracting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKT())){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
			}
			else{
				
				float energy2[3];
				
				//TODO refraction index -> array[3] (r,g,b)
				
				//Red
				photonIntersection->getObject()->setRefracting(true, 1.5, 1.0);
				
				energy2[0] *= energy[0] * 1.0;
				energy2[1] *= energy[1] * 0.0;
				energy2[2] *= energy[2] * 0.0;
				
				Ray* refracted = refractedRay(ray, photonIntersection, objects);
				shootPhoton(refracted, lights, objects, energy2, true);
				delete(refracted);
				
				
				//Green
				
				energy2[0] *= energy[0] * 0.0;
				energy2[1] *= energy[1] * 1.0;
				energy2[2] *= energy[2] * 0.0;
				
				photonIntersection->getObject()->setRefracting(true, 1.4, 1.0);
				
				refracted = refractedRay(ray, photonIntersection, objects);
				shootPhoton(refracted, lights, objects, energy2, true);
				delete(refracted);
				
				//Blue
				energy2[0] *= energy[0] * 0.0;
				energy2[1] *= energy[1] * 0.0;
				energy2[2] *= energy[2] * 1.0;
				
				photonIntersection->getObject()->setRefracting(true, 1.3, 1.0);
				
				refracted = refractedRay(ray, photonIntersection, objects);
				shootPhoton(refracted, lights, objects, energy2, true);
				delete(refracted);
			}
			
		}
		
		if(indirect && !photonIntersection->getObject()->isReflecting() && !photonIntersection->getObject()->isRefracting()){
			
			if(russianRoulette(0.5)){
				Color* objectColor = photonIntersection->getObject()->getEnlightment()->getColor(photonIntersection->getPoint(), photonIntersection->getNormal(), ray, lights);
				
				energy[0] *= (float)objectColor->getR();
				energy[1] *= (float)objectColor->getG();
				energy[2] *= (float)objectColor->getB();
				
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
				delete(objectColor);
			}
			else{
				//TODO random reflection
			}
		}
	}
	
	delete(photonIntersection);
}

void PhotonShooter::storePhoton(Point* position, Vector* direction, float energy[3]){
	float* pos = position->toArray();
	float* dir = direction->toArray();
	
	map->store(energy, pos, dir);
	stored++;
	
	free(pos);
	free(dir);
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
