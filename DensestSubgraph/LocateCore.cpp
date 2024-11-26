#include <string>
#include <vector>
#include <cmath>
#include "DensestCore.h"
#include "LocateCore.h"

using namespace std;

LocateCore::LocateCore(vector<vector<int>> Graph, vector<vector<double>> core, int graph_size)
{
    this->Graph = Graph;
    this->core = core;
    this->graph_size = graph_size;
}

DensestCore LocateCore::locate()
{
    double max = core[0][2]; // sets max as the density of the full graph
    double kmax = 0; // sets the maximum k-value as 0 (changed by degrees)

    // loop through the k-core's to find the one with highest density
    // for every vertex in the graph
    for (int i = 1; i < graph_size; ++i) {
        // if max density is less than this vertex's k-shell density, set the max to that density
        if (max < core[i][2])
            max = core[i][2];
        // if the k-value is less than this vertex's motif degree (in its k-shell),
        // set the kmax to that density
        if (kmax < core[i][1])
            kmax = core[i][1];
    }

    // sets the lower k-value bound to the ceiling of the maximum density
    int low_bound = static_cast<int>(ceil(max));

    // vertex index for lowest to highest
    int index = 1;
    // empty array to be filled with vertices to be deleted, then fills with 0
    vector<int> delete_vec(graph_size, 0);
    // sets vertices that should be deleted as -1 until the vertices have a motif degree
    // greater than the lower bound
    // this means all vertices that are not in the chosen k-core shall be removed in our
    // new subgraph
    for (; index < graph_size; ++index) {
        if (core[index][1] >= low_bound)
            break;
        delete_vec[static_cast<int>(core[index][0])] = -1;
    }

    int temp = 0;
    // fills delete with 0, 1, 2, 3... for every vertex to be kept in
    for (int i = 0; i < graph_size; ++i) {
        if (delete_vec[i] == 0) {
            delete_vec[i] = temp;
            temp++;
        }
    }

    // new_core will be an array of arrays
    vector<vector<double>> new_core(temp, vector<double>(2));

    // size of the new subgraph
    int New_graph_size = temp;
    // initializes empty adjacency list for the subgraph
    vector<vector<int>> New_Graph(New_graph_size);
    temp = 0; // resets temp to 0

    // This for loop fills the new_core array with info on every vertex, being whether
    // it should be removed and its motif degree
    // for every vertex after the cutoff point from the deletion for loop.
    // (all vertices of motif degree > lower bound)
    for (int i = index; i < graph_size; ++i) {
        int m = static_cast<int>(core[i][0]); // set m as the vertex of this core value
        new_core[temp][0] = delete_vec[m]; // adds if the vertex will be removed, or the value from
                                           // the previous for loop
        new_core[temp][1] = core[i][1]; // adds that vertex's motif degree
        temp++; // increase temp by 1
    }

    // This sets up our new graph with only the vertices and edges that have NOT been removed
    // for every vertex in the graph
    // In essence, this creates the k-core, which is specifically the densest k-core
    for (int i = 0; i < graph_size; ++i) {
        // if the vertex is NOT removed from the graph
        if (delete_vec[i] != -1) {
            int count = 0; // set count to 0
            // create empty array as the size of all of i's edges
            vector<int> array(Graph[i].size());
            // for every edge of vertex i
            for (int j = 0; j < Graph[i].size(); ++j) {
                // if the vertex connected to i by this edge was not deleted
                if (delete_vec[Graph[i][j]] != -1) {
                    // add that vertex's delete "rank" to the array at position count
                    array[count] = delete_vec[Graph[i][j]];
                    count++; // increase count by 1
                }
            }
            // at vertex's delete "rank", set size of its array as the size of all vertices still
            // connect to it
            vector<int> placer(count);
            New_Graph[delete_vec[i]] = placer;

            for (int j = 0; j < count; ++j) {
                //add the vertex to the edge
                New_Graph[delete_vec[i]][j] = array[j];
            }
        }
    }

    int delete_motif = static_cast<int>(core[0][3] - core[index - 1][3]);

    // result is set as a DensestCore (k-core of highest density)
    return DensestCore(New_Graph, New_graph_size, low_bound, index - 1, delete_motif, static_cast<double>(core[index - 1][2]), static_cast<int>(kmax));
}
