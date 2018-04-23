#ifndef SPOTTINGFBP
#define SPOTTINGFBP

#include "CellsFBP.h" 
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<int> SpottingFBP(std::unordered_map<int, CellsFBP> Cells_Obj, std::vector<std::vector<int>> coordCells, std::unordered_set<int> AvailSet, double WSD, double WSC, std::unordered_map<std::string, double> spottingParams, bool verbose
);

#endif
