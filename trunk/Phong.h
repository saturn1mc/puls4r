/*
 *  Phong.h
 *  RayTracing
 *
 *  Created by Camille on 23/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PHONG_H
#define PHONG_H

#include <list>

#include "Enlightment.h"
#include "Light.h"

class Phong : public Enlightment{
private:
	
	Color* oa; //ambient color
	Color* od; //diffuse color
	Color* os; //specular color
	
	double ia;
	
	double ka; //ambient reflection constant
	double kd; //diffuse reflection constant
	double ks; //specular reflection constant
	
	int n; //rugosity constant

public:
		
	Phong(Color* _od) : oa(new Color((*_od) * ia)), od(new Color(_od)), os(new Color(1.0, 1.0, 1.0)), ia(1.0), ka(1.0), kd(0.7), ks(0.3), n(10) {}
	Phong(Color* _oa, Color* _od, Color* _os, double _ia, double _ka, double _kd, double _ks, int _n) : oa(new Color(_oa)), od(new Color(_od)), os(new Color(_os)), ia(_ia), ka(_ka), kd(_kd), ks(_ks), n (_n) {}
	Phong(const Phong& phong) : oa(new Color(phong.oa)), od(new Color(phong.od)), os(new Color(phong.os)), ia(phong.ia), ka(phong.ka), kd(phong.kd), ks(phong.ks), n(phong.n) {}
	Phong(const Phong* phong) : oa(new Color(phong->oa)), od(new Color(phong->od)), os(new Color(phong->os)), ia(phong->ia), ka(phong->ka), kd(phong->kd), ks(phong->ks), n(phong->n) {}
	
	virtual ~Phong(void) {
		delete(oa);
		delete(od);
		delete(os);		
	}
	
	virtual Color* getColor(Point* point, Vector* norm, Ray* ray, std::list<Light* > lights) const;
	virtual Enlightment* clone() {return new Phong(*this);}
	
	Phong& operator=(const Phong& phong){
		delete(oa);
		delete(od);
		delete(os);
		
		oa = new Color(phong.oa);
		od = new Color(phong.od);
		os = new Color(phong.os);
		
		ia = phong.ia;
		
		ka = phong.ka;
		kd = phong.kd;
		ks = phong.ks;
		
		n = phong.n;
		
		return *this;
	}
};

#endif //PHONG_H
