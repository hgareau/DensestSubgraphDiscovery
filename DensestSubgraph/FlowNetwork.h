#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

#ifndef FLOWNETWORK_H
#define FLOWNETWORK_H

class FlowNetwork {
public:
    unordered_map<string, vector<int>> Motif_Record;
    int motif_size;
    int graph_size;
    vector<unordered_map<int, vector<double>>> FlowNetwork1;
    vector<int> Motif_degree;
    
    FlowNetwork(unordered_map<string, vector<int>> map, int motif_size, int graph_size, vector<int> Motif_degree);
    vector<unordered_map<int, vector<double>>> Construct(double alph);
    vector<unordered_map<int, vector<double>>> Update(double alph);
};
#endif