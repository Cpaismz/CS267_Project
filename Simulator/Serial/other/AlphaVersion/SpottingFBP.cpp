#include "SpottingFBP.h"

std::vector<int> SpottingFBP(std::unordered_map<int, CellsFBP> Cells_Obj, std::vector<std::vector<int>> coordCells, std::unordered_set<int> AvailSet, double WSD, double WSC, std::unordered_map<std::string, double> spottingParams, bool verbose
) {
    // TODO data structures should be passed by reference   
    // TODO
    std::unordered_map<int, std::unordered_map<int, int>> Angles = std::unordered_map<int, std::unordered_map<int, int>>();
    std::unordered_map<int, std::unordered_map<int, int>> Distances = std::unordered_map<int, std::unordered_map<int, int>>();
    std::unordered_map<int, std::unordered_map<int, double>> SpotProb = std::unordered_map<int, std::unordered_map<int, double>>();

    if (spottingParams["SPOTANGLE"] * spottingParams["SPOT0PROB"] * spottingParams["SPOT10TIME"] * WSC == 0) {
        return vector<int>();
    }

    double WTolerance = spottingParams["SPOTANGLE"] / 2.0;
    std::cout << "debug AvailSet size=" << AvailSet.size(); << std::endl;

    double WA = WSD - WTolerance;
    double WB = WSD + WTolerance;


    double WWindowA = WA;
    double WWindowB = WB;

    if (WA < 0)
        WWindowA += 360;

    if (WB > 360)
        WWindowB -= 360;

    if (verbose) {
        std::cout<< "Wind Direction:" << WSD << std::endl;
        std::cout << "Wind Speed:" << WSC << std::endl;
        std::cout << "Spotting Wind Windows: [" << WA << ", " << WB << "]" << std::endl;
    }

    // TODO: maybe true debugging
    std::cout << "debug obj keys size " << Cells_Obj.size();
    std::cout << "debug AvailSet size " << AvailSet.size();
    std::cout << "debug CoordCells size " << CoordCells.size();

    for (auto & _c1 : Cells_Obj) {
        int c1 = _c1.first;
        Angles[c1] = std::unordered_map<int, int>();
        Distances[c1] = std::unordered_map<int, int>();
        for (auto & c2 : AvailSet){
         
            if (c1 == c2) {
                // TODO: can't be None
                Angles[c1][c2] = None;
                Distances[c1][c2] = None;
            } else {
                int a = coordCells[c1][0] - coordCells[c2 - 1][0];
                int b = coordCells[c1][1] - coordCells[c2 - 1][1];

                if (a == 0) {
                    if (b >= 0) 
                        Angles[c1][c2] = 270;
                    else
                        Angles[c1][c2] = 90;
                    Distances[c1][c2] = cmath::abs(b);
                }
                if (b == 0) {
                    if (a >= 0) 
                        Angles[c1][c2] = 180;
                    else
                        Angles[c1][c2] = 0;
                    Distances[c1][c2] = cmath::abs(a);
                }
            }
            if (a != 0 && b != 0) {
                double radToDeg = 180 / cmath::M_PI;
                double angle = cmath::atan(b * 1.0 / a) * radToDeg;
                double distance = cmath::sqrt(a * a + b * b);

                if (a > 0)
                    angle += 180;
                if (a < 0 && b > 0)
                    angle += 360;
                Angles[c1][c2] = angle;
                Distances[c1][c2] = distance;
            }
        }
    }
    if (verbose) {
        std::cout<< "Angles size: " << Angles.size() << std::endl;
        std::cout<< "Distances size: " << Distances.size() << std::endl;
    }

    int anyCell = Cells_Obj.begin()->first;
    double cellsize = Cells_Obj[anyCell].Perimeter / 4.0;
    double beta = SpottingParams["SPOT0PROB"];
    double tilde_d = SpottingParams["SPOT10TIME"] * WSC / cellsize;
    double alpha = std::log(.1) / tilde_d + std::log(beta) / tilde_d;

    for (auto & _c1 : Cells_Obj) {
        int c1 = _c1.first;
        SpotProb[c1] = std::unordered_map<int, double>();
        for (auto & c2 : AvailSet) {
            // TODO: can't be None
            if (angles[c1][c2]  == None) {
                SpotProb[c1][c2] = 0;
            } else {
                SpotProb[c1][c2] = beta * std::exp(-1 * Distances[c1][c2] * alpha);
                double WA_t = WA;
                double WB_t = WB;
                // TODO the logic here is a shitshow
                if (WA_t >= 0 && WB_t >= 0 && WA_t < 360 && WTolerance < 180) {
                    if (WB_t >= 360)
                        WB_t -= 360;
                    if (!(Angles[c1][c2] <= WB_t && Angles[c1][c2] >= WA_t)) 
                        SpotProb[c1][c2] = 0;
                }

                WA_t = WA;
                WB_t = WB;
                
                if (WA_t < 0 && WB_t >= 0 && WB_t < 360 && WTolerance < 180) {
                    if (!(Angles[c1][c2] <= WB_t || Angles[c1][c2] >= WA_t + 360) {
                        SpotProb[c1][c2] = 0;
                    }
                }
            }
        }
    }

    if (verbose) {
        std::cout << "Probabilities size: " << SpotProb.size() << std::endl;
    }

    std::vector<int> ret = vector<int>();
    for (auto & _c1 : SpotProb) {
        int c1 = _c1.first;
        for (auto & _c2 : SpotProb[c1]) {
            double random = 1.0 * std::rand() / RAND_MAX; 
            if (SpotProb[c1][c2] > 0 && SpotProb[c1][c2] < random) {
                if (verbose) {
                    std::cout << "Spotting msg from " << c1 + 1 << " to " << c2; 
                }
                msg_list.push_back(c2);
            }
        }
    }
    return msg_list;
    
    
     


}


