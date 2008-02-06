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

void runTestScene(){
	Color* white = new Color(1.0, 1.0, 1.0);
	Color* black = new Color(0.0, 0.0, 0.0);
	Color* red = new Color(1.0, 0.0, 0.0);
	Color* green = new Color(0.0, 1.0, 0.0);
	Color* blue = new Color(0.0, 0.0, 1.0);
	Color* yellow = new Color(1.0, 1.0, 0.0);
	Color* orange = new Color(1.0, 0.3, 0.0);
	Color* purple = new Color(1.0, 0.0, 1.0);
	
	Observer* obs = new Observer(new Point(0.0, 10.0, 50.0), new Point(0.0, 0.0, 0.0), M_PI/4.0);
	Scene* scene = new Scene(obs, new Image("test.bmp", 1900, 1200, 1), black);
	
	scene->addLight(new Light(new Point(20.0, 15.0, 20.0), white));
	
	Sphere* reflectingSphere = new Sphere(new Linear(white), new Point (0, 10, 0), 3.0);
	reflectingSphere->setReflecting(true);
	scene->addObject(reflectingSphere);
	
	Sphere* sphere1 = new Sphere(new Phong(red), new Point (0, 0, 0), 2.0);
	sphere1->setReflecting(false);
	scene->addObject(sphere1);
	
	Sphere* sphere2 = new Sphere(new Phong(green), new Point (0, 4, 0), 2.0);
	sphere2->setReflecting(false);
	scene->addObject(sphere2);
	
	Sphere* sphere3 = new Sphere(new Phong(blue), new Point (4, 0, 0), 2.0);
	sphere3->setReflecting(false);
	scene->addObject(sphere3);
	
	Sphere* sphere4 = new Sphere(new Phong(yellow), new Point (0, 0, 4), 2.0);
	sphere4->setReflecting(false);
	scene->addObject(sphere4);

	Plan* plan1 = new Plan(new Phong(red), new Vector(1, 0, 0), 20.0, false);
	plan1->setReflecting(false);
	scene->addObject(plan1);
	
	Plan* plan2 = new Plan(new Phong(green), new Vector(0, 1, 0), 4.0, false);
	plan2->setReflecting(false);
	scene->addObject(plan2);
	
	Plan* plan3 = new Plan(new Phong(blue), new Vector(0, 0, 1), 50.0, false);
	plan3->setReflecting(false);
	scene->addObject(plan3);
	
	Plan* plan5 = new Plan(new Phong(purple), new Vector(-1, 0, 0), 50.0, false);
	plan5->setReflecting(false);
	scene->addObject(plan5);
	
	Plan* plan4 = new Plan(new Phong(orange), new Vector(0, -1, 0), 20.0, false);
	plan4->setReflecting(false);
	scene->addObject(plan4);
	
	Plan* plan6 = new Plan(new Phong(yellow), new Vector(0, 0, -1), 60.0, false);
	plan6->setReflecting(false);
	scene->addObject(plan6);
	
	cout << scene << endl;
	
	scene->rayTrace();
}

int main (int argc, char*  const argv[]) {
	runTestScene();
}
