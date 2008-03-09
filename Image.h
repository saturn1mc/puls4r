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

#define MALLOC(ptr, type, n) { ptr=(type* )malloc(sizeof(type)*((size_t)(n))); }
#define CALLOC(ptr, type, n) { ptr=(type* )calloc(1,sizeof(type)*((size_t)(n))); }
#define REALLOC(ptr, type, n) { ptr=(type* )realloc(ptr,sizeof(type)*((size_t)(n))); }
#define FREE(ptr) free(ptr);

class Image{
private:
	
	int w;
	int h;
	int antialiasing;
	unsigned char* pic;
	char* filename;
	int writingPos;
	
public:
	
	Image(char* _filename, int _w, int _h) : w(_w), h(_h), antialiasing(1), pic(0), filename(0), writingPos(0){
		
		MALLOC(filename, char, strlen(_filename)+1);
		strcpy(filename, _filename);
			
		MALLOC(pic, unsigned char, _w*_h*3);
	}	
	
	Image(char* _filename, int _w, int _h, int _antialiasing) : w(_w), h(_h), antialiasing(_antialiasing), pic(0), filename(0), writingPos(0){
		
		MALLOC(filename, char, strlen(_filename)+1);
		strcpy(filename, _filename);
		
		MALLOC(pic, unsigned char, _w*_h*3);
		
		if(antialiasing <= 0){
			antialiasing = 1;
		}
	}
	
	Image(const Image& image) : w(image.w), h(image.h), antialiasing(image.antialiasing), pic(0), filename(0), writingPos(image.writingPos){
		MALLOC(filename, char, strlen(image.filename)+1);
		strcpy(filename, image.filename);
		
		MALLOC(pic, unsigned char, image.w*image.h*3);
	}
	
	Image(const Image* image) : w(image->w), h(image->h), antialiasing(image->antialiasing), pic(0), filename(0), writingPos(image->writingPos){
		MALLOC(filename, char, strlen(image->filename)+1);
		strcpy(filename, image->filename);
		
		MALLOC(pic, unsigned char, image->w*image->h*3);
	}
	
	~Image(){
		free(pic);
		free(filename);
	}
	
	void writePixel(Color* color);
	
	int getW(void) const {return w;}
	int getH(void) const {return h;}
	int getAntialiasing(void) const {return antialiasing;}
	char* getFilename(void) const {return filename;}
	
	void setFilename(char* _filename){
		free(filename);
		
		MALLOC(filename, char, strlen(_filename)+1);
		strcpy(filename, _filename);
	}
	
	void reset(void){
		free(pic);
		MALLOC(pic, unsigned char, w*h*3);
		writingPos = 0;
	}
	
	static void putshort(FILE* file, int i);
	static void putint(FILE* file, int i);
	static void writeBMP24(FILE* file, unsigned char* pic24, int w, int h);
	
	void writeBitmap(void);
	
	Image& operator=(const Image& image){
		
		free(filename);
		free(pic);
		
		w = image.w;
		h = image.h;
		
		writingPos = image.writingPos;
		
		MALLOC(filename, char, strlen(image.filename)+1);
		strcpy(filename, image.filename);
		
		MALLOC(pic, unsigned char, image.w*image.h*3);
		
		antialiasing = image.antialiasing;
		
		return *this;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits>& operator << (std::basic_ostream<charT,traits>& strm, const Image& img){
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
	s << "Antialiasing : " << img.getAntialiasing() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

template <class charT, class traits> std::basic_ostream<charT,traits>& operator << (std::basic_ostream<charT,traits>& strm, const Image* img){
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
	s << "Width : " << img->getW() << std::endl;
	s << "Height : " << img->getH() << std::endl;
	s << "Filename : " << img->getFilename() << std::endl;
	s << "Antialiasing : " << img->getAntialiasing() << std::endl;
	s << "---------------------------" << std::endl;
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif //IMAGE_H
