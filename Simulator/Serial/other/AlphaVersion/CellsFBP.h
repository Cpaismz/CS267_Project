#ifndef CELLSFBP
#define CELLSFBP

// include stuff
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

class CellsFBP {
    // TODO: find where to put the enums
    public:
        // immutable
        int id;
        double area;
        double vol;
        std::vector<int> coord; //maybe change this into a tuple or class	CP: 2-tuple (int)
        double age;
        int fType;
        double perimeter;
        std::unordered_map<std::string, std::vector<int>> adjacents; // CP: dictionary {string: [int array]}
        std::vector<double> color; // 4-tuple

        // mutable
        int status;
        int hPeriod;
        int fireStarts;
        std::unordered_map<int, std::vector<int>> gMsgList; // {40 -> [1, 2, 3] }

        std::string fType2;	
        int realId;
        double _ctr2ctrdist;							
        int harvestStarts;																															
        int fireStartsSeason;																																		
        int tYears;	
        std::unordered_map<int, std::vector<<int>> gMsgListSeason;
        std::unordered_map<int, double> fireProgress;	// CP: dictionary {int: double}
        std::unordered_map<int, double> angleDict;				// CP: dictionary {int: double}
        std::unordered_map<double, double> ROSAngleDir;       // CP: dictionary {int: double|None}   Instead of None we can use a determined number like -9999 = None  TODO: maybe int : double
        std::unordered_map<int, double> distToCenter;   	// CP: dictionary {int: double}
        std::unordered_map<double, int> angleToNb;			// CP: dictionary {double: int}
        bool triedToSpot;

        // TODO: reference to shared object


        //std::unordered_map<int, std::vector<int, int>> FSCell; // CP: this vector will be very sparse, a dict should be better?  need to re-think its logic
        //std::vector<int> FICell; // CP: this vector will be very sparse, a dict should be better? need to re-think its logic
        //int terrain;
        //std::vector<int> CH;																																			// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        //std::vector<int> CHVar;																																	// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        //double value;																																						// CP: double (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        // std::vector<double> productivity;																															// CP: vector of doubles (not currently implemented in the simulator, should be initilized by the heuristic class in the future)


        // constructor and methods here
        CellsFBP(int _id, double _area, std::vector<std::vector<double>> & _coord, double _age, int _fType, std::string _fType2, double _vol, double _perimeter, int _status, std::unordeded_map<std::string, std::vector<int>> & _adjacents, std::vector<double> _color, int _realId, bool outputGrid);
        
        void initializeFireFields(std::vector<std::vector<int>> & coordCells, std::unordered_set<int> availSet); // TODO: need TYPE
        
        void ros_distr(double thetafire, double forward, double flank, double back);
        
        std::vector<int> manageFire(int period, std::unordered_set<int> AvailSet, bool verbose, TYPE df, struct fuel_coeffs * coef, bool spotting, std::unordered_map<std::string, double> spottingParams, std::vector<int> & coordCells, std::unordered_map<int, CellsFBP> Cells_Obj, std::vector<std::string> args); // TODO: we can't have a generic "args" in c                                 CP: Returns a vector of integers
        
        bool get_burned(int period, int NMsg, int season, bool verbose, TYPE df, struct fuel_coeffs * coef, double ROSThresh);

        void set_Adj(std::unordered_map<std::string, std::vector<int>> & adjacentCells);
        void setStatus(int status_int);
        std::string getStatus();
        bool ignition(int period, int season, std::vector<int> ignitionPoints, TYPE df, struct fuel_coeffs * coef, double ROSThresh, double HFIThresh);
        //std::vector<TYPE> got_burnt_from_mem(int period, std::vector<TYPE> msgLists, int season, bool verbose);
        // void FS_definition();
        void harvested(int id, int period);
        void print_info();
        
    private:
        double allocate(double offset, double base, double ros1, double ros2);
};

#endif
