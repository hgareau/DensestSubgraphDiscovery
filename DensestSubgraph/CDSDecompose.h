#include <vector>
#include <unordered_map>

using namespace std;

#ifndef CDSDECOMPOSE_H
#define CDSDECOMPOSE_H

class CDSDecompose {
public:
    vector<vector<int>> Graph;
    vector<vector<int>> Motif;
    int graph_size;
    int motif_size;
    vector<long long> degree;
    vector<unordered_map<int, int>> Share;
    int motif_type;
    unordered_map<string, vector<int>> motif_list;
    vector<long> motif_degree;

    CDSDecompose(vector<vector<int>>& Graph, vector<vector<int>>& Motif, int graph_size, int motif_size, int motif_type,
        unordered_map<string, vector<int>>& motif_list, vector<long> motif_degree);
    vector<vector<double>> Decompose();
    unordered_map<int, long> Generate(int index, vector<int>& mark, vector<int>& array, vector<int>& map_s);
};
#endif