CC = g++
CC_OPTIONS = 
LNK_OPTIONS = 
INCLUDE = -I.
PROJ=pulsar

pulsar : \
	./main.o\
	./Observer.o\
	./Plan.o\
	./Sphere.o\
	./Scene.o\
	./bmp.o\
		
	$(CC) $(LNK_OPTIONS) \
	./main.o\
	./Observer.o\
	./Plan.o\
	./Sphere.o\
	./Scene.o\
	./bmp.o\
	-o $(PROJ)

clean : 
	rm \
	./main.o\
	./Observer.o\
	./Plan.o\
	./Sphere.o\
	./Scene.o\
	./bmp.o\
	*~\
	$(PROJ)


./main.o : main.cpp
	$(CC) $(CC_OPTIONS) main.cpp -c $(INCLUDE) -o ./main.o

./Observer.o : Observer.h
	$(CC) $(CC_OPTIONS) Observer.cpp -c $(INCLUDE) -o ./Observer.o

./Plan.o : Plan.h
	$(CC) $(CC_OPTIONS) Plan.cpp -c $(INCLUDE) -o ./Plan.o

./Sphere.o : Sphere.h
	$(CC) $(CC_OPTIONS) Sphere.cpp -c $(INCLUDE) -o ./Sphere.o

./Scene.o : Scene.h
	$(CC) $(CC_OPTIONS) Scene.cpp -c $(INCLUDE) -o ./Scene.o

./bmp.o :
	$(CC) $(CC_OPTIONS) bmp.c -c $(INCLUDE) -o ./bmp.o
