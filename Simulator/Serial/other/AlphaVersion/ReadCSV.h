#ifndef READCSV
#define READCSV

#include "FBP5.0.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
 
/*
*   Weather structure
*/
typedef struct
   { std::string scenario, datetime;
      float apcp, tmp, rh, ws, ffmc, dmc, dc, isi, bui, fwi;
      int waz;
   } weatherDF;
   
 
/*
 * A class to read data from a csv file.
 */
class CSVReader{ 
public:
	// inmutable 
	std::string fileName;
	std::string delimeter;
	
	// Constructor
	CSVReader(std::string filename, std::string delm = ",");
 
	// Function to fetch data from a CSV File
	std::vector<std::vector<std::string>> getData();
	
	//Print data to console (Debug)
	void printData(std::vector<std::vector<std::string>> DF);
	
	//Populate DF 
	void parseDF(inputs * df_ptr, std::vector<std::vector<std::string>> DF, int NCells);
	
	//Populate Weather DF
	void parseWeatherDF(weatherDF * wt_ptr, std::vector<std::vector<std::string>> DF, int WPeriods);
	
	// Populate Ignition Points
	void parseIgnitionDF(std::vector<int> ig, std::vector<std::vector<std::string>> DF, int IgPeriods);
	
	// Prints individual cell info
	void printDF(inputs df);
	
	// Prints individual weather row info
	void printWeatherDF(weatherDF wdf);
};
 
#endif