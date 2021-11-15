# *****************************************************
# Variables to control Makefile operation
 
CC=g++
CFLAGS=-Wall -g
SNDFILE=$$(pkg-config --libs sndfile)
OPENCV4=$$(pkg-config --libs --cflags opencv4)

# ****************************************************
# Targets needed to bring the executable up to date

ex3sndfile:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex3sndfile.cpp -o bin/ex3sndfile $(SNDFILE)

ex4video:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteB/ex4video.cpp -o bin/ex4video $(OPENCV4)
 
ex7:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex7.cpp -o bin/ex7 $(OPENCV4)

ex6:
	@ mkdir -p bin
	@ $(CC) $(CFLAGS) ParteC/ex6.cpp -o bin/ex6 $(SNDFILE)

clean:
	rm bin/ex3sndfile
	rm bin/ex4video
	rm bin/ex6
	rm bin/ex7