#include "ReadArgs.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void parseArgs(int argc, char * argv[], arguments * args_ptr)
{
	// Help
    if(cmdOptionExists(argv, argv+argc, "-h")){
        printf("-------------------------------------------\n         Help manual!!! \n-------------------------------------------\n");
    }
	
	// Empty default
	char empty = '\0';
	
	// Strings
	// instance-folder
	char * input_forest = getCmdOption(argv, argv + argc, "--instance-folder");
    if (input_forest){
        printf("input_forest: %s \n", input_forest);
    }
	else input_forest = &empty;
	
	// fbp-lookup
	char * input_fpblookup = getCmdOption(argv, argv + argc, "--input-fpblookup");
    if (input_fpblookup){
        printf("input_fpblookup: %s \n", input_fpblookup);
    }
	else input_fpblookup = &empty;
	
	//--input-instance-folder
	char * input_folder = getCmdOption(argv, argv + argc, "--input-instance-folder");
    if (input_folder){
        printf("input_folder: %s \n", input_folder);
    }
	else input_folder = &empty;
	
	//--output-folder
	char * output_folder = getCmdOption(argv, argv + argc, "--output-folder");
    if (output_folder){
        printf("output_folder: %s \n", output_folder );
    }
	else output_folder = &empty;
	
		//--weather
	char * input_weather = getCmdOption(argv, argv + argc, "--weather");
    if (input_weather){
        printf("--weather: %s \n", input_weather);
    }
	else input_weather = &empty;
	
	//--spotting-parameter-data-file-name
	char * spotting_parameter_data_file_name = getCmdOption(argv, argv + argc, "--spotting-parameter-data-file-name");
    if (spotting_parameter_data_file_name){
        printf("--spotting-parameter-data-file-name: %s \n", spotting_parameter_data_file_name);
    }
	else spotting_parameter_data_file_name = &empty;
	
	
	
	
	// Booleans
	bool input_plottrue = false;
	bool verbose_input = false;
	bool input_ignitions = false;
	bool input_excel = false;
	bool input_combine = false;
	bool input_save = false;
	bool input_scenario = false;
	bool no_output = false; 
	bool output_grid = false;
	bool spotting = false;
	
	//--plot
    if(cmdOptionExists(argv, argv+argc, "--plot")){
        input_plottrue = true;
        printf("--plot: %d \n", input_plottrue);
    }
	
	//--verbose
	if(cmdOptionExists(argv, argv+argc, "--verbose")){
        verbose_input = true;
		printf("--verbose: %d \n", verbose_input);
    }
	
	//--ignition-points
	if(cmdOptionExists(argv, argv+argc, "--ignition-points")){
        input_ignitions = true;
        printf("--ignition-points: %d \n", input_ignitions);
    }
	
	//--ignitions
	if(cmdOptionExists(argv, argv+argc, "--ignitions")){
        input_ignitions = true;
        printf("--ignitions: %d \n", input_ignitions);
    }
	
	//--statistics
	if(cmdOptionExists(argv, argv+argc, "--statistics")){
        input_excel = true;
		printf("--statistics: %d \n", input_excel);
    }
	
	//--combine
	if(cmdOptionExists(argv, argv+argc, "--combine")){
        input_combine = true;
		printf("--combine: %d \n", input_combine);
    }
	
	//--save-memory
	if(cmdOptionExists(argv, argv+argc, "--save-memory")){
		input_save = true;
		printf("--save-memory: %d \n", input_save);
    }
	
	//--scenarios-out
	if(cmdOptionExists(argv, argv+argc, "--scenarios-out")){
		input_scenario = true;
		printf("--scenarios-out: %d \n", input_scenario);
    }
	
	//--no-output
	if(cmdOptionExists(argv, argv+argc, "--no-output")){
		no_output = true;
		printf("--no-output: %d \n", no_output);
    }
	
	//--output-grid
	if(cmdOptionExists(argv, argv+argc, "--output-grid")){
		output_grid = true;
		printf("--output-grid: %d \n", output_grid);
    }
	



	// Floats and ints
	// defaults
	int dsim_years = 4;
	int dnsims = 1;
	int dinput_PeriodLen= 60;
	int dweather_period_len= 60;
	float dROS_Threshold= 0.1;
	float dHFI_Threshold= 0.1;
	float dROSCV= 0;
	int dinput_heur= 0;
	int dmax_fire_periods= 1000;
	int dseed = 123;
	
	// aux 
	std::string::size_type sz;

	//--sim-years  (float)
	char * sim_years = getCmdOption(argv, argv + argc, "--sim-years");
    if (sim_years){
        printf("--sim-years: %s \n", sim_years);
		args_ptr->TotalYears = std::stoi (sim_years ,&sz); 
    }
	else args_ptr->TotalYears = dsim_years;
	
	//--nsims
	char * input_nsims = getCmdOption(argv, argv + argc, "--nsims");
    if (input_nsims){
        printf("--nsims: %s \n", input_nsims);
		args_ptr->TotalSims = std::stoi (input_nsims ,&sz);  
    }
	else args_ptr->TotalSims = dnsims; 
	
	//--Weather-Period-Length
	char * weather_period_len = getCmdOption(argv, argv + argc, "--Weather-Period-Length");
    if (weather_period_len){
        printf("--Weather-Period-Length: %s \n", weather_period_len);
		args_ptr->MinutesPerWP = std::stoi (weather_period_len ,&sz); 
    }
	else args_ptr->MinutesPerWP = dweather_period_len;
	
	//--Fire-Period-Length
	char * input_PeriodLen = getCmdOption(argv, argv + argc, "--Fire-Period-Length");
    if (input_PeriodLen){
        printf("--Fire-Period-Length: %s \n", input_PeriodLen);
		if (std::stoi (input_PeriodLen ,&sz) <= args_ptr->MinutesPerWP){
			 args_ptr->FirePeriodLen = std::stoi (input_PeriodLen ,&sz); 
		}
		else args_ptr->FirePeriodLen =  args_ptr->MinutesPerWP;
    }
	else args_ptr->FirePeriodLen =  args_ptr->MinutesPerWP;
	
	//--ROS-Threshold
	char * ROS_Threshold = getCmdOption(argv, argv + argc, "--ROS-Threshold");
    if (ROS_Threshold){
        printf("--ROS-Threshold: %s \n", ROS_Threshold);
		args_ptr->ROSThreshold = std::stof (ROS_Threshold ,&sz); 
    }
	else args_ptr->ROSThreshold = dROS_Threshold;
	
	//--HFI-Threshold
	char * HFI_Threshold = getCmdOption(argv, argv + argc, "--HFI-Threshold");
    if (HFI_Threshold){
        printf("--HFI-Threshold: %s \n", HFI_Threshold);
		args_ptr->HFIThreshold = std::stof (HFI_Threshold ,&sz);
    }
	else args_ptr->HFIThreshold = dHFI_Threshold;
	
	//--ROS-CV
	char * ROS_CV = getCmdOption(argv, argv + argc, "--ROS-CV");
    if (ROS_CV){
        printf("--ROS-CV: %s \n", ROS_CV);
		args_ptr->ROSCV = std::stof (ROS_CV ,&sz); 
    }
	else args_ptr->ROSCV = dROSCV;
	
	//--heuristic
	char * input_heur = getCmdOption(argv, argv + argc, "--heuristic");
    if (input_heur){
        printf("--heuristic: %s \n", input_heur);
		args_ptr->heuristic = std::stoi (input_heur ,&sz); 
    }
	else args_ptr->heuristic = dinput_heur;
	
	//--max-fire-periods
	char * max_fire_periods = getCmdOption(argv, argv + argc, "--max-fire-periods");
    if (max_fire_periods){
        printf("--max-fire-periods: %s \n", max_fire_periods);
		args_ptr->Max_Fire_Periods = std::stoi (max_fire_periods ,&sz); 
    }
	else args_ptr->Max_Fire_Periods = dmax_fire_periods;
	
	//--seed  (int)
	char * seed = getCmdOption(argv, argv + argc, "--seed");
    if (seed){
        printf("--seed: %s \n", seed);
		args_ptr->seed = std::stoi (seed ,&sz); 
    }
	else args_ptr->seed = dseed;
	
	// Populate structure
	// Strings 
	if (input_folder == &empty){
		args_ptr->InFolder = ""; 
	}
	else args_ptr->InFolder = input_folder; 
	
	if (output_folder == &empty && input_folder != &empty){
		args_ptr->OutFolder = args_ptr->InFolder + "SimOut";
	} else if(output_folder == &empty && input_folder == &empty){
		args_ptr->OutFolder = "SimOut";
	} else if(output_folder != &empty && input_folder == &empty){
		args_ptr->OutFolder = output_folder;
	} else if(output_folder != &empty && input_folder != &empty){
		args_ptr->OutFolder = args_ptr->InFolder + output_folder;
	}
	
	
	if (input_forest == &empty && input_folder != &empty){
		args_ptr->ForestFile = args_ptr->InFolder + "Forest.csv";
	} else if(input_forest == &empty && input_folder == &empty){
		args_ptr->ForestFile = "Forest.csv";
	} else if(input_forest != &empty && input_folder == &empty){
		args_ptr->ForestFile = input_forest;
	} else if(input_forest != &empty && input_folder != &empty){
		args_ptr->ForestFile = args_ptr->InFolder + input_forest;
	}
	
	
	if (input_fpblookup == &empty && input_folder != &empty){
		args_ptr->FBPlookup = args_ptr->InFolder + "FBPlookup.csv";
	} else if(input_fpblookup == &empty && input_folder == &empty){
		args_ptr->FBPlookup = "FBPlookup.csv";
	} else if(input_fpblookup != &empty && input_folder == &empty){
		args_ptr->FBPlookup = input_fpblookup;
	} else if(input_fpblookup != &empty && input_folder != &empty){
		args_ptr->FBPlookup = args_ptr->InFolder + input_fpblookup;
	}
	
	
	if (input_weather == &empty){
		args_ptr->WeatherOpt = "rows";
	}
	else{
		args_ptr->WeatherOpt = input_weather;
	}
		
	// booleans
	args_ptr->SaveMem = input_save; 
	args_ptr->scenarios = input_scenario; 
	args_ptr->nooutput = no_output;
	args_ptr->OutputGrid = output_grid; 
	args_ptr->verbose = verbose_input; 
	args_ptr->plottrue = input_plottrue;
	//if(spotting_parameter_data_file_name) args_ptr->spotting = true;   TODO LATER
	//else args_ptr->spotting = false;
	args_ptr->spotting = spotting;
	args_ptr->ignitions = input_ignitions;
	args_ptr->exceltrue = input_excel; 
	args_ptr->combine = input_combine;
	
	  
	
}


void printArgs(arguments args){
	std::cout << "InFolder: " << args.InFolder << std::endl; 
	std::cout << "OutFolder: " << args.OutFolder << std::endl; 
	std::cout << "ForestFile: " << args.ForestFile << std::endl; 
	std::cout << "FBPlookup: " << args.FBPlookup << std::endl; 
	std::cout << "WeatherOpt: " << args.WeatherOpt << std::endl; 
	std::cout << "Ignitions: " << args.ignitions << std::endl; 
	std::cout << "SaveMem: " << args.SaveMem << std::endl; 
	std::cout << "scenarios: " << args.scenarios << std::endl; 
	std::cout << "noOutput: " << args.nooutput << std::endl; 
	std::cout << "OutputGrid: " << args.OutputGrid << std::endl; 
	std::cout << "verbose: " << args.verbose << std::endl; 
	std::cout << "plottrue: " << args.plottrue << std::endl; 
	std::cout << "spotting: " << args.spotting << std::endl; 
	std::cout << "exceltrue: " << args.exceltrue << std::endl; 
	std::cout << "combine: " << args.combine << std::endl; 
	std::cout << "MinutesPerWP: " << args.MinutesPerWP << std::endl; 
	std::cout << "Max_Fire_Periods: " << args.Max_Fire_Periods << std::endl; 
	std::cout << "TotalYears: " << args.TotalYears << std::endl; 
	std::cout << "TotalSims: " << args.TotalSims << std::endl; 
	std::cout << "FirePeriodLen: " << args.FirePeriodLen << std::endl; 
	std::cout << "heuristic: " << args.heuristic << std::endl; 
	std::cout << "seed: " << args.seed << std::endl; 
	
}