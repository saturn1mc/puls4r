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

#include "Color.h"
#include "Intersection.h"

class Image{
private:
	
	unsigned char *pic;
	int w;
	int h;
	char *filename;
	
public:
		
	Image(unsigned char *_pic, int _w, int _h, char *_filename){
		pic = _pic;
		w = _w;
		h = _h;
		filename = _filename;
	}
};

#endif //IMAGE_H
