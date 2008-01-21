#include "Scene.h"

void Scene::addObject(Object *obj){
	objects.push_front(obj);
}

void Scene::addLight(Light *light){
	lights.push_front(light);
}
	
void Scene::rayTrace(void){
	for(int l=-getH()/2; l<getH()/2; l++){
		
		for(int p=-getW()/2; p<getW()/2; p++){
			
			Intersection *current_intersection = 0;
			Point *pix = new Point(p, l, focal());
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
			
			if(current_intersection != 0){
				
				Color *color;
				
				for(list<Light *>::iterator iter = lights.begin(); iter != lights.end(); ++iter){
					
					//TODO enlight
					color = new Color(current_intersection->getColor());
				}
				
				img->writePixel(*color);
				delete(color);
			}
			else{
				img->writePixel(*background);
			}
		}
	}
	
	img->writeBitmap();
}

double Scene::focal(void) const{
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}
