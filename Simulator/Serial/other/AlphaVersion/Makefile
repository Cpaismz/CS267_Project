CC = g++
MPCC = g++
OPENMP = -openmp
CFLAGS = -O3 -std=c++11
LIBS =


TARGETS = SimulatorDebug

all:	$(TARGETS)

CellsFBP: CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o
	$(CC) -o $@ $(LIBS) CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o
	
SimulatorDebug: SimulatorDebug.o CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o Lightning.o
	$(CC) -o $@ $(LIBS) SimulatorDebug.o CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o Lightning.o

CellsFBP.o: CellsFBP.cpp CellsFBP.h FBPfunc5_NoDebug.o
	$(CC) -c $(CFLAGS) CellsFBP.cpp

SimulatorDebug.o: SimulatorDebug.cpp  CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o
	$(CC) -c $(CFLAGS) SimulatorDebug.cpp
	
FBPfunc5_NoDebug.o: FBPfunc5_NoDebug.c FBP5.0.h
	$(CC) -c $(CFLAGS) FBPfunc5_NoDebug.c

ReadCSV.o: ReadCSV.cpp ReadCSV.h FBPfunc5_NoDebug.o
	$(CC) -c $(CFLAGS) ReadCSV.cpp
	
ReadArgs.o: ReadArgs.cpp ReadArgs.h
	$(CC) -c $(CFLAGS) ReadArgs.cpp
	
Lightning.o: Lightning.cpp Lightning.h
	$(CC) -c $(CFLAGS) Lightning.cpp

	
clean:


