#include <vector>

using namespace std;

#ifndef MDS_H
#define MDS_H

class MDS {
public:
    vector<int> s_t_result;
    long motif_num;
    int vertex_num;
    double densest;
    Component core;
    
    MDS(vector<int> s_t_result, long motif_num, int vertex_num, double densest);
};
#endif