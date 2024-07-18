#include <vector>

#ifndef KLIST_H
#define KLIST_H

class KList {
public:
    std::vector<std::vector<int>> graph; // DAG of the graph
    int k; // This is the size of the given motif
    std::vector<int> order; // core values of the vertices + 1
    static int graph_size; // number of vertices in the graph
    std::vector<int> degree; // the "edge" degrees of every vertex in the DAG
    std::vector<int> label; // the current motif size each vertex is in
    int motif_num = 0; // the number of motifs in the DAG
    std::vector<long> motif_degree; // The motif degree of every vertex in the DAG
    std::vector<std::vector<std::string>> Adjlist;
    std::vector<std::vector<int>> GenGraph;
    std::unordered_map<std::string, std::vector<int>> Statistic; // Statistic is a map of all the motifs in the DAG

    KList(std::vector<std::vector<int>> graph, int k);
    void getListingOrder();
    void GenerateDAG();
    void ListingRecord(int k,std::vector<int> c,std::vector<int> arr);
    void Listing(int k, std::vector<int> c,std::vector<int> arr);
    void Listing(int k, std::vector<int>& c, std::vector<int>& arr, int map);
    void ListFast();
    void ListRecord();
    void ListOne(int a);
    int getMotifNum();
    std::vector<long> getMotifDegree();
};
#endif