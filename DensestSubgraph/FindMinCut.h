#include <vector>
#include <unordered_map>

#ifndef FINDMINCUT_H
#define FINDMINCUT_H

class FindMinCut {
public:
    // data structure used to record flow network
    std::vector<std::unordered_map<int, std::vector<double>>> FlowNetwork;
    
    // array used to save path
    std::vector<int> parent;
    
    // source vertex
    int s = 0;
    
    // sink vertex
    int t = 0;

    FindMinCut(std::vector<std::unordered_map<int, std::vector<double>>> FlowNetwork, int s, int t);
    double EdmondsKarp();
    double augmentPath(std::vector<int>& parent);
    std::vector<int> getparent();
};
#endif