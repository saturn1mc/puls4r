/*
 *  PhotonShooter.cpp
 *  puls4r
 *
 *  Created by Camille on 06/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PhotonShooter.h"

const double PhotonShooter::EPSILON = 0.000001;
const double PhotonShooter::IRRADIANCE_AREA = 1.5;

void PhotonShooter::shoot(std::list<Light* > lights, std::list<Object * > objects){
	
	int lightNum = 0;
	
	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){
		lightNum++;
		
		int progress = 0;
		
		storedDirect = 0;
		storedIndirect = 0;
		storedCaustic = 0;
		
		while((storedDirect + storedIndirect + storedCaustic) < (maxPhotons / nbLights)){
			
			int done = (int)round(100 * ((storedDirect + storedIndirect + storedCaustic)+1) / (maxPhotons / nbLights));
			
			if(progress != done){
				progress = done;
				std::cout << "\r\tLight (" << lightNum << "/" << lights.size() << ") : " << progress << "%";
				std::cout.flush();
			}
			
			Vector randDir = randomDirection();
			Ray ray((*iter)->getSource(), &randDir);
			
			float energy[3] = {	(*iter)->getPower() * (*iter)->getColor()->getR(), 
								(*iter)->getPower() * (*iter)->getColor()->getG(), 
								(*iter)->getPower() * (*iter)->getColor()->getB()};
			
			currentRecursions = 0;
			shootPhoton(&ray, lights, objects, energy, true, false, false);
		}
		
		/* Photons energy scaling */
		if(storedDirect != 0){
			directEnlightment->scale_photon_power(1.0 / storedDirect);
		}
		
		if(storedIndirect != 0){
			indirectEnlightment->scale_photon_power(1.0 / storedIndirect);
		}
		
		if(storedCaustic != 0){
			caustics->scale_photon_power(1.0 / storedCaustic);
		}
		
		std::cout << std::endl;
	}
	
	std::cout << "---> Balancing direct photon map..." << std::endl;
	directEnlightment->balance();
	
	std::cout << "---> Balancing indirect photon map..." << std::endl;
	indirectEnlightment->balance();
	
	std::cout << "---> Balancing caustic photon map..." << std::endl;
	caustics->balance();
}

/*
 * Random emission from diffuse point light 
 * As described by Henrik Wann Jensen
 */
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
	double e = ((double)std::rand() / (double)RAND_MAX); //e is in [0, 1]
	
	if(e < d){
		//Photon continues course
		return false;
	}
	else{
		//Absorption
		return true;
	}
}

void PhotonShooter::shootPhoton(Ray* ray, std::list<Light * > lights, std::list<Object * > objects, float energy[3], bool direct, bool indirect, bool caustic){
	
	//TODO split refraction coeff for all waves (r, g and b)
	currentRecursions++;
	
	Intersection* photonIntersection = getNearestIntersection(ray, objects);
	
	if(photonIntersection != 0){
		if(photonIntersection->getObject()->isReflecting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKR()) || (currentRecursions >= MAX_RECURSIONS)){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy, direct, indirect, caustic);
			}
			else{
				Ray reflected = reflectedRay(ray, photonIntersection);
				shootPhoton(&reflected, lights, objects, energy, false, true, false);
			}
		}
		
		if(photonIntersection->getObject()->isRefracting()){
			
			if(russianRoulette(photonIntersection->getObject()->getKT()) || (currentRecursions >= MAX_RECURSIONS)){
				storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy, direct, indirect, caustic);
			}
			else{
				Ray refracted = refractedRay(ray, photonIntersection, objects);
				shootPhoton(&refracted, lights, objects, energy, false, false, true);
			}
			
		}
		
		if(!photonIntersection->getObject()->isReflecting() && !photonIntersection->getObject()->isRefracting()){
			
			Color objectColor = photonIntersection->getObject()->getEnlightment()->getColor(photonIntersection->getPoint(), photonIntersection->getNormal(), ray, lights);
			scaleEnergy(energy, &objectColor);
			
			storePhoton(photonIntersection->getPoint(), ray->getDirection(), energy, direct, indirect, caustic);
			
			if(!russianRoulette(photonIntersection->getObject()->getKR()) && !(currentRecursions >= MAX_RECURSIONS)){
				Vector randDir = randomDirection();
				Ray reflected(photonIntersection->getPoint(), &randDir);
				shootPhoton(&reflected, lights, objects, energy, false, true, false);
			}
		}
	}
	
	delete(photonIntersection);
}

