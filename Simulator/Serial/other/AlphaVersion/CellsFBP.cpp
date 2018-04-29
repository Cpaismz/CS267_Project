// Include classes
#include "CellsFBP.h"
#include "SpottingFBP.h"
#include "FBP5.0.h"
#include "ReadCSV.h"
#include "ReadArgs.h"

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
//#define RAND_MAX 0.5

using namespace std;


/*
	Constructor   // WORKING CHECK OK
*/
CellsFBP::CellsFBP(int _id, double _area, std::vector<int> _coord, double _age, 
							int _fType, std::string _fType2, double _vol, double _perimeter, 
							int _status, std::unordered_map<std::string, int> & _adjacents, 
							std::vector<double> _color, int _realId, bool outputGrid)
{
	// Global "dictionaries" (vectors) for status and types
	// Status: 0: "Available", 1: "Burning", 2: "Burnt", 3: "Harvested", 4:"Non Fuel"
	this->StatusD[0] = "Available";
	this->StatusD[1] = "Burning";
	this->StatusD[2] = "Burnt";
	this->StatusD[3] = "Harvested";
	this->StatusD[4] = "Non Fuel";
	
	// FTypeD: 0: "NonBurnable", 1: "Normal", 2: "Burnable
	this->FTypeD[0] = "NonBurnable";
	this->FTypeD[1] = "Normal";
	this->FTypeD[2] = "Burnable";
	
	// Initialize fields of the Cell object 
    this->id = _id;
    this->area = _area;
    this->coord = _coord;
    this->age = _age;
    this->fType = _fType;
    this->fType2 = _fType2;
    this->vol = _vol;
    this->perimeter = _perimeter;
    this->status = _status;
    this->adjacents = _adjacents;
    this->color = _color;
    this->realId = _realId;
    this->_ctr2ctrdist = std::sqrt(this->area);

    if (std::abs(4 * this->_ctr2ctrdist - this->perimeter) > 0.01 * this->perimeter) {
        std::cerr << "Cell ID=" << this->id << "Area=" <<  this->area <<  "Perimeter=" <<  this->perimeter << std::endl;
        // maybe raise runtime error
    }
	
	// Inner fields
    this->gMsgList = std::unordered_map<int, std::vector<int>>();
    this->hPeriod = 0;

    this->fireStarts = 0;
    this->harvestStarts = 0;
    this->fireStartsSeason = 0;
    this->tYears = 4;
	
    this->gMsgListSeason = std::unordered_map<int, std::vector<int>>();
    this->fireProgress = std::unordered_map<int, double>();
    this->angleDict = std::unordered_map<int, double>();
    this->ROSAngleDir = std::unordered_map<int, double>();
    this->distToCenter = std::unordered_map<int, double>();
    this->angleToNb = std::unordered_map<int, int>();
    this->triedToSpot = false;
}


/*
    Populates angles, distances, and initialize ROS per axis
    Modified by dlw to use cell area to compute distances in meters.
    ASSUME square fire cells.
    
    Returns        void
    
    Inputs:
    CoorCells      array of 2D int arrays
    AvailSet       int set
*/
void CellsFBP::initializeFireFields(std::vector<std::vector<int>> & coordCells,    // TODO: should probably make a coordinate type
												std::unordered_set<int> & availSet) 				// WORKING CHECK OK
{  
    for (auto & nb : this->adjacents) {
        // CP Default value is replaced: None = -1
		//std::cout << "DEBUG1: adjacent: " << nb.second << std::endl;
        if (nb.second != -1) {
            int a = -1 * coordCells[nb.second - 1][0] + coordCells[this->id][0];
            int b = -1 * coordCells[nb.second - 1][1] + coordCells[this->id][1];
            
            int angle = -1;
            if (a == 0) {
                if (b >= 0) 
                    angle = 270; 
                else 
                    angle = 90;
            }
            else if (b == 0) {
                if (a >= 0)
                    angle = 180;
                else
                    angle = 0;
            }
            else {
                // TODO: check this logi
                double radToDeg = 180 / M_PI;
                // TODO: i think all the negatives and abs cancel out
                double temp = std::atan(b * 1.0 / a) * radToDeg;
                if (a > 0)
                    temp += 180;
                if (a < 0 && b > 0) 
                    temp += 360;
                angle = temp;
            }

            this->angleDict[nb.second] = angle;
            if (availSet.find(nb.second) != availSet.end()) {
                // TODO: cannot be None, replaced None = -1   and ROSAngleDir has a double inside 
                this->ROSAngleDir[angle] = -1;
            }
            this->angleToNb[angle] = nb.second;
            this->fireProgress[nb.second] = 0.0;
            this->distToCenter[nb.second] = std::sqrt(a * a + b * b) * this->_ctr2ctrdist;
        }
    }
}

        
		
