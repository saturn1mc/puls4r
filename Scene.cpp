#include "Scene.h"

void Scene::add(Object *obj){
	objects.push_front(obj);
}
	
void Scene::rayTrace(void){
	for(int l=-getH()/2; l<getH()/2; l++){
		
		for(int p=-getW()/2; p<getW()/2; p++){
			
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
			
			// ------- FOR TESTING PURPOSE
			if(current_intersection != 0){
				cout << "#";
			}
			else{
				cout << "-";
			}
			// -------
		}
		
		// ------- FOR TESTING PURPOSE
		cout << endl;
		// -------
	}
}

double Scene::focal(void){
	return ( (getW() / 2.0) / tan(observer->getAlpha()/2.0) );
}
