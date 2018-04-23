#include "DFWeather.h"
#include <math.h>
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
    printf("\nscenario: %s" , this->scenario.c_str());
    printf("\ndatetime: %s " , this->datetime.c_str());
    printf("\napcp: %f" , this->apcp);
    printf("\ntmp: %f" , this->tmp);
    printf("\nrh: %f" , this->rh);
    printf("\nws: %f" , this->ws);
    printf("\nwd: %f" , this->wd);
    printf("\nffmc: %f" , this->ffmc);
    printf("\ndmc: %f" , this->dmc);
    printf("\ndc: %f" , this->dc);
    printf("\nisi: %f" , this->isi);
    printf("\nbui: %f" , this->bui);
    printf("\nfwi: %f" , this->fwi);
}

/*
int main()
{
    // Initialize one row
    DFWeather DFWeather1("CPTest", "2018-04-22 00:00", 0.0, 2.5, 94.0,
                         2.0, 360, 80.9, 58.0, 482.0, 1.4, 89.0, 6.4);
    // Print out info
    DFWeather1.printWeather();




}
*/
