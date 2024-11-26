#include <queue>
#include "MDS.h"
#include "Component.h"
#include "DensestCore.h"

using namespace std;

#ifndef DYNAMICEXACT_H
#define DYNAMICEXACT_H

class DynamicExactAlgo {
public:
    queue<Component> compQueue;
    DensestCore Core;
    int motif_size;

    DynamicExactAlgo(queue<Component> queue, DensestCore Core, int motif_size);
    MDS DynamicExact();
};
#endif