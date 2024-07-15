#include <DensestCore.h>
#include <vector>

#ifndef LOCATECORE_H
#define LOCATECORE_H

class LocateCore {
public:
    LocateCore(std::vector<std::vector<int>> Graph, std::vector<std::vector<double>> core, int graph_size);
    DensestCore locate();
};
#endif