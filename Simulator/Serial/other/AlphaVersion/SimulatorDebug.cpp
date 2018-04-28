// Include classes
#include "CellsFBP.h"
#include "SpottingFBP.h"
#include "FBP5.0.h"
#include "ReadCSV.h"
#include "ReadArgs.h"
#include "Lightning.h"

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <string.h>
#include <random>
#include <algorithm> 

using namespace std;

/*
		Utils
*/
void printSets(int week_number, std::unordered_set<int> availCells, std::unordered_set<int> nonBurnableCells, 	
					 std::unordered_set<int> burningCells, std::unordered_set<int> burntCells, std::unordered_set<int> harvestCells)
{
	std::cout << "\nSet information period (week " << week_number << ")" << std::endl;
	std::cout << "Available Cells:";
	for (auto & ac : availCells){
			std::cout << " " << ac;
	}
	std::cout << std::endl;
	
	std::cout << "nonBurnable Cells:";
	for (auto & nbc : nonBurnableCells){
			std::cout << " " << nbc;
	}
	std::cout << std::endl;
	
	std::cout << "Burning Cells:";
	for (auto & bc : burningCells){
			std::cout << " " << bc;
	}
	std::cout << std::endl;
	
	std::cout << "Burnt Cells:";
	for (auto & bc : burntCells){
			std::cout << " " << bc;
	}
	std::cout << std::endl;
	
	
	std::cout << "Harvested Cells:";
	for (auto & hc : harvestCells){
			std::cout << " " << hc;
	}
	std::cout << std::endl;
}

