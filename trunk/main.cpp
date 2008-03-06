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
#include "Quadric.h"
#include "Box.h"
#include "Plan.h"
#include "Phong.h"
#include "Linear.h"
#include "Lambert.h"

using namespace std;

Scene* createTestScene(){
	
	/* Colors */
	Color* white = new Color(1.0, 1.0, 1.0);
	Color* black = new Color(0.0, 0.0, 0.0);
	Color* red = new Color(1.0, 0.0, 0.0);
	Color* green = new Color(0.0, 1.0, 0.0);
	Color* blue = new Color(0.0, 0.0, 1.0);
	Color* yellow = new Color(1.0, 1.0, 0.0);
	Color* orange = new Color(1.0, 0.3, 0.0);
	Color* purple = new Color(1.0, 0.0, 1.0);
	
	/* Enlightments */
	Enlightment* enl1 = new Phong(red);
	Enlightment* enl2 = new Phong(green);
	Enlightment* enl3 = new Phong(blue);
	Enlightment* enl4 = new Phong(yellow);
	Enlightment* enl5 = new Phong(purple);
	Enlightment* enl6 = new Phong(orange);
	Enlightment* enl7 = new Phong(orange);
	
	/* Points */
	Point* tempPoint;
	Point* A;
	Point* B;
	Point* C;
	Point* eye = new Point(0.0, 5.0, 30.0);
	Point* sight = new Point(0.0, 0.0, 0.0);
	Point* lightPos = new Point(-5.0, 10.0, 5.0);
	
	/* Vectors */
	Vector* tempVector;
	
	/* Image */
	Image* image = new Image("test.bmp", 400, 300, 1);
	
	/* Observer */
	Observer* obs = new Observer(eye, sight, M_PI/4.0);
	
	/* Scene */
	Scene* scene = new Scene(obs, image, black);
	
	//Lights
	Light* light1 = new Light(lightPos, white);
	light1->setRadius(2.5);
	scene->addLight(light1);
	
	//Objects
	
	//BOX
	A = new Point(0, 0, 0);
	B = new Point(10, 10, 10);
	
	Box* box1 = new Box(A, B);
	scene->addBox(box1);
	
	delete(A);
	delete(B);
	
	//TRIANGLES
	A = new Point(0, 0, 0);
	B = new Point(10, 0, 0);
	C = new Point(0, 10, 0);
	
	Triangle* triangle1 = new Triangle(enl1, A, B, C);
	//scene->addObject(triangle1);
	
	delete(A);
	delete(B);
	delete(C);
	
	
	//QUADRICS
	Quadric* quadric1 = new Quadric(enl1, 1, 4, 2, 0, 0, 0, 0, 0, 0, -12);
	quadric1->setReflecting(false);
	quadric1->setRefracting(true, 1.2, 1.0);
	//scene->addObject(quadric1);
	
	
	//SPHERES
	tempPoint = new Point (3.0, 0.2, 0);
	
	Sphere* sphere1 = new Sphere(enl2, tempPoint, 2.0);
	sphere1->setRefracting(true, 1.5, 1.0);
	scene->addObject(sphere1);
	
	delete(tempPoint);
	
	tempPoint = new Point (0, 4, 0);
	
	Sphere* sphere2 = new Sphere(enl3, tempPoint, 2.0);
	//scene->addObject(sphere2);
	
	delete(tempPoint);

	tempPoint = new Point (4, 0, 0);
	
	Sphere* sphere3 = new Sphere(enl4, tempPoint, 2.0);
	sphere3->setReflecting(false);
	//scene->addObject(sphere3);
	
	delete(tempPoint);
	
	tempPoint = new Point (0, 0, 4);
	
	Sphere* sphere4 = new Sphere(enl5, tempPoint, 2.0);
	sphere4->setReflecting(false);
	//scene->addObject(sphere4);
	
	delete(tempPoint);
	
	tempPoint = new Point (10.0, 10, 0);
	
	Sphere* specialSphere = new Sphere(enl1, tempPoint, 3.0);
	specialSphere->setReflecting(true, 1.0);
	specialSphere->setRefracting(true, 2.0, 1.0);
	//scene->addObject(specialSphere);
	
	delete(tempPoint);
	
	tempPoint = new Point (0.0, 10, 0);
	
	Sphere* refractingSphere = new Sphere(enl1, tempPoint, 3.0);
	refractingSphere->setRefracting(true, 1.8, 1.0);
	//scene->addObject(refractingSphere);
	
	delete(tempPoint);
	
	
	tempPoint = new Point (-10.0, 10, 0);
	
	Sphere* reflectingSphere = new Sphere(enl1, tempPoint, 3.0);
	reflectingSphere->setReflecting(true, 1.0);
	//reflectingSphere->setGlossy(200.0, 20.0);
	//scene->addObject(reflectingSphere);
	
	delete(tempPoint);
	
	//PLANS
	tempVector = new Vector(0, 1, 0);
	
	Plan* plan1 = new Plan(enl1, tempVector, 2.0, false);
	scene->addObject(plan1);
	
	delete(tempVector);
	
	tempVector = new Vector(1, 0, 0);
	
	Plan* plan2 = new Plan(enl2, tempVector, 10.0, false);
	scene->addObject(plan2);
	
	delete(tempVector);
	
	tempVector = new Vector(0, 0, 1);
	
	Plan* plan3 = new Plan(enl3, tempVector, 20.0, false);
	scene->addObject(plan3);
	
	delete(tempVector);
	
	tempVector = new Vector(0, -1, 0);
	
	Plan* plan4 = new Plan(enl4, tempVector, 15.0, false);
	plan4->setReflecting(false);
	scene->addObject(plan4);
	
	delete(tempVector);
	
	tempVector = new Vector(-1, 0, 0);
	
	Plan* plan5 = new Plan(enl5, tempVector, 10.0, false);
	plan5->setReflecting(false);
	scene->addObject(plan5);

	delete(tempVector);
	
	tempVector = new Vector(0, 0, -1);
	
	Plan* plan6 = new Plan(enl6, tempVector, 50.0, false);
	plan6->setReflecting(false);
	scene->addObject(plan6);
	
	delete(tempVector);
	
	delete(white);
	delete(black);
	delete(red);
	delete(green);
	delete(blue);
	delete(yellow);
	delete(orange);
	delete(purple);

	delete(enl1);
	delete(enl2);
	delete(enl3);
	delete(enl4);
	delete(enl5);
	delete(enl6);
	delete(enl7);
	
	delete(eye);
	delete(sight);
	delete(lightPos);
	
	delete(image);
	
	delete(obs);
	
	return scene;
}

void viewY360(Scene* scene, int images){
	
	Observer* obs = new Observer(scene->getObserver());
	Point* eye = new Point(scene->getObserver()->getEye());
	
	double rotation = M_PI * 2.0;
	double delta = rotation / images;
	
	Matrix* rotateY = new Matrix();
	rotateY->loadRotateY(delta);
	
	system("mkdir images");
	
	for(int i = 0; i<images; i++){

		cout << "Generating image " << (i+1) << "/" << images << endl;
	
		//Changing filename
		char* filename = (char*) malloc(strlen("images/img000.bmp") + 1);
		sprintf(filename, "images/img%d.bmp", i+1);
		scene->getImage()->reset();
		scene->getImage()->setFilename(filename);
		free(filename);
		
		//Tracing new scene
		scene->rayTrace();
		
		//Observer rotation
		*eye = (*rotateY) * eye;
		delete(obs);
		obs = new Observer(eye, new Point(0.0, 0.0, 0.0), M_PI/4.0);
		scene->setObserver(obs);
		
		cout << "Image " << (i+1) << "/" << images << " generated" << endl;
	}
	
	cout << "Generating AVI" << endl;
	
	char* cmd = (char*)malloc(strlen("java -jar BmpSeq.jar -CMD images/img000.bmp images/img000.bmp 00 images/seq.avi") + 1);
	sprintf(cmd, "java -jar BmpSeq.jar -CMD images/img%d.bmp images/img%d.bmp %d images/seq.avi", 1, (int)images, 30);
	system(cmd);
	
	free(cmd);
	delete(obs);
	delete(eye);
	delete(rotateY);
}

int main (int argc, char*  const argv[]) {
	Scene* scene = createTestScene();
	//viewY360(scene, 100);
	scene->rayTrace();
	
	delete(scene);
	
	//while(1){}//Malloc debug
}
