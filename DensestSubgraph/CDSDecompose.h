#include <vector>
#include <unordered_map>

#ifndef CDSDECOMPOSE_H
#define CDSDECOMPOSE_H

class CDSDecompose {
public:
    CDSdecompose(std::vector<std::vector<int>> Graph, std::vector<std::vector<int>> Motif, int graph_size, int motif_size, int motif_type, std::unordered_map<std::string, std::vector<int>> motif_list, std::vector<long long> motif_degree);
    std::vector<std::vector<double>> Decompose(std::vector<std::vector<int>>& Graph, int graph_size, int motif_size);
    std::unordered_map<int, long> Generate(int index, std::vector<int>& mark, std::vector<int>& array, std::vector<int>& map_s);
};
#endif