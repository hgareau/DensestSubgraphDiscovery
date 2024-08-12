#include "DensestCore.h"
#include <vector>

#ifndef LOCATECORE_H
#define LOCATECORE_H

class LocateCore {
public:
    // Adjacency list to represent the graph
    std::vector<std::vector<int>> Graph;
    // int** Motif = nullptr;
    // This is an array of arrays for every vertex (not necessarily
    // in order of vertex 0 to vertex 1 to vertex 2 etc. however)
    // Each vertex's array has various pieces of information
    std::vector<std::vector<double>> core;
    // number of vertices in the graph
    int graph_size;
    
    LocateCore(std::vector<std::vector<int>> Graph, std::vector<std::vector<double>> core, int graph_size);
    DensestCore locate();
};
#endif