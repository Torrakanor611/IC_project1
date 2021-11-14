# *****************************************************
# Variables to control Makefile operation
 
CC=g++
CFLAGS=-Wall -g
SNDFILE=$$(pkg-config --libs sndfile)
OPENCV4=$$(pkg-config --libs --cflags opencv4)

# ****************************************************
# Targets needed to bring the executable up to date
 
ex7:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex7.cpp -o bin/ex7 $(OPENCV4)

ex6:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex6.cpp -o bin/ex6 $(SNDFILE)

clean:
	rm bin/ex6
	rm bin/ex7