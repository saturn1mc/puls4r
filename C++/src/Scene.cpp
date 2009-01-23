/*
 *  Scene.cpp
 *  puls4r
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene.h"

const double Scene::EPSILON = 0.000001;
const double Scene::SMOOTHING = 4.0;

void Scene::addObject(Object* obj){
	objects.push_front(obj);
}

void Scene::addLight(Light* light){
	lights.push_front(light);
}

void Scene::addBox(Box* box){
	boxes.push_front(box);
}

/**************************/
/* Global Functions       */
/**************************/

double Scene::calcFocal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}

void Scene::trace(int mode){

	if(observer != 0 && image !=0 && background !=0){
		switch(mode){
			case RAYCASTING_MODE:
				rayCasting();

				break;

			case PHOTONMAPPING_MODE:
				photonMapping();

				break;

			default:
				std::cerr << "Unknown mode " << mode << " for tracing" << std::endl;
		}
	}
	else{
		std::cerr << "Can't trace Scene : attributes uninitialized (check observer, image and background color)" << std::endl;
	}
}

Color Scene::antialiasedColor(double l, double p, int mode){

	Color finalColor;
	double cpt = 0;
	double aa = 1.0 / ((double)image->getAntialiasing());

	for(double l2 = (l - 1); l2 <= (l + 1); l2+=aa){
		for(double p2 = (p - 1); p2 <= (p + 1); p2+=aa){

			finalColor = finalColor + colorAt(l2, p2, mode);
			cpt++;

		}
	}

	finalColor = finalColor * (1.0 / cpt);
	finalColor.normalize();

	return finalColor;
}

Color Scene::colorAt(double l, double p, int mode){

	Point target(p, l, focal);
	Ray ray = observer->ray(&target);

	currentRecursions = 0;

	return observedColor(&ray, mode);
}

Color Scene::observedColor(Ray* ray, int mode){
	Color oc (background);
	Intersection* nearestIntersection = getNearestIntersection(ray);

	currentRecursions++;

	if(nearestIntersection == 0){
		return oc;
	}
	else{

		Color objectColor = nearestIntersection->getObject()->getEnlightment()->getColor(nearestIntersection->getPoint(), nearestIntersection->getNormal(), ray, lights);

		if((currentRecursions >= MAX_RECURSIONS) || (!nearestIntersection->getObject()->isReflecting() && !nearestIntersection->getObject()->isRefracting())){

			switch(mode){
				case RAYCASTING_MODE :
					oc = objectColor;
					shadow(&oc, nearestIntersection);

					break;

				case PHOTONMAPPING_MODE:

					oc = shooter->irradianceEstimate(nearestIntersection);

					break;

				default:
					std::cerr << "Unknown mode " << mode << " for tracing" << std::endl;
			}
		}
		else{
			Color reflectedColor;
			Color refractedColor;

			if(nearestIntersection->getObject()->isReflecting()){

				if(nearestIntersection->getObject()->getGlossyFocal() == 0){
					Ray reflected = reflectedRay(ray, nearestIntersection);
					reflectedColor = observedColor(&reflected, mode);
				}
				else{
					reflectedColor = glossyReflection(ray, nearestIntersection, mode);
				}

				reflectedColor = (objectColor * (1.0 - nearestIntersection->getObject()->getKR())) + (reflectedColor * nearestIntersection->getObject()->getKR());
				oc = oc + reflectedColor;
			}

			if(nearestIntersection->getObject()->isRefracting()){
				Ray refracted = refractedRay(ray, nearestIntersection);

				refractedColor = observedColor(&refracted, mode);

				refractedColor = (objectColor * (1.0 - nearestIntersection->getObject()->getKT())) + (refractedColor * nearestIntersection->getObject()->getKT());
				oc = oc + refractedColor;
			}

			if(nearestIntersection->getObject()->isReflecting() && nearestIntersection->getObject()->isRefracting()){
				oc = oc * 0.5;
			}
		}

		delete(nearestIntersection);

		return oc;
	}
}

