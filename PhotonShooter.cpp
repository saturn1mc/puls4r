/*
 *  PhotonShooter.cpp
 *  puls4r
 *
 *  Created by Camille on 06/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PhotonShooter.h"

const double PhotonShooter::epsilon = 0.000001;

void PhotonShooter::shoot(std::list<Light* > lights, std::list<Object * > objects){
	
	int lightNum = 0;
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		lightNum++;
		
		int shooted = 0;
		int progress = 0;
		
		
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
			Vector randDir = randomDirection();
			Ray ray((*iter)->getSource(), &randDir);
			
			float energy[3] = {	(*iter)->getPower() * (*iter)->getColor()->getR(), 
								(*iter)->getPower() * (*iter)->getColor()->getG(), 
								(*iter)->getPower() * (*iter)->getColor()->getB()};
			
			shootPhoton(&ray, lights, objects, energy);
			shooted++;
		}
		
		if(stored != 0){
			map->scale_photon_power(1.0 / stored);
		}
		
		std::cout << std::endl;
	}
	
	std::cout << "---> Balancing photon map..." << std::endl;
	map->balance();
}

Vector PhotonShooter::randomDirection(void) const{
	
	double x, y, z;
	
	do{
		x = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
		y = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
		z = (((double)std::rand() / (double)RAND_MAX) * 2.0) - 1.0;
	}while( (x*x)+(y*y)+(z*z) > 1);
	
	Vector randDir(x, y, z);
	
	return randDir;
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

void PhotonShooter::shootPhoton(Ray* ray, std::list<Light * > lights, std::list<Object * > objects, float energy[3], bool canStore){
	
	//TODO take object color into account for refraction
	//TODO split refraction coeff for all waves (r, g and b)
	
	Intersection* photonIntersection = getNearestIntersection(ray, objects);
	
	if(photonIntersection != 0){
		if(photonIntersection->getObject()->isReflecting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKR())){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
			}
			else{
				Ray reflected = reflectedRay(ray, photonIntersection);
				shootPhoton(&reflected, lights, objects, energy);
			}
		}
		
		if(photonIntersection->getObject()->isRefracting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKT())){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
			}
			else{
				Ray refracted = refractedRay(ray, photonIntersection, objects);
				shootPhoton(&refracted, lights, objects, energy);
			}
			
		}
		
		if(canStore && !photonIntersection->getObject()->isReflecting() && !photonIntersection->getObject()->isRefracting()){
			
			Color objectColor = photonIntersection->getObject()->getEnlightment()->getColor(photonIntersection->getPoint(), photonIntersection->getNormal(), ray, lights);
			scaleEnergy(energy, &objectColor);
			
			storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy);
			
			if(!russianRoulette(photonIntersection->getObject()->getKR())){
				
				Vector randDir = randomDirection();
				Ray reflected(photonIntersection->getPoint(), &randDir);
				shootPhoton(&reflected, lights, objects, energy, true);
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

void PhotonShooter::scaleEnergy(float energy[3], Color* color){
	energy[0] *= (float)color->getR();
	energy[1] *= (float)color->getG();
	energy[2] *= (float)color->getB();
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

Ray PhotonShooter::reflectedRay(Ray* ray, Intersection* intersection){
	Vector reflectDirection( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	reflectDirection.normalize();
	
	Point origin((reflectDirection * epsilon) + intersection->getPoint());
	Ray reflected(&origin, &reflectDirection);
	
	return reflected;
}

Ray PhotonShooter::refractedRay(Ray* ray, Intersection* intersection, std::list<Object * > objects){
	
	Ray r1 = refractRay(ray, intersection, 1.0, intersection->getObject()->getN());
	Intersection* refractionIntersection = getNearestIntersection(&r1, objects);
	
	if(refractionIntersection != 0){
		if(refractionIntersection->getObject() == intersection->getObject()){
			refractionIntersection->getNormal()->invert();
			return refractRay(&r1, refractionIntersection, intersection->getObject()->getN(), 1.0);
		}
		else{
			return r1;
		}
	}
	else{
		return r1;
	}
}

Ray PhotonShooter::refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon){
	
	double n = n2 / n1;
	double cosT = (*intersection->getNormal()) * ray->getDirection();
	double sinT2 = 1.0 - ((1.0  - cosT * cosT ) / ( n * n ));
	
	Vector refractDirection;
	
	if(sinT2 > 0){
		//refraction
		refractDirection = ( (( (*ray->getDirection()) - ( (*intersection->getNormal()) * cosT ) ) * (1.0 / n)) - ( (*intersection->getNormal()) * sqrt(sinT2) ));
	}
	else{
		//reflexion
		refractDirection = ( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	}
	
	Point origin((refractDirection * epsilon) + intersection->getPoint());
	Ray refracted(&origin, &refractDirection);
	
	return refracted;
}

