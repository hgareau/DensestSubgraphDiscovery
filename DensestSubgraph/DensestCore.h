#include <vector>

#ifndef DENSESTCORE_H
#define DENSESTCORE_H

class DensestCore {
public:
    std::vector<std::vector<int>> Graph;
    int graph_size;
    int kcore;
    int delete_vertex;
    int delete_motif;
    double densest;
    int kmax;

    DensestCore(std::vector<std::vector<int>> Graph, int graph_size, int kcore,
                int delete_vertex, int delete_motif, double densest, int kmax);
    DensestCore();
};
#endif