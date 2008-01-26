/*
 *  Color.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

class Color{
private:
	
	double r;
	double g;
	double b;
	
public:
	
	Color(void){
		r = 0;
		g = 0;
		b = 0;
	}
	
	Color(Color &color){
		r = color.r;
		g = color.g;
		b = color.b;
	}
		
	Color(double _r, double _g, double _b)  throw(exception){
		
		if(_r < 0 || _r > 1 || _g < 0 || _g > 1 || _b < 0 || _b > 1){
			throw new exception();
		}
		
		r = _r;
		g = _g;
		b = _b;
	}
	
	~Color(){}
	
	double getR(void) const { return r; }
	double getG(void) const { return g; }
	double getB(void) const { return b; }	
	
	void setR(double _r) {r = _r;}
	void setG(double _g) {g = _g;}
	void setB(double _b) {b = _b;}
	
	
	Color &operator=(const Color &c){
		r = c.r;
		g = c.g;
		b = c.b;
		
		return *this;
	}
	
	Color& operator+(const Color& c){
		
		Color *res = new Color();
		
		res->r = (c.r + r) / 2.0;
		res->g = (c.g + g) / 2.0;
		res->b = (c.b + b) / 2.0;
		
		return *res;
	}
	
	Color& operator-(const Color& c){
		
		Color *res = new Color();
		
		if(r > c.r){
			res->r = r - c.r;
		}
		else{
			res->r = r;
		}
		
		if(g > c.g){
			res->g = g - c.g;
		}
		else{
			res->g = g;
		}

		if(r > c.b){
			res->b = b - c.b;
		}
		else{
			res->b = b;
		}		
		
		return *res;
	}
	
	Color& operator*(double coeff){
		
		Color *res = new Color();
		
		res->r = r * coeff;
		res->g = g * coeff;
		res->b = b * coeff;
		
		return *res;
	}
	
	Color& operator*(Color &color){
		
		Color *res = new Color();
		
		res->r = r * color.r;
		res->g = g * color.g;
		res->b = b * color.b;
		
		return *res;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Color &c){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	s << "{" << c.getR() << "," << c.getG() << "," << c.getB() << "}";
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //COLOR_H
