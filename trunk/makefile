CC = g++
CC_OPTIONS = -O3
LNK_OPTIONS = 
INCLUDE = -I.
PROJ=pulsar

pulsar : main.o Observer.o Plan.o Sphere.o Triangle.o Scene.o Image.o Linear.o Phong.o Lambert.o 
	$(CC) $(LNK_OPTIONS) main.o Observer.o Plan.o Sphere.o Triangle.o Scene.o Image.o Linear.o Phong.o Lambert.o -o $(PROJ)

clean :
	rm -fr *.o *~ $(PROJ)

main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o main.o

Observer.o : Observer.h
	$(CC) $(CC_OPTIONS) Observer.cpp -c $(INCLUDE) -o Observer.o

Plan.o : Object.h Plan.h
	$(CC) $(CC_OPTIONS) Plan.cpp -c $(INCLUDE) -o Plan.o

Sphere.o : Object.h Sphere.h
	$(CC) $(CC_OPTIONS) Sphere.cpp -c $(INCLUDE) -o Sphere.o

Triangle.o : Object.h Triangle.h
	$(CC) $(CC_OPTIONS) Triangle.cpp -c $(INCLUDE) -o Triangle.o

Scene.o : Scene.h
	$(CC) $(CC_OPTIONS) Scene.cpp -c $(INCLUDE) -o Scene.o

Image.o : Image.h
	$(CC) $(CC_OPTIONS) Image.cpp -c $(INCLUDE) -o Image.o

Linear.o : Enlightment.h Linear.h
	$(CC) $(CC_OPTIONS) Linear.cpp -c $(INCLUDE) -o Linear.o

Phong.o : Enlightment.h Phong.h
	$(CC) $(CC_OPTIONS) Phong.cpp -c $(INCLUDE) -o Phong.o

Lambert.o : Enlightment.h Lambert.h
	$(CC) $(CC_OPTIONS) Lambert.cpp -c $(INCLUDE) -o Lambert.o
