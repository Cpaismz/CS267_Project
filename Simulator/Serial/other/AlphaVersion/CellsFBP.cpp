// Include classes
#include "CellsFBP.h"
#include "SpottingFBP.h"
#include "FBP5.0.h"

// Include libraries
#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;


/*
	Constructor
*/
CellsFBP::CellsFBP(int _id, double _area, std::vector<int> _coord, double _age, 
							int _fType, std::string _fType2, double _vol, double _perimeter, 
							int _status, std::unordered_map<std::string, std::vector<int>> & _adjacents, 
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
												std::unordered_set<int> & availSet) 
{  
    for (auto & nb : this->adjacents) {
        // CP Default value is replaced: None = -1
        if (nb.second[0] != -1) {
            int a = -1 * coordCells[nb.second[0] - 1][0] + coordCells[this->id - 1][0];
            int b = -1 * coordCells[nb.second[0] - 1][1] + coordCells[this->id - 1][1];
            
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

            this->angleDict[nb.second[0]] = angle;
            if (availSet.find(nb.second[0]) != availSet.end()) {
                // TODO: cannot be None, replaced None = -1   and ROSAngleDir has a double inside 
                this->ROSAngleDir[angle] = -1;
            }
            this->angleToNb[angle] = nb.second[0];
            this->fireProgress[nb.second[0]] = 0.0;
            this->distToCenter[nb.second[0]] = std::sqrt(a * a + b * b) * this->_ctr2ctrdist;
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
void CellsFBP::ros_distr(double thetafire, double forward, double flank, double back) {
    for (auto & angle : this->ROSAngleDir) {
        double offset = std::abs(angle.first - thetafire);
        
        double first;
        double second;
		double base = ((int)(offset)) / 90 * 90;
        
		// Distribute ROS
		if (offset >= 0 && offset <= 90) {
            first = forward;
            second = flank;
        } else if (offset > 90 && offset < 180) {
            first = flank;
            second = back;
        } else if (offset >= 180 && offset <= 270) {
            first = back;
            second = flank;
        } else if (offset > 270 && offset < 360) {
            first = flank;
            second = forward;
        }
        this->ROSAngleDir[angle.first] = this->allocate(offset, base, first, second);
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
double CellsFBP::allocate(double offset, double base, double ros1, double ros2) {
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
        
std::vector<int> CellsFBP::manageFire(int period, std::unordered_set<int> AvailSet, 
                                                          bool verbose, vector<inputs> & df, fuel_coefs * coef, 
														  bool spotting, std::unordered_map<std::string, double> spottingParams, 
														  std::vector<std::vector<int>> & coordCells, std::unordered_map<int, CellsFBP> Cells_Obj, 
														  std::vector<std::string> args) 
	{
	// Special flag for repetition (False = -99 for the record)
	int repeat = -99;
	
    // msg lists contains integers (True = -100)
    std::vector<int> msg_list_aux;
	msg_list_aux.push_back(0);
    std::vector<int> msg_list;

	// If spotting and haven't tried to spotting, make it true
    if (spotting && !this->triedToSpot) {
        this->triedToSpot = true;

		// Print-out spotting parameters
        if (verbose) {
            std::cout << "SPOTANGLE:" << spottingParams["SPOTANGLE"] << std::endl;
            std::cout << "SPOT0PROB:" << spottingParams["SPOT0PROB"] << std::endl;
            std::cout << "SPOT10TIME:" << spottingParams["SPOT10TIME"] << std::endl;
        }

        vector<int> spot_list = SpottingFBP(Cells_Obj, coordCells, AvailSet, df[0].waz, df[0].ws, spottingParams, verbose);
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
     
    // TODO: find a way to deal with args CP: OK for the moment since we will debug the deterministic version
    double ROSRV = 0;
    double ROSCV = 0;
    // might need to set it to random normal (numpy.random.randn())

	// Display if verbose True (FBP ROSs, Main angle, and ROS std (if included))
    if (verbose) {
        std::cout << "Main Angle: " << mainstruct.raz << std::endl;
        std::cout << "FBP Front ROS Value: " << headstruct.ros << std::endl; 
        std::cout << " FBP Flanks ROS Value: " << flankstruct.ros << std::endl;
        std::cout <<  "FBP Rear ROS Value: " << backstruct.ros << std::endl;
        std::cout << "Std Normal RV for Stochastic ROS CV: " << ROSRV << std::endl;
    }

	// If cell cannot send (thresholds), then it will be burned out in the main loop
    double HROS = (1 + ROSCV * ROSRV) * headstruct.ros;
    // TODO : args
	// Workaround: hard-coded thresholds from Python tests
	double ROS_Threshold = 0.1;   //args.
	double HFI_Threshold = 0.1;    //args.
	
	// Extra debug step for sanity checks
	if (verbose){
            std::cout << "Sending message conditions" << std::endl;
            std::cout << "HROS: " << HROS << " Threshold: "<<  ROS_Threshold << std::endl;
            std::cout << "HeadStruct FI: " << headstruct.fi << " Threshold: " << HFI_Threshold << std::endl;
	}
	
    // Check thresholds for sending messages	
    if (HROS > ROS_Threshold && headstruct.fi > HFI_Threshold) {
        // True = -100
		repeat = -100;	
		
		if (verbose) {
            std::cout << "Repeat condition: " << repeat << std::endl;
            std::cout << "Cell can send messages" << std::endl;
        }
        
		// ROS distribution method
        ros_distr(mainstruct.raz,  headstruct.ros, flankstruct.ros, backstruct.ros);
        /*if (verbose){
			std::cout << "ROSAngleDir Cell" << this->id << ":" << this->ROSAngleDir << std::endl;
            std::cout << "Fire Progress before this update" << this>id << ":" << this->FireProgress << std::endl;
		}*/
		
		
		/* Fire progress using ROS from burning cell, not the neighbors */
        vector<double> toPop = vector<double>();
        
		// this is a iterator through the keyset of a dictionary
        for (auto&  _angle : this->ROSAngleDir) {
            double angle = _angle.first;
            int nb = angleToNb[angle];
            double ros = (1 + ROSCV * ROSRV) * _angle.second;

            if (verbose) {
                std::cout << "     (angle, realized ros in m/min): (" << angle << ", " << ros << ")" << std::endl;
            }
			
            // TODO: args
			// Workaround PeriodLen in 60 minutes
			double PeriodLen = 60.0;   // args.input_PeriodLen
            this->fireProgress[nb] += ros * PeriodLen;   // Updates fire progress
		
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
        
			for (double temp : toPop) {
				this->ROSAngleDir.erase(angle); 
			}
			
			
			if (this->fireProgress[nb] < this->distToCenter[nb] && repeat == -100 && -100  != msg_list_aux[0]){
                    if (verbose){
                        std::cout << "A Repeat = TRUE flag is sent in order to continue with the current fire....." << std::endl;
                        std::cout << "Main workaround of the new sim logic....." << std::endl;
					}
                    msg_list_aux[0] = repeat;
			}
						
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
				
    if (verbose){
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
	
bool CellsFBP::get_burned(int period, int NMsg, int season, bool verbose, std::vector<inputs> & df, 
									   fuel_coefs * coef, double ROSThresh) {
    if (verbose) { 
        std::cout << "ROS Threshold get_burned method" << std::endl;
		std::cout << "ROSThresh" << ROSThresh << std::endl;
    }

	// Structures
    main_outs mainstruct;
    snd_outs sndstruct;
    fire_struc headstruct, backstruct, flankstruct;

	// Compute main angle and ROSs: forward, flanks and back
    calculate(&(df[this->id]), coef, &mainstruct, &sndstruct, &headstruct, &flankstruct, &backstruct);

    if (verbose) { 
		std::cout << "Main Angle:" << mainstruct.raz << std::endl;
		std::cout << "Front ROS Value:" << headstruct.ros << std::endl;
		std::cout << "Flanks ROS Value:" << flankstruct.ros << std::endl;
		std::cout << "Rear ROS Value:" << backstruct.ros << std::endl;
	}
    
	// Check a threshold for the ROS
    if (headstruct.ros > ROSThresh) {
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
void CellsFBP::set_Adj(std::unordered_map<std::string, std::vector<int>> & adjacentCells) {
    // TODO: in python, these are pointers, maybe make these pointers too :P
    this->adjacents = adjacentCells;
}


/* 
    Returns            void
    
    Inputs:  
    Status_int         int
*/
void CellsFBP::setStatus(int status_int) {
    this->status = status_int;
}


/*
    Returns            string
    
    Inputs:  
*/
std::string CellsFBP::getStatus() {
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
bool CellsFBP::ignition(int period, int season, int year, std::vector<int> ignitionPoints, vector<inputs> & df, 
								 fuel_coefs * coef, double ROSThreshold, double HFIThreshold, bool verbose) {
    
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

        calculate(&(df[this->id]), coef, &mainstruct, &sndstruct, &headstruct, &flankstruct, &backstruct);

        if (verbose) {
			std::cout << "In ignition function" << std::endl;
			std::cout << "Main Angle:" << mainstruct.raz << std::endl;
			std::cout << "Front ROS Value:" << headstruct.ros << std::endl;
			std::cout << "Flanks ROS Value:" << flankstruct.ros << std::endl;
			std::cout << "Rear ROS Value:" << backstruct.ros  << std::endl;
			std::cout << "need to fill out this verbose" << std::endl;
        }
		
		// Check a threshold for the ROS
        if (headstruct.ros > ROSThreshold && headstruct.fi > HFIThreshold) {
            if (verbose) {
                std::cout << "Head (ROS, FI) values of" << headstruct.ros << headstruct.fi  <<  "are enough for ignition" << std::endl;
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
void CellsFBP::harvested(int id, int period) {
    // TODO: unused param
    this->status = 3;
    this->harvestStarts = period;
}



/*
    Returns      void
*/
void CellsFBP::print_info() {
	std::cout << "Cell Information" << std::endl;
	std::cout << "ID = "  << this->id<< std::endl;
    std::cout << "Status = " << this->StatusD[this->status] << std::endl;
    //std::cout << "Coordinates = " << this->coord << std::endl;
    std::cout << "Area = "<<  this->area << std::endl;
    std::cout << "Vol = " << this->vol << std::endl;
    std::cout << "Age = " << this->age << std::endl;
    std::cout << "FTypes = "<< this->FTypeD[this->fType] << std::endl;
    //std::cout << "Adjacents = " << this->adjacents << std::endl;
    std::cout << "need to fill out this verbose" << std::endl;
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		
// Main for debugging
int main(){
	std::cout << "CellsFBP has been compiled!" << std::endl;
	return 0;
}
