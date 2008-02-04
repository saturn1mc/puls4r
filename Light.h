/*
 *  Light.h
 *  RayTracing
 *
 *  Created by Camille on 21/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <sstream>

#include "Point.h"
#include "Color.h"

class Light{
private:
	
	Point* source;
	Color* color;
	
public:
	Light(Point* _source, Color* _color) : source(new Point(_source)), color(new Color(_color)) {}
	
	Light(const Light& light) : source(new Point(light.source)), color(new Color(light.color)) {}
	
	~Light(){
		delete(source);
		delete(color);
	}
	
	Point* getSource(void) const {return source;}
	Color* getColor(void) const {return color;}
	
	Light& operator=(const Light& light){
		delete(source);
		delete(color);
		
		source = new Point(light.source);
		color = new Color(light.color);
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits>& operator<<(std::basic_ostream<charT,traits>& strm, const Light& light){
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
	s << "Light :" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Source : " << light.getSource() << std::endl;
	s << "Color : " << light.getColor() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Light *light){
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
	s << "Light :" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Source : " << light->getSource() << std::endl;
	s << "Color : " << light->getColor() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //LIGHT_H
