#include "DFWeather.h"
#include <stdio.h>
#include <string>
#include <vector>

DFWeather::DFWeather(string _scenario, string _datetime, double _apcp, double _tmp, double _rh, double _ws, double _wd,
                     double _ffmc, double _dmc, double _dc, double _isi, double _bui, double _fwi)
{
   // Populate fields
   this->scenario = _scenario;
   this->datetime = _datetime;
   this->apcp = _apcp;
   this->tmp = _tmp;
   this->rh = _rh;
   this->ws = _ws;
   this->wd = _wd;
   this->ffmc = _ffmc;
   this->dmc = _dmc;
   this->dc = _dc;
   this->isi = _isi;
   this->bui = _bui;
   this->fwi = _fwi;
}

// Prints-out info from the object (all fields)
void DFWeather::printWeather()
{
    cout << "scenario: " << this->scenario << "\n";
    cout << "datetime: " << this->datetime<< "\n";
    cout << "apcp: " << this->apcp << "\n";
    cout << "tmp: " << this->tmp << "\n";
    cout << "rh: " << this->rh<< "\n";
    cout << "ws: " << this->ws<< "\n";
    cout << "wd: " << this->wd<< "\n";
    cout << "ffmc: " << this->ffmc<< "\n";
    cout << "dmc: " << this->dmc << "\n";
    cout << "dc: " << this->dc << "\n";
    cout << "isi: " << this->isi << "\n";
    cout << "bui: " << this->bui << "\n";
    cout << "fwi: " << this->fwi << "\n";
}


int main()
{
    // Initialize one row
    DFWeather DFWeather1("CPTest", "2018-04-22 00:00", 0.0, 2.5, 94.0,
                         2.0, 360, 80.9, 58.0, 482.0, 1.4, 89.0, 6.4);
    // Print out info
    DFWeather1.printWeather();




}

