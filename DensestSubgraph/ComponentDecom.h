#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <Component.h>

#ifndef COMPONENTDECOM_H
#define COMPONENTDECOM_H

class ComponentDecom {
public:
    ComponentDecom(std::vector<std::vector<int>>& Graph, int graph_size, std::unordered_map<std::string, std::vector<int>>& motif_list);
    std::queue<Component> decompose(const std::vector<std::vector<int>>& graph, int graph_size, const std::unordered_map<std::string, std::vector<int>>& motif_list);
    void BFS(std::vector<int>& delete_values, int s, int index);
};
#endif