Intersection* Scene::getNearestIntersection(Ray* ray, double _epsilon){

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

Intersection* Scene::getNearestShadowIntersection(Ray* ray, double _epsilon){

	Intersection* nearestIntersection = 0;

	for(std::list<Object* >::iterator iter = objects.begin(); iter != objects.end(); ++iter){

		Intersection* candidate = (*iter)->intersection(ray);

		if(candidate != 0){
			if((nearestIntersection == 0 || nearestIntersection->getT() > candidate->getT()) && (!candidate->getObject()->isRefracting()) && (candidate->getT() > _epsilon)){
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

Ray Scene::reflectedRay(Ray* ray, Intersection* intersection){
	Vector reflectDirection( (*ray->getDirection()) - ( ((*intersection->getNormal()) * 2.0) * ((*intersection->getNormal()) * ray->getDirection()) ) );
	reflectDirection.normalize();

	Point origin((reflectDirection * EPSILON) + intersection->getPoint());
	Ray reflected(&origin, &reflectDirection);

	return reflected;
}

Color Scene::glossyReflection(Ray* ray, Intersection* intersection, int mode, bool random, double _smoothing){

	Color color;

	double cpt = 0;

	double f = intersection->getObject()->getGlossyFocal();
	double radius = intersection->getObject()->getGlossyWidth();
	double step = 1.0 / _smoothing;

	Ray reflected = reflectedRay(ray, intersection);
	Point sight(((*reflected.getDirection()) * f) + intersection->getPoint());
	Observer virtualObs(intersection->getPoint(), &sight, M_PI / 4.0);

	for(double i=-radius/2.0; i<radius/2.0; i+= step){
		for(double j=-radius/2.0; j<radius/2.0; j+= step){

			Point target;

			if(random){
				double ii = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
				double jj = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
				Point temp(ii, jj, f);

				target = temp;
			}
			else{
				Point temp(i, j, f);

				target = temp;
			}

			Ray glossyRay = virtualObs.ray(&target);
			Intersection* glossyIntersection = getNearestIntersection(&glossyRay);

			if(glossyIntersection != 0){

				Color glossyColor = observedColor(&glossyRay, mode);

				color = color + glossyColor;
				cpt++;
			}

			delete(glossyIntersection);
		}
	}

	color = color * (1.0 / cpt);
	color.normalize();

	return color;
}

Ray Scene::refractedRay(Ray* ray, Intersection* intersection){

	Ray r1 = refractRay(ray, intersection, 1.0, intersection->getObject()->getN());
	Intersection* refractionIntersection = getNearestIntersection(&r1);

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

Ray Scene::refractRay(Ray* ray, Intersection* intersection, double n1, double n2, double epsilon){

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

void Scene::shadow(Color* color, Intersection* intersection, bool random, double _smoothing){

	for(std::list<Light* >::iterator iter = lights.begin(); iter != lights.end(); ++iter){

		double enlighted = 0;
		double shadowed = 0;
		double radius = (*iter)->getRadius();
		double step = 1.0 / _smoothing;

		Point shadowedPoint(((*intersection->getNormal()) * EPSILON) + intersection->getPoint());
		Vector distanceTolight(&shadowedPoint, (*iter)->getSource());
		Observer virtualObs(&shadowedPoint, (*iter)->getSource(), M_PI / 4.0);
		double f = distanceTolight.norm();

		for(double i=-radius/2.0; i<radius/2.0; i+= step){
			for(double j=-radius/2.0; j<radius/2.0; j+= step){

				Point target;

				if(random){
					double ii = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
					double jj = ( ((double)std::rand() / (double)RAND_MAX) * radius ) - (radius/2.0);
					Point temp(ii, jj, f);

					target = temp;
				}
				else{
					Point temp(i, j, f);
					target = temp;
				}

				Ray shadowRay = virtualObs.ray(&target);
				Intersection* shadowIntersection = getNearestShadowIntersection(&shadowRay);

				if(shadowIntersection != 0){

					Vector shadowVect(intersection->getPoint(), shadowIntersection->getPoint());

					if(shadowVect.norm() < f){
						shadowed++;
					}
					else{
						enlighted++;
					}
				}
				else{
					enlighted++;
				}

				delete(shadowIntersection);
			}
		}

		if(shadowed > 0){
			color->scale(std::min(1.0, (enlighted / (shadowed + enlighted)) + 0.3));
			color->normalize();
		}
	}

	color->normalize();
}

/**************************/
/* Ray Casting Function  */
/**************************/

void Scene::rayCasting(void){
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

			Color color;

			if(image->getAntialiasing() > 1){
				color = antialiasedColor(l, p, RAYCASTING_MODE);
			}
			else{
				color = colorAt(l, p, RAYCASTING_MODE);
			}

			image->writePixel(&color);
		}
	}

	std::cout << std::endl;
	std::cout << "\tWriting image to " << image->getFilename() << std::endl;
	image->writeBitmap();
	std::cout << "---> End of rendering" << std::endl;
}

/*****************************/
/* Photon Mapping Function  */
/*****************************/

void Scene::photonMapping(void){
	std::cout << "---> Photon Tracing..." << std::endl;

	shooter = new PhotonShooter(lights.size(), PHOTONS);
	shooter->shoot(lights, objects);

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

			Color color;

			if(image->getAntialiasing() > 1){
				color = antialiasedColor(l, p, PHOTONMAPPING_MODE);
			}
			else{
				color = colorAt(l, p, PHOTONMAPPING_MODE);
			}

			image->writePixel(&color);
		}
	}

	std::cout << std::endl;
	std::cout << "\tWriting image to " << image->getFilename() << std::endl;
	image->writeBitmap();
	std::cout << "---> End of rendering" << std::endl;
}
