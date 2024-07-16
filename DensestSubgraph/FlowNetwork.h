#include <vector>
#include <unordered_map>
#include <string>

#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H

class FlowNetwork {
public:
    std::unordered_map<std::string, std::vector<int>> Motif_Record;
    int motif_size;
    int graph_size;
    std::vector<std::unordered_map<int, std::vector<double>>> FlowNetwork1;
    std::vector<int> Motif_degree;
    
    FlowNetwork(std::unordered_map<std::string, std::vector<int>> map, int motif_size, int graph_size, std::vector<int> Motif_degree);
    std::unordered_map<int, std::vector<double>>* Construct(double alph);
    std::vector<std::unordered_map<int, double[]>> Update(double alph);
};
#endif