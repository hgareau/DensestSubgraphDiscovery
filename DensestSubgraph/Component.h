#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
    // Adjacency list of this component
    vector<vector<int>> Graph;

    // Size of the subgraph
    int graph_size;

    // List of the motifs in this subgraph
    unordered_map<string, vector<int>> motif_list;

    // The number of motifs in this subgraph
    long motif_num;

    // The density of this component
    double densest;

    // The motif degrees of the vertices in this subgraph
    vector<int> motif_degree;

    // Constructor
    Component(vector<vector<int>> Graph, int graph_size, 
          unordered_map<string, vector<int>> motif_list, long motif_num, double densest, vector<int> motif_degree);

    Component();
};
#endif