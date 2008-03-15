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

#include "SceneParser.h"

using namespace std;

const std::string RAYCASTING_OPT = "-R";
const std::string PHOTONMAPPING_OPT = "-P";

void viewY360(Scene* scene, int images, int mode){
	
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
		scene->trace(mode);
		
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

void causticEvolution(Scene* scene, double nmin, double nmax, int images, int mode){
	
	double delta = (nmax-nmin) / images;
	Color* white = new Color(1.0, 1.0, 1.0);
	Enlightment* enl = new Phong(white);
	
	Point* tempPoint = new Point (0, 0, 0);
	
	Sphere* sphere = new Sphere(enl, tempPoint, 2.5);
	sphere->setRefracting(true, nmin, 1.0);
	scene->addObject(sphere);
	
	delete(tempPoint);
	delete(white);
	delete(enl);
	
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
		scene->trace(mode);
		
		//Changing refraction index
		sphere->setRefracting(true, nmin + ((double)i*delta), 1.0);
		
		cout << "Image " << (i+1) << "/" << images << " generated" << endl;
	}
	
	cout << "Generating AVI" << endl;
	
	char* cmd = (char*)malloc(strlen("java -jar BmpSeq.jar -CMD images/img000.bmp images/img000.bmp 00 images/seq.avi") + 1);
	sprintf(cmd, "java -jar BmpSeq.jar -CMD images/img%d.bmp images/img%d.bmp %d images/seq.avi", 1, (int)images, 30);
	system(cmd);
	
	free(cmd);
}

void printUsage(void){
	cerr << "Usage : pulsar (" << RAYCASTING_OPT << " | " << PHOTONMAPPING_OPT << ") scene_file.xml target_file.bmp width height [antialiasing_factor]" << endl;
}

void traceScene(int mode, char* sceneFile, char* targetFile, int width, int height, int antialiasing){
	
	Scene* scene = SceneParser::getInstance().parse(sceneFile);
	Image image(targetFile, width, height, antialiasing);
	
	scene->setImage(&image);
	
	scene->trace(mode);
	
	delete(scene);
}

void pulsar(int argc, char*  const argv[]) {
	if(argc < 6){
		printUsage();
	}
	else{
	
		bool optionRecognized = false;
	
		if(strcmp(argv[1], RAYCASTING_OPT.c_str()) == 0){
			optionRecognized = true;
			
			if(argc > 6){
				traceScene(Scene::RAYCASTING_MODE, argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
			}
			else{
				traceScene(Scene::RAYCASTING_MODE, argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), 1);
			}
		}
		
		if(strcmp(argv[1], PHOTONMAPPING_OPT.c_str()) == 0){
			optionRecognized = true;
			
			if(argc > 6){
				traceScene(Scene::PHOTONMAPPING_MODE, argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
			}
			else{
				traceScene(Scene::PHOTONMAPPING_MODE, argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), 1);
			}
		}
		
		if(!optionRecognized){
			cerr << "Option unknown : " << argv[1] << endl;
		}
	}
}


int main (int argc, char*  const argv[]) {
	pulsar(argc, argv);
}
