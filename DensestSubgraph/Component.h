#include <vector>
#include <string>
#include <unordered_map>

#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
    // Adjacency list of this component
    std::vector<std::vector<int>> Graph;

    // Size of the subgraph
    int graph_size;

    // List of the motifs in this subgraph
    std::unordered_map<std::string, std::vector<int>> motif_list;

    // The number of motifs in this subgraph
    long motif_num;

    // The density of this component
    double densest;

    // The motif degrees of the vertices in this subgraph
    std::vector<int> motif_degree;

    // Constructor
    Component(std::vector<std::vector<int>> Graph, int graph_size, 
          std::unordered_map<std::string, std::vector<int>> motif_list, long motif_num, double densest, std::vector<int> motif_degree);

    Component();
};
#endif