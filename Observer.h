/*
 *  Observer.h
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <sstream>

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"

class Observer{
private:
	
	Point* eye;
	Vector* sight;
	Matrix* view;
	double alpha;
	
	void initMatrix(void);
	
public:

	Observer(Point* _eye, Point* _sight, double _alpha) : eye(new Point(_eye)), sight(new Vector(eye, _sight)), alpha(_alpha), view(0){
		sight->normalize();
		initMatrix();
	}
	
	Observer(Point* _eye, Vector* _sight, double _alpha) : eye(new Point(_eye)), sight(new Vector(_sight)), alpha(_alpha), view(0) {	
		sight->normalize();
		initMatrix();
	}
	
	Observer(const Observer& observer) : eye(new Point(observer.eye)), sight(new Vector(observer.sight)), alpha(observer.alpha), view(new Matrix(observer.view)) {}
	Observer(const Observer* observer) : eye(new Point(observer->eye)), sight(new Vector(observer->sight)), alpha(observer->alpha), view(new Matrix(observer->view)) {}
	
	~Observer(){}
	
	Ray* ray(Point* sp);
	
	Point* getEye(void) const {return eye;}	
	Vector* getSight(void) const {return sight;}
	Matrix* getView(void) const {return view;}
	double getAlpha(void) const {return alpha;}
	void setAlpha(int _alpha) {alpha=_alpha;}
	
	Observer& operator=(const Observer& observer){
		
		//delete(eye);
		//delete(sight);
		//delete(view);
		
		eye = new Point(observer.eye);
		sight = new Vector(observer.sight);
		alpha = observer.alpha;
		view = new Matrix(observer.view);
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Observer* obs){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "---------------------------" << std::endl;
	s << "Observer :" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Eye : " << obs->getEye() << std::endl;
	s << "Sight : " << obs->getSight() << std::endl;
	s << "View : " << std::endl;
	s << obs->getView() << std::endl;
	s << "Alpha : " << obs->getAlpha() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //OBSERVER_H
