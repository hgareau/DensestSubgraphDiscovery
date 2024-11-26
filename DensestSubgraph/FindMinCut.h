#include <vector>
#include <unordered_map>

using namespace std;

#ifndef FINDMINCUT_H
#define FINDMINCUT_H

class FindMinCut {
public:
    // data structure used to record flow network
    vector<unordered_map<int, vector<double>>> FlowNetwork;
    
    // array used to save path
    vector<int> parent;
    
    // source vertex
    int s = 0;
    
    // sink vertex
    int t = 0;

    FindMinCut(vector<unordered_map<int, vector<double>>> FlowNetwork, int s, int t);
    double EdmondsKarp();
    double augmentPath();
    vector<int> getparent();
};
#endif