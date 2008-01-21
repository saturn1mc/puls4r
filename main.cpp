/*
 *  main.cpp
 *  RayTracing
 *
 *  Created by Camille on 09/01/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include "Observer.h"

using namespace std;

int main (int argc, char * const argv[]) {
	Observer *obs = new Observer(new Point(6.0, 2.0, 6.0), new Point(0.0, 0.0, 0.0));
	Image *img = new Image("/Users/camille/Desktop", , );
}
