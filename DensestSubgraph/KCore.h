#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

#ifndef KCORE_H
#define KCORE_H

class KCore {
public:
    vector<vector<int>> graph;
    int n;
    vector<int> deg;
    vector<int> coreReverseFang; // 2015-9-17, an array sorted by coreness in descending order

    KCore(const vector<vector<int>>& graph);
    vector<int> decompose();
    int obtainMaxCore();
    vector<int> obtainReverseCoreArr();
    string distribute();
    static vector<vector<int>> readGraphFromFile(const string& filename);
};
#endif