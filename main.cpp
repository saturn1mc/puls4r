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

void generateTestScene(){
	Color* white = new Color(1.0, 1.0, 1.0);
	Color* black = new Color(0.0, 0.0, 0.0);
	Color* red = new Color(1.0, 0.0, 0.0);
	Color* green = new Color(0.0, 1.0, 0.0);
	Color* blue = new Color(0.0, 0.0, 1.0);
	Color* yellow = new Color(1.0, 1.0, 0.0);
	Color* purple = new Color(1.0, 0.0, 1.0);
	
	Observer* obs = new Observer(new Point(0.0, 6.0, 30.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene* scene = new Scene(obs, new Image("test.bmp", 400, 300, 2), black);
	
	scene->addLight(new Light(new Point(10.0, 30.0, 40.0), white));
	
	scene->addObject(new Sphere(new Phong(red), new Point(-4.0, 3.0, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(purple), new Point(-2.0, 3.0, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(green), new Point(0.0, 3.0, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(blue), new Point(2.0, 3.0, 0.0), 1.0));
	scene->addObject(new Sphere(new Phong(yellow), new Point(4.0, 3.0, 0.0), 1.0));
	
	Sphere* reflectingSphere = new Sphere(new Phong(white), new Point(0.0, -1.0, 0.0), 2.0);
	reflectingSphere->setReflectance(true);
	scene->addObject(reflectingSphere);
	
	scene->addObject(new Plan(new Phong(white), new Vector(0.0, 1.0, 0.0), 10.0, true));
	
	cout << scene << endl;
	
	scene->rayTrace();
}

int main (int argc, char*  const argv[]) {
	generateTestScene();
}
