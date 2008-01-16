#include "Scene.h"

void Scene::add(Object *obj){
	objects.push_front(obj);
}
	
void Scene::rayTrace(void){
	//TODO
}

double Scene::focal(void){
	return (np / 2.0) / tan(alpha/2.0);
}
