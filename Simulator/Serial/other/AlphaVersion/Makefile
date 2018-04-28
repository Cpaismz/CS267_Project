CC = g++
MPCC = g++
OPENMP = -openmp
CFLAGS = -O3 -std=c++11
LIBS =


TARGETS = SimulatorDebug

all:	$(TARGETS)

SimulatorDebug: SimulatorDebug.o CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o Lightning.o
	$(CC) -o $@ $(LIBS) SimulatorDebug.o CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o Lightning.o

SimulatorDebug.o: SimulatorDebug.cpp CellsFBP.o FBPfunc5_NoDebug.o SpottingFBP.o ReadCSV.o ReadArgs.o
	$(CC) -c $(CFLAGS) SimulatorDebug.cpp

SpottingFBP.o: SpottingFBP.cpp SpottingFBP.h CellsFBP.h
	$(CC) -c $(CFLAGS) SpottingFBP.cpp CellsFBP.h

CellsFBP.o: CellsFBP.cpp CellsFBP.h FBPfunc5_NoDebug.o
	$(CC) -c $(CFLAGS) CellsFBP.cpp
	
FBPfunc5_NoDebug.o: FBPfunc5_NoDebug.c FBP5.0.h
	$(CC) -c $(CFLAGS) FBPfunc5_NoDebug.c

ReadCSV.o: ReadCSV.cpp ReadCSV.h FBPfunc5_NoDebug.o
	$(CC) -c $(CFLAGS) ReadCSV.cpp
	
ReadArgs.o: ReadArgs.cpp ReadArgs.h
	$(CC) -c $(CFLAGS) ReadArgs.cpp
	
Lightning.o: Lightning.cpp Lightning.h
	$(CC) -c $(CFLAGS) Lightning.cpp

Forest.o: Forest.cpp Forest.h
	$(CC) -c $(CFLAGS) Forest.cpp


	
clean:
	rm Lightning.o ReadArgs.o ReadCSV.o FBPfunc5_NoDebug.o SimulatorDebug.o CellsFBP.o SimulatorDebug SpottingFBP.o Forest.o *.gch
