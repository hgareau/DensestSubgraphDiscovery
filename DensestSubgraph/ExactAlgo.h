#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <string>

using namespace std;

#ifndef EXACTALGO_H
#define EXACTALGO_H

class ExactAlgo {
public:
    unordered_map<string, vector<int>> Motif_Record;
    int motif_size;
    int graph_size;
    vector<int> Motif_degree;

    ExactAlgo(std::unordered_map<string, vector<int>> map, int motif_size, int graph_size, vector<int> Motif_degree);
    vector<int> Exact(double l, double u, long motif_num);
};
#endif