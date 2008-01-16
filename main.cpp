/*
 *  main.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include "Observer.h"

using namespace std;

int main (int argc, char * const argv[]) {
// 	Observer *obs = new Observer(new Point(6.0, 2.0, 6.0), new Point(0.0, 0.0, 0.0));
// 	cout << "Matrice :\n" << *obs->getView();
	
	Point *p = new Point(6.0,2.0,6.0);
	Point *d = new Point(0.0, 0.0 ,0.0);
	
	Vector *sight = new Vector(*d, *p);
	sight->normalize();
	
	cout << "sight norm " << *sight << endl;
	
	Vector up(0,1,0);
	
	up.normalize();
	
	cout << "up norm " <<  up << endl;
	
	Vector &w = *sight ^ up;
	w.normalize();
	
	Vector &u = *sight ^ w;
	u.normalize();
	
	Matrix *v = new Matrix(u, *sight, w, *p);
	
	cout << "Matrice\n" << v->t();
}
