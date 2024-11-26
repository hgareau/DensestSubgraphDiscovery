#include <string>
#include <vector>

using namespace std;

#ifndef DATAREADER_H
#define DATAREADER_H

class DataReader {
public:
    string Graph_File;
    string Motif_File;
    int Motif_Type = 0;
    int Motif_Count = 1;
    int graph_size = 0;
    vector<vector<int>> Graph;
    vector<vector<int>> Motif;

    DataReader(string Graph_File, string Motif_File);
    vector<vector<int>> readGraph();
    vector<vector<int>> readMotif();
    int getMotif_Type() const;
    int getMotif_Count() const;
    int getGraph_Size() const;
};
#endif