/*
    New functions for calculating the ROS based on the fire angles
	Distribute the rate of spread (ROS,ros) to the axes given in the AngleList.
    All angles are w.t.r. E-W with East positive and in non-negative degrees.
    Inputs:
            thetafire: direction of "forward"
            forward : forward ROS
            flank: ROS normal to forward (on both sides)
            back: ROS in the opposide direction of forward
            AngleList: List of angles for the axes connecting centers
                       of interest (might have less than 8 angles)
    Effect:
            Populate the ROSAngleDir, whose indexes are the angles,
            with ROS values.
        
	Returns       void
 */		
void CellsFBP::ros_distr(double thetafire, double forward, double flank, double back) {   // WORKING CHECK OK
    for (auto & angle : this->ROSAngleDir) {
        double offset = std::abs(angle.first - thetafire);
        
        double base = ((int)(offset)) / 90 * 90;
        double result;
		
		// Distribute ROS
		if (offset >= 0 && offset <= 90) {
            result = this->allocate(offset, 0, forward, flank);
        } else if (offset > 90 && offset < 180) {
            result = this->allocate(offset, 90, flank, back);
        } else if (offset >= 180 && offset <= 270) {
            result = this->allocate(offset, 180, back, flank);
        } else if (offset > 270 && offset < 360) {
            result = this->allocate(offset, 270, flank, forward);
        }
        this->ROSAngleDir[angle.first] = result;
    }
}		
		

/*
	Returns      double
	
	Inputs:
	offset       double
	base         double
	ros1         double
	ros2         double
*/	
double CellsFBP::allocate(double offset, double base, double ros1, double ros2) {   // WORKING CHECK OK
    double d = (offset - base) / 90;
    return (1 - d) * ros1 + d * ros2;
}


/*
    Returns           vect[integers]   Important: we are sending a True sometimes, pick a special value -x for replacing it
    
    Inputs:
    period            int
    AvailSet          int set
    verbose           boolean
    df                Data frame
    coef              pointer
    spotting          boolean
    SpottingParams    Data frame
    CoordCells        array of 2D doubles arrays
    Cells_Obj         dictionary of cells objects
*/
        
