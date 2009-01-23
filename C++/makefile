###################################################
#
# Makefile for Puls4r
#
###################################################

#
# Macros
#

CC = g++
CC_OPTIONS = -g -Wall -pedantic
LNK_OPTIONS = 
PROGRAM = pulsar

#
# INCLUDE directories for pulsar
#

INCLUDE = -I.

#
# Build pulsar
#

all : \
		Sphere.o\
		Scene.o\
		Plan.o\
		Phong.o\
		Linear.o\
		Lambert.o\
		main.o\
		Image.o\
		Observer.o\
		PhotonShooter.o\
		tinyxmlparser.o\
		tinyxmlerror.o\
		tinyxml.o\
		SceneParser.o\
		tinystr.o\
		Quadric.o\
		Triangle.o\
		PhotonMap.o\
		Box.o\
		Perlin.o
	$(CC) $(CC_OPTIONS) $(LNK_OPTIONS) \
		Sphere.o\
		Scene.o\
		Plan.o\
		Phong.o\
		Linear.o\
		Lambert.o\
		main.o\
		Image.o\
		Observer.o\
		PhotonShooter.o\
		tinyxmlparser.o\
		tinyxmlerror.o\
		tinyxml.o\
		SceneParser.o\
		tinystr.o\
		Quadric.o\
		Triangle.o\
		PhotonMap.o\
		Box.o\
		Perlin.o\
		-o $(PROGRAM)

clean : 
		rm *.o $(PROGRAM)
		
cleanWin : 
		rm *.o $(PROGRAM).exe

#
# Build the parts of pulsar
#

# -- Sphere --
Sphere.o : Sphere.cpp
	$(CC) $(CC_OPTIONS) Sphere.cpp -c $(INCLUDE) -o Sphere.o

# -- Scene --
Scene.o : Scene.cpp
	$(CC) $(CC_OPTIONS) Scene.cpp -c $(INCLUDE) -o Scene.o

# -- Plan --
Plan.o : Plan.cpp
	$(CC) $(CC_OPTIONS) Plan.cpp -c $(INCLUDE) -o Plan.o

# -- Phong --
Phong.o : Phong.cpp
	$(CC) $(CC_OPTIONS) Phong.cpp -c $(INCLUDE) -o Phong.o

# -- Linear --
Linear.o : Linear.cpp
	$(CC) $(CC_OPTIONS) Linear.cpp -c $(INCLUDE) -o Linear.o

# Item # 6 -- Lambert --
Lambert.o : Lambert.cpp
	$(CC) $(CC_OPTIONS) Lambert.cpp -c $(INCLUDE) -o Lambert.o

# -- Image --
Image.o : Image.cpp
	$(CC) $(CC_OPTIONS) Image.cpp -c $(INCLUDE) -o Image.o

# -- Observer --
Observer.o : Observer.cpp
	$(CC) $(CC_OPTIONS) Observer.cpp -c $(INCLUDE) -o Observer.o

# -- PhotonShooter --
PhotonShooter.o : PhotonShooter.cpp
	$(CC) $(CC_OPTIONS) PhotonShooter.cpp -c $(INCLUDE) -o PhotonShooter.o

# -- SceneParser --
SceneParser.o : SceneParser.cpp
	$(CC) $(CC_OPTIONS) SceneParser.cpp -c $(INCLUDE) -o SceneParser.o

# -- tinystr --
tinystr.o : tinystr.cpp
	$(CC) $(CC_OPTIONS) tinystr.cpp -c $(INCLUDE) -o tinystr.o

# -- tinyxmlparser --
tinyxmlparser.o : tinyxmlparser.cpp
	$(CC) $(CC_OPTIONS) tinyxmlparser.cpp -c $(INCLUDE) -o tinyxmlparser.o

# -- tinyxmlerror --
tinyxmlerror.o : tinyxmlerror.cpp
	$(CC) $(CC_OPTIONS) tinyxmlerror.cpp -c $(INCLUDE) -o tinyxmlerror.o
	
# -- tinyxml --
tinyxml.o : tinyxml.cpp
	$(CC) $(CC_OPTIONS) tinyxml.cpp -c $(INCLUDE) -o tinyxml.o

# -- Quadric --
Quadric.o : Quadric.cpp
	$(CC) $(CC_OPTIONS) Quadric.cpp -c $(INCLUDE) -o Quadric.o

# -- Triangle --
Triangle.o : Triangle.cpp
	$(CC) $(CC_OPTIONS) Triangle.cpp -c $(INCLUDE) -o Triangle.o

# -- PhotonMap --
PhotonMap.o : PhotonMap.cpp
	$(CC) $(CC_OPTIONS) PhotonMap.cpp -c $(INCLUDE) -o PhotonMap.o

# -- Box --
Box.o : Box.cpp
	$(CC) $(CC_OPTIONS) Box.cpp -c $(INCLUDE) -o Box.o

# -- Perlin --
Perlin.o : Perlin.cpp
	$(CC) $(CC_OPTIONS) Perlin.cpp -c $(INCLUDE) -o Perlin.o
	
# -- main --
main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o main.o
