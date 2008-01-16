/*
 *  Vector.h
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <sstream>
#include <cmath>

#include "Point.h"

class Vector{
private:
	
	double x;
	double y;
	double z;
	double t;
	
public:
	
	Vector(void){
		x = 0;
		y = 0;
		z = 0;
		t = 1;
	}
		
	Vector(double _x, double _y, double _z) {
		x = _x; 
		y = _y; 
		z = _z; 
		t = 1;
	}	
	
	Vector(Point &a, Point &b) {
		x = b.getX() - a.getX(); 
		y = b.getY() - a.getY(); 
		z = b.getZ() - a.getZ(); 
		t = 1;
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
	
	double set(int d, int val){
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
	
	Vector& operator=(const Vector& v){
		x = v.x;
		y = v.y;
		z = v.z;
		
		return *this;
	}
	
	void normalize(){
		double n = norm(*this);
		x /= n;
		y /= n;
		z /= n;
	}
	
	double norm(const Vector& v){
		sqrt(v*v);
	}
	
	double operator*(const Vector& v) const{
		return (x*v.getX()) + (y*v.getY()) + (z*v.getZ());
	}
	
	Vector& operator^(const Vector& v) const{
		Vector *res = new Vector(
				  (y*v.getZ()) - (z*v.getY()),
				  (z*v.getX()) - (x*v.getZ()),
				  (x*v.getY()) - (y*v.getX())
				);
		return *res;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Vector &v){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "[" << v.getX() << "," << v.getY() << "," << v.getZ()  << "," << v.getT() << "]";
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //VECTOR_H
