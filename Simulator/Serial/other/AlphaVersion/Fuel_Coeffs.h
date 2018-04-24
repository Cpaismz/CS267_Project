#ifndef FUEL_COEFFS
#define FUEL_COEFFS
 

struct fuel_coeffs {
    char fueltype[4];
    double q;
    double bui0;
    double cbh;
    double cfl;
    double a;
    double b;
    double c;
}
#endif 

// Not using it, calling the structure from FBP5.0.h (directly)