std::vector<int> CellsFBP::manageFire(int period, std::unordered_set<int> & AvailSet,      
                                                          inputs df[], fuel_coefs * coef, 
														  std::unordered_map<std::string, double> spottingParams, 
														  std::vector<std::vector<int>> & coordCells, std::unordered_map<int, CellsFBP> & Cells_Obj, 
														  arguments * args, weatherDF * wdf_ptr) 
	{
	// Special flag for repetition (False = -99 for the record)
	int repeat = -99;
	
    // msg lists contains integers (True = -100)
    std::vector<int> msg_list_aux;
	msg_list_aux.push_back(0);
    std::vector<int> msg_list;

	df[this->id].waz = wdf_ptr->waz;
	df[this->id].ws = wdf_ptr->ws;
	df[this->id].ffmc = wdf_ptr->ffmc;
	df[this->id].bui = wdf_ptr->bui;	
	
	// If spotting and haven't tried to spotting, make it true
    if (args->spotting && !this->triedToSpot) {
        this->triedToSpot = true;

		// Print-out spotting parameters
        if (args->verbose) {
            std::cout << "SPOTANGLE:" << spottingParams["SPOTANGLE"] << std::endl;
            std::cout << "SPOT0PROB:" << spottingParams["SPOT0PROB"] << std::endl;
            std::cout << "SPOT10TIME:" << spottingParams["SPOT10TIME"] << std::endl;
        }
        
        vector<int> spot_list = SpottingFBP(Cells_Obj, coordCells, AvailSet, df[this->id].waz, df[this->id].ws, spottingParams, args->verbose);
        std::cout << "debug: spot_list len= " << spot_list.size() << std::endl;

		// Populate the message list from spotting
        for (int si : spot_list) {
            msg_list.push_back(si);
        }
    }

	// Compute main angle and ROSs: forward, flanks and back
    main_outs mainstruct;
    snd_outs sndstruct;
    fire_struc headstruct, backstruct, flankstruct;

	calculate(&(df[this->id]), coef, &mainstruct, &sndstruct, &headstruct, &flankstruct, &backstruct);
    double cartesianAngle = 450 - mainstruct.raz; 
	if (cartesianAngle >= 360){
		cartesianAngle -= 360;
	} 
	 
    double ROSRV = 0;
    if (args->ROSCV > 0) {
	    //std::srand(args->seed);
		std::default_random_engine generator(args->seed);
		std::normal_distribution<double> distribution(0.0,1.0);
		ROSRV = distribution(generator);
	}

	// Display if verbose True (FBP ROSs, Main angle, and ROS std (if included))
    if (args->verbose) {
        std::cout << "Main Angle (raz): " << mainstruct.raz  << " Cartesian: " << cartesianAngle << std::endl;
        std::cout << "FBP Front ROS Value: " << headstruct.ros << std::endl; 
        std::cout << "FBP Flanks ROS Value: " << flankstruct.ros << std::endl;
        std::cout <<  "FBP Rear ROS Value: " << backstruct.ros << std::endl;
        std::cout << "Std Normal RV for Stochastic ROS CV: " << ROSRV << std::endl;
    }

	// If cell cannot send (thresholds), then it will be burned out in the main loop
    double HROS = (1 + args->ROSCV * ROSRV) * headstruct.ros;
    	
	// Extra debug step for sanity checks
	if (args->verbose){
            std::cout << "\nSending message conditions" << std::endl;
            std::cout << "HROS: " << HROS << " Threshold: "<<  args->ROSThreshold << std::endl;
            std::cout << "HeadStruct FI: " << headstruct.fi << " Threshold: " << args->HFIThreshold << std::endl;
	}
	
    // Check thresholds for sending messages	
    if (HROS > args->ROSThreshold && headstruct.fi > args->HFIThreshold) {
        // True = -100
		repeat = -100;	
		
		if (args->verbose) {
            std::cout << "\nRepeat condition: " << repeat << std::endl;
            std::cout << "Cell can send messages" << std::endl;
        }
        
		// ROS distribution method
        //ros_distr(mainstruct.raz,  headstruct.ros, flankstruct.ros, backstruct.ros);
		ros_distr(cartesianAngle,  headstruct.ros, flankstruct.ros, backstruct.ros);
        		
		/* Fire progress using ROS from burning cell, not the neighbors */
        vector<double> toPop = vector<double>();
        
		// this is a iterator through the keyset of a dictionary
        for (auto&  _angle : this->ROSAngleDir) {
            double angle = _angle.first;
            int nb = angleToNb[angle];
            double ros = (1 + args->ROSCV * ROSRV) * _angle.second;

            if (args->verbose) {
                std::cout << "     (angle, realized ros in m/min): (" << angle << ", " << ros << ")" << std::endl;
            }
			            
			// Workaround PeriodLen in 60 minutes
            this->fireProgress[nb] += ros * args->FirePeriodLen;   // Updates fire progress
		
		    // If the message arrives to the adjacent cell's center, send a message
            if (this->fireProgress[nb] >= this->distToCenter[nb]) {
                msg_list.push_back(nb);
                // cannot mutate ROSangleDir during iteration.. we do it like 10 lines down
                toPop.push_back(angle);
                /*if (verbose) {
                    //fill out this verbose section
                    std::cout << "MSG list" << msg_list << std::endl;
                }*/
            }    
        
			// Info for deebugging status of the cell and fire evolution
			if (args->verbose){
				printf("\n\n IMPORTANT INFO CELL FOR DEBUG: MANAGEFIRE \n\n");
				this->print_info();
				printf("\n\n IMPORTANT INFO CELL FOR DEBUG: MANAGEFIRE \n\n");
			}
			
			if (this->fireProgress[nb] < this->distToCenter[nb] && repeat == -100 && -100  != msg_list_aux[0]){
                    if (args->verbose){
                        std::cout << "A Repeat = TRUE flag is sent in order to continue with the current fire....." << std::endl;
                        std::cout << "Main workaround of the new sim logic....." << std::endl;
					}
                    msg_list_aux[0] = repeat;
			}
						
		}

        for (double temp : toPop) {
            this->ROSAngleDir.erase(temp);
        }
			
		

    }
	
	
	// If original is empty (no messages but fire is alive if aux_list is not empty)
	if  (msg_list.size() == 0){
		if (msg_list_aux[0] == -100){
			msg_list = msg_list_aux;
		}
	
		else{
			this->status = 2;   // we are done sending messages, call us burned
		}
	}
				
    if (args->verbose){
		std::cout << " ----------------- End of new manageFire function -----------------" << std::endl;
	}
    return msg_list;
}
    
		
		
