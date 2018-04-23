#include "DFGrid.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>


DFGrid::DFGrid(string _fueltype, double _mon, double _jd, double _m, double _jd_min, double _lat, double _lon,
               double _elev, double _ffmc, double _ws, double _waz, double _bui, double _ps, double _saz,
               double _pc, double _pdf, double _gfl, double _cur, double _time)
{
   // Populate fields
   this->fueltype = _fueltype;
   this->mon = _mon;
   this->jd = _jd;
   this->m = _m;
   this->jd_min = _jd_min;
   this->lat = _lat;
   this->lon = _lon;
   this->elev = _elev;
   this->ffmc = _ffmc;
   this->ws = _ws;
   this->waz = _waz;
   this->bui = _bui;
   this->ps = _ps;
   this->saz = _saz;
   this->pc = _pc;
   this->pdf =_pdf;
   this->gfl =_gfl;
   this->cur =_cur;
   this->time =_time;
}

// Prints-out info from the object (all fields)
void DFGrid::printInfo()
{
cout << "fueltype: " << this->fueltype << "\n";
cout << "mon: " << this->mon << "\n";
cout << "jd: " << this->jd << "\n";
cout << "m: " << this->m << "\n";
cout << "jd_min: " << this->jd_min << "\n";
cout << "lat: " << this->lat << "\n";
cout << "lon: " << this->lon << "\n";
cout << "elev: " << this->elev << "\n";
cout << "ffmc: " << this->ffmc << "\n";
cout << "ws: " << this->ws << "\n";
cout << "waz: " << this->waz << "\n";
cout << "bui: " << this->bui << "\n";
cout << "ps: " << this->ps << "\n";
cout << "saz: " << this->saz << "\n";
cout << "pc: " << this->pc << "\n";
cout << "pdf: " << this->pdf << "\n";
cout << "gfl: " << this->gfl << "\n";
cout << "cur: " << this->cur << "\n";
cout << "time: " << this->time << "\n";
}


int main()
{
    // Initialize one row
    DFGrid DFTest("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    // Print out info
    DFTest.printInfo();




}
