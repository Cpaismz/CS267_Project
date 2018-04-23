#ifndef DFGRID
#define DFGRID
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DFGrid
{
    public:
       // Inmutable
       string fueltype;
       double mon;
       double jd;
       double m;
       double jd_min;
       double lat;
       double lon;
       double elev;
       double ps;
       double saz;
       double pc;
       double pdf;
       double gfl;
       double cur;
       double time;

       // Mutable
       double ffmc;
       double ws;
       double waz;
       double bui;

       // Constructor and methods here
       DFGrid(string _fueltype, double _mon, double _jd, double _m, double _jd_min, double _lat, double _lon,
              double _elev, double _ffmc, double _ws, double _waz, double _bui, double _ps, double _saz,
              double _pc, double _pdf, double _gfl, double _cur, double _time);

       void printInfo();
};

#endif // DFGRID_H
