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
printf("\nfueltype: %s ", this->fueltype.c_str());
printf("\nmon: %f",this->mon);
printf("\njd: %f", this->jd);
printf("\nm: %f", this->m);
printf("\njd_min: %f", this->jd_min);
printf("\nlat: %f", this->lat);
printf("\nlon: %f", this->lon);
printf("\nelev: %f", this->elev);
printf("\nffmc: %f", this->ffmc);
printf("\nws: %f", this->ws);
printf("\nwaz: %f", this->waz);
printf("\nbui: %f", this->bui);
printf("\nps: %f", this->ps);
printf("\nsaz: %f", this->saz);
printf("\npc: %f", this->pc);
printf("\npdf: %f", this->pdf);
printf("\ngfl: %f", this->gfl);
printf("\ncur: %f", this->cur);
printf("\ntime: %f", this->time);
}

/*
int main()
{
    // Initialize one row
    DFGrid DFTest("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    // Print out info
    DFTest.printInfo();




}*/
