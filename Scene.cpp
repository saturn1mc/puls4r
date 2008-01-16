#include "Scene.h"

void Scene::add(Object *obj){
	objects.push_front(obj);
}
	
void Scene::rayTrace(void){
	for(int l=0; l<nl; l++){
		for(int p=0; p<np; p++){
			
			Intersection *current_intersection = 0;
			Point *pix = new Point(p, l, 0);
			Ray &ray = observer->ray(pix);
			delete(pix);
			
			for(list<Object *>::iterator iter = objects.begin(); iter != objects.end(); ++iter){
				Intersection *candidate = (*iter)->intersection(ray);
				
				if(candidate != 0){
					if(current_intersection == 0 || current_intersection.getT() > ){
					
					}
				}
			}
			
		}
	}
}

double Scene::focal(void){
	return ( (np / 2.0) / tan(alpha/2.0) );
}
