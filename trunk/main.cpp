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

using namespace std;

int main (int argc, char * const argv[]) {
	Observer *obs = new Observer(new Point(6.0, 2.0, 6.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene *scene = new Scene(obs, new Image("/Users/camille/Desktop/test.bmp", 300, 300), new Color(0.0, 0.0, 0.0));
	
	scene->add(new Sphere(new Color(1.0, 0.0, 0.0), new Point(0.0, 0.0, 0.0), 1.0));
	
	cout << *scene << endl;
	
	scene->rayTrace();
}
