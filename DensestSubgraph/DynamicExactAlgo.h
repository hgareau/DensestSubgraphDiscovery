#include <queue>
#include <MDS.h>
#include <Component.h>
#include <DensestCore.h>

#ifndef DYNAMICEXACT_H
#define DYNAMICEXACT_H

class DynamicExact {
public:
    DynamicExactalgo(std::queue<Component*> queue, DensestCore* Core, int motif_size)
        : queue(queue), Core(Core), motif_size(motif_size) {};
    MDS DynamicExact();
};
#endif