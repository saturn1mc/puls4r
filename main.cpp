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

#include "Scene.h"
#include "Sphere.h"
#include "Plan.h"
#include "Phong.h"
#include "Linear.h"
#include "Lambert.h"

using namespace std;

int main (int argc, char * const argv[]) {
	
	Color *white = new Color(1.0, 1.0, 1.0);
	Color *black = new Color(0.0, 0.0, 0.0);
	Color *red = new Color(1.0, 0.0, 0.0);
	
	Linear *linear = new Linear(red);
	Phong *phong = new Phong(red);
	Lambert *lambert = new Lambert(red);
	
	Observer *obs = new Observer(new Point(20.0, 20.0, 20.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene *scene = new Scene(obs, new Image("/Users/camille/Desktop/test.bmp", 800, 600), black);
	
	scene->addLight(new Light(new Point(6.0, 2.0, 6.0), white));
	
	scene->addObject(new Sphere(linear, new Point(0.0, 0.0, 0.0), 1.0));
	
	cout << *scene << endl;
	
	scene->rayTrace();
}
