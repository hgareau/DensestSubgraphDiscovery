#include <vector>

#ifndef KLIST_H
#define KLIST_H

class KList {
public:
    std::unordered_map<std::string, std::vector<int>> Statistic;

    KList(std::vector<std::vector<int>> graph, int k);
    void getListingOrder(std::vector<int>& GenGraph, std::vector<int>& order, int graph_size);
    void GenerateDAG(std::vector<std::vector<int>>& GenGraph, std::vector<int>& order, std::vector<int>& degree, std::vector<std::vector<int>>& graph, int graph_size);
    void ListingRecord(int k,std::vector<int> c,std::vector<int> arr);
    void Listing(int k, std::vector<int> c,std::vector<int> arr);
    void Listing(int k, std::vector<int>& c, std::vector<int>& arr, int map);
    void Listing(int k, std::vector<int>& c, std::vector<int>& arr, int map[]);
    void ListFast();
    void ListRecord();
    void ListOne(int a);
    int getMotifNum();
    std::vector<long> getMotifDegree();
};
#endif