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

int main(int argc, char * argv[])
{
	// Help
    if(cmdOptionExists(argv, argv+argc, "-h")){
        printf("-------------------------------------------\n         Help manual!!! \n-------------------------------------------\n");
    }
	
	
	
	// Strings
	// instance-folder
	char * input_forest = getCmdOption(argv, argv + argc, "--instance-folder");
    if (input_forest){
        printf("input_forest: %s \n", input_forest);
    }
	
	// fbp-lookup
	char * input_fpblookup = getCmdOption(argv, argv + argc, "--input-fpblookup");
    if (input_fpblookup){
        printf("input_fpblookup: %s \n", input_fpblookup);
    }
	
	//--input-instance-folder
	char * input_folder = getCmdOption(argv, argv + argc, "--input-instance-folder");
    if (input_folder){
        printf("input_folder: %s \n", input_folder);
    }
	
	//--output-folder
	char * output_folder = getCmdOption(argv, argv + argc, "--output-folder");
    if (output_folder){
        printf("output_folder: %s \n", output_folder );
    }
	
	//--seed  (int)
	char * seed = getCmdOption(argv, argv + argc, "--seed");
    if (seed){
        printf("--seed: %s \n", seed);
    }
	
	//--weather
	char * input_weather = getCmdOption(argv, argv + argc, "--weather");
    if (input_weather){
        printf("--weather: %s \n", input_weather);
    }
	
	//--spotting-parameter-data-file-name
	char * spotting_parameter_data_file_name = getCmdOption(argv, argv + argc, "--spotting-parameter-data-file-name");
    if (spotting_parameter_data_file_name){
        printf("--spotting-parameter-data-file-name: %s \n", spotting_parameter_data_file_name);
    }
	
	
	
	
	// Booleans
	//--plot
    if(cmdOptionExists(argv, argv+argc, "--plot")){
        bool input_plottrue = true;
        printf("--plot: %d \n", input_plottrue);
    }
	
	//--verbose
	if(cmdOptionExists(argv, argv+argc, "--verbose")){
        bool verbose_input = true;
		printf("--verbose: %d \n", verbose_input);
    }
	
	//--ignition-points
	if(cmdOptionExists(argv, argv+argc, "--ignition-points")){
        bool input_ignitions = true;
        printf("--ignition-points: %d \n", input_ignitions);
    }
	
	//--ignitions
	if(cmdOptionExists(argv, argv+argc, "--ignitions")){
        bool act_ignitions = true;
        printf("--ignitions: %d \n", act_ignitions);
    }
	
	//--statistics
	if(cmdOptionExists(argv, argv+argc, "--statistics")){
        bool input_excel = true;
		printf("--statistics: %d \n", input_excel);
    }
	
	//--combine
	if(cmdOptionExists(argv, argv+argc, "--combine")){
        bool input_combine = true;
		printf("--combine: %d \n", input_combine);
    }
	
	//--save-memory
	if(cmdOptionExists(argv, argv+argc, "--save-memory")){
		bool input_save = true;
		printf("--save-memory: %d \n", input_save);
    }
	
	//--scenarios-out
	if(cmdOptionExists(argv, argv+argc, "--scenarios-out")){
		bool input_scenario = true;
		printf("--scenarios-out: %d \n", input_scenario);
    }
	
	//--no-output
	if(cmdOptionExists(argv, argv+argc, "--no-output")){
		bool no_output = true;
		printf("--no-output: %d \n", no_output);
    }
	
	//--output-grid
	if(cmdOptionExists(argv, argv+argc, "--output-grid")){
		bool output_grid = true;
		printf("--output-grid: %d \n", output_grid);
    }
	



	// Floats
	//--sim-years  (float)
	char * sim_years = getCmdOption(argv, argv + argc, "--sim-years");
    if (sim_years){
        printf("--sim-years: %s \n", sim_years);
    }
	
	//--nsims
	char * input_nsims = getCmdOption(argv, argv + argc, "--nsims");
    if (input_nsims){
        printf("--nsims: %s \n", input_nsims);
    }
	
	//--Fire-Period-Length
	char * input_PeriodLen = getCmdOption(argv, argv + argc, "--Fire-Period-Length");
    if (input_PeriodLen){
        printf("--Fire-Period-Length: %s \n", input_PeriodLen);
    }
	
	//--Weather-Period-Length
	char * weather_period_len = getCmdOption(argv, argv + argc, "--Weather-Period-Length");
    if (weather_period_len){
        printf("--Weather-Period-Length: %s \n", weather_period_len);
    }
	
	//--ROS-Threshold
	char * ROS_Threshold = getCmdOption(argv, argv + argc, "--ROS-Threshold");
    if (ROS_Threshold){
        printf("--ROS-Threshold: %s \n", ROS_Threshold);
    }
	
	//--HFI-Threshold
	char * HFI_Threshold = getCmdOption(argv, argv + argc, "--HFI-Threshold");
    if (HFI_Threshold){
        printf("--HFI-Threshold: %s \n", HFI_Threshold);
    }
	
	//--ROS-CV
	char * ROS_CV = getCmdOption(argv, argv + argc, "--ROS-CV");
    if (ROS_CV){
        printf("--ROS-CV: %s \n", ROS_CV);
    }
	
	//--heuristic
	char * input_heur = getCmdOption(argv, argv + argc, "--heuristic");
    if (input_heur){
        printf("--heuristic: %s \n", input_heur);
    }
	
	//--max-fire-periods
	char * max_fire_periods = getCmdOption(argv, argv + argc, "--max-fire-periods");
    if (max_fire_periods){
        printf("--max-fire-periods: %s \n", max_fire_periods);
    }
	
	return 0;
}
