#ifndef FOREST
#define FOREST

#include <string>
#include <unordered_map>
#include <vector>

class Forest {
    public:
        int id;
        int nCells;
        double area;
        double vol;
        double age;
        std::string location;
        std::vector<int> coord;	
        double perimeter;
        std::unordered_map<std::string, int> fTypes;
        // cellsDistance;
        //std::vector<int> availCells;
        //std::vector<int> burntCells;
        //std::vector<int> harvestCells;
        
        Forest(int _id, std::string _location, std::vector<int> _coord, int _nCells, double _area, double _vol, double _age, double _perimeter, std::unordered_map<std::string, int> & _fTypes);

        //std::vector<int> set_AvailCells(int period, TYPE AvailCells_set);
        //std::vector<int> set_BurntCells(int period, TYPE BurntCells_set);
        void print_info();

    private:
        int TODO;
}

#endif
