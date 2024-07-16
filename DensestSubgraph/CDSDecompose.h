#include <vector>
#include <unordered_map>

#ifndef CDSDECOMPOSE_H
#define CDSDECOMPOSE_H

class CDSDecompose {
public:
    std::vector<std::vector<int>> Graph;
    std::vector<std::vector<int>> Motif;
    int graph_size;
    int motif_size;
    std::vector<long long> degree;
    std::vector<std::unordered_map<int, int>> Share;
    int motif_type;
    std::unordered_map<std::string, std::vector<int>> motif_list;
    std::vector<long long> motif_degree;

    CDSDecompose(std::vector<std::vector<int>> Graph, std::vector<std::vector<int>> Motif, int graph_size, int motif_size, int motif_type);
    std::vector<std::vector<double>> Decompose();
    std::unordered_map<int, long> Generate(int index, std::vector<int>& mark, std::vector<int>& array, std::vector<int>& map_s);
};
#endif