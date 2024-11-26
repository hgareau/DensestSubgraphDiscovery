#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "KCore.h"

using namespace std;

KCore::KCore(const vector<vector<int>> &graph)
{
    this->graph = graph;
    this->n = graph.size();
    this->coreReverseFang.resize(n); //initialize this array
}

vector<int> KCore::decompose()
{
    deg.resize(n);

    // Step 1: obtain the degree and the maximum degree
    int md = -1; // the maximum degree in the graph
    for (int i = 0; i < n; i++) {
        deg[i] = graph[i].size();
        if (deg[i] > md) {
            md = deg[i];
        }
    }

    // Step 2: fill the bin
    vector<int> bin(md + 1, 0);
    for (int i = 0; i < n; i++) {
        bin[deg[i]] += 1;
    }

    // Step 3: update the bin
    int start = 0;
    for (int d = 0; d <= md; d++) {
        int num = bin[d];
        bin[d] = start;
        start += num;
    }

    // Step 4: find the position
    vector<int> pos(n + 1);
    vector<int> vert(n + 1);
    for (int v = 0; v < n; v++) {
        pos[v] = bin[deg[v]];
        vert[pos[v]] = v;
        bin[deg[v]] += 1;
    }

    for (int d = md; d >= 1; d--) {
        bin[d] = bin[d - 1];
    }
    if (!bin.empty())
        bin[0] = 1;

    // Step 5: decompose
    for (int i = 0; i < n; i++) {
        int v = vert[i];
        for (int j = 0; j < graph[v].size(); j++) {
            int u = graph[v][j];
            if (deg[u] > deg[v]) {
                int du = deg[u];
                int pu = pos[u];
                int pw = bin[du];
                int w = vert[pw];
                if (u != w) {
                    pos[u] = pw;
                    vert[pu] = w;
                    pos[w] = pu;
                    vert[pw] = u;
                }
                bin[du] += 1;
                deg[u] -= 1;
            }
        }
        coreReverseFang[n - i - 1] = v;
    }
    return deg;
}

int KCore::obtainMaxCore()
{
    int max = -1;
    for (int i = 1; i < deg.size(); i++) {
        if (deg[i] > max) {
            max = deg[i];
        }
    }
    return max;
}

vector<int> KCore::obtainReverseCoreArr()
{
    return coreReverseFang;
}

string KCore::distribute()
{
    int iteration = 1;
    int size = 5;
    int count = 0;
    string sss = "";
    do {
        count = 0;
        for (int i = 0; i < deg.size(); ++i) {
            if (deg[i] < size * iteration && deg[i] >= size * (iteration - 1)) {
                count++;
            }
        }
        if (count != 0) {
            sss += "core_number [" + to_string(size * (iteration - 1)) + " " + to_string(size * iteration) + ")\tnum: " + to_string(count) + "\tratio:" + to_string(count * 1.0 / deg.size()) + "\n";
            cout << "core_number [" << size * (iteration - 1) << " " << size * iteration << ")\tnum: " << count << "\tratio:" << (count * 1.0 / deg.size()) << endl;
        }
        iteration++;
    } while (count != 0);

    int max = -1;
    for (int i = 1; i < deg.size(); i++) {
        if (deg[i] > max) {
            max = deg[i];
        }
    }
    for (int i = 1; i < deg.size(); i++) {
        if (deg[i] == max) {
            count++;
        }
    }
    sss += "maxCore:" + to_string(max) + "\t\tnum: " + to_string(count) + "\tratio:" + to_string(count * 1.0 / deg.size()) + "\n";
    cout << "maxCore:" << max << "\t\tnum: " << count << "\tratio:" << (count * 1.0 / deg.size()) << endl;
    return sss;
}

vector<vector<int>> KCore::readGraphFromFile(const string &filename)
{
    vector<vector<int>> Graph;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File not found: " << filename << endl;
        return Graph;
    }

    string line;
    int vertex = 0;

    getline(file, line);
    istringstream iss(line);
    int graph_size;
    iss >> graph_size;
    Graph.resize(graph_size);

    while (getline(file, line)) {
        istringstream iss(line);
        iss >> vertex;
        vector<int> neighbors;
        int neighbor;
        while (iss >> neighbor) {
            neighbors.push_back(neighbor);
        }
        Graph[vertex] = neighbors;
    }
    file.close();
    return Graph;
}
