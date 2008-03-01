/*
 *  Quadric.h
 *  Pulsar
 *
 *  Created by Camille on 01/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef QUADRIC_H
#define QUADRIC_H

#include "Object.h"

class Quadric : public Object{
private:
	
	double A;
	double B;
	double C;
	double D;
	double E;
	double F;
	double G;
	double H;
	double I;
	double J;
	
public:

	Quadric(Enlightment* _enlightment, double _A, double _B, double _C, double _D, double _E, double _F, double _G, double _H, double _I, double _J) : A(_A), B(_B), C(_C), D(_D), E(_E), F(_F), G(_G), H(_H), I(_I), J(_J){
		enlightment = _enlightment->clone();
	}
	
	virtual ~Quadric(void) {}
	virtual Intersection* intersection(Ray* ray);
	virtual std::string toString(void) const;
	
	Intersection* createIntersection(Ray* ray);
	
	Quadric& operator=(const Quadric& quadric){
	
		delete(enlightment);
		
		enlightment = quadric.enlightment->clone();
		
		A = quadric.A;
		B = quadric.B;
		C = quadric.C;
		D = quadric.D;
		E = quadric.E;
		F = quadric.F;
		G = quadric.G;
		H = quadric.H;
		I = quadric.I;
		J = quadric.J;
	
		return *this;
	}
};

#endif //QUADRIC_H
