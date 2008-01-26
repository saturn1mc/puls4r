/*
 *  Point.h
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <sstream>

class Point{
private:
	
	double x;
	double y;
	double z;
	double t;
	
public:
	
	Point(void){
		x = 0;
		y = 0;
		z = 0;
		t = 0;
	}
	
	Point(double _x, double _y, double _z) {
		x = _x; 
		y = _y; 
		z = _z; 
		t = 0;
	}
	
	double get(int d) const{
		switch(d){
			case 0:
				return x;
				break;
				
			case 1:
				return y;
				break;
				
			case 2:
				return z;
				break;
				
			case 3:
				return t;
				break;
		}
	}
	
	double getX(void) const { return x; }
	double getY(void) const { return y; }
	double getZ(void) const { return z; }
	double getT(void) const { return t; }
	
	double set(int d, double val){
		switch(d){
			case 0:
				x = val;
				break;
				
			case 1:
				y = val;
				break;
				
			case 2:
				z = val;
				break;
				
			case 3:
				t = val;
				break;
		}
	}
	
	void setX(double _x) {x = _x;}
	void setY(double _y) {y = _y;}
	void setZ(double _z) {z = _z;}
	void setT(double _t) {t = _t;}
	
	Point& operator=(const Point& a){
		x = a.x;
		y = a.y;
		z = a.z;
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Point &p){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "(" << p.getX() << "," << p.getY() << "," << p.getZ()  << "," << p.getT() << ")";
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //POINT_H
