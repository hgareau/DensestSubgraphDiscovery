#include <vector>
#include <unordered_map>
#include <string>
#include "Component.h"

// Constructor
Component::Component(std::vector<std::vector<int>> Graph, int graph_size, std::unordered_map<std::string, std::vector<int>> motif_list, long motif_num, double densest, std::vector<int> motif_degree)
{
    this->Graph = Graph;
    this->graph_size = graph_size;
    this->motif_list = motif_list;
    this->motif_num = motif_num;
    this->densest = densest;
    this->motif_degree = motif_degree;
}

Component::Component()
{
}
