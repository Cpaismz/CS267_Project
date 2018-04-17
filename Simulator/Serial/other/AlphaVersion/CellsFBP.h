#ifndef CELLSFBP
#define CELLSFBP

// include stuff
#include <vector>

class CellsFBP {
    // TODO: find where to put the enums
    public:
        // immutable
        int id;
        double area;
        double vol;
        std::vector<double> coord; //TODO: maybe change this into a tuple or class													   CP: 2D array/vector of doubles/floats
        int age;
        int fType;
        int terrain;
        double perimeter;
        std::vector<std::vector<TYPE>> adjacents; // TODO: what type is a a cell? TODO: adjacents is a dictionary         CP: dictionary {string: [int array]}
        std::vector<TYPE>> color; // TODO: what type is a color?                                                                                  CP: vector of strings

        // mutable
        int status;
        std::vector<int> FICell;																																       // CP: this vector will be very sparse, a dict should be better?  need to re-think its logic
        std::vector<int> FSCell;																																		// CP: this vector will be very sparse, a dict should be better? need to re-think its logic
        int hPeriod;
        int fireStarts;
        int gMsgList;																																						//  CP: vector of vectors [[],[],[],...,[]]

        // what are these TODO: check types for all fo these
        int fType2;																																						// CP: int
        int realId; 																																							// CP: int
        double _ctr2ctrdist;																																			// CP: double
        int harvestStarts;																																				// CP: int
        int fireStartsSeason;																																			// CP: int
        int tYears;																																							// CP: int
        std::vector<std::vector<<TYPE>> gMsgListSeason;																						    // CP: vector of integer vectors [[int1,int2], [intx,inty,intz]]  (can have multiple dimensions inside)
        std::vector<int> CH;																																			// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        std::vector<int> CHVar;																																	// CP:  int vector (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        TYPE value;																																						// CP: double (not currently implemented in the simulator, should be initilized by the heuristic class in the future)
        std::vector<int> productivity;																															// CP: vector of doubles (not currently implemented in the simulator, should be initilized by the heuristic class in the future)

        std::vector<TYPE> fireProgress;																															// CP: dictionary {int: double}
        std::vector<TYPE> angleDict;																																// CP: dictionary {int: double}
        std::vector<TYPE> ROSAngleDir;                           																							// CP: dictionary {int: double|None}   Instead of None we can use a determined number like -9999 = None
        std::vector<TYPE> distToCenter;   																													    // CP: dictionary {int: double}
        std::vector<TYPE> angleToNb;																															// CP: dictionary {int: double}

        bool triedToSpot;																																				// CP: boolean

        // constructor and methods here
        CellsFBP(int _ID, double _area, std::vector<double> & _coord, int _age, int _fType, int _fType2, int _terrain, double _vol, double _perimeter, int _status, std::vector<<std::vector<TYPE>> & _adjacents, std::vector<TYPE> _color, int _realId, bool outputGrid);
        
        void initializeFireFields(std::vector<std::vector<double>> & coordCells, TYPE availSet);
        
        void ros_distr(double thetafire, double forward, double flank, double back);
        
        TYPE manageFire(int period, TYPE AvailSet, bool verbose, TYPE df, TYPE coef, TYPE spotting, TYPE spottingParams, std::vector<std::vector<double>> & coordCells, TYPE Cells_Obj, TYPE args); // TODO: we can't have a generic "args" in c                                 CP: Returns a vector of integers
        
        bool get_burned(int period, TYPE NMsg, int season, bool verbose, TYPE df, TYPE coef, double ROSThresh);

        void set_Adj(std::vector<std::vector<TYPE>> adjacentCells);
        void setStatus(int status_int);
        int getStatus();
        bool ignition(int period, int season, std::vector<TYPE> ignitionPoints, TYPE df, TYPE coef, double ROSThresh, double HFIThresh);
        std::vector<TYPE> got_burnt_from_mem(int period, std::vector<TYPE> msgLists, int season, bool verbose);
        void FS_definition();
        void harvested(int id, int period);
        void print_info();
        
    private:
        int TODO; // TODO: move stuff here
        double allocate(double offset, double base, TYPE ros1, TYPE ros2);
};

#endif
