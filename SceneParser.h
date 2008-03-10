/*
 *  SceneParser.h
 *  TP1-C++
 *
 *  Created by Camille on 09/03/08.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include <exception>

#include "tinyxml.h"

#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Quadric.h"
#include "Box.h"
#include "Plan.h"
#include "Phong.h"
#include "Linear.h"
#include "Lambert.h"
#include "Light.h"

class SceneParser{
public:
	
	static const std::string ROOT_NODE;
	
	static const std::string BACKGROUND_NODE;
	
	static const std::string OBSERVER_NODE;
	static const std::string EYE_NODE;
	static const std::string SIGHT_NODE;
	
	static const std::string IMAGE_NODE;
	
	static const std::string LIGHT_LIST_NODE;
	static const std::string LIGHT_NODE;
	
	static const std::string OBJECTS_LIST_NODE;
	static const std::string SPHERE_NODE;
	static const std::string PLAN_NODE;
	
	static const std::string TARGET_ATTR;
	static const std::string WIDTH_ATTR;
	static const std::string HEIGHT_ATTR;
	static const std::string ANTIALIASING_ATTR;
	
	static const std::string X_ATTR;
	static const std::string Y_ATTR;
	static const std::string Z_ATTR;
	
	static const std::string R_ATTR;
	static const std::string G_ATTR;
	static const std::string B_ATTR;
	
	static const std::string D_ATTR;
	
	static const std::string RADIUS_ATTR;
	static const std::string POWER_ATTR;
	
	static const std::string ENLIGHTMENT_ATTR;
	static const std::string ENL_PHONG;
	
	static const std::string REFLECTING_ATTR;
	static const std::string KR_ATTR;
	static const std::string GLOSSY_FOCAL_ATTR;
	static const std::string GLOSSY_WIDTH_ATTR;
	static const std::string REFRACTING_ATTR;
	static const std::string N_ATTR;
	static const std::string KT_ATTR;
	
	static const std::string PERLIN_ATTR;
	static const std::string EPSILON_ATTR;
	
private:

	void parseBackgroundElement(TiXmlElement* backgroundElement, Scene *scene) const throw(std::exception);

	void parseObserverElement(TiXmlElement* observerElement, Scene *scene) const throw(std::exception);
	Point* parseEyeElement(TiXmlElement* eyeElement) const throw(std::exception);
	Point* parseSightElement(TiXmlElement* sightElement) const throw(std::exception);
	
	void parseLightList(TiXmlElement* lightListElement, Scene* scene) const throw(std::exception);
	void parseLightElement(TiXmlElement* lightElement, Scene* scene) const throw(std::exception);
	
	void parseObjectList(TiXmlElement* objectListElement, Scene* scene) const throw(std::exception);
	void parseObjectElement(TiXmlElement* objectElement, Scene* scene) const throw(std::exception);
	void parseSphereElement(TiXmlElement* sphereElement, Scene* scene) const throw(std::exception);
	void parsePlanElement(TiXmlElement* planElement, Scene* scene) const throw(std::exception);
	
	Enlightment* parseEnlightment(TiXmlElement* objectElement) const throw(std::exception);
	
public :
	SceneParser(void){};
	~SceneParser(void){};
	
	Scene* parse(std::string filePath) const throw(std::exception);
};

#endif //SCENE_PARSER_H
