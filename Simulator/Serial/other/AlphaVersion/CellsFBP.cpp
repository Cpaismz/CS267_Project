#include "CellsFBP.h"

#include <cmath>
#include <iostream>



CellsFBP::CellsFBP(int _id, double _area, std::vector<std::vector<double>> & _coord, double _age, std::string _fType, int _fType2, double _vol, double _perimeter, int _status, std::unodreded_map<std::string, std::vector<int>> & _adjacents, std::vector<double> _color, int _realId, bool outputGrid); // TODO: check type of age, fType, coord, color {
    this.id = _id;
    this.area = _area;
    this.coord = _coord;
    this.age = _age;
    this.fType = _fType;
    this.fType2 = _fType2;
    this.vol = _vol;
    this.perimeter = _perimeter;
    this.status = _status;
    this.adjacents = _adjacents;
    this.color = _color;
    this.realId = _realId;
    this._ctr2ctrdist = std::cmath.sqrt(this.area);

    if (std::cmath.abs(4 * self._ctr2ctrdist - self.perimeter) > 0.01 * self.perimeter) {
        std::cerr << "Cell ID=" << self.ID << "Area=" <<  self.Area <<  "Perimeter=" <<  self.Perimeter << std::endl;
        // maybe raise runtime error
    }
    this.gMsgList = std::unordered_map<int, std::vector<int>>();
    this.FSCell = std::unordered_map<int, std::vector<double>>();
    this.FICell = std::unordered_map<int, int>();
    this.hPeriod = 0;

    this.fireStarts = 0;
    this.harvestStarts = 0;
    this.fireStartsSeason = 0;
    this.tYears = 4;
    this.gMsgListSeason = std::vector<std::vector<int>>();
    
    this.fireProgress = std::unordered_map<int, double>();
    this.angleDict = std::unordered_map<int, double>();
    this.ROSAngleDir = std::unordered_map<int, double>();
    this.distToCenter = std::unordered_map<int, double>();
    this.angleToNb = std::unordered_map<int, double>();
    this.triedToSpot = false;
}
        
void CellsFBP::initializeFireFields(std::vector<std::vector<int>> & coordCells, std::unordered_set<int> availSet) { // TODO: should probably make a coordinate type

}
        
void CellsFBP::ros_distr(double thetafire, double forward, double flank, double back) {

}
        
std::vector<int> CellsFBP::manageFire(int period, std::unordered_set<int> AvailSet, bool verbose, TYPE df, struct fuel_coeffs * coef, bool spotting, std::unordered_map<std::string, double> spottingParams, std::vector<int> & coordCells, std::unordered_map<int, CellsFBP> Cells_Obj, std::vector<std::string> args) {

}
    
bool CellsFBP::get_burned(int period, int NMsg, int season, bool verbose, TYPE df, struct fuel_coeffs * coef, double ROSThresh) {

}

void CellsFBP::set_Adj(std::unordered_map<std::string, std::vector<int>> & adjacentCells) {

}
void CellsFBP::setStatus(int status_int) {

}
std::string CellsFBP::getStatus() {

}

bool CellsFBP::ignition(int period, int season, std::vector<int> ignitionPoints, TYPE df, struct fuel_coeffs * coef, double ROSThresh, double HFIThresh) {

}
void CellsFBP::harvested(int id, int period) {

}
void CellsFBP::print_info() {

}

double CellsFBP::allocate(double offset, double base, double ros1, double ros2) {

}
