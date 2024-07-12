#include <vector>
#include <string>

#ifndef KCORE_H
#define KCORE_H

class KCore {
public:
    KCore(const std::vector<std::vector<int>>& graph);
    std::vector<int> decompose();
    int obtainMaxCore();
    std::vector<int> obtainReverseCoreArr();
    std::string distribute();
    static std::vector<std::vector<int>> readGraphFromFile(const std::string& filename);
};
#endif