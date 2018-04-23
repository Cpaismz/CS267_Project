#include "DFGrid.h"
#include "DFWeather.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	/* Initializing a cell (manually, instance 9x9 flat and homogeneous, no data besides fueltype)*/
    DFGrid Cell1("c1", 100.0, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
	DFGrid Cell2("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell3("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell4("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell5("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell6("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell7("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell8("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);
    DFGrid Cell9("c1", NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                  NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN);


	/* Vector of DF objects */
    std::vector<DFGrid> DFVectorGrid;
    DFVectorGrid.push_back(Cell1);    // Add Row object to vector
	DFVectorGrid.push_back(Cell2);    // Add Row object to vector
	DFVectorGrid.push_back(Cell3);    // Add Row object to vector
	DFVectorGrid.push_back(Cell4);    // Add Row object to vector
	DFVectorGrid.push_back(Cell5);    // Add Row object to vector
	DFVectorGrid.push_back(Cell6);    // Add Row object to vector
	DFVectorGrid.push_back(Cell7);    // Add Row object to vector
	DFVectorGrid.push_back(Cell8);    // Add Row object to vector
	DFVectorGrid.push_back(Cell9);    // Add Row object to vector
    
    DFVectorGrid[0].printInfo();    // Check access
    
	/*  Test printing loop   */
	int i;
	printf("\n\nCells Type loop");
	for (i=0; i<9; i++){
		printf("\nDFRows vector object %d fueltype: %s", i+1, DFVectorGrid[i].fueltype.c_str());
	}
	
	printf("\nFull info loop\n");
	for (i=0; i<9; i++){
		printf("\n\nCell %d", i+1);
		DFVectorGrid[i].printInfo();
	}
	
	
	/*  Weather DF (manually filled, 7 period weather)  */ 
	DFWeather WR1("CP", "2017-07-24 12:00", 0.0, 23.5, 55, 0.0, 0.0, 89.6, 54.9, 247.5, 5.2, 70.6, 16.5);
	DFWeather WR2("CP", "2017-07-24 13:00", 0.0, 22.5, 70, 0.0, 0.0, 86.4, 56.6, 255.3, 4.6, 72.8, 15.4);
	DFWeather WR3("CP", "2017-07-24 14:00", 0.0, 22.9, 50, 11.5, 347, 87.6, 59.4, 263.1, 5.4, 75.9, 17.8);
	DFWeather WR4("CP", "2017-07-24 15:00", 0.0, 24.9, 42, 4.1, 300, 89.2, 62.9, 271.3, 4.7, 79.7, 16.4);
	DFWeather WR5("CP", "2017-07-24 16:00", 0.0, 29.5, 34, 4.7, 200, 91.6, 67.7, 280.3, 6.8, 84.4, 22.1);
	DFWeather WR6("CP", "2017-07-24 17:00", 0.0, 28.9, 38, 10.3, 263, 91.6, 72, 289.2, 9.1, 88.8, 27.8);
	DFWeather WR7("CP", "2017-07-24 18:00", 0.0, 29.2, 27, 4.5, 350, 93.1, 77.2,298.1, 8.4, 93.8, 27);
	DFWeather WR8("CP", "2017-07-24 19:00", 20.8, 18.3, 88, 10.0, 247, 33.5, 34.7, 243.8, 0.0, 51.2, 0.0);
	
	/* Vector of DF Weather objects */
    std::vector<DFWeather> DFVectorWeather;
    DFVectorWeather.push_back(WR1);    // Add Row object to vector
	DFVectorWeather.push_back(WR2);    // Add Row object to vector
	DFVectorWeather.push_back(WR3);    // Add Row object to vector
	DFVectorWeather.push_back(WR4);    // Add Row object to vector
	DFVectorWeather.push_back(WR5);    // Add Row object to vector
	DFVectorWeather.push_back(WR6);    // Add Row object to vector
	DFVectorWeather.push_back(WR7);    // Add Row object to vector
	DFVectorWeather.push_back(WR8);    // Add Row object to vector
	
	/*  Printing Loop  */
	printf("\nFull Weather info loop\n");
	for (i=0; i<8; i++){
		printf("\n\nPeriod %d", i+1);
		DFVectorWeather[i].printWeather();
	}
	printf("\n");
	
	//std::cout << "Check: " << DFVectorTest[0].fueltype << "\n";
}


