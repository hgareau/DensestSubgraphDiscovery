#include <string>
#include <vector>

#ifndef DATAREADER_H
#define DATAREADER_H

class DataReader {
public:
    std::string Graph_File;
    std::string Motif_File;
    int Motif_Type = 0;
    int Motif_Count = 1;
    int graph_size = 0;
    std::vector<std::vector<int>> Graph;
    std::vector<std::vector<int>> Motif;

    DataReader(std::string Graph_File, std::string Motif_File);
    std::vector<std::vector<int>> readGraph();
    std::vector<std::vector<int>> readMotif();
    int getMotif_Type() const;
    int getMotif_Count() const;
    int getGraph_Size() const;
};
#endif