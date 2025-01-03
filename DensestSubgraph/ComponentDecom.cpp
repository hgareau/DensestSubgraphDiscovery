//need to add the #includes
//need to add the variable declarations
#include <vector>
#include <string>
#include <unordered_map>
#include "Component.h"
#include <queue>
#include "ComponentDecom.h"
#include <iostream>

using namespace std;

ComponentDecom::ComponentDecom(vector<vector<int>> &Graph, int graph_size, unordered_map<string, vector<int>> &motif_list)
{
    this->Graph = Graph;
    this->graph_size = graph_size;
    this->motif_list = motif_list;
}

queue<Component> ComponentDecom::decompose()
{
    // creates array delete[] of equal size to the graph and fills it with 0s
    vector<int> delete_arr(graph_size, 0);

    int index = 0;
    // index is the number of connected components
    for (int i = 0; i < graph_size; ++i) {
        // if the vertex has a delete value of 0
        if (delete_arr[i] == 0) {
            index++;
            // For every vertex connected to i (including itself), set its delete value to index
            // if its value is 0
            BFS(delete_arr, i, index);
        }
    }

    queue<Component> result;

    // Index == 1 only occurs if every vertex is connected(?)
    if (index == 1) {
        long motif_num = 0;
        // creates array of size equal to graph to store the motif degree of every vertex
        vector<int> motif_degree(graph_size, 0);
        int motif_size = 1;
        // Then for every motif in the graph (the DAG I should say)
        for (const auto& entry : motif_list) {
            // temp is set as the motif (contains all the vertices in the motif)
            const vector<int>& temp = entry.second;
            // For every vertex in the motif (except the final "1")
            for (int i = 0; i < temp.size() - 1; ++i) {
                // increaase the motif degree of vertex i in the motif
                // by 1 (since based on KList, the final value of a motif array is 1 I think?)
                motif_degree[temp[i]] += temp[temp.size() - 1];
            }
            // motif size is set to the number of vertices in the motif
            motif_size = temp.size() - 1;
            // increase the number of motifs by the 2nd to last value of temp
            motif_num += temp[motif_size];
        }
        // creates a component object and adds it to result
        Component c(Graph, graph_size, motif_list, motif_num, static_cast<double>(motif_num) / graph_size, motif_degree);
        result.push(c);
    } else {
        vector<unordered_map<string, vector<int>>> map_array(index + 1);

        // for every connected component
        for (int i = 1; i < index + 1; ++i) {
            // create an empty hash map for the component
            map_array[i] = unordered_map<string, vector<int>>();
        }

        // Creates arrays and fills them with 0s
        vector<int> New_graph_size(index + 1, 0);
        vector<int> Map_node(graph_size, 0);

        // for every vertex in this subgraph
        for (int i = 0; i < graph_size; ++i) {
            // sets map node i as the current size of the connected component containing i
            Map_node[i] = New_graph_size[delete_arr[i]];
            // increases the size of the connected component contianing i by 1
            New_graph_size[delete_arr[i]]++;
        }

        for (const auto& entry : motif_list) {
            // set temp as the first vertex of this motif
            int temp = entry.second[0];
            // set array as the motif vertices
            vector<int> array = entry.second;
            // Not sure what this for loop is for since array[] is never used
            for (size_t i = 0; i < array.size() - 1; ++i) {
                array[i] = Map_node[array[i]];
            }
            motif_list[entry.first] = array;
            // puts this motif in the map for the connected component containing temp
            map_array[delete_arr[temp]].emplace(entry.first, entry.second);
        }

        // creates an amount of array arrays equal to the amount of connected components
        vector<vector<vector<int>>> C_Graph(index + 1);
        // for every connected component (+1?)
        for (int i = 1; i < index + 1; ++i) {
            vector<vector<int>> temp(New_graph_size[i]);
            C_Graph[i] = temp;
        }
        int motif_size = 1;

        // for every connected component
        for (int i = 1; i < index + 1; ++i) {
            long motif_num = 0;
            // create empty array for the motif degrees of every vertex in the component
            vector<int> motif_degree(New_graph_size[i], 0);
            // for every motif in this component
            for (const auto& entry : map_array[i]) {
                motif_num += entry.second[entry.second.size() - 1];
                motif_size = entry.second.size() - 1;
                // gets the array of vertices in the motif and sets it as temp
                const vector<int>& temp = entry.second;
                // for every vertex in the motif
                for (int j = 0; j < temp.size() - 1; ++j) {
                    // increase the motif degree by 1
                    motif_degree[temp[j]] += temp[temp.size() - 1];
                }
                }
                Component c = Component(C_Graph[i], New_graph_size[i],
	                map_array[i], motif_num, (double)motif_num / (New_graph_size[i] * 1.0), motif_degree);
	            result.push(c);
            }
        }
    return result;
}

void ComponentDecom::BFS(vector<int> &delete_values, int s, int index)
{
    //creates a queue
    queue<int> queue;
    //adds vertex s to that queue
    queue.push(s);
    //while the queue is not empty
    while(!queue.empty()) {
        //Sets node as the vertex at the front of the list then removes it from the list
        int node = queue.front();
        queue.pop();
        //sets the vertex's delete value as current index
        delete_values[node] = index;
        //Then for every edge of node
        for(int i = 0; i < Graph[node].size(); ++i) {
            //if the vertex connected to node by edge i has a delete value of 0
            if(delete_values[Graph[node][i]] == 0) {
                //add it to the queue
                queue.push(Graph[node][i]);
            }
        }
    }
}
