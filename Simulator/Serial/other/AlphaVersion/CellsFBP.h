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
        std::vector<double> coord; //TODO: maybe change this into a tuple or class
        int age;
        int fType;
        int terrain;
        double perimeter;
        std::vector<std::vector<TYPE>> adjacents; // TODO: what type is a a cell? TODO: adjacents is a dictionary
        std::vector<TYPE>> color; // TODO: what type is a color?

        // mutable
        int status;
        std::vector<int> FICell;
        std::vector<int> FSCell;
        int hPeriod;
        int fireStarts;
        int gMsgList;

        // what are these TODO: check types for all fo these
        int fType2;
        int realId;
        double _ctr2ctrdist;
        int harvestStarts;
        int fireStartsSeason;
        int tYears;
        std::vector<std::vector<<TYPE>> gMsgListSeason;
        std::vector<int> CH;
        std::vector<int> CHVar;
        TYPE value;
        std::vector<int> productivity;

        std::vector<TYPE> fireProgress;
        std::vector<TYPE> angleDict;
        std::vector<TYPE> ROSAngleDir;
        std::vector<TYPE> distToCenter;
        std::vector<TYPE> angleToNb;

        bool triedToSpot;

        // constructor and methods here
        CellsFBP(int _ID, double _area, std::vector<double> & _coord, int _age, int _fType, int _fType2, int _terrain, double _vol, double _perimeter, int _status, std::vector<<std::vector<TYPE>> & _adjacents, std::vector<TYPE> _color, int _realId, bool outputGrid);
        
        void initializeFireFields(std::vector<std::vector<double>> & coordCells, TYPE availSet);
        
        void ros_distr(double thetafire, double forward, double flank, double back);
        
        TYPE manageFire(int period, TYPE AvailSet, bool verbose, TYPE df, TYPE coef, TYPE spotting, TYPE spottingParams, std::vector<std::vector<double>> & coordCells, TYPE Cells_Obj, TYPE args); // TODO: we can't have a generic "args" in c
        
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