/*
    Get burned new logic: Checks if the ROS on its side is above a threshold for burning
	
	Returns     boolean  
    
    Inputs:
    period      int
    NMsg        int
    Season      int
    verbose     boolean
    df          Data frame
    coef        pointer
    ROSThresh   double
 */
	
bool CellsFBP::get_burned(int period, int season, int NMsg, inputs df[],  fuel_coefs * coef, arguments * args, weatherDF * wdf_ptr) {
    if (args->verbose) { 
        std::cout << "ROS Threshold get_burned method" << std::endl;
		std::cout << "ROSThreshold: " << args->ROSThreshold << std::endl;
    }

	// Structures
    main_outs mainstruct;
    snd_outs sndstruct;
    fire_struc headstruct, backstruct, flankstruct;

	// Compute main angle and ROSs: forward, flanks and back
	df[this->id].waz = wdf_ptr->waz;
	df[this->id].ws = wdf_ptr->ws;
	df[this->id].ffmc = wdf_ptr->ffmc;
	df[this->id].bui = wdf_ptr->bui;	
    calculate(&(df[this->id]), coef, &mainstruct, &sndstruct, &headstruct, &flankstruct, &backstruct);

    if (args->verbose) { 
		std::cout << "\nMain Angle :" << mainstruct.raz << std::endl;
		std::cout << "Front ROS Value :" << headstruct.ros << std::endl;
		std::cout << "Flanks ROS Value :" << flankstruct.ros << std::endl;
		std::cout << "Rear ROS Value :" << backstruct.ros << std::endl;
	}
    
	// Check a threshold for the ROS
    if (headstruct.ros > args->ROSThreshold) {
        this->status = 1;
        this->fireStarts = period;
        this->fireStartsSeason = season;
        this->burntP = period;
        return true;
    }
    // Not burned
    return false; 
}


		
/* Old functions
    Returns            void
    
    Inputs:  
    AdjacentCells      dictionary{string:[array integers]}
*/
void CellsFBP::set_Adj(std::unordered_map<std::string, int> & adjacentCells) {   // WORKING CHECK OK
    // TODO: in python, these are pointers, maybe make these pointers too :P
    this->adjacents = adjacentCells;
}


/* 
    Returns            void
    
    Inputs:  
    Status_int         int
*/
void CellsFBP::setStatus(int status_int) {   // WORKING CHECK OK
    this->status = status_int;
}


/*
    Returns            string
    
    Inputs:  
*/
std::string CellsFBP::getStatus() {		// WORKING CHECK OK
    // Return cell's status
    return this->StatusD[this->status];
}

		
/*
    Returns           boolean
    
    Inputs:
    period            int
    Season            int
    IgnitionPoints    array of int
    df                Data frame
    coef              pointer
    ROSThresh         double
    HFIThreshold      double
 */
