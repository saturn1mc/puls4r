/*
 *  SceneParser.cpp
 *  puls4r
 *
 *  Created by Camille on 09/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "SceneParser.h"

using namespace std;

SceneParser* SceneParser::singleton = 0;

const std::string SceneParser::ROOT_NODE = "scene";

const std::string SceneParser::BACKGROUND_NODE = "background";

const std::string SceneParser::OBSERVER_NODE = "observer";
const std::string SceneParser::EYE_NODE = "eye";
const std::string SceneParser::SIGHT_NODE = "sight";

const std::string SceneParser::IMAGE_NODE = "image";

const std::string SceneParser::LIGHT_LIST_NODE = "lights";
const std::string SceneParser::LIGHT_NODE = "light";

const std::string SceneParser::OBJECTS_LIST_NODE = "objects";
const std::string SceneParser::SPHERE_NODE = "sphere";
const std::string SceneParser::PLAN_NODE = "plan";
const std::string SceneParser::TRIANGLE_NODE = "triangle";
const std::string SceneParser::QUADRIC_NODE = "quadric";

const std::string SceneParser::TARGET_ATTR = "target";
const std::string SceneParser::WIDTH_ATTR = "width";
const std::string SceneParser::HEIGHT_ATTR = "height";
const std::string SceneParser::ANTIALIASING_ATTR = "antialiasing";

const std::string SceneParser::X_ATTR = "x";
const std::string SceneParser::Y_ATTR = "y";
const std::string SceneParser::Z_ATTR = "z";

const std::string SceneParser::AX_ATTR = "ax";
const std::string SceneParser::AY_ATTR = "ay";
const std::string SceneParser::AZ_ATTR = "az";

const std::string SceneParser::BX_ATTR = "bx";
const std::string SceneParser::BY_ATTR = "by";
const std::string SceneParser::BZ_ATTR = "bz";

const std::string SceneParser::CX_ATTR = "cx";
const std::string SceneParser::CY_ATTR = "cy";
const std::string SceneParser::CZ_ATTR = "cz";

const std::string SceneParser::R_ATTR = "r";
const std::string SceneParser::G_ATTR = "g";
const std::string SceneParser::B_ATTR = "b";

const std::string SceneParser::QA_ATTR = "qa";
const std::string SceneParser::QB_ATTR = "qb";
const std::string SceneParser::QC_ATTR = "qc";
const std::string SceneParser::QD_ATTR = "qd";
const std::string SceneParser::QE_ATTR = "qe";
const std::string SceneParser::QF_ATTR = "qf";
const std::string SceneParser::QG_ATTR = "qg";
const std::string SceneParser::QH_ATTR = "qh";
const std::string SceneParser::QI_ATTR = "qi";
const std::string SceneParser::QJ_ATTR = "qj";

const std::string SceneParser::D_ATTR = "d";
const std::string SceneParser::MONOFACE_ATTR = "monoface";

const std::string SceneParser::RADIUS_ATTR = "radius";

const std::string SceneParser::POWER_ATTR = "power";

const std::string SceneParser::ENLIGHTMENT_ATTR = "enlightment";
const std::string SceneParser::ENL_PHONG = "phong";
const std::string SceneParser::ENL_LINEAR = "linear";
const std::string SceneParser::ENL_LAMBERT = "lambert";

const std::string SceneParser::REFLECTING_ATTR = "reflecting";
const std::string SceneParser::KR_ATTR = "kr";
const std::string SceneParser::GLOSSY_FOCAL_ATTR = "glossyFocal";
const std::string SceneParser::GLOSSY_WIDTH_ATTR = "glossyWidth";
const std::string SceneParser::REFRACTING_ATTR = "refracting";
const std::string SceneParser::N_ATTR = "n";
const std::string SceneParser::KT_ATTR = "kt";

const std::string SceneParser::PERLIN_ATTR = "perlin";
const std::string SceneParser::EPSILON_ATTR = "epsilon";

Scene* SceneParser::parse(std::string filePath) const throw(std::exception){
	
	std::cout << "---> Parsing " << filePath << " ... " << std::endl;
	
	Scene *scene = new Scene();
	
	TiXmlDocument doc(filePath.c_str());
	
	if(!doc.LoadFile()){
		throw new std::exception;
	}
	
	TiXmlHandle hdl(&doc);
	
	//Background color parsing
	std::cout << "\tParsing background ... " << std::endl;
	TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement(BACKGROUND_NODE.c_str()).Element();
	parseBackgroundElement(elem, scene);
	
	//Observer parsing
	std::cout << "\tParsing observer ... " << std::endl;
	elem = hdl.FirstChildElement().FirstChildElement(OBSERVER_NODE.c_str()).Element();
	parseObserverElement(elem, scene);
	
	//Light list parsing
	std::cout << "\tParsing lights ... " << std::endl;
	elem = hdl.FirstChildElement().FirstChildElement(LIGHT_LIST_NODE.c_str()).Element();
	parseLightList(elem, scene);
	
	//Object list parsing
	std::cout << "\tParsing objects ... " << std::endl;
	elem = hdl.FirstChildElement().FirstChildElement(OBJECTS_LIST_NODE.c_str()).Element();
	parseObjectList(elem, scene);
	
	std::cout << "---> End of parsing." << std::endl;
	
	return scene;
}

void SceneParser::parseBackgroundElement(TiXmlElement* backgroundElement, Scene *scene) const throw(std::exception){
	double r, g, b;
	
	backgroundElement->QueryDoubleAttribute(R_ATTR.c_str(), &r);
	backgroundElement->QueryDoubleAttribute(G_ATTR.c_str(), &g);
	backgroundElement->QueryDoubleAttribute(B_ATTR.c_str(), &b);
	
	Color background(r, g, b);
	scene->setBackground(&background);
}

void SceneParser::parseObserverElement(TiXmlElement* observerElement, Scene *scene) const throw(std::exception){
	Point eye = parseEyeElement(observerElement->FirstChildElement(EYE_NODE.c_str()));
	Point sight = parseSightElement(observerElement->FirstChildElement(SIGHT_NODE.c_str()));
	
	Observer observer(&eye, &sight, M_PI/4.0);
	scene->setObserver(&observer);
}

Point SceneParser::parseEyeElement(TiXmlElement* eyeElement) const throw(std::exception){
	double x, y, z;
	
	eyeElement->QueryDoubleAttribute(X_ATTR.c_str(), &x);
	eyeElement->QueryDoubleAttribute(Y_ATTR.c_str(), &y);
	eyeElement->QueryDoubleAttribute(Z_ATTR.c_str(), &z);
	
	Point eye(x, y, z);
	
	return eye;
}

Point SceneParser::parseSightElement(TiXmlElement* sightElement) const throw(std::exception){
	double x, y, z;
	
	sightElement->QueryDoubleAttribute(X_ATTR.c_str(), &x);
	sightElement->QueryDoubleAttribute(Y_ATTR.c_str(), &y);
	sightElement->QueryDoubleAttribute(Z_ATTR.c_str(), &z);
	
	Point sight(x, y, z);
	
	return sight;
}

void SceneParser::parseLightList(TiXmlElement* lightListElement, Scene* scene) const throw(std::exception){
	TiXmlElement *elem = lightListElement->FirstChildElement(LIGHT_NODE.c_str());
	
	while(elem != 0){
		parseLightElement(elem, scene);
		elem = elem->NextSiblingElement(LIGHT_NODE.c_str());
	}
}

void SceneParser::parseLightElement(TiXmlElement* lightElement, Scene* scene) const throw(std::exception){
	
	//Position
	double x, y, z;
	
	lightElement->QueryDoubleAttribute(X_ATTR.c_str(), &x);
	lightElement->QueryDoubleAttribute(Y_ATTR.c_str(), &y);
	lightElement->QueryDoubleAttribute(Z_ATTR.c_str(), &z);
	
	Point position(x,y,z);
	
	//Color
	double r, g, b;
	
	lightElement->QueryDoubleAttribute(R_ATTR.c_str(), &r);
	lightElement->QueryDoubleAttribute(G_ATTR.c_str(), &g);
	lightElement->QueryDoubleAttribute(B_ATTR.c_str(), &b);
	
	Color color(r,g,b);
	
	//Radius
	double radius;
	lightElement->QueryDoubleAttribute(RADIUS_ATTR.c_str(), &radius);
	
	//Power
	double power;
	lightElement->QueryDoubleAttribute(POWER_ATTR.c_str(), &power);
	
	Light* light = new Light(&position, &color);
	light->setRadius(radius);
	light->setPower(power);
	scene->addLight(light);
}

void SceneParser::parseObjectList(TiXmlElement* objectListElement, Scene* scene) const throw(std::exception){
	TiXmlElement *elem = objectListElement->FirstChildElement();
	
	while(elem != 0){
		parseObjectElement(elem, scene);
		elem = elem->NextSiblingElement();
	}
}

void SceneParser::parseObjectElement(TiXmlElement* objectElement, Scene* scene) const throw(std::exception){
	
	bool handled = false;
	
	if(strcmp(objectElement->Value(), SPHERE_NODE.c_str()) == 0){
		parseSphereElement(objectElement, scene);
		handled = true;
	}
	
	if(strcmp(objectElement->Value(), PLAN_NODE.c_str()) == 0){
		parsePlanElement(objectElement, scene);
		handled = true;
	}
	
	if(strcmp(objectElement->Value(), TRIANGLE_NODE.c_str()) == 0){
		parseTriangleElement(objectElement, scene);
		handled = true;
	}
	
	if(strcmp(objectElement->Value(), QUADRIC_NODE.c_str()) == 0){
		parseQuadricElement(objectElement, scene);
		handled = true;
	}
	
	if(!handled){
		std::cerr << "Unknown object " << objectElement->Value() << std::endl;
	}
}

void SceneParser::parseSphereElement(TiXmlElement* sphereElement, Scene* scene) const throw(std::exception){
	//Position
	double x, y, z;
	
	sphereElement->QueryDoubleAttribute(X_ATTR.c_str(), &x);
	sphereElement->QueryDoubleAttribute(Y_ATTR.c_str(), &y);
	sphereElement->QueryDoubleAttribute(Z_ATTR.c_str(), &z);
	
	Point position(x,y,z);
	
	//Radius
	double radius;
	sphereElement->QueryDoubleAttribute(RADIUS_ATTR.c_str(), &radius);
	
	//Enlightment
	Enlightment* enl = parseEnlightment(sphereElement);
	
	//Relfection attributes
	int reflecting;
	double kr;
	double glossyFocal;
	double glossyWidth;
	
	sphereElement->QueryIntAttribute(REFLECTING_ATTR.c_str(), &reflecting);
	sphereElement->QueryDoubleAttribute(KR_ATTR.c_str(), &kr);
	sphereElement->QueryDoubleAttribute(GLOSSY_FOCAL_ATTR.c_str(), &glossyFocal);
	sphereElement->QueryDoubleAttribute(GLOSSY_WIDTH_ATTR.c_str(), &glossyWidth);
	
	//Refraction attributes
	int refracting;
	double n;
	double kt;
	
	sphereElement->QueryIntAttribute(REFRACTING_ATTR.c_str(), &refracting);
	sphereElement->QueryDoubleAttribute(N_ATTR.c_str(), &n);
	sphereElement->QueryDoubleAttribute(KT_ATTR.c_str(), &kt);
	
	
	//Noise attributes
	int perlin;
	double epsilon;
	
	sphereElement->QueryIntAttribute(PERLIN_ATTR.c_str(), &perlin);
	sphereElement->QueryDoubleAttribute(EPSILON_ATTR.c_str(), &epsilon);	
	
	//Creating and adding object
	Sphere* sphere = new Sphere(enl, &position, radius, perlin == 1);
	sphere->setReflecting(reflecting == 1, kr);
	sphere->setGlossy(glossyFocal, glossyWidth);
	sphere->setRefracting(refracting == 1, n, kt);
	sphere->setEpsilon(epsilon);
	
	scene->addObject(sphere);
	
	delete(enl);
}

void SceneParser::parsePlanElement(TiXmlElement* planElement, Scene* scene) const throw(std::exception){
	
	//Equation parameters
	double x, y, z, d;
	
	planElement->QueryDoubleAttribute(X_ATTR.c_str(), &x);
	planElement->QueryDoubleAttribute(Y_ATTR.c_str(), &y);
	planElement->QueryDoubleAttribute(Z_ATTR.c_str(), &z);
	planElement->QueryDoubleAttribute(D_ATTR.c_str(), &d);
	
	Vector normal(x,y,z);
	
	//Monoface property
	int monoface;
	planElement->QueryIntAttribute(MONOFACE_ATTR.c_str(), &monoface);
	
	//Enlightment
	Enlightment* enl = parseEnlightment(planElement);
	
	//Relfection attributes
	int reflecting;
	double kr;
	double glossyFocal;
	double glossyWidth;
	
	planElement->QueryIntAttribute(REFLECTING_ATTR.c_str(), &reflecting);
	planElement->QueryDoubleAttribute(KR_ATTR.c_str(), &kr);
	planElement->QueryDoubleAttribute(GLOSSY_FOCAL_ATTR.c_str(), &glossyFocal);
	planElement->QueryDoubleAttribute(GLOSSY_WIDTH_ATTR.c_str(), &glossyWidth);
	
	//Refraction attributes
	int refracting;
	double n;
	double kt;
	
	planElement->QueryIntAttribute(REFRACTING_ATTR.c_str(), &refracting);
	planElement->QueryDoubleAttribute(N_ATTR.c_str(), &n);
	planElement->QueryDoubleAttribute(KT_ATTR.c_str(), &kt);
	
	
	//Noise attributes
	int perlin;
	double epsilon;
	
	planElement->QueryIntAttribute(PERLIN_ATTR.c_str(), &perlin);
	planElement->QueryDoubleAttribute(EPSILON_ATTR.c_str(), &epsilon);
	
	//Creating and adding object
	Plan* plan = new Plan(enl, &normal, d, monoface == 1, perlin == 1);
	plan->setReflecting(reflecting == 1, kr);
	plan->setGlossy(glossyFocal, glossyWidth);
	plan->setRefracting(refracting == 1, n, kt);
	plan->setEpsilon(epsilon);
	
	scene->addObject(plan);
	
	delete(enl);
}

void SceneParser::parseTriangleElement(TiXmlElement* triangleElement, Scene* scene) const throw(std::exception){
	
	//Equation parameters
	double ax, ay, az, bx, by, bz, cx, cy, cz;
	
	triangleElement->QueryDoubleAttribute(AX_ATTR.c_str(), &ax);
	triangleElement->QueryDoubleAttribute(AY_ATTR.c_str(), &ay);
	triangleElement->QueryDoubleAttribute(AZ_ATTR.c_str(), &az);
	Point a(ax, ay, az);
	
	triangleElement->QueryDoubleAttribute(BX_ATTR.c_str(), &bx);
	triangleElement->QueryDoubleAttribute(BY_ATTR.c_str(), &by);
	triangleElement->QueryDoubleAttribute(BZ_ATTR.c_str(), &bz);
	Point b(bx, by, bz);
	
	triangleElement->QueryDoubleAttribute(CX_ATTR.c_str(), &cx);
	triangleElement->QueryDoubleAttribute(CY_ATTR.c_str(), &cy);
	triangleElement->QueryDoubleAttribute(CZ_ATTR.c_str(), &cz);
	Point c(cx, cy ,cz);
	
	//Enlightment
	Enlightment* enl = parseEnlightment(triangleElement);
	
	//Relfection attributes
	int reflecting;
	double kr;
	double glossyFocal;
	double glossyWidth;
	
	triangleElement->QueryIntAttribute(REFLECTING_ATTR.c_str(), &reflecting);
	triangleElement->QueryDoubleAttribute(KR_ATTR.c_str(), &kr);
	triangleElement->QueryDoubleAttribute(GLOSSY_FOCAL_ATTR.c_str(), &glossyFocal);
	triangleElement->QueryDoubleAttribute(GLOSSY_WIDTH_ATTR.c_str(), &glossyWidth);
	
	//Refraction attributes
	int refracting;
	double n;
	double kt;
	
	triangleElement->QueryIntAttribute(REFRACTING_ATTR.c_str(), &refracting);
	triangleElement->QueryDoubleAttribute(N_ATTR.c_str(), &n);
	triangleElement->QueryDoubleAttribute(KT_ATTR.c_str(), &kt);
	
	
	//Noise attributes
	int perlin;
	double epsilon;
	
	triangleElement->QueryIntAttribute(PERLIN_ATTR.c_str(), &perlin);
	triangleElement->QueryDoubleAttribute(EPSILON_ATTR.c_str(), &epsilon);
	
	//Creating and adding object
	Triangle* triangle = new Triangle(enl, &a, &b, &c, perlin == 1);
	triangle->setReflecting(reflecting == 1, kr);
	triangle->setGlossy(glossyFocal, glossyWidth);
	triangle->setRefracting(refracting == 1, n, kt);
	triangle->setEpsilon(epsilon);
	
	scene->addObject(triangle);
	
	delete(enl);
}

void SceneParser::parseQuadricElement(TiXmlElement* quadricElement, Scene* scene) const throw(std::exception){
	
	//Equation parameters
	double a, b, c, d, e, f, g, h, i, j;
	
	quadricElement->QueryDoubleAttribute(QA_ATTR.c_str(), &a);
	quadricElement->QueryDoubleAttribute(QB_ATTR.c_str(), &b);
	quadricElement->QueryDoubleAttribute(QC_ATTR.c_str(), &c);
	quadricElement->QueryDoubleAttribute(QD_ATTR.c_str(), &d);
	quadricElement->QueryDoubleAttribute(QE_ATTR.c_str(), &e);
	quadricElement->QueryDoubleAttribute(QF_ATTR.c_str(), &f);
	quadricElement->QueryDoubleAttribute(QG_ATTR.c_str(), &g);
	quadricElement->QueryDoubleAttribute(QH_ATTR.c_str(), &h);
	quadricElement->QueryDoubleAttribute(QI_ATTR.c_str(), &i);
	quadricElement->QueryDoubleAttribute(QJ_ATTR.c_str(), &j);
	
	//Enlightment
	Enlightment* enl = parseEnlightment(quadricElement);
	
	//Relfection attributes
	int reflecting;
	double kr;
	double glossyFocal;
	double glossyWidth;
	
	quadricElement->QueryIntAttribute(REFLECTING_ATTR.c_str(), &reflecting);
	quadricElement->QueryDoubleAttribute(KR_ATTR.c_str(), &kr);
	quadricElement->QueryDoubleAttribute(GLOSSY_FOCAL_ATTR.c_str(), &glossyFocal);
	quadricElement->QueryDoubleAttribute(GLOSSY_WIDTH_ATTR.c_str(), &glossyWidth);
	
	//Refraction attributes
	int refracting;
	double n;
	double kt;
	
	quadricElement->QueryIntAttribute(REFRACTING_ATTR.c_str(), &refracting);
	quadricElement->QueryDoubleAttribute(N_ATTR.c_str(), &n);
	quadricElement->QueryDoubleAttribute(KT_ATTR.c_str(), &kt);
	
	
	//Noise attributes
	int perlin;
	double epsilon;
	
	quadricElement->QueryIntAttribute(PERLIN_ATTR.c_str(), &perlin);
	quadricElement->QueryDoubleAttribute(EPSILON_ATTR.c_str(), &epsilon);
	
	//Creating and adding object
	Quadric* quadric = new Quadric(enl, a, b, c, d, e, f, g, h, i, j, perlin == 1);
	quadric->setReflecting(reflecting == 1, kr);
	quadric->setGlossy(glossyFocal, glossyWidth);
	quadric->setRefracting(refracting == 1, n, kt);
	quadric->setEpsilon(epsilon);
	
	scene->addObject(quadric);
	
	delete(enl);
}

Enlightment* SceneParser::parseEnlightment(TiXmlElement* objectElement) const throw(std::exception){
	
	//Color
	double r, g, b;
	
	objectElement->QueryDoubleAttribute(R_ATTR.c_str(), &r);
	objectElement->QueryDoubleAttribute(G_ATTR.c_str(), &g);
	objectElement->QueryDoubleAttribute(B_ATTR.c_str(), &b);
	
	Color color(r,g,b);
	
	//Type
	const char* enlName = objectElement->Attribute(ENLIGHTMENT_ATTR.c_str());
	Enlightment* enl = 0;
	
	//TODO handle all enlightments
	if(strcmp(enlName, ENL_PHONG.c_str()) == 0){
		enl = new Phong(&color);
	}
	
	if(strcmp(enlName, ENL_LINEAR.c_str()) == 0){
		enl = new Linear(&color);
	}
	
	if(strcmp(enlName, ENL_LAMBERT.c_str()) == 0){
		enl = new Lambert(&color);
	}
	
	if(enl == 0){
		std::cerr << "Enlightment technique unknown : " << enlName << std::endl;
		enl = new Linear(&color);
	}
	
	return enl;
}
