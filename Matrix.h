/*
 *  Matrix.h
 *  RayTracing
 *
 *  Created by Camille on 19/12/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream>

#include "Point.h"
#include "Vector.h"

class Matrix{
private:
	
	double content[4][4];
	
public:
	
	Matrix(void){
		for(int i =0; i<4; i++){
			for(int j=0; j<4; j++){
				content[i][j] = 0;
			}
		}
	}
	
	Matrix(const Vector &l1, const Vector &l2, const Vector &l3, const Point &l4){
		content[0][0] = l1.getX();
		content[0][1] = l1.getY();
		content[0][2] = l1.getZ();
		content[0][3] = 0;
		
		content[1][0] = l2.getX();
		content[1][1] = l2.getY();
		content[1][2] = l2.getZ();
		content[1][3] = 0;
		
		content[2][0] = l3.getX();
		content[2][1] = l3.getY();
		content[2][2] = l3.getZ();
		content[2][3] = 0;
		
		content[3][0] = l4.getX();
		content[3][1] = l4.getY();
		content[3][2] = l4.getZ();
		content[3][3] = 1;
	}
	
	void loadIdentity(void) {
		
		content[0][0] = 1;
		content[0][1] = 0;
		content[0][2] = 0;
		content[0][3] = 0;
		
		content[1][0] = 0;
		content[1][1] = 1;
		content[1][2] = 0;
		content[1][3] = 0;
		
		content[2][0] = 0;
		content[2][1] = 0;
		content[2][2] = 1;
		content[2][3] = 0;
		
		content[3][0] = 0;
		content[3][1] = 0;
		content[3][2] = 0;
		content[3][3] = 1;
	}
	
	void loadRotateX(const double angle) {
		
		double cosA = cos(angle), sinA = sin(angle);
		
		content[0][0]  = 1;
		content[0][1]  = 0;
		content[0][2]  = 0;
		content[0][3]  = 0;
		
		content[1][0]  = 0;
		content[1][1]  = cosA;
		content[1][2]  = -sinA;
		content[1][3]  = 0;
		
		content[2][0]  = 0;
		content[2][1]  = sinA;
		content[2][2] = cosA;
		content[2][3] = 0;
		
		content[3][0] = 0;
		content[3][1] = 0;
		content[3][2] = 0;
		content[3][3] = 1;
	}
	
	void loadRotateY(const double angle) {
		double cosA = cos(angle), sinA = sin(angle);
		
		content[0][0]  = cosA;
		content[0][1]  = 0;
		content[0][2]  = sinA;
		content[0][3]  = 0;
		
		content[1][0]  = 0;
		content[1][1]  = 1;
		content[1][2]  = 0;
		content[1][3]  = 0;
		
		content[2][0]  = -sinA;
		content[2][1]  = 0;
		content[2][2] = cosA;
		content[2][3] = 0;
		
		content[3][0] = 0;
		content[3][1] = 0;
		content[3][2] = 0;
		content[3][3] = 1;
	}
	
	void loadRotateZ(const double angle) {
		double cosA = cos(angle), sinA = sin(angle);
		
		content[0][0]  = cosA;
		content[0][1]  = -sinA;
		content[0][2]  = 0;
		content[0][3]  = 0;
		
		content[1][0]  = sinA;
		content[1][1]  = cosA;
		content[1][2]  = 0;
		content[1][3]  = 0;
		
		content[2][0]  = 0;
		content[2][1]  = 0;
		content[2][2] = 1;
		content[2][3] = 0;
		
		content[3][0] = 0;
		content[3][1] = 0;
		content[3][2] = 0;
		content[3][3] = 1;
	}
	
	void loadTranslation( const double x, const double y, const double z ){
		content[0][0] = 1;
		content[0][1] = 0;
		content[0][2] = 0;
		content[0][3] = x;
		
		content[1][0] = 0;
		content[1][1] = 1;
		content[1][2] = 0;
		content[1][3] = y;
		
		content[2][0] = 0;
		content[2][1] = 0;
		content[2][2] = 1;
		content[2][3] = z;
		
		content[3][0] = 0;
		content[3][1] = 0;
		content[3][2] = 0;
		content[3][3] = 1;
	}
	
	void loadTranslation(const Vector &v){
		loadTranslation(v.getX(), v.getY(), v.getZ());
	}

	double operator()(int l, int c) const{
		return content[l][c];
	}
	
	Matrix& t(void){
		Matrix *res = new Matrix();
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				res->content[i][j] = content[j][i];
			}
		}
		
		return *res;
	}
	
	Matrix& operator*(const Matrix &m){
		
		Matrix *res = new Matrix();
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				for(int k=0; k<4; k++){
					res->content[i][j] += content[i][k] * m.content[k][j];
				}	
			}
		}
	}
	
	Point& operator*(const Point &p){
		
		Point *res = new Point();
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				res->set(i, res->get(i) + content[i][j] * p.get(j));
			}
		}
		
		return *res;
	}
};

template <class charT, class traits> std::basic_ostream<charT,traits> &operator << (std::basic_ostream<charT,traits>& strm, const Matrix &m){
	/* From : "C++ Standard Library, The A Tutorial And Reference - Nicolai M. Josuttis - Addison Wesley - 1999" */
	
	/* string stream
	* - with same format
	* - without special field width
	*/
	std::basic_ostringstream<charT,traits> s;
	s.copyfmt(strm);
	s.width(0);
	
	// fill string stream
	for(int i=0; i<4; i++){
		s << "|" << m(i, 0) << "," << m(i, 1) << "," << m(i, 2)  << "," << m(i, 3) << "|" << std::endl;
	}
	
	// print string stream
	strm << s.str();
	
	return strm;
}

#endif // MATRIX_H