bool CellsFBP::ignition(int period, int year, std::vector<int> & ignitionPoints, inputs df[],   // WORKING CHECK OK
								 fuel_coefs * coef, arguments *args, weatherDF * wdf_ptr) {
    
	// If we have ignition points, update
    if (ignitionPoints.size() > 0) {
        this->status = 1;
        this->fireStarts = period;
        this->fireStartsSeason = year;
        this->burntP = period;

		// An ignition has happened
        return true;
    } else {
        // Ignites if implied head ros andfire intensity are high enough
        main_outs mainstruct;
        snd_outs sndstruct;
        fire_struc headstruct, backstruct, flankstruct;

		printf("\nWeather inside ignition:\n");
		std::cout << "waz: " << wdf_ptr->waz << "  ffmc: " <<    wdf_ptr->ffmc << "  bui: " <<   wdf_ptr->bui << std::endl;
		
		df[this->id].waz = wdf_ptr->waz;
		df[this->id].ws = wdf_ptr->ws;
		df[this->id].ffmc = wdf_ptr->ffmc;
		df[this->id].bui = wdf_ptr->bui;	
			
        calculate(&df[this->id], coef, &mainstruct, &sndstruct, &headstruct, &flankstruct, &backstruct);

        if (args->verbose) {
			std::cout << "\nIn ignition function" << std::endl;
			std::cout << "Main Angle: " << mainstruct.raz << std::endl;
			std::cout << "Front ROS Value: " << headstruct.ros << std::endl;
			std::cout << "Flanks ROS Value: " << flankstruct.ros << std::endl;
			std::cout << "Rear ROS Value: " << backstruct.ros  << std::endl;
        }
		
		// Check a threshold for the ROS
        if (headstruct.ros > args->ROSThreshold && headstruct.fi > args->HFIThreshold) {
            if (args->verbose) {
                std::cout << "Head (ROS, FI) values of: (" << headstruct.ros << ", " << headstruct.fi  <<  ") are enough for ignition" << std::endl;
            }

            this->status = 1;
            this->fireStarts = period;
            this->fireStartsSeason = year;
            this->burntP = period;

            return true;
        }
        return false;
    }
}		
		
		
		
/*
    Returns      void
    Inputs
    ID           int
    period       int
*/
void CellsFBP::harvested(int id, int period) {     // WORKING CHECK OK
    // TODO: unused param
    this->status = 3;
    this->harvestStarts = period;
}



/*
    Returns      void
*/
void CellsFBP::print_info() {    // WORKING CHECK OK
	std::cout << "Cell Information" << std::endl;
	std::cout << "ID = "  << this->id<< std::endl;
	std::cout << "In Forest ID = "  << this->realId<< std::endl;
    std::cout << "Status = " << this->StatusD[this->status] << std::endl;
    std::cout << "Coordinates: ";
	std::cout << this->coord[0] <<  " " << this->coord[1]  << std::endl;
	
	std::cout << "Area = "<<  this->area << std::endl;
    std::cout << "Vol = " << this->vol << std::endl;
    std::cout << "Age = " << this->age << std::endl;
    std::cout << "FTypes = "<< this->FTypeD[this->fType] << std::endl;
    std::cout << "AdjacentCells:";
	for (auto & nb : this->adjacents){
		std::cout << " " << nb.first << ":" << nb.second;
	}
	std::cout << std::endl;
	
	printf("Angle Dict: ");
	for (auto & nb : this->angleDict){
		std::cout << " " << nb.first << " : " << nb.second;
	}
	std::cout << std::endl;
	
	printf("Ros Angle Dict: ");
	for (auto & nb : this->ROSAngleDir){
		std::cout << " " << nb.first << " : " << nb.second;
	}
	std::cout << std::endl;
	
	
	printf("angleToNb Dict: ");
	for (auto & nb : this->angleToNb){
		std::cout << " " << nb.first << " : " << nb.second;
	}
	std::cout << std::endl;
	
	
	printf("fireProgress Dict: ");
	for (auto & nb : this->fireProgress){
		std::cout << " " << nb.first << " : " << nb.second;
	}
	std::cout << std::endl;
	
	
	printf("distToCenter Dict: ");
	for (auto & nb : this->distToCenter){
		std::cout << " " << nb.first << " : " << nb.second;
	}
	std::cout << std::endl;
}


