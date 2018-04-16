#ifndef WEATHER
#define WEATHER

#include <string>

class Weather {
    public:
        Weather(string wdf_path);
        void set_columns(TYPE df, TYPE Row);
        void set_columns(TYPE df, TYPE datetime); // TODO: hopefully datetime has a different type than Row :P

        TYPE update_Weather_FBP(TYPE df, string weatherOpt);
        void print_info();
    private:
        int TODO;

};

#endif
