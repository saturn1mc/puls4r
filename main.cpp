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
#include "Triangle.h"
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
	Color *yellow = new Color(1.0, 1.0, 0.0);
	
	Linear *linear = new Linear(red);
	
	Observer *obs = new Observer(new Point(10.0, 10.0, 10.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene *scene = new Scene(obs, new Image("/Users/Camille/Desktop/test.bmp", 800, 600), black);
	
	scene->addLight(new Light(new Point(0.0, 20.0, 0.0), white));
	
	scene->addObject(new Sphere(new Phong(red), new Point(0.7, 0.0, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(green), new Point(0.0, 0.7, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(blue), new Point(0.0, 0.0, 0.7), 1.0));
	
	scene->addObject(new Triangle(new Phong(yellow), new Point(0.0, 3.0, -1.5), new Point(0.0, 0.0, 1.5), new Point(3.0, 0.0, -1.5)));
	
	scene->addObject(new Plan(new Lambert(white), new Vector(0.0, 1.0, -1.0), 3.0, true));
	
	cout << *scene << endl;
	
	scene->rayTrace();
}
