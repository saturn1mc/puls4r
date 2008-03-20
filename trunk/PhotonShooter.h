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
	
	static const int MAX_RECURSIONS = 500;
	static const double IRRADIANCE_AREA;
	static const int IRRADIANCE_PHOTON_NUMBER = 1000000;
	
	int currentRecursions;
	
	static const double EPSILON;
	
	int storedDirect;
	int storedIndirect;
	int storedCaustic;
	
	int nbLights;
	int maxPhotons;
	
	PhotonMap* directEnlightment;
	PhotonMap* indirectEnlightment;
	PhotonMap* caustics;
	
	void shootPhoton(Ray* ray, std::list<Light* > lights, std::list<Object * > objects, float energy[3], bool direct, bool indirect, bool caustic);
	Intersection* getNearestIntersection(Ray* ray, std::list<Object * > objects, double _epsilon = EPSILON);
	
	Ray reflectedRay(Ray* ray, Intersection* intersection);
	Ray refractedRay(Ray* ray, Intersection* intersection, std::list<Object * > objects);
	Ray refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double _epsilon = EPSILON);
	
	Vector randomDirection(void) const;
	bool russianRoulette(double d) const;
	void storePhoton(Point* position, Vector* direction, float energy[3], bool direct, bool indirect, bool caustic);
	
	void scaleEnergy(float energy[3], Color* color);
	
public:
	
	PhotonShooter(int _nbLights, int _maxPhotons) : nbLights(_nbLights), maxPhotons(_maxPhotons), directEnlightment(new PhotonMap(_maxPhotons)), indirectEnlightment(new PhotonMap(_maxPhotons)), caustics(new PhotonMap(_maxPhotons)) {
		std::srand(std::time(0));
	}
	
	PhotonShooter(PhotonShooter& photonShooter) : nbLights(photonShooter.nbLights), maxPhotons(photonShooter.maxPhotons), directEnlightment(new PhotonMap(photonShooter.maxPhotons)), indirectEnlightment(new PhotonMap(photonShooter.maxPhotons)), caustics(new PhotonMap(photonShooter.maxPhotons)) {
		std::srand(std::time(0));
	}
	
	PhotonShooter(PhotonShooter* photonShooter) : nbLights(photonShooter->nbLights), maxPhotons(photonShooter->maxPhotons), directEnlightment(new PhotonMap(photonShooter->maxPhotons)), indirectEnlightment(new PhotonMap(photonShooter->maxPhotons)), caustics(new PhotonMap(photonShooter->maxPhotons)) {
		std::srand(std::time(0));
	}
	
	
	~PhotonShooter(void) {
		delete(directEnlightment);
		delete(indirectEnlightment);
		delete(caustics);
	}
	
	void shoot(std::list<Light* > lights, std::list<Object * > objects);
	
	Color irradianceEstimate(Intersection* intersection);
};

#endif //PHOTON_SHOOTER_H
