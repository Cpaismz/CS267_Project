#ifndef FOREST
#define FOREST

#include <string>
#include <vector>

class Forest {
    public:
        int id;
        int nCells;
        double area;
        double vol;
        int age;
        std::string location;
        std::vector<double> coord;
        double perimeter;
        std::vector<TYPE> fTypes; // TODO i will decide the data structure later, just need the typing
        std::vector<TYPE> cellsDistance;
        std::vector<int> availCells;
        std::vector<int> burntCells;
        std::vector<int> harvestCells;
        
        Forest(int _id, std::string _location, std::vector<double> _coord, int _nCells, double _area, double _col, int _age, double _perimeter, std::vector<TYPE> fTypes);

        std::vector<int> set_AvailCells(int period, TYPE AvailCells_set);
        std::vector<int> set_BurntCells(int period, TYPE BurntCells_set);
        void print_info();

    private:
        int TODO;
}

#endif
