#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <string>
#include "FindMinCut.h"
#include "FlowNetwork.h"
#include "ExactAlgo.h"

ExactAlgo::ExactAlgo(std::unordered_map<std::string, std::vector<int>> map, int motif_size, int graph_size, std::vector<int> Motif_degree)
{
    this->Motif_Record = map;
    this->motif_size = motif_size;
    this->graph_size = graph_size;
    this->Motif_degree = Motif_degree;
}

std::vector<int> ExactAlgo::Exact(double l, double u, long motif_num)
{
    // Creates a flow network instance from the given info
    FlowNetwork flownetwork(Motif_Record, motif_size, graph_size, Motif_degree);

    // Sets alpha as the average of the upper and lower bound
    double alph = (u + l) / 2;

    // Sets the bias value
    double bais = 1.0 / (graph_size * (graph_size - 1));
    if (bais < 0.000000000000001) {
        bais = 0.000000000000001;
    }

    // Fully constructs the flow network with the current test density
    std::vector<std::unordered_map<int, std::vector<double>>> Network = flownetwork.Construct(alph);

    // Creates a FindMinCut object from the Flow Network, the source, and the sink
    FindMinCut compute(Network, Network.size() - 2, Network.size() - 1);

    // Creates the result array and fills it with 1s
    std::vector<int> res(graph_size, 1);

    // The main loop of Exact
    while (u - l > bais) {
        // Computes the maximum flow in the current graph
        double temp = compute.EdmondsKarp();

        // Updates the upper and lower bounds
        if (temp == motif_num * motif_size) {
            u = alph;
        } else {
            l = alph;
            std::vector<int> temp_array = compute.getparent();
            for (int i = 0; i < graph_size; ++i) {
                res[i] = temp_array[i];
            }
        }

        // Updates alpha and the flow network
        alph = (u + l) / 2;
        Network = flownetwork.Update(alph);
    }

    return res;
}
