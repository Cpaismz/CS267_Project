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
        int fType;
		int realId;
		double _ctr2ctrdist;							
		double area;
        double age;
        double vol;
		double perimeter;
		
        std::string ftype2;
        std::vector<int> coord; //maybe change this into a tuple or class	CP: 2-tuple (int)
		std::unordered_map<std::string, std::vector<int>> adjacents; // CP: dictionary {string: [int array]}
        std::vector<double> color; // 4-tuple
		
        
		// mutable
        int status;
        int hPeriod;
        int fireStarts;
        int harvestStarts;
        int fireStartsSeason;
        int burntP;
        int tYears;	
		
        std::unordered_map<int, std::vector<int>> gMsgList; // {40 -> [1, 2, 3] }
		std::unordered_map<int, std::vector<int>> gMsgListSeason;
        std::unordered_map<int, double> fireProgress;	// CP: dictionary {int: double}
        std::unordered_map<int, double> angleDict;				// CP: dictionary {int: double}
        std::unordered_map<int, double> ROSAngleDir;       // CP: dictionary {int: double|None}   Instead of None we can use a determined number like -9999 = None  TODO: maybe int : double
        std::unordered_map<int, double> distToCenter;   	// CP: dictionary {int: double}
        std::unordered_map<int, int> angleToNb;			// CP: dictionary {double: int}
        bool triedToSpot;

        // TODO: reference to shared object

        // constructor and methods here
        CellsFBP(int _id, double _area, std::vector<int> coord, double _age, 
					 int _fType, std::string _fType2, double _vol, double _perimeter, 
					 int _status, std::unodreded_map<std::string, std::vector<int>> & _adjacents, 
					 std::vector<double> _color, int _realId, bool outputGrid);
        
        void initializeFireFields(std::vector<std::vector<int>> & coordCells, std::unordered_set<int> & availSet); // TODO: need TYPE
        
        void ros_distr(double thetafire, double forward, double flank, double back);
			
		// TODO: we can't have a generic "args" in c                
        std::vector<int> manageFire(int period, std::unordered_set<int> AvailSet, 
																  bool verbose, vector<inputs> & df, struct fuel_coeffs * coef, 
																  bool spotting, std::unordered_map<std::string, double> spottingParams, 
																  std::vector<std::vector<int>> & coordCells, std::unordered_map<int, CellsFBP> Cells_Obj, 
																  std::vector<std::string> args); 
        
        bool get_burned(int period, int NMsg, int season, bool verbose, vector<inputs> & df, 
								struct fuel_coeffs * coef, double ROSThresh);

        void set_Adj(std::unordered_map<std::string, std::vector<int>> & adjacentCells);

        void setStatus(int status_int);
        
		std::string getStatus();

        bool ignition(int period, int season, int year, std::vector<int> ignitionPoints, vector<inputs> & df, 
						  struct fuel_coeffs * coef, double ROSThresh, double HFIThresh);

        void harvested(int id, int period);

        void print_info();
        
    private:
        double allocate(double offset, double base, double ros1, double ros2);
};

#endif
