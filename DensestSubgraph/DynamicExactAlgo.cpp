#include <iostream>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <iterator>
#include "Component.h"
#include "DensestCore.h"
#include "MDS.h"
#include "ExactAlgo.h"
#include "DynamicExactAlgo.h"

using namespace std;

DynamicExactAlgo::DynamicExactAlgo(queue<Component> queue, DensestCore Core, int motif_size)
{
    this->compQueue = queue;
    this->Core = Core;
    this->motif_size = motif_size;
}

MDS DynamicExactAlgo::DynamicExact()
{
    Component C, index;
    index = compQueue.front();
    double low_bound = 0;

    queue<Component> queueCopy = compQueue;

    while (!queueCopy.empty()) {
        C = queueCopy.front();
        queueCopy.pop();
        if (low_bound < C.densest) {
            low_bound = C.densest;
            index = C;
        }
    }

    if (ceil(low_bound) < ceil(Core.densest)) {
        low_bound = Core.densest;
    }

    double up_bound = Core.kmax;

    vector<int> placeholder;

    MDS mds(placeholder, index.motif_num, index.graph_size, low_bound);

    while (!compQueue.empty()) {
        C = compQueue.front();
        compQueue.pop();

        ExactAlgo exact(C.motif_list, motif_size, C.graph_size, C.motif_degree);
        vector<int> res = exact.Exact(ceil(low_bound), ceil(up_bound) + 1, C.motif_num);

        long motif_num = 0;
        int vertex_num = 0;

        //this is to find density
        for (auto& entry : C.motif_list) {
            vector<int>& temp = entry.second;
            int i = 0;
            for (; i < temp.size() - 1; ++i) {
                if (res[temp[i]] == -1)
                    break;
            }
            if (i == temp.size() - 1) {
                motif_num += temp.back();
            }
        }

        for (int i = 0; i < C.graph_size; ++i) {
            if (res[i] != -1)
                vertex_num++;
        }

        if (vertex_num == 0)
            vertex_num = C.graph_size;

        low_bound = (double)motif_num / (vertex_num * 1.0);

        if (low_bound > mds.densest) {
            mds.densest = low_bound;
            mds.motif_num = motif_num;
            mds.s_t_result = res;
            mds.vertex_num = vertex_num;
            mds.core = C;
        }
    }

    return mds;
}
