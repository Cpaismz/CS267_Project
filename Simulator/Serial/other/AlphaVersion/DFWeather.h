#ifndef DFWEATHER
#define DFWEATHER
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DFWeather
{
    public:
        // Inmutables
        string scenario;
        string datetime;
        double apcp;
        double tmp;
        double rh;
        double ws;
        double wd;
        double ffmc;
        double dmc;
        double dc;
        double isi;
        double bui;
        double fwi;

        // Constructor and methods here
       DFWeather(string _scenario, string _datetime, double _apcp, double _tmp, double _rh, double _ws,
                 double _wd, double _ffmc, double _dmc, double _dc, double _isi, double _bui, double _fwi);

       void printWeather();

};

#endif // DFWEATHER_H
