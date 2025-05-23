#include <vector>

using namespace std;

#ifndef DENSESTCORE_H
#define DENSESTCORE_H

class DensestCore {
public:
    vector<vector<int>> Graph;
    int graph_size;
    int kcore;
    int delete_vertex;
    int delete_motif;
    double densest;
    int kmax;

    DensestCore(vector<vector<int>> Graph, int graph_size, int kcore,
                int delete_vertex, int delete_motif, double densest, int kmax);
    DensestCore();
};
#endif