#include "Forest.h"

Forest::Forest(int _id, std::string _location, std::vector<double> _coord, int _nCells, double _area, double _col, int _age, double _perimeter, std::unordered_map<std::string, int> & _fTypes) {
    this.id = _id;
    this.location = _location;
    this.coord = _coord;
    this.nCells = _nCells;
    this.area = _area;
    this.vol = _vol;
    this.age = _age;
    this.fTypes = _fTypes;
    
    this.cellsDistance = ; // TODO TYPE
    this.availCells = std::vector<int>();
    for (int i = 0; i <= this.nCells; i++) {
        this.availCells.push_back(i);
    }
    this.burntCells = std::vector<int>();

}

std::vector<int> Forest::set_AvailCells(int period, TYPE AvailCells_set) {

}

std::vector<int> Forest::set_BurntCells(int period, TYPE BurntCells_set) {

}

void print_info() {

}
