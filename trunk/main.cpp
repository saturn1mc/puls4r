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

using namespace std;

int main (int argc, char * const argv[]) {
	Point *a = new Point();
	Point *b = new Point(1, 2, 3);
	
	cout << "Test point : " << endl;
	cout << "Point par defaut : " << *a << endl;
	cout << "Point 1,2,3 : " << *b << endl;
	
	
	Vector *v1 = new Vector();
	Vector *v2 = new Vector(1,2,3);
	Vector *v3 = new Vector(4,5,6);
	cout << "Vecteur par défaut : " << *v1 << endl;
	cout << "Vecteur 1,2,3 : " << *v2 << endl;
	cout << "Vecteur (1,2,3) * (4,5,6) : " << (*v2) * (*v3)  << endl;
	cout << "Vecteur (1,2,3) ^ (4,5,6) : " << ((*v2) ^ (*v3))  << endl;
	
	Matrix *matrix = new Matrix();
	cout << "Matrice par défaut : " << endl;
	cout << *matrix << endl;
	
	matrix->loadIdentity();
	cout << "Matrice identité : " << endl;
	cout << *matrix << endl;
	
	matrix->loadTranslation(*v3);
	cout << "Matrice translation v3 : " << endl;
	cout << *matrix << endl;
	
	cout << "Matrice transposée v3 : " << endl;
	cout << (matrix->t()) << endl;
	
	matrix->loadRotateX(M_PI/2.0);
	cout << "Matrice translation v3 : " << endl;
	cout << *matrix << endl;
}
