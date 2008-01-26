/*
 *  Image.h
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Color.h"

#define MALLOC(ptr, type, n) { ptr=(type *)malloc(sizeof(type)*((size_t)(n))); }
#define CALLOC(ptr, type, n) { ptr=(type *)calloc(1,sizeof(type)*((size_t)(n))); }
#define REALLOC(ptr, type, n) { ptr=(type *)realloc(ptr,sizeof(type)*((size_t)(n))); }
#define FREE(ptr) free(ptr);

class Image{
private:
	
	unsigned char *pic;
	int w;
	int h;
	char *filename;
	
	int writingPos;
	
public:
	
	Image(char *name, int np, int nl){
		
		writingPos = 0;
		
		MALLOC(filename, char, strlen(name)+1);
		strcpy(filename, name);
		
		w = np;
		h = nl;
			
		MALLOC(pic, unsigned char, np*nl*3);
	}	
	
	Image(unsigned char *_pic, int _w, int _h, char *_filename){
		pic = _pic;
		w = _w;
		h = _h;
		filename = _filename;
	}
	
	int getW(void) const {return w;}
	
	int getH(void) const {return h;}
	
	char *getFilename(void) const {return filename;}
	
	static void putshort(FILE *file, int i);
	static void putint(FILE *file, int i);
	static void writeBMP24(FILE *file, unsigned char *pic24, int w, int h);
	
	void writePixel(Color &color);
	
	void writeBitmap(void);
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Image &img){
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
	s << "Image:" << std::endl;
	s << "---------------------------" << std::endl;
	s << "Width : " << img.getW() << std::endl;
	s << "Height : " << img.getH() << std::endl;
	s << "Filename : " << img.getFilename() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //IMAGE_H
