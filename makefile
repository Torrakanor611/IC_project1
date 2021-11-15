# *****************************************************
# Variables to control Makefile operation
 
CC=g++
CFLAGS=-Wall -g
SNDFILE=$$(pkg-config --libs sndfile)
OPENCV4=$$(pkg-config --libs --cflags opencv4)
MATPLOTLIB=-std=c++11 -I/usr/include/python3.8 -lpython3.8

# ****************************************************
# Targets needed to bring the executable up to date

ex3:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex3.cpp -o bin/ex3

ex3sndfile:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex3sndfile.cpp -o bin/ex3sndfile $(SNDFILE)

ex4:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex4.cpp -o bin/ex4 $(OPENCV4)

ex4video:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex4video.cpp -o bin/ex4video $(OPENCV4)

ex5:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex5.cpp -o bin/ex5 $(MATPLOTLIB)

ex6:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex6.cpp -o bin/ex6 $(SNDFILE)

ex7:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex7.cpp -o bin/ex7 $(OPENCV4)

ex8:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex8.cpp -o bin/ex8 $(MATPLOTLIB)

ex10:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex10.cpp -o bin/ex10

clean:
	rm -rf bin/ex3
	rm -rf bin/ex3sndfile
	rm -rf bin/ex4
	rm -rf bin/ex4video
	rm -rf bin/ex5
	rm -rf bin/ex6
	rm -rf bin/ex7
	rm -rf bin/ex8
	rm -rf bin/ex10