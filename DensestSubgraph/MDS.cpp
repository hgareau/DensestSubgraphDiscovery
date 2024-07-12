#include <vector>
#include <Component.h>
#include "MDS.h"

class MDS {
public:
    std::vector<int> s_t_result;
    long motif_num;
    int vertex_num;
    double densest;
    Component core;

    MDS(std::vector<int> s_t_result, long motif_num, int vertex_num, double densest) {
        this->s_t_result = s_t_result;
        this->motif_num = motif_num;
        this->vertex_num = vertex_num;
        this->densest = densest;
    }
};