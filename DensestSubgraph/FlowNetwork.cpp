#include <unordered_map>
#include <vector>
#include <string>
#include "FlowNetwork.h"

using namespace std;

FlowNetwork::FlowNetwork(unordered_map<string, vector<int>> map, int motif_size, int graph_size, vector<int> Motif_degree)
{
    this->Motif_Record = map;
    this->motif_size = motif_size;
    this->graph_size = graph_size;
    this->Motif_degree = Motif_degree;
}

vector<unordered_map<int, vector<double>>> FlowNetwork::Construct(double alph)
{
    // Set a as the number of motifs in the graph
    int a = Motif_Record.size();
    // Initialize i and weight as 0
    int i = 0;
    double weight = 0;
    vector<int> temp_array; // Create an empty temp_array

    // Set the FlowNetwork datastructure to have a slot for every motif in the graph,
    // every vertex in the graph, and s and t
    vector<unordered_map<int, vector<double>>> flowNet(a + graph_size + 2);
    FlowNetwork1 = flowNet;

    // For every slot in FlowNetwork
    for (i = 0; i < a + graph_size + 2; ++i){
        // Give the motif or vertex its own unordered_map

        FlowNetwork1[i] = unordered_map<int, vector<double>>();
    }

    i = graph_size; // Set i as the number of vertices in the graph

    // For every motif in the graph
    for (auto entry : Motif_Record) {
        // Set temp_array as the list of vertices in this motif
        temp_array = entry.second;
        // Weight = 1 * the id of the final vertex in this specific motif's vertex list
        weight = temp_array[motif_size] * (motif_size - 1);

        // For every vertex of the motif
        for (a = 0; a < motif_size; ++a) {
            // temp1 is a flow/capacity pair of 1/1 (the final slot of a motif in Statistic is always 1)
            // temp2 is a flow/capacity pair of weight/weight
            vector<double> temp1 = {(double)temp_array[motif_size], (double)temp_array[motif_size]};
            vector<double> temp2 = {weight, weight};

            // These set up the edges with flow/capacity of temp1 and temp2 between the two
            // vertices in the motif
            FlowNetwork1[i][temp_array[a]] = temp2;
            FlowNetwork1[temp_array[a]][i] = temp1;
        }
        ++i; // Increase i by 1
    }

    // Set source and sink as s and t
    int source = Motif_Record.size() + graph_size;
    int sink = Motif_Record.size() + graph_size + 1;

    // For every vertex in the graph
    for (i = 0; i < graph_size; ++i) {
        // Put an edge in vertex i's map with 0 flow and 0 capacity connecting vertex i to s (source)
        vector<double> temp1 = {0.0, 0.0};
        FlowNetwork1[i][source] = temp1;

        // Put an edge in vertex i's map with flow and capacity of alpha*# of motifs connecting
        // i to t
        vector<double> temp2 = {alph * (motif_size), alph * (motif_size)};
        FlowNetwork1[i][sink] = temp2;

        // Put an edge in s's map with flow and capacity of vertex i's motif degree
        // connecting s to i
        vector<double> temp3 = {(double)Motif_degree[i], (double)Motif_degree[i]};
        FlowNetwork1[source][i] = temp3;

        // Put an edge in t's map with flow and capacity of 0 connecting t to i
        vector<double> temp4 = {0, 0};
        FlowNetwork1[sink][i] = temp4;
    }

    // Once every edge is set up, return the Flow Network Map array
    return FlowNetwork1;
}

vector<unordered_map<int, vector<double>>> FlowNetwork::Update(double alph)
{
    // sets tink as the sink
    int tink = graph_size + Motif_Record.size() + 1;
    vector<double> temp_array; // creates empty temp array
    // for every vertex and Motif + s (not sure how this works without brackets though)
    for (int i = 0; i <= tink; ++i) {
        // for every edge of vertex/motif i
        for (auto &entry : FlowNetwork1[i]) {
            temp_array = entry.second; // get the flow/capacity
            temp_array[0] = temp_array[1]; // set the flow as the capacity
        }
    }
    // for every vertex in the graph
    for (int i = 0; i < graph_size; ++i) {
        // get the edge pointing from vertex i to t
        // set the flow/capacity of the edge to alpha * motif size
        FlowNetwork1[i][tink][0] = alph * motif_size;
        FlowNetwork1[i][tink][1] = alph * motif_size;
    }
    // return the updated Flow Network
    return FlowNetwork1;
}
