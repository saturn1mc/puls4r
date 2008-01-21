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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
public:
	
	Image(char *name, int np, int nl){
		
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
	
	int getW(){
		return w;
	}
	
	int getH(){
		return h;
	}
	
	static void putshort(FILE *file, int i);
	static void putint(FILE *file, int i);
	static void writeBMP24(FILE *file, unsigned char *pic24, int w, int h);
	void WriteBitmap();
};

#endif //IMAGE_H
