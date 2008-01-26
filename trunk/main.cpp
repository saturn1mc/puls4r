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
	Color *green = new Color(0.0, 1.0, 0.0);
	Color *blue = new Color(0.0, 0.0, 1.0);
	
	Linear *linear = new Linear(red);
	
	Observer *obs = new Observer(new Point(6.0, 2.0, 6.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene *scene = new Scene(obs, new Image("/Users/Camille/Desktop/test.bmp", 800, 600), black);
	
	scene->addLight(new Light(new Point(60.0, 20.0, 60.0), white));
	
	scene->addObject(new Sphere(new Phong(red), new Point(0.0, 0.5, 0.0), 1.0));
	//scene->addObject(new Sphere(new Lambert(green), new Point(0.5, 0.0, 0.0), 1.0));
	//scene->addObject(new Sphere(new Lambert(blue), new Point(-0.5, 0.0, 0.0), 1.0));
	
	cout << *scene << endl;
	
	scene->rayTrace();
}
