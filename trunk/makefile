###################################################
#
# Makefile for pulsar
# Creator [Xcode -> Makefile Ver: Feb 14 2007 09:18:41]
# Created: [Sat Mar  8 12:25:41 2008]
#
###################################################

#
# Macros
#

CC = g++ 
CC_OPTIONS = -O3 -Wall -pedantic 
LNK_OPTIONS = 


#
# INCLUDE directories for pulsar
#

INCLUDE = -I.


#
# Build pulsar
#

pulsar : \
		./Sphere.o\
		./Scene.o\
		./Plan.o\
		./Phong.o\
		./Linear.o\
		./Lambert.o\
		./main.o\
		./Image.o\
		./Observer.o\
		./PhotonShooter.o\
		./Quadric.o\
		./Triangle.o\
		./PhotonMap.o\
		./Box.o\
		./Perlin.o
	$(CC) $(LNK_OPTIONS) \
		./Sphere.o\
		./Scene.o\
		./Plan.o\
		./Phong.o\
		./Linear.o\
		./Lambert.o\
		./main.o\
		./Image.o\
		./Observer.o\
		./PhotonShooter.o\
		./Quadric.o\
		./Triangle.o\
		./PhotonMap.o\
		./Box.o\
		./Perlin.o\
		-o pulsar

clean : 
		rm \
		./Sphere.o\
		./Scene.o\
		./Plan.o\
		./Phong.o\
		./Linear.o\
		./Lambert.o\
		./main.o\
		./Image.o\
		./Observer.o\
		./PhotonShooter.o\
		./Quadric.o\
		./Triangle.o\
		./PhotonMap.o\
		./Box.o\
		./Perlin.o\
		pulsar

install : pulsar
		cp pulsar pulsar

#
# Build the parts of pulsar
#


# Item # 1 -- Sphere --
./Sphere.o : Sphere.cpp
	$(CC) $(CC_OPTIONS) Sphere.cpp -c $(INCLUDE) -o ./Sphere.o


# Item # 2 -- Scene --
./Scene.o : Scene.cpp
	$(CC) $(CC_OPTIONS) Scene.cpp -c $(INCLUDE) -o ./Scene.o


# Item # 3 -- Plan --
./Plan.o : Plan.cpp
	$(CC) $(CC_OPTIONS) Plan.cpp -c $(INCLUDE) -o ./Plan.o


# Item # 4 -- Phong --
./Phong.o : Phong.cpp
	$(CC) $(CC_OPTIONS) Phong.cpp -c $(INCLUDE) -o ./Phong.o


# Item # 5 -- Linear --
./Linear.o : Linear.cpp
	$(CC) $(CC_OPTIONS) Linear.cpp -c $(INCLUDE) -o ./Linear.o


# Item # 6 -- Lambert --
./Lambert.o : Lambert.cpp
	$(CC) $(CC_OPTIONS) Lambert.cpp -c $(INCLUDE) -o ./Lambert.o


# Item # 7 -- main --
./main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o ./main.o


# Item # 8 -- Image --
./Image.o : Image.cpp
	$(CC) $(CC_OPTIONS) Image.cpp -c $(INCLUDE) -o ./Image.o


# Item # 9 -- Observer --
./Observer.o : Observer.cpp
	$(CC) $(CC_OPTIONS) Observer.cpp -c $(INCLUDE) -o ./Observer.o


# Item # 10 -- PhotonShooter --
./PhotonShooter.o : PhotonShooter.cpp
	$(CC) $(CC_OPTIONS) PhotonShooter.cpp -c $(INCLUDE) -o ./PhotonShooter.o


# Item # 11 -- Quadric --
./Quadric.o : Quadric.cpp
	$(CC) $(CC_OPTIONS) Quadric.cpp -c $(INCLUDE) -o ./Quadric.o


# Item # 12 -- Triangle --
./Triangle.o : Triangle.cpp
	$(CC) $(CC_OPTIONS) Triangle.cpp -c $(INCLUDE) -o ./Triangle.o


# Item # 13 -- PhotonMap --
./PhotonMap.o : PhotonMap.cpp
	$(CC) $(CC_OPTIONS) PhotonMap.cpp -c $(INCLUDE) -o ./PhotonMap.o


# Item # 14 -- Box --
./Box.o : Box.cpp
	$(CC) $(CC_OPTIONS) Box.cpp -c $(INCLUDE) -o ./Box.o


# Item # 15 -- Perlin --
./Perlin.o : Perlin.cpp
	$(CC) $(CC_OPTIONS) Perlin.cpp -c $(INCLUDE) -o ./Perlin.o


##### END RUN ####
