#include <vector>

using namespace std;

#ifndef KLIST_H
#define KLIST_H

class KList {
public:
    vector<vector<int>> graph; // DAG of the graph
    int k; // This is the size of the given motif
    vector<int> order; // core values of the vertices + 1
    int graph_size; // number of vertices in the graph
    vector<int> degree; // the "edge" degrees of every vertex in the DAG
    vector<int> label; // the current motif size each vertex is in
    int motif_num = 0; // the number of motifs in the DAG
    vector<long> motif_degree; // The motif degree of every vertex in the DAG
    vector<vector<string>> Adjlist;
    vector<vector<int>> GenGraph;
    unordered_map<string, vector<int>> Statistic; // Statistic is a map of all the motifs in the DAG

    KList(vector<vector<int>> graph, int k);
    void getListingOrder();
    void GenerateDAG();
    void ListingRecord(int k, vector<int> c, vector<int> arr);
    void Listing(int k, vector<int> c, vector<int> arr);
    void Listing(int k, vector<int>& c, vector<int>& arr, int map);
    void ListFast();
    void ListRecord();
    void ListOne(int a);
    int getMotifNum();
    vector<long> getMotifDegree();
};
#endif