void PhotonShooter::storePhoton(Point* position, Vector* direction, float energy[3], bool direct, bool indirect, bool caustic){
	float* pos = position->toArray();
	float* dir = direction->toArray();
	
	if(direct){
		storedDirect++;
		directEnlightment->store(energy, pos, dir);
	}
	
	if(indirect){
		storedIndirect++;
		indirectEnlightment->store(energy, pos, dir);
	}
	
	if(caustic){
		storedCaustic++;
		caustics->store(energy, pos, dir);
	}
	
	free(pos);
	free(dir);
}

void PhotonShooter::scaleEnergy(float energy[3], Color* color){
	energy[0] *= (float)color->getR();
	energy[1] *= (float)color->getG();
	energy[2] *= (float)color->getB();
}

Color PhotonShooter::irradianceEstimate(Intersection* intersection){
	Color color;
	
	float *irradiance = (float*) malloc(3*sizeof(float));
	float* pos = intersection->getPoint()->toArray();
	float* normal = intersection->getNormal()->toArray();
	
	//Direct enlightment component
	irradiance[0] = 0;
	irradiance[1] = 0;
	irradiance[2] = 0;
	
	directEnlightment->irradiance_estimate(irradiance, pos, normal, IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
	
	color.setR(color.getR() + (double)irradiance[0]);
	color.setG(color.getG() + (double)irradiance[1]);
	color.setB(color.getB() + (double)irradiance[2]);			
	
	//Indirect enlightment component
	irradiance[0] = 0;
	irradiance[1] = 0;
	irradiance[2] = 0;
	
	indirectEnlightment->irradiance_estimate(irradiance, pos, normal, IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
	
	color.setR(color.getR() + (double)irradiance[0]);
	color.setG(color.getG() + (double)irradiance[1]);
	color.setB(color.getB() + (double)irradiance[2]);	
	
	//Caustics component
	irradiance[0] = 0;
	irradiance[1] = 0;
	irradiance[2] = 0;
	
	caustics->irradiance_estimate(irradiance, pos, normal, IRRADIANCE_AREA, IRRADIANCE_PHOTON_NUMBER);
	
	color.setR(color.getR() + (double)irradiance[0]);
	color.setG(color.getG() + (double)irradiance[1]);
	color.setB(color.getB() + (double)irradiance[2]);	
	
	
	free(irradiance);
	free(pos);
	free(normal);
	
	color.normalize();
	
	return color;
}

Intersection* PhotonShooter::getNearestIntersection(Ray* ray, std::list<Object * > objects, double _epsilon){
	
	Intersection* nearestIntersection = 0;
	
	for(std::list<Object* >::iterator iter = objects.begin(); iter != objects.end(); ++iter){
		
		Intersection* candidate = (*iter)->intersection(ray);
		
		if(candidate != 0){
			if((nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()) && (candidate->getT() > _epsilon)){
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
	
	Point origin((reflectDirection * EPSILON) + intersection->getPoint());
	Ray reflected(&origin, &reflectDirection);
	
	return reflected;
}

Ray PhotonShooter::refractedRay(Ray* ray, Intersection* intersection, std::list<Object * > objects){
	
	Ray r1 = refractRay(ray, intersection, 1.0, intersection->getObject()->getN());
	Intersection* refractionIntersection = getNearestIntersection(&r1, objects);
	
	if(refractionIntersection != 0){
		if(refractionIntersection->getObject() == intersection->getObject()){
			refractionIntersection->getNormal()->invert();
			
			Ray r2 = refractRay(&r1, refractionIntersection, intersection->getObject()->getN(), 1.0);
			
			delete(refractionIntersection);
			return r2;
		}
		else{
			
			delete(refractionIntersection);
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

