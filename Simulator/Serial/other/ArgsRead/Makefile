CC = g++
MPCC = g++
OPENMP = -openmp
CFLAGS = -O3 -std=c++11
LIBS =


TARGETS = ArgsTest

all:	$(TARGETS)

TestCSV: ArgsTest.o 
	$(CC) -o $@ $(LIBS) ArgsTest.o 

TestCSV.o: ArgsTest.cpp 
	$(CC) -c $(CFLAGS) ArgsTest.cpp

clean:
