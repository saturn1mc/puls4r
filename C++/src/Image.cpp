/*
 *  Image.cpp
 *  puls4r
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

void Image::writePixel(Color* color){
	
	pic[writingPos] = (unsigned char) ((int)(255 * color->getR()));
	pic[writingPos+1] = (unsigned char) ((int)(255 * color->getG()));
	pic[writingPos+2] = (unsigned char) ((int)(255 * color->getB()));
	
	writingPos += 3;
}

// Ecrit un short dans un fichier
void Image::putshort(FILE* file, int i){
	int c, c1;
	
	c = ((unsigned int ) i) & 0xff;  
	c1 = (((unsigned int) i)>>8) & 0xff;
	putc(c, file);   
	putc(c1, file);
}


// Ecrit un int dans un fichier
void Image::putint(FILE* file, int i){
	int c, c1, c2, c3;
	
	c  = ((unsigned int ) i)      & 0xff;  
	c1 = (((unsigned int) i)>>8)  & 0xff;
	c2 = (((unsigned int) i)>>16) & 0xff;
	c3 = (((unsigned int) i)>>24) & 0xff;
	
	putc(c, file);
	putc(c1, file);
	putc(c2, file);
	putc(c3, file);
}

// write bmp 24 bits in file
void Image::writeBMP24(FILE* file, unsigned char* pic24, int w, int h){
	int   i, j, pad_bytes;
	unsigned char* pp;
	
	pad_bytes = (4 - ((w*3) % 4)) & 0x03;  // # of pad bytes to write at EOscanline 
	
	for (i=h-1; i>=0; i--){
		
		pp = pic24 + (i * w * 3);
		
		for (j=0; j<w; j++){
			putc(pp[2], file);
			putc(pp[1], file);
			putc(pp[0], file);
			pp += 3;
		}
		
		for (j=0; j<pad_bytes; j++) {
			putc(0, file);
		}
    }
}

// Ecriture d'un buffer image dans un fichier au format BMP
void Image::writeBitmap(void){
	
	int i, nbits = 24, bperlin;
	FILE* file;
	
	file=fopen(filename, "wb");
	
	// nombre d'octets ecrits par ligne
	bperlin = ((w * nbits + 31) / 32) * 4;   
	
	// BMP file magic number 
	putc('B', file);  putc('M', file);           
	
	// calcul de la taille du fichier et ecriture
	i = 14 +        // taille du header bitmap
		40 +	      // taille du header d'info 
		bperlin * h;  // taille du buffer image 
	
	putint(file, i);
	putshort(file, 0);        // reserve
	putshort(file, 0);        // reserve 
	putint(file, 14 + 40);    
	putint(file, 40);         // taille du header bitmap
	putint(file, w);          // largeur
	putint(file, h);          // hauteur 
	putshort(file, 1);        // plans: doit etre 1' 
	putshort(file, nbits);    // nombre de bits/pixel = 24
	putint(file, 0);          // Compression:  BI_RGB
	putint(file, bperlin*h);  // taille du buffer image
	putint(file, 75 * 39);    
	putint(file, 75 * 39);     
	putint(file, 0);			// nombre de couleurs used dans la colormap
	putint(file, 0);           
	
	// Ecriture du buffer image dans un fichier
	writeBMP24(file, pic, w, h);
	
	fprintf(stdout, "\tSaved in file: %s\n", filename);
	
	fclose(file);
}
