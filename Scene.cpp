#include "Scene.h"

void Scene::add(Object *obj){
	objects.push_front(obj);
}
	
void Scene::rayTrace(void){
	for(int l=0; l<img->getH(); l++){
		for(int p=0; p<img->getW(); p++){
			
			Intersection *current_intersection = 0;
			Point *pix = new Point(p, l, 0);
			Ray &ray = observer->ray(pix);
			delete(pix);
			
			for(list<Object *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
				Intersection *candidate = (*iter)->intersection(ray);
				
				if(candidate != 0){
					if(current_intersection == 0 || current_intersection->getT() > candidate->getT()){
						current_intersection = candidate;
					}
				}
			}
			
			//TODO ecrire pixel
			
		}
	}
}

double Scene::focal(void){
	return ( (img->getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}
