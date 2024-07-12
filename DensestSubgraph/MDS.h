#include <vector>

#ifndef MDS_H
#define MDS_H

class MDS {
public:
    std::vector<int> s_t_result;
    long motif_num;
    int vertex_num;
    double densest;
    Component core;
    
    MDS(std::vector<int> s_t_result, long motif_num, int vertex_num, double densest);
};
#endif