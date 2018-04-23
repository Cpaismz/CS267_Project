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
    this._ctr2ctrdist = cmath::sqrt(this.area);

    if (cmath::abs(4 * self._ctr2ctrdist - self.perimeter) > 0.01 * self.perimeter) {
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
        
void CellsFBP::initializeFireFields(std::vector<std::vector<int>> & coordCells, std::unordered_set<int> & availSet) { // TODO: should probably make a coordinate type
    for (auto & nb : this.adjacents) {
        // TODO: default adjacent value CANNOT be None:
        if (nb.second != None) {
            int a = -1 * coordCells[nb.second[0] - 1][0] + coordCells[this.id - 1][0];
            int b = -1 * coordCells[nb.second[0] - 1][1] + coordCells[this.id - 1][1];
            
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
                double radToDeg = 180 / cmath::M_PI;
                // TODO: i think all the negatives and abs cancel out
                double temp = cmath::atan(b * 1.0 / a) * radToDeg;
                if (a > 0)
                    temp += 180;
                if (a < 0 && b > 0) 
                    temp += 360;
                angle = temp;
            }

            this.angleDict[nb.second[0]] = angle;
            if (availSet.find(nb.second[0] != availSet.end()) {
                // TODO: cannot be None
                this.ROSAngleDir[angle] = None;
            }
            this.angleToNb[angle] = nb.second[0];
            this.fireProgress[nb.second[0]] = 0.0;
            this.distToCenter[nb.second[0]] = cmath::sqrt(a * a + b * b) * this._ctr2ctrdist;
        }
    }
}
        
void CellsFBP::ros_distr(double thetafire, double forward, double flank, double back) {
    for (auto & angle : this.ROSAngleDir) {
        double offset = cmath::abs(angle.first - thetafire);
        
        double first;
        double second;
        double base = ((int)(offset)) / 90 * 90
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
        this.ROSAngleDir[angle.first] = this.allocate(offset, base, first, second);
    }
}
        
std::vector<int> CellsFBP::manageFire(int period, std::unordered_set<int> AvailSet, bool verbose, TYPE df, struct fuel_coeffs * coef, bool spotting, std::unordered_map<std::string, double> spottingParams, std::vector<std::vector<int>> & coordCells, std::unordered_map<int, CellsFBP> Cells_Obj, std::vector<std::string> args) {
    std::string repeat = "False";
    // TODO: type
    TYPE msg_list_aux = new TYPE();
    TYPE msg_list = new TYPE();

    if (spotting && !this.triedToSpot) {
        this.triedToSpot = true;

        if (verbose) {
            std::cout << "SPOTANGLE:" << SpottingParams["SPOTANGLE"] << std::endl;
            std::cout << "SPOT0PROB:" << SpottingParams["SPOT0PROB"] << std::endl;
            std::cout << "SPOT10TIME:" << SpottingParams["SPOT10TIME"] << std::endl;
        }

    }
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
    double d = (offset - base) / 90;
    return (1 - d) * ros1 + d * ros2;
}
