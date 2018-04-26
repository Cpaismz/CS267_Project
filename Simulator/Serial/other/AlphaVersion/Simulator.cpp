// TODO: not sure what to do about args for now
#include <string>
#include <vector>

void Simulator::init_args() {
}

void run() {
    // TODO: maybe we should move this to init_args...
    // not sure yet
    this->listLen = 18;
    coef_ptr // TODO
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
    TYPE spotting
    TYPE spottingParams
    bool outputGrid = false;
    int totalSims = ;// initialize
    int totalYears = ;
    std::string weatherOpt; 
    int minutesPerWP;
    int firePeriodLen;
    int maxFirePeriods;
    int startThreshold;

    if (firePeriodLen > minutesPerWP) {
        firePeriodLen = minutesPerWP;
    }

    /*############## READ DATA FRAM# & FUEL TYPES #########################*/

    int max_weeks = 12;
    int sim = 1;



    /*##################### GLOBAL FOREST DATA ############################*/

    // TODO: fill in output from GForestN, GForestType, Rows, Cols, AdjCells, CoordCells, CellSide = ReadDataPrometheus.ForestGrid(ForestFile,FBPDict)
    vector<std::string> GForestType = ;
    int rows = ;
    int cols = ;
    std::unordered_map<std::string, std::vector<int>> adjCells = ;
    std::vector<std::vector<int>> CoordCells = ;
    double cellSide;

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
                    std::cout << "realCells[aux]: " << realCells[aux] << std::endl;
                    
                    if (statusCells[aux] != 4 && burntCells.find(aux+1) == burntCells.end()) {
                        if (Cells_Obj.find(aux) == Cells_Obj.end()) {
                            std::string data = GForestType[aux];
                            std::transform(data.begin(), data.end(), data.begin(), std::tolower);
                            Cells_Obj[aux] = CellsFBP.Cells((aux+1), areaCells, CoordCells[aux], ageCells, fTypeCells[aux], coef_ptr[FTypes2[data]], volCells, perimeterCells, statusCells[aux], adjCells[aux], colors[aux], realCells[aux], OutputGrid);
                            Cells_Obj[ignitions[year] - 1].initializeFireFields(CoordCells, availCells);
                        }

                        if (Cells_Obj[aux].getStatus() == "Available" && Cells_Obj[aux].fType != 0) {
                            if (Cells_Obj[aux].ignition(fire_period[year - 1], year, ignitions, df, coef_ptr, startThreshold, HFIThreshold)) {
                                // TODO: outputgrid
                                // TODO: verbose
                                // TODO: plottrue
                                break;  
                            }
                        }
                        loops++;
                        if (loops > nCells) {
                            noIgnition = true;
                            break;
                        }
                    }

                }
            } else {
                 // we have specific ignitions
                int temp = ignitions[year];
                std::string data = GForestType[temp - 1];
                std::transform(data.begin(), data.end(), data.begin(), std::tolower);

                if (burntCells.find(temp) == burntCells.end() && statusCells[temp - 1] != 4) {
                    if (Cells_Obj.find(temp - 1) == Cells_Obj.end()) {
                        Cells_Obj[temp - 1] = CellsFBP.Cells(temp, areaCells, CoordCells[temp-1], ageCells, fTypeCells[temp-1], coef_ptr[FTypes2[data]], volCells, perimeterCells, statusCells[temp - 1], adjCells[temp - 1], colors[temp - 1], realCells[temp - 1], outputGrid);
                        Cells_Obj[temp - 1].initializeFireFields(CoordCells, availCells);
                    }
                    if (Cells_Obj[temp - 1].getStatus() != "Available" || Cells_Obj[temp - 1].fType == 0) {
                        noIgnition = true;
                    }

                    if (Cells_Obj[temp - 1].getStatus() == "Available" && Cells_Obj[temp - 1].fType != 0) {
                        // do nothing
                        // TODO: verbose, output, etc.
                        std::cout<< "holder print" << std::endl;
                    }

                } else {
                    noIgnition = true;
                    // TODO: verbose
                }
                
            }
            if (!noIgnition) {
                if (ignitions == "") {
                    // TODO: type safety of ignitions
                    int newId = Cells_obj[aux].id;
                    burningCells.insert(newId);
                    // this won't scale
                    std::unordered_set<int> intersect;
                    // https://stackoverflow.com/a/13448094
                    std::set_difference(availCells.begin(), availCells.end(), burningCells.begin(), burningCells.end(), std::inserter(intersect, intersect.begin()));
                    availCells = intersect;
                } else {
                    int newId = Cells_Obj[ignitions[year] - 1].id;
                    burningCells.insert(newId);
                    burntCells.insert(newId);

                    std::unordered_set<int> intersect;
                    // https://stackoverflow.com/a/13448094
                    std::set_difference(availCells.begin(), availCells.end(), burningCells.begin(), burningCells.end(), std::inserter(intersect, intersect.begin()));
                    availCells = intersect;
                    availCells = intersect; 
                }
            }

            // ****************NEXT PERIOD t +1 
            firePeriod[year - 1] += 1;
            // TODO: verbose
            if (weatherOpt != "constant" && firePeriod[year - 1] * firePeriodLen / minutesPerWP > weatherPeriod + 1) {
                weatherPeriod++;
                df = weatherObj.updateWEatherFBP(df, weatherOpd, weatherPeriod);
                // TODO: make sure weather thing works
            }
            // TODO: verbose

            if (week_number == 12 || fire_Period[year - 1] == 2016) { // what does 2016 mean lol
                std::cout << "end of year " << year << "------------------------------------" << std::endl;
            }

            if (noIgnition) {
                // TODO: verbose
                year += 1;
                week_number = 1;
            }


                
            // SEND RECEIVE MESSAGES ----------------------------------
            if (!noIgnition) {
                while (firePeriod[year - 1] < maxFirePeriods) {
                    if (firePeriod[year - 1] == madFirePeriod - 1) {
                        std::cout << "*** WARNING!!! About to hit MaxFirePeriods: " << maxFirePeriods << std::endl;
                    }


                    /// send messages !!
                    bool messagesSent = false;
                    std::unordered_map<int, vector<int>> sendMessageList;

                    // TODO: verbose
                    for (auto & _cell : Cells_Obj) {
                        int cell = _cell.first;
                        if (_cell.second.ROSAngleDir.size() > 0) {
                            for (auto & _angle : _cell.second.angle_to_nb) {
                                int angle = _angle.first;
                                int nb = _angle.second;
                                if (availCells.find(nb) == availCells.end() && _cell.second.ROSAngleDir.find(angle) != _cell.second.ROSAngleDir.end()) {
                                    // TODO: verbose
                                    _cell.second.ROSAngleDir.erase(angle);
                                }
                            }
                        }
                    }

                    // TODO: verbose

                    bool repeatFire = false;
                    vector<int> burnedOutList;


                    // PARALLEL ZONE
                    vector<int> aux_list;
                    for (int cell : burningCells) {
                        // TODO: verbose

                        if (Cells_Obj[cell - 1].ROSAngleDir.size() > 0) {
                            // TODO: verbose
                            aux_list = Cells_Obj[cell - 1].manageFire(firePeriod[year - 1], availCells, verbose, df, coef_ptr, spotting, spottingParams, CoordCells, Cells_Obj, args);
                        } // TODO: side effect-less else branch

                        // TODO: verbose
                        

                        // TODO: TYPE SAFETY
                        // TODO: CP i forgot what the constant is
                        if (aux_list.size() > 0 && aux_list[0] != "True") {
                            // TODO: verbose
                            messagesSent = true;
                            sendMessageList[Cells_Obj[cell - 1].id] = aux_list; 
                        }

                        // TODO: TYPE SAFETY
                        if (aux_list.size() > 0 && aux_list[0] == "True") {
                            repeatFire = true;
                        }

                        if (aux_list.size() == 0) {
                            burnedOutList.append(Cells_Obj[cell - 1].id);
                        }
 
                    }


                    std::unordered_set<int> tempBurningSet;
                    std::set_difference(burningCells.begin(), burningCells.end(), burnedOutList.begin(), burnedOutList.end(), std::inserter(tempBurningSet, tempBurningSet.begin()));
                    // this won't scale
                    burningCells = tempBurningSet;
                    


                    int numMessages = 0;
                    for (auto & p : sendMessageList) {
                        for (auto & q : p.second) {
                            numMessages += q.size();
                        }
                    }

                    // TODO: lots of verbose
                    if (repeatFire && numMessages == 0) {
                        std::cout < "Fires are still alive, no message generated" << std::endl;
                        std::cout <<  "Current fire period: " << firePeriod[Year - 1] << std::endl;
                        firePeriod[year - 1] += 1;

                        if (weatherOpt != "constant" && firePeriod[year - 1] * firePEriodLen / minutesPerWP > weatherPeriod + 1) {
                            weatherPeriod += 1;
                            df = weather_Obj.updateWeatherFBP(df, weatherOpt, weatherPeriod);
                            // TODO: weather + verbose
                        }
                    }

                    if (repeatFire && numMessage > 0) {
                        std::cout << "messages have been sent, next step. current period: " << firePeriod[year - 1] << std::endl;
                        repeatFire = false;
                    }
                    if (!messagesSent && !repeatFire) {
                        year += 1;
                        week_number = 1;
                        weatherPeriod = 0;
                        std::unordered_set<int> tempBurntCells;
                        std::set_union(burntCells.begin(), burntCells.end(), burningCells.begin(), burningCells.end(), std::inserter(tempBurntCells, tempBurntCells.begin()));

                        burntCells = tempBurntCells;
                        burningCells = std::unordered_set<int>();
                        // TODO: savemem

                        break;
                    }
                    
                    // ****************** RECEIVING MESSAges

                    if (messagesSent && !repeatFire) {
                        // frequency array
                        std:unordered_map<int, int> globalMessagesList;
                        for (auto & sublist : sendMessageList) {
                            for (int val : sublist.second) {
                                if (globalMessagesList.find(val) == globalMessagesList.end() {
                                    globalMessagesList[val] = 1;
                                } else {
                                    globalMessagesList[val] = globalMessagesList[val] + 1;
                                }
                            }
                        }
                        for (auto & _bc : globalMessagesList) {
                            int bc = _bc.first;
                            if (Cells_Obj.find(bc - 1) == Cells_Obj.end() && burntCells.find(bc) == burntCells.end()) {
                                std::string data = GForestType[bc - 1];
                                std::transform(data.begin(), data.end(), data.begin(), std::tolower);
                                Cells_Obj[bc-1] = CellsFBP.Cells(bc, areaCells, CoordCells[bc - 1], ageCells, fTypeCells[be-1], coef_ptr[fTypes2[data]], volCells, perimeterCells, statusCells[bc-1], adjCells[bc-1], colors[bc-1], realCells[bc-1], outputGrid);
                                Cells_Obj[bc-1].initializeFireFields(CoordCells, availCells);
                            }
                        }

                        // TODO: plot

                        std::unordered_set<int> burntList;
                        for (auto & _bc : globalMessagesList) {
                            int bc = _bc.first;
                            if (burntCells.find(bc) == burntCells.end()) {
                                if (Cells_Obj.find(bc - 1) == Cells_Obj.end()) {
                                    
                                    std::string data = GForestType[bc - 1];
                                    std::transform(data.begin(), data.end(), data.begin(), std::tolower);
                                    Cells_Obj[bc-1] = CellsFBP.Cells(bc, areaCells, CoordCells[bc - 1], ageCells, fTypeCells[be-1], coef_ptr[fTypes2[data]], volCells, perimeterCells, statusCells[bc-1], adjCells[bc-1], colors[bc-1], realCells[bc-1], outputGrid);
                                    Cells_Obj[bc-1].initializeFireFields(CoordCells, availCells);
                                }
                                if (Cells_Obj[bc-1].fType != 0) {
                                    
                                    checkBurnt = Cells_Obj[bc-1].getBurned(firePeriod[year-1], globalMessagesList[bc-1], year, verbose, df, coef_ptr, args.ROS_Threshold);// TODO: ARGS
                                } else {
                                    checkBurnt = false;
                                }
                                // TODO: verbose
                                if (checkBurnt) {
                                    burntList.insert(Cells_Obj[bc-1].id);
                                }

                            }
                        }
                        // TODO:might want to optimize these
                        std::unordered_set<int> tempSet;
                        std::setUnion(burntList.begin(), burntList.end(), burntCells.begin(), burntCells.end(), std::inserter(tempSet, tempSet.begin()));
                        std::setUnion(tempSet.begin(), tempSet.end(), burnedOutList.begin(), burnedOutList.end(), std::inserter(burntCells, burntCells.begin()));
                        tempSet = unordered_set<int>();
                        std::setUnion(burntList.begin(), burntList.end(), burningCells.begin(), burningCells.end(), std::inserter(tempSet, tempSet.begin())); 
                        tempSet = unordered_set<int>();
                        std::setDifference(availCells.begin(), availCellsend(), burntList.begin(), burntList.end(), std::inserter(tempSet, tempSet.begin())); 
                        availCells = tempSet;

                        // TODO: verbose + plot


                        // ******************* NEXT PERIOD

                        firePeriod[year - 1] += 1;
                        if (weatherOpt != "constant" && firePeriod[year - 1] * firePeriodLen/minutesPerWP > weatherPeriod) {
                            weatherPeriod += 1;
                            df = weather_OBJ.updateWeatherFBP(df, weatherOpt, weatherPeriod=weatherPeriod)

                            // TODO: verbose
                        }
                        if (firePeriod[year - 1] >= 168 * 60 / firePeriodLen) {
                            weekNumber += 1;
                        }

                    }

                }
                std::cout << "next year" << std::endl;
                year += 1;
                week_number = 1;
                weatherPeriod = 0;
            }
        }
        for (auto & br : burntCells) {
            if (Cells_Obj.find(br-1) != Cells_Obj.end()) {
                Cells_Obj[br-1].status = 2;
            }
        }

        for (auto & br : burningCells) {
            if (Cells_Obj.find(br-1) != Cells_Obj.end()) {
                Cells_Obj[br-1].status = 2;
            }
        }
        sim += 1;
        // TODO: figure out what you want to do about output
        
    }



}
