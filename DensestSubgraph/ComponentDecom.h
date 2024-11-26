#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

#include "Component.h"

#ifndef COMPONENTDECOM_H
#define COMPONENTDECOM_H

class ComponentDecom {
public:
    // adjacency list of the graph
    vector<vector<int>> Graph;
    // size of the graph (number of vertices)
    int graph_size;
    // All the motifs in the graph(??? This should be Statistic, which may shed light on what it really is)
    unordered_map<string, vector<int>> motif_list;
    // private double core[][];

    ComponentDecom(vector<vector<int>>& Graph, int graph_size, unordered_map<string, vector<int>>& motif_list);
    queue<Component> decompose();
    void BFS(vector<int>& delete_values, int s, int index);
};
#endif