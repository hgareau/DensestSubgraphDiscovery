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
    Component(const std::vector<std::vector<int>>& Graph, int graph_size,
              const std::unordered_map<std::string, std::vector<int>>& motif_list, long motif_num, double densest, const std::vector<int>& motif_degree)
        : Graph(Graph), graph_size(graph_size), motif_list(motif_list), motif_num(motif_num), densest(densest), motif_degree(motif_degree) {};

    Component() = default;
};
#endif