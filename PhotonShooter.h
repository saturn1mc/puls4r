/*
 *  PhotonShooter.h
 *  puls4r
 *
 *  Created by Camille on 06/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PHOTON_SHOOTER_H
#define PHOTON_SHOOTER_H

#include <list>

#include "PhotonMap.h"
#include "Light.h"
#include "Ray.h"
#include "Intersection.h"
#include "Object.h"

class PhotonShooter{

private:
	
	int stored;
	int nbLights;
	int maxPhotons;
	PhotonMap* map;
	
	void shootPhoton(Ray* ray, std::list<Light* > lights, std::list<Object * > objects, float energy[3], bool canStore = true);
	Intersection* getNearestIntersection(Ray* ray, std::list<Object * > objects, double epsilon = 0.000001);
	
	Ray* reflectedRay(Ray* ray, Intersection* intersection);
	Ray* refractedRay(Ray* ray, Intersection* intersection, std::list<Object * > objects);
	Ray* refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon = 0.000001);
	
	Vector* randomDirection(void) const;
	bool russianRoulette(double d) const;
	void storePhoton(Point* position, Vector* direction, float energy[3]);
	
	void scaleEnergy(float energy[3], Color* color);
	
public:
	
	PhotonShooter(int _nbLights, int _maxPhotons) : nbLights(_nbLights), maxPhotons(_maxPhotons), map(new PhotonMap(_maxPhotons)) {
		std::srand(std::time(0));
	}
	
	PhotonShooter(PhotonShooter& photonShooter) : nbLights(photonShooter.nbLights), maxPhotons(photonShooter.maxPhotons), map(new PhotonMap(photonShooter.maxPhotons)) {
		std::srand(std::time(0));
	}
	
	PhotonShooter(PhotonShooter* photonShooter) : nbLights(photonShooter->nbLights), maxPhotons(photonShooter->maxPhotons), map(new PhotonMap(photonShooter->maxPhotons)) {
		std::srand(std::time(0));
	}
	
	
	~PhotonShooter(void) {
		delete(map);
	}
	
	void shoot(std::list<Light* > lights, std::list<Object * > objects);
	
	PhotonMap* getPhotonMap(void) const{
		return map;
	}
};

#endif //PHOTON_SHOOTER_H
