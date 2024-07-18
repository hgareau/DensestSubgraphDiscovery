#include <vector>
#include "DensestCore.h"

DensestCore::DensestCore(std::vector<std::vector<int>> Graph, int graph_size, int kcore, int delete_vertex, int delete_motif, double densest, int kmax)
{
    this->Graph = Graph;
    this->graph_size = graph_size;
    this->kcore = kcore;
    this->delete_motif = delete_motif;
    this->delete_vertex = delete_vertex;
    this->densest = densest;
    this->kmax = kmax;
}

DensestCore::DensestCore()
{
}