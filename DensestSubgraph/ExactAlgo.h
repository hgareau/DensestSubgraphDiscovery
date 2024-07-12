#include <vector>
#include <map>
#include <string>

#ifndef EXACTALGO_H
#define EXACTALGO_H

class ExactAlgo {
public:
    Exactalgo(std::map<std::string, std::vector<int>>& map, int motif_size, int graph_size, std::vector<int>& Motif_degree)
        : Motif_Record(map), motif_size(motif_size), graph_size(graph_size), Motif_degree(Motif_degree) {};
    std::vector<int> Exact(double l, double u, long motif_num);
    std::vector<int> Exact(double l, double u, long motif_num, long n2);
    bool Try(double l, long motif_num);
};
#endif