CC = g++
MPCC = g++
OPENMP = -openmp
CFLAGS = -O3 -std=c++11
LIBS =


TARGETS = TestCSV

all:	$(TARGETS)

TestCSV: TestCSV.o 
	$(CC) -o $@ $(LIBS) TestCSV.o 

TestCSV.o: TestCSV.cpp 
	$(CC) -c $(CFLAGS) TestCSV.cpp

clean:
