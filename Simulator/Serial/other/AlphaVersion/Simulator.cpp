// TODO: not sure what to do about args for now
#include <string>
#include <vector>

void Simulator::init_args() {
}

void run() {
    // TODO: maybe we should move this to init_args...
    // not sure yet
    this->listLen = 18;
    std::vector<std::string> fTypes2 = {"m1", "m2", "m3", "m4", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "d1", "s1", "s2", "s3", "o1a", "o1b", "d2"};

    // TODO: initialize these args
    // inFolder, outFolder, saveMem, scenarios, noOutput, outputGrid, minutesPerWP, cellID, verbose, plotTrue, maxFirePeriods, totalYears, totalSims, firePeriodLen, forestFile, FBPLookup, ignitions, weatherOpt, spotting, excelTrue, heuristic, combine, genData, thresholds

    // TODO: args
    /*
    InFolder = args.input_folder;
    OutFolder = args.output_folder;
    SaveMem = args.input_save;
    scenarios = args.input_scenario;
    nooutput = args.no_output;
    OutputGrid = args.output_grid;
    MinutesPerWP = args.weather_period_len;
    cellID = args.FBP_tester_cell;
    verbose = args.verbose_input;
    plottrue = args.input_plottrue;
    Max_Fire_Periods = args.max_fire_periods;
    TotalYears= args.sim_years;
    TotalSims = args.input_nsims;
    FirePeriodLen = args.input_PeriodLen;
    ForestFile = args.input_forest;
    FBPlookup = args.input_fbplookup;
    Ignitions = args.input_ignitions;
    WeatherOpt = str.lower(args.input_weather);
    spotting = args.spotting_parameter_data_file_name;// is not None;
    exceltrue = args.input_excel;
    heuristic = args.input_heur;
    combine = args.input_combine;
    GenData = args.input_gendata;
    fireperiodLen = args.input_PeriodLen
    if (firePeriodLen > MinutesPerWP) {
        firePeriodLen = MinutesPerWP;
    }
    */
    int totalSims = ;// initialize
    int totalYears = ;
    std::string weatherOpt; 
    int minutesPerWP;
    int firePeriodLen;
    int maxFirePeriods;

    if (firePeriodLen > minutesPerWP) {
        firePeriodLen = minutesPerWP;
    }

    /*############## READ DATA FRAM# & FUEL TYPES #########################*/

    int max_weeks = 12;
    int sim = 1;



    /*##################### GLOBAL FOREST DATA ############################*/

    // TODO: fill in output from GForestN, GForestType, Rows, Cols, AdjCells, CoordCells, CellSide = ReadDataPrometheus.ForestGrid(ForestFile,FBPDict)
    int rows = ;
    int cols = ;
    std::unordered_map<std::string, std::vector<int>> adjCells = ;
    std::vector<std::vector<int>> CoordCells = ;
    double cellSide;
    int coordCells = ;
    int cellSide = ;

    int nCells = rows * cols;

    // TODO: these are initialize through a call to ParseInputs.InitCells
    std::vector<int> fTypeCells = ;
    std::vector<int> statusCells = ;
    std::vector<int> realCells = ;
    std::vector<std::vector<double>> colors = ;


    double volCells = 0.0;
    double ageCells = 0.0;

    double areaCells = cellSide * cellSide;
    double perimeterCells = cellSide * 4;

    


    /*########################### IFNITION, WEATHER... */

    int weatherPeriod = 0;
    // these are outputs from ParseInputs.init
    std::unordered_map<int, int> ignitions = ; // TODO
    Weather weather_obj = // TODO
    vector<inputs> df = // TODO: inputs your dataframe here!

    std::vector<Weather_Things> WOBJ;; TODO





    /* ################### SIMULATION LOOP ########################*/

    while (sim < totalSims) {
        std::cout << "------------------ Simulation Number: " << sim << std::endl;
        
        int week_number = 1;
        int year = 1;
        int weatherPeriod = 0;
        bool noIgnition = None; // TODO: cannot be None
        bool messagesSent = None; // TODO: cannot be None
        int plotNumber = 1;

        // for scoping reasons, we cannot do this in the if block, and tbh it's not expensive anyways
        std::unordered_map<TYPE, TYPE> FI;
        vector<int> hPeriod;
        hPeriod.push_back(0);
        vector<int> fire_period = vector<int>(totalYears, 0);

        std::unordered_map<TYPE, TYPE> burntP;

        // TODO: grab the time

        // TODO: plot

        if (weatherOpt == "rows") {
            int maxFP = minutesPerWP / FirePeriodLen * WOBJ.size(); // TODO: i just truncated instaed of rounding, is that ok
            if (maxFirePeriods >= maxFP) {
                maxFirePeriods = maxFP - 1;
                // TODO verbose
            }
        }
        
        //TODO: check if correct
        totalYears = std::max(totalYears, ignitions.size());

        Lightning Lambda_Strike = Lightning();

        //############################# CELLS OBJ DICTIONARY 

        std::unordered_map<int, CellsFBP> Cells_Obj;

        std::unordered_set<int> availCells;// TODO: no idea how to initialize this
        std::unordered_set<int> nonBurnableCells; // TODO: initialize
        std::unordered_set<int> burningCells;
        std::unordered_set<int> burntCells;
        std::unordered_set<int> harvestCells;

        // TODO: verbose

        while (year < totalYears) {
            // TODO: verbose x2

            // TODO: savemem

            int aux = 0;
            int loops = 0;
            bool noIgnition = False;
            int sel_week;
            if (ignitions == "") { // TODO: this violates type safety
                while (week_number <= max_weeks) {
                    if (Lambda_Strike.Lambda_NH(week_number, verbose)) {
                        sel_week = week_number;
                        //TODO: verbose
                    } else {
                        week_number++;
                    }
                }
            } else {
                week_number = 1;
                weatherPeriod = 0;
                sel_week = 1;
            }
            std::cout << "Selected Week (ignition)" << sel_week << std::endl;

            // TODO: is this repeated code?
            aux = 0;
            loops = 0;
            noIgnition = False; 
            if (ignitions == "") { // TODO: ignitions type safety
                while (true) {
                    aux = 1.0 * std::rand / RAND_MAX * nCells;

                    std::cout << "aux: " << aux << std::endl;
                    std::cout << "RealCells[aux]: " << realCells[aux] << std::endl;


                }
            }
        }
        
    }



}
