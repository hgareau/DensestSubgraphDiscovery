#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

#include "Component.h"

#ifndef COMPONENTDECOM_H
#define COMPONENTDECOM_H

class ComponentDecom {
public:
    // adjacency list of the graph
    std::vector<std::vector<int>> Graph;
    // size of the graph (number of vertices)
    int graph_size;
    // All the motifs in the graph(??? This should be Statistic, which may shed light on what it really is)
    std::unordered_map<std::string, std::vector<int>> motif_list;
    // private double core[][];

    ComponentDecom(std::vector<std::vector<int>>& Graph, int graph_size, std::unordered_map<std::string, std::vector<int>>& motif_list);
    std::queue<Component> decompose();
    void BFS(std::vector<int>& delete_values, int s, int index);
};
#endif