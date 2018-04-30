#ifndef READARGS
#define READARGS

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

/*
*   Argsstructure
*/
typedef struct
   { std::string InFolder, OutFolder, ForestFile, FBPlookup, WeatherOpt;
      bool SaveMem, scenarios, nooutput, OutputGrid, verbose, plottrue, spotting, exceltrue, combine, ignitions;
	  float ROSCV, ROSThreshold, HFIThreshold;
	  int MinutesPerWP, Max_Fire_Periods,  TotalYears, TotalSims, FirePeriodLen, heuristic, seed;
   } arguments;

char* getCmdOption(char ** begin, char ** end, const std::string & option);

bool cmdOptionExists(char** begin, char** end, const std::string& option);

void parseArgs(int argc, char * argv[], arguments * args_ptr);

void printArgs(arguments args);


#endif