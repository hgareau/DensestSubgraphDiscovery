#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#ifndef KCORE_H
#define KCORE_H

class KCore {
public:
    std::vector<std::vector<int>> graph;
    int n;
    std::vector<int> deg;
    std::vector<int> coreReverseFang; // 2015-9-17, an array sorted by coreness in descending order

    KCore(const std::vector<std::vector<int>>& graph);
    std::vector<int> decompose();
    int obtainMaxCore();
    std::vector<int> obtainReverseCoreArr();
    std::string distribute();
    static std::vector<std::vector<int>> readGraphFromFile(const std::string& filename);
};
#endif