CC = g++
MPCC = g++
OPENMP = -openmp
CFLAGS = -O3 -std=c++11
LIBS =


TARGETS = TestClasses

all:	$(TARGETS)

TestClasses: TestClasses.o DFWeather.o DFGrid.o
	$(CC) -o $@ $(LIBS) TestClasses.o DFWeather.o DFGrid.o


TestClasses.o: TestClasses.cpp DFWeather.h DFGrid.h
	$(CC) -c $(CFLAGS) TestClasses.cpp

clean:
