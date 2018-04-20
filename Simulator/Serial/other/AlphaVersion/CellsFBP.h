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
        std::vector<std::vector<double<> coord; //TODO: maybe change this into a tuple or class	CP: 2D array/vector of doubles/floats // need example
        double age; // TODO: are you sure this isn't an int?
        std::string fType; // TODO: are you sure this isn't an int?
        double perimeter;
        std::unordered_map<std::string, std::vector<int>> adjacents; // CP: dictionary {string: [int array]}
        std::vector<std::vector<double>> color; // TODO: python docs say color is String, but you claim -> CP: vector of 4D double lists/arrays [(d1,d2,d3,d4), (d11,d22,d33,d44)]

        // mutable
        int status;
        std::unordered_map<int, std::vector<int, int>> FSCell; // CP: this vector will be very sparse, a dict should be better?  need to re-think its logic
        std::vector<int> FICell; // CP: this vector will be very sparse, a dict should be better? need to re-think its logic
        int hPeriod; // TODO: is this an int?
        int fireStarts;
        std::vector<std::vector<TYPE>> gMsgList; // TODO: i need a type!  CP: vector of vectors [[],[],[],...,[]]

        int fType2;	
        int realId;
        double _ctr2ctrdist;							
        int harvestStarts;																															
        int fireStartsSeason;																																		
        int tYears;	
        std::vector<std::vector<<int>> gMsgListSeason;	// CP: vector of integer vectors [[int1,int2], [intx,inty,intz]]  (can have multiple dimensions inside)
        std::unordered_map<int, double> fireProgress;	// CP: dictionary {int: double}
        std::unordered_map<int, double> angleDict;				// CP: dictionary {int: double}
        std::unordered_map<int, double> ROSAngleDir;       // CP: dictionary {int: double|None}   Instead of None we can use a determined number like -9999 = None
        std::unordered_map<int, double> distToCenter;   	// CP: dictionary {int: double}
        std::unordered_map<int, double> angleToNb;			// CP: dictionary {int: double}
        bool triedToSpot;


        //int terrain;
        //std::vector<int> CH;																																			// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        //std::vector<int> CHVar;																																	// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        //double value;																																						// CP: double (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        // std::vector<double> productivity;																															// CP: vector of doubles (not currently implemented in the simulator, should be initilized by the heuristic class in the future)


        // constructor and methods here
        CellsFBP(int _id, double _area, std::vector<std::vector<double>> & _coord, double _age, std::string _fType, int _fType2, double _vol, double _perimeter, int _status, std::unodreded_map<std::string, std::vector<int>> & _adjacents, TYPE _color, int _realId, bool outputGrid); // TODO: check type of age, fType, coord, color
        
        void initializeFireFields(TYPE & coordCells, std::unordered_set<int> availSet); // TODO: need TYPE
        
        void ros_distr(double thetafire, double forward, double flank, double back);
        
        std::vector<int> manageFire(int period, std::unordered_set<int> AvailSet, bool verbose, TYPE df, TYPE coef, TYPE spotting, TYPE spottingParams, TYPE & coordCells, TYPE Cells_Obj, TYPE args); // TODO: we can't have a generic "args" in c                                 CP: Returns a vector of integers
        
        bool get_burned(int period, int NMsg, int season, bool verbose, TYPE df, TYPE coef, double ROSThresh);

        void set_Adj(std::unordered_map<std::string, std::vector<int>> & adjacentCells);
        void setStatus(int status_int);
        std::string getStatus();
        bool ignition(int period, int season, std::vector<int> ignitionPoints, TYPE df, TYPE coef, double ROSThresh, double HFIThresh);
        //std::vector<TYPE> got_burnt_from_mem(int period, std::vector<TYPE> msgLists, int season, bool verbose);
        // void FS_definition();
        void harvested(int id, int period);
        void print_info();
        
    private:
        double allocate(double offset, double base, double ros1, double ros2);
};

#endif