/*
	Main
*/
int main(int argc, char * argv[])
{
	/********************************************************************
	*
	*															Initialization steps
	*
	********************************************************************/
	std::cout << "------------------ Simulator C Beta version ----------------------\n" << std::endl;
	/*
		      Command line arguments (all of them inside args structure)
	*/
	std::cout << "------ Command line values ------\n";
	arguments args;
	arguments * args_ptr = &args;
	parseArgs(argc, argv, args_ptr);
	printArgs(args);
	
	/********************************************************************
										Initialize fuel coefficients for FBP
	********************************************************************/
	fuel_coefs coefs[18];	
	fuel_coefs* coef_ptr = &coefs[0];
	setup_const(coef_ptr);
	
	/********************************************************************
					Global Values (Forest) and Instance (in memory for the moment)
	********************************************************************/
	std::cout << "\n------ Instance in memory initialization ------\n";	
	int max_weeks = 12;
	int sim = 1;
		
	/********************************************************************
							Instance in memory (4 cells = 2 x 2 grid)
	********************************************************************/
	int rows = 2;
	int cols = 2;
	int nCells = rows * cols; 
	double cellSide = 100;
	double areaCells= cellSide * cellSide;
	double ageCells = 10;
	double volCells = 300;
	double perimeterCells = 4 * cellSide;
	
	std::vector<std::vector<int>> coordCells = {{0,1},{1,1},{0,0},{1,0}};
	std::unordered_map<std::string, int> adjacents, adjacents2, adjacents3, adjacents4;    // -1 = None 
	adjacents = {{"N",-1},{"S",3},{"E",2},{"W",-1}, {"NE", -1}, {"NW", -1}, {"SE", 4}, {"SW", -1}};
	adjacents2 = {{"N",-1},{"S",4},{"E",-1},{"W",1},{"NE", -1}, {"NW", -1}, {"SE", -1}, {"SW", 3}};
	adjacents3 = {{"N",1},{"S",-1},{"E",4},{"W",-1},{"NE", 2}, {"NW", -1}, {"SE", -1}, {"SW", -1}};
	adjacents4 = {{"N",2},{"S",-1},{"E",-1},{"W",3},{"NE", -1}, {"NW", 1}, {"SE", -1}, {"SW", -1}};
	std::vector<std::unordered_map<std::string, int>> adjCells = {adjacents, adjacents2,adjacents3,adjacents4};
	
	std::vector<double> color = {0.000, 1.000, 2.0334, 1.3223};
	std::vector<std::vector<double>> colors = {color, color, color, color};

	std::vector<int> fTypeCells = {1,1,1,1};
	std::vector<string> fTypeCells2 = {"Burnable","Burnable","Burnable","Burnable"};
    std::vector<int> statusCells = {0,0,0,0};
    std::vector<int> realCells = {1,2,3,4};
	
	/********************************************************************
		Dataframes initialization: Forest and Weather
	********************************************************************/
	std::cout << "\n------ Read DataFrames: Forest and Weather ------\n";
	
	/* Forest DataFrame */
	std::string filename = args.InFolder + "Data.csv";
	std::string sep = ",";
	CSVReader CSVParser(filename, sep);
	
	// Populate DF 
	std::vector<std::vector<std::string>> DF = CSVParser.getData();
	std::cout << "Forest DataFrame from instance " << filename << std::endl;
	CSVParser.printData(DF);
	
	// Create empty df with size of NCells
	inputs df [nCells];
	inputs * df_ptr = &df[0];
	
	// Populate the df [nCells] objects
	CSVParser.parseDF(df_ptr, DF, nCells);
	
	/* Weather DataFrame */
	std::string weatherFile = args.InFolder + "Weather.csv";
	CSVReader CSVWeather(weatherFile, sep);
	std::vector<std::vector<std::string>> WeatherDF = CSVWeather.getData();
	std::cout << "\nWeather DataFrame from instance " << weatherFile << std::endl;
	CSVWeather.printData(WeatherDF);
	
	// Populate WDF 
	int WPeriods = WeatherDF.size() - 1;  // -1 due to header
	weatherDF wdf [WPeriods];
	weatherDF * wdf_ptr = &wdf[0];
	
	// Populate the wdf objects
	CSVWeather.parseWeatherDF(wdf_ptr, WeatherDF, WPeriods);
	
	/*  Ignitions */
	int IgnitionYears;
	std::vector<int> IgnitionPoints{4,4,4,4};   //HACK: HARD CODED FOR OUT OF SCOPE
	
	if(args.ignitions){
		std::cout << "\nWe have specific ignition points:" << std::endl;
		
		/* Ignition points */
		std::string ignitionFile = args.InFolder + "Ignitions.csv";
		std::string sep = ",";
		CSVReader CSVIgnitions(ignitionFile, sep);
						
		// Populate Ignitions vector 
		std::vector<std::vector<std::string>> IgnitionsDF = CSVIgnitions.getData();
		std::cout << "Ignition points from file " << ignitionFile << std::endl;
		CSVIgnitions.printData(IgnitionsDF);
		
		// Total Years
		IgnitionYears = IgnitionsDF.size() - 1;
		args.TotalYears = std::max(args.TotalYears, IgnitionYears);
		std::cout << "Setting TotalYears to " << args.TotalYears << " for consistency with Ignitions file" << std::endl;
		
		// Ignition points 
		std::vector<int> IgnitionPoints(IgnitionYears, 0);
		CSVIgnitions.parseIgnitionDF(IgnitionPoints, IgnitionsDF, IgnitionYears);
	}
	
	
	/********************************************************************
	*
	*												Global Parameters for loop 
	*
	*********************************************************************/
	// Global parameters for the loop
	int week_number = 1;
	int year = 1;
	int weatherPeriod = 0;
	bool noIgnition = true;  		//  None = -1
	//bool messagesSent = false;   //  None = -1
	int plotNumber = 1;
	vector<int> fire_period = vector<int>(args.TotalYears, 0);
	
	// Check maxFirePeriods and Weather File consistency
	if(args.WeatherOpt.compare("rows") == 0) {
		int maxFP = args.MinutesPerWP / args.FirePeriodLen * WPeriods;
		if (args.Max_Fire_Periods > maxFP) {
			args.Max_Fire_Periods = maxFP ;
            if (args.verbose){
				std::cout << "Maximum fire periods are set to: " << args.Max_Fire_Periods << " based on the weather file, Fire Period Length, and Minutes per WP" << std::endl;
			}
         }
     }
	 
	 //Lightning object 
	 Lightning Lambda_Strike = Lightning();
	 
	 // aux indexes
	 int i;
	
	/***************************************************************************************************************************************
	*
	*																				Main Simulation loop: Number of replications (nsims)
	*
	***************************************************************************************************************************************/
	while (sim <= args.TotalSims){
		std::cout << "------------------------------------------ Simulation Number: " << sim << "------------------------------------------" << std::endl;
		
		// Reset global parameters for the simulation
		week_number = 1;
		year = 1;
		weatherPeriod = 0;
		noIgnition = true;  		//  None = -1
		//messagesSent = false; 	//  None = -1
		plotNumber = 1;
		
		// Cells dictionary
		std::unordered_map<int, CellsFBP> Cells_Obj;
		
		// Declare an iterator to unordered_map
		std::unordered_map<int, CellsFBP>::iterator it;
		   
		// Relevant sets: Initialization
		std::unordered_set<int> availCells;				
		std::unordered_set<int> nonBurnableCells; 	
		std::unordered_set<int> burningCells;
        std::unordered_set<int> burntCells;
        std::unordered_set<int> harvestCells;
		for (i=0; i < statusCells.size(); i++){
			if(statusCells[i] != 4) availCells.insert (i+1);
			else nonBurnableCells.insert(i+1);
		}
		
		// Print-out sets information
		if (args.verbose){
			printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);
		}
		
		
		/***************************************************************************************************************************************
		*
		*																							Main Simulation loop: Specific replication (Years)
		*
		***************************************************************************************************************************************/
		while (year <= args.TotalYears){
				// Check current year
				if (args.verbose) {
					printf("\n----------------------------- Simulating Year %d -----------------------------\n", year);
					printf("---------------------- Step 1: Ignition ----------------------\n");
				}
				// TODO: Savemem
				
				
				/*******************************************************************
				*
				*												Step 1: Ignition 
				*
				*******************************************************************/
			
				// Ignitions 
				int aux = 0;
				int loops = 0;
				noIgnition = false;
								
				// No Ignitions provided
				if (args.ignitions == 0) { 
					while (true) {
						// Pick any cell (uniform distribution [a,b])
						std::default_random_engine generator (args.seed);
						std::uniform_int_distribution<int> distribution(0, nCells-1);
						aux = distribution(generator);
						
						// Check information (Debugging)
						if (args.verbose){
							std::cout << "aux: " << aux << std::endl;
							std::cout << "realCells[aux]: " << realCells[aux] << std::endl;
						}
						
						// If cell is available and not initialized, initialize it 
						if (statusCells[aux] != 4 && burntCells.find(aux+1) == burntCells.end()) {
							if (Cells_Obj.find(aux) == Cells_Obj.end()) {
									
								// Initialize cell, insert it inside the unordered map
								CellsFBP Cell(aux, areaCells,  coordCells[aux],  ageCells,  fTypeCells[aux],  fTypeCells2[aux], 
								                             volCells, perimeterCells, statusCells[aux], adjCells[aux], colors[aux], aux+1, 
															 args.OutputGrid);
								Cells_Obj.insert(std::make_pair(aux, Cell));							 
																
								// Get object from unordered map
								it = Cells_Obj.find(aux);
								
								// Initialize the fire fields for the selected cel
								it->second.initializeFireFields(coordCells, availCells);
								
								// Print info for debugging
								if (args.verbose) it->second.print_info();
							}

							if (it->second.getStatus() == "Available" && it->second.fType != 0) {
                                std::vector<int> ignPts = {};
								if (it->second.ignition(fire_period[year - 1], year, ignPts, df, coef_ptr, args_ptr, &wdf[weatherPeriod])) {
									// TODO: outputgrid
									
									
									//Printing info about ignitions        
									if (args.verbose){
										std::cout << "Cell " <<  it->second.realId <<  " Ignites" << std::endl;
										std::cout << "Cell " <<  it->second.realId << " Status: "<< it->second.getStatus() << std::endl;
									}
									
									// TODO: plottrue
									break;  
								}
							}
						}
						
						loops++;
						if (loops > nCells) {
							noIgnition = true;
							break;
						}
						

					}
				} 
			
				// Ignitions with provided points from CSV
				else {
                    int temp = IgnitionPoints[year-1];
				
					// If cell is available 
					if (burntCells.find(temp) == burntCells.end() && statusCells[temp - 1] != 4) {
						if (Cells_Obj.find(temp - 1) == Cells_Obj.end()) {
						
							// Initialize cell, insert it inside the unordered map
							CellsFBP Cell(temp-1, areaCells,  coordCells[temp-1],  ageCells,  fTypeCells[temp-1],  fTypeCells2[temp-1], 
												volCells, perimeterCells, statusCells[temp-1], adjCells[temp-1], colors[temp-1], temp, 
												args.OutputGrid);
							Cells_Obj.insert(std::make_pair(temp-1, Cell));							 
															
							// Get object from unordered map
							it = Cells_Obj.find(temp-1);
							
							// Initialize the fire fields for the selected cel
							it->second.initializeFireFields(coordCells, availCells);
						}
						
						// Not available or non burnable: no ignition
						if (it->second.getStatus() != "Available" || it->second.fType == 0) {
							noIgnition = true;
						}
						
						// Available anr Burnable: ignition
						if (it->second.getStatus() == "Available" && it->second.fType != 0) {
                            std::vector<int> ignPts = {temp};
							if (it->second.ignition(fire_period[year - 1], year, ignPts, df, coef_ptr, args_ptr, &wdf[weatherPeriod])) {
									// TODO: outputgrid
									
									//Printing info about ignitions        
									if (args.verbose){
										std::cout << "Cell " <<  it->second.realId <<  " Ignites" << std::endl;
										std::cout << "Cell " <<  it->second.realId << " Status: "<< it->second.getStatus() << std::endl;
									}
									
									// TODO: plottrue
									
							}
							
						}

					} else {
						noIgnition = true;
						if (args.verbose){
							std::cout << "No ignition during year " << year << ", Cell " << IgnitionPoints[year-1] << " is already burnt or non-burnable type" << std::endl;
						}
					}
                }
				
				// If ignition occurs, we update the forest status
				if (!noIgnition) {
					int newId = it->second.realId;
					std:cout << "New ID for burning cell: " << newId << std::endl;
					
					burningCells.insert(newId);
					burntCells.insert(newId);
					availCells.erase(newId);
					
					// Print sets information
					if (args.verbose){
						printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);
					}
				}
				
				// Next period
				fire_period[year - 1] += 1;
				std::cout << "Fire period updated to " << fire_period[year - 1] << std::endl; 
				
				// Check weather period consistency
				if (args.WeatherOpt != "constant" && fire_period[year - 1] * args.FirePeriodLen / args.MinutesPerWP > weatherPeriod + 1) {
					weatherPeriod++;  // Now we don't need to update anything, just sending the relevant data to manageFire
				}
				
				// Print-out information regarding the weather and fire period
				if (args.verbose){
					std::cout << "Current Week: " << week_number << std::endl;
					std::cout << "Fire Period Starts: " <<  fire_period[year-1] << std::endl;
					std::cout << "\nCurrent weather conditions:" << std::endl;
					CSVWeather.printWeatherDF(wdf[weatherPeriod]);
					
					if (args.WeatherOpt == "constant")
						std::cout << "(NOTE: current weather is not used for ROS with constant option)" << std::endl;
								
					// End of the ignition step
					std::cout << "\nNext Fire Period: " << fire_period[year-1] << std::endl;
				}
				
				// Week ending condition 
				if (week_number==12 && args.verbose){
					std::cout << "-------------------------------------------------------------------------\n" << std::endl;
					std::cout << "                           End of the fire year " << year << "               "  << std::endl;
					std::cout << "-------------------------------------------------------------------------" << std::endl;
				}
				
				// If no ignition occurs, go to next year (no multiple ignitions per year, only one)
				if(noIgnition){
					if (args.verbose){
						std::cout << "No ignition in year " << year << std::endl;
						std::cout << "-------------------------------------------------------------------------\n" << std::endl;
						std::cout << "                           End of the fire year " << year << "               "  << std::endl;
						std::cout << "-------------------------------------------------------------------------" << std::endl;
					}
					
					// Next year, reset the week
					year+=1;  
					week_number = 1;
				}
				
				
				/*
				*
				*												Steps 2,3: Send/Receive messages 
				*
				*/
				if (!noIgnition) {
					while (fire_period[year - 1] < args.Max_Fire_Periods) {
						if (fire_period[year - 1] == args.Max_Fire_Periods - 1) {
							std::cout << "*** WARNING!!! About to hit MaxFirePeriods: " << args.Max_Fire_Periods << std::endl;
						}
						
						/// Send messages logic
						bool messagesSent = false;
						std::unordered_map<int, vector<int>> sendMessageList;

						
						// Information of the current step 
						if (args.verbose){
							std::cout << "\n---------------------- Step 2: Sending Messages from Ignition ----------------------" << std::endl;
							std::cout << "Current Week: " <<  week_number << std::endl;
							std::cout << "Current Fire Period: " <<  fire_period[year-1] << std::endl;
							printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);
							std::cout <<  "-------------------- Cleaning step (angles) ------------------------" << std::endl;
						}						
						
						// Clean the angles of non available cells 
						for (auto & _cell : Cells_Obj) {
							int cell = _cell.first;
							if (_cell.second.ROSAngleDir.size() > 0) {
								for (auto & _angle : _cell.second.angleToNb) {
									int angle = _angle.first;
									int nb = _angle.second;
									if (availCells.find(nb) == availCells.end() && _cell.second.ROSAngleDir.find(angle) != _cell.second.ROSAngleDir.end()) {
										if(args.verbose){
											std::cout <<  "Cell " << _cell.second.realId <<   ": clearing ROSAngleDir" << std::endl;
										}
										_cell.second.ROSAngleDir.erase(angle);
									}
								}
							}
						}

						// Close section with lines
						if(args.verbose){
							std::cout << "--------------------------------------------------------------------" << std::endl; 
						}

						// Repeat fire flag 
						bool repeatFire = false;
						vector<int> burnedOutList;
	
						/*
								Potential parallel zone: Send messages
								Burning cells loop: sending messages (Embarrasingly parallel?: CP: should be)
								Each burning cell updates its fire progress and (if needed) populates their message
						*/
						vector<int> aux_list;
						for (int cell : burningCells) {
							// Get object from unordered map
							it = Cells_Obj.find(cell-1);
							
							// Cell's info 
							if (args.verbose) {
								it->second.print_info();
							}
							
							/*
									Manage Fire method main step
							*/
							
							if (it->second.ROSAngleDir.size() > 0) {
																
								aux_list = it->second.manageFire(fire_period[year-1], availCells,  df, coef_ptr, 
																     			  {{"SPOTANGLE", 1},{"SPOT0PROB",0.1},{"SPOT10TIME", 10}}, 
																				   coordCells, Cells_Obj, args_ptr, &wdf[weatherPeriod]);
																
								//aux_list = Cells_Obj[cell - 1].manageFire(firePeriod[year - 1], availCells, verbose, df, coef_ptr, spotting, spottingParams, CoordCells, Cells_Obj, args);
							} // TODO: side effect-less else branch

							else{
								std::cout << "\nCell " << cell <<  "does not have any neighbor available for receiving messages" << std::endl;
							}
							
							// If message and not a true flag 
							if (aux_list.size() > 0 && aux_list[0] != -100) {
								if (args.verbose) std::cout <<"\nList is not empty" << std::endl;
								messagesSent = true;
								sendMessageList[it->second.realId] = aux_list; 
								if (args.verbose){
									std::cout << "Message list content" << std::endl;
									for (auto & msg : sendMessageList[it->second.realId]){
										std::cout << "  Fire reaches the center of the cell " << msg << "  Distance to cell (in meters) was 100.0" << " " << std::endl;
									}
								}
								
							}

							// Repeat fire conditions if true flag
							if (aux_list.size() > 0 && aux_list[0] == -100) {
								repeatFire = true;
							}

							// Burnt out inactive burning cells
							if (aux_list.size() == 0) {
								burnedOutList.push_back(it->second.realId);
								if (args.verbose){
									std::cout  << "\nMessage and Aux Lists are empty; adding to BurnedOutList" << std::endl;
								}
							}
	 
						}
						
						/* End sending messages loop */
						
						
						// Check for burnt out updates via sets' difference
                        for(auto &bc : burnedOutList){
                            auto lt = burningCells.find(bc);
                            if (lt != burningCells.end()) { 
                                burningCells.erase(bc);
                            }
                        }

						printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);

						// Number of messages received per cell 
						int numMessages = 0;
						for (auto & p : sendMessageList) {
							numMessages += p.second.size();
						}
						
						if (args.verbose){
							std::cout << "Number of messages: " <<  numMessages  << std::endl;
						}
						
						// Conditions depending on number of messages and repeatFire flag 
						// No messages but repetition
						if (repeatFire && numMessages == 0) {
							std::cout << "Fires are still alive, no message generated" << std::endl;
							std::cout <<  "Current fire period: " << fire_period[year - 1] << std::endl;
							fire_period[year - 1] += 1;

							// Check if we need to update the weather
							if (args.WeatherOpt != "constant" && fire_period[year - 1] * args.FirePeriodLen / args.MinutesPerWP > weatherPeriod + 1) {
								weatherPeriod += 1;
									
								if(args.verbose){
									std::cout << "\nCurrent weather conditions:" << std::endl;
									CSVWeather.printWeatherDF(wdf[weatherPeriod]);
								}
							}
						}

						// Messages and repetition
						if (repeatFire && numMessages > 0) {
							std::cout << "Messages have been sent, next step. Current period: " << fire_period[year - 1] << std::endl;
							repeatFire = false;
						}
						
						// No messages, no repeat (break and next year)
						if (!messagesSent && !repeatFire) {
							if (args.verbose){
								std::cout << "\nNo messages during the fire period, end of year "<< year << std::endl;
							}
							
							// Reset values 
							year += 1;
							week_number = 1;
							weatherPeriod = 0;
							
							// Update sets
                            for(auto &bc : burningCells){
                                burntCells.insert(bc);
                            }
							burningCells = std::unordered_set<int>();
							
							printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);
							
							// TODO: savemem

							break;
						}
					
					
					
						/*
						*
						*					Receiving messages
						*
						*/
						// Mesages and no repeat 
						 if (messagesSent && !repeatFire) {
                        
							// frequency array
							std::unordered_map<int, int> globalMessagesList;
							for (auto & sublist : sendMessageList) {
								for (int val : sublist.second) {
									if (globalMessagesList.find(val) == globalMessagesList.end()){
										globalMessagesList[val] = 1;
									} else {
										globalMessagesList[val] = globalMessagesList[val] + 1;
									}
								}
							}
							
							// Initialize cells if needed (getting messages)
							for (auto & _bc : globalMessagesList) {
								int bc = _bc.first;
								if (Cells_Obj.find(bc - 1) == Cells_Obj.end() && burntCells.find(bc) == burntCells.end()) {
																
									// Initialize cell, insert it inside the unordered map
									CellsFBP Cell(bc-1, areaCells,  coordCells[bc-1],  ageCells,  fTypeCells[bc-1],  fTypeCells2[bc-1], 
														volCells, perimeterCells, statusCells[bc-1], adjCells[bc-1], colors[bc-1], bc, 
														args.OutputGrid);
									
									Cells_Obj.insert(std::make_pair(bc-1, Cell));							 
																	
									// Get object from unordered map
									it = Cells_Obj.find(bc-1);
									
									// Initialize the fire fields for the selected cel
									it->second.initializeFireFields(coordCells, availCells);
								}
							}
							
							    // TODO: plot
							
							// Get burnt loop
							std::unordered_set<int> burntList;
							bool checkBurnt;
							for (auto & _bc : globalMessagesList) {
								int bc = _bc.first;
								if (burntCells.find(bc) == burntCells.end()) {
									if (Cells_Obj.find(bc - 1) == Cells_Obj.end()) {
										
									// Initialize cell, insert it inside the unordered map
									CellsFBP Cell(bc-1, areaCells,  coordCells[bc-1],  ageCells,  fTypeCells[bc-1],  fTypeCells2[bc-1], 
														volCells, perimeterCells, statusCells[bc-1], adjCells[bc-1], colors[bc-1], bc, 
														args.OutputGrid);
									
									Cells_Obj.insert(std::make_pair(bc-1, Cell));							 
																	
									// Get object from unordered map
									it = Cells_Obj.find(bc-1);
									
									// Initialize the fire fields for the selected cel
									it->second.initializeFireFields(coordCells, availCells);
									
									}
									
									// Check if burnable, then check potential ignition
									if (it->second.fType != 0) {
										checkBurnt = it->second.get_burned(fire_period[year-1], globalMessagesList[bc-1], year, df, coef_ptr, args_ptr, &wdf[weatherPeriod]);
				
									} else {
										checkBurnt = false;
									}
									
									// Print-out regarding the burnt cell
									if(args.verbose){
										std::cout << "\nCell " << it->second.realId << " got burnt (1 true, 0 false): " << checkBurnt << std::endl;
									}
									
									// Update the burntlist
									if (checkBurnt) {
										burntList.insert(it->second.realId);
									}

								}
							}
							
						
							// Update sets (TODO: optimize)

                            for(auto &bc : burntList) {
                                burntCells.insert(bc);
                            }

                            for(auto &bc : burnedOutList) {
                                burntCells.insert(bc);
                            }
							
                            for(auto &bc : burntList) {
                                burningCells.insert(bc);
                            }

							for(auto &bc : burningCells){
								auto lt = availCells.find(bc);
								if (lt != availCells.end()) {
                                    availCells.erase(bc);
                                }
							}
							
							// Display info for debugging
							if(args.verbose){
								printSets(week_number, availCells, nonBurnableCells, burningCells, burntCells, harvestCells);
							}

							/*  
							*					Next Period
							*/
							fire_period[year - 1] += 1;
							
							// If weather is not constant (random weather to be supported in next commit...)
							if (args.WeatherOpt != "constant" && fire_period[year - 1] * args.FirePeriodLen / args.MinutesPerWP > weatherPeriod + 1) {
								weatherPeriod++;
								if (args.verbose){
									std::cout  << "\nWeather has been updated" << std::endl;
									CSVWeather.printWeatherDF(wdf[weatherPeriod]);
								}
							}
							
							// Message for constant weather
							if (args.WeatherOpt == "constant" && args.verbose){
								std::cout << "(NOTE: current weather is not used for ROS with constant option)" << std::endl;
							}
							
							// Next week 
							if (fire_period[year - 1] >= 168 * 60 / args.FirePeriodLen) {
								week_number++;
							}

						}
					
					
					
					
					
					
					
					//break;		// Debugging inner while of sending and receiving messages
					}
					
					// End of the year (out of inner loop)
					std::cout << "Next year..." << std::endl;
					year += 1;
					week_number = 1;
					weatherPeriod = 0;
					
					
				}

				
				
	
				//break;  // For debugging KEEP IT TO RUN ONLY ONE PERIOD!!!!!! 
			
		}  // End of years loop
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*****************************************************************************
		*
		*												Steps 4: Results and outputs 
		*
		******************************************************************************/
		for (auto & br : burntCells) {
            if (Cells_Obj.find(br-1) != Cells_Obj.end()) {
                // Get object from unordered map
				it = Cells_Obj.find(br-1);
				
				// Initialize the fire fields for the selected cel
				it->second.status = 2;
            }
        }

        for (auto & br : burningCells) {
            if (Cells_Obj.find(br-1) != Cells_Obj.end()) {
                // Get object from unordered map
				it = Cells_Obj.find(br-1);
				
				// Initialize the fire fields for the selected cel
				it->second.status = 2;
            }
        }
		
		
		// Next simulation (replication)
		sim++;
		
		
		
		
		
	} // End of simulations loop 
	
	
	
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
}	
