#include <vector>
#include <unordered_map>

#ifndef FINDMINCUT_H
#define FINDMINCUT_H

class FindMinCut {
public:
    FindMinCut(std::vector<std::unordered_map<int, std::vector<double>>> FlowNetwork, int s, int t);
    double EdmondsKarp();
    double augmentPath(std::vector<int>& parent);
    std::vector<int> getparent();
};
#endif