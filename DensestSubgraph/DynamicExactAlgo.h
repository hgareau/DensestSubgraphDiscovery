#include <queue>
#include "MDS.h"
#include "Component.h"
#include "DensestCore.h"

#ifndef DYNAMICEXACT_H
#define DYNAMICEXACT_H

class DynamicExactAlgo {
public:
    std::queue<Component> queue;
    DensestCore Core;
    int motif_size;

    DynamicExactAlgo(std::queue<Component> queue, DensestCore Core, int motif_size);
    MDS DynamicExact();
};
#endif