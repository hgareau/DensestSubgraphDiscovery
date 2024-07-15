#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <string>

#ifndef EXACTALGO_H
#define EXACTALGO_H

class ExactAlgo {
public:
    std::unordered_map<std::string, std::vector<int>> Motif_Record;
    int motif_size;
    int graph_size;
    std::vector<int> Motif_degree;

    ExactAlgo(std::unordered_map<std::string, std::vector<int>> map, int motif_size, int graph_size, std::vector<int> Motif_degree);
    std::vector<int> Exact(double l, double u, long motif_num);
};
#endif