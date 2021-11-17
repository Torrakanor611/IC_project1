# *****************************************************
# Variables to control Makefile operation
 
CC=g++
CFLAGS=-Wall -g -std=c++11
SNDFILE=$$(pkg-config --libs sndfile)
OPENCV4=$$(pkg-config --libs --cflags opencv4)
MATPLOTLIB=-I/usr/include/python3.8 -lpython3.8

# ****************************************************
# Targets needed to bring the executable up to date

all:
	@ make --no-print-directory ex2 ex3 ex3sndfile ex4 ex4video ex5 ex6 ex7 ex8 ex10

ex2:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex2.cpp -o bin/ex2

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
	@ $(CC) $(CFLAGS) ParteC/ex6.cpp -o bin/ex6 $(SNDFILE) $(MATPLOTLIB)

ex7:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex7.cpp -o bin/ex7 $(OPENCV4)

ex8:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex8.cpp -o bin/ex8 $(MATPLOTLIB)

ex9:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex9.cpp -o bin/ex9 $(OPENCV4)

ex10:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex10.cpp -o bin/ex10

ex11:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteD/ex11.cpp -o bin/ex11 $(OPENCV4)

clean:
	rm -rf bin/ex2
	rm -rf bin/ex3
	rm -rf bin/ex3sndfile
	rm -rf bin/ex4
	rm -rf bin/ex4video
	rm -rf bin/ex5
	rm -rf bin/ex6
	rm -rf bin/ex7
	rm -rf bin/ex8
	rm -rf bin/ex9
	rm -rf bin/ex10
	rm -rf bin/ex11