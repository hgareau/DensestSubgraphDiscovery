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

using namespace std;

ExactAlgo::ExactAlgo(unordered_map<string, vector<int>> map, int motif_size, int graph_size, vector<int> Motif_degree)
{
    this->Motif_Record = map;
    this->motif_size = motif_size;
    this->graph_size = graph_size;
    this->Motif_degree = Motif_degree;
}

vector<int> ExactAlgo::Exact(double l, double u, long motif_num)
{
    // Creates a flow network instance from the given info
    FlowNetwork flownetwork(Motif_Record, motif_size, graph_size, Motif_degree);

    // Sets alpha as the average of the upper and lower bound
    double alph = (u + l) / 2;

    // Sets the bias value
    double bais = 1.0 / (graph_size * (graph_size - 1));
    //originally set to 0.000000000000001
    if (bais < 1.0) {
        bais = 1.0;
    }

    // Fully constructs the flow network with the current test density

    vector<unordered_map<int, vector<double>>> Network = flownetwork.Construct(alph);

    unordered_map<int, vector<double>> testA = Network[0];

    // Creates a FindMinCut object from the Flow Network, the source, and the sink

    // Creates the result array and fills it with 1s
    vector<int> res(graph_size, 1);

    // The main loop of Exact
    while (u - l > bais) {
        // Creates a FindMinCut object from the Flow Network, the source, and the sink
        FindMinCut compute(Network, Network.size() - 2, Network.size() - 1);

        // Computes the maximum flow in the current graph
        double temp = compute.EdmondsKarp();

        cout << "upper_bound: " << u << "    lower_bound: " << l << "    next_guess: " << alph << '\n';

        // Updates the upper and lower bounds
        if (temp == motif_num * motif_size) {
            u = alph;
        } else {
            l = alph;
            vector<int> temp_array = compute.getparent();
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
