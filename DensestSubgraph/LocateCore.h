#include <DensestCore.h>

#ifndef LOCATECORE_H
#define LOCATECORE_H

class LocateCore {
public:
    LocateCore(int** Graph, double** core, int graph_size);
    DensestCore locate(double** core, int** Graph, int graph_size);
};
#endif