#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "DataReader.h"

DataReader::DataReader(std::string Graph_File, std::string Motif_File)
{
    this->Graph_File = Graph_File;
    this->Motif_File = Motif_File;
}

std::vector<std::vector<int>> DataReader::readGraph()
{
    std::vector<std::vector<int>> Graph;
    long count_edge = 0;
    try {
        std::ifstream inputFile(Graph_File);
        std::string line;
        int vertex = 0;

        std::getline(inputFile, line);
        std::istringstream iss(line);
        int graph_size;
        iss >> graph_size;

        Graph.resize(graph_size);
        this->graph_size = graph_size;

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            int vertex;
            iss >> vertex;
            std::vector<int> edges;
            int edge;
            while (iss >> edge) {
                edges.push_back(edge);
                count_edge++;
            }
            Graph[vertex] = edges;
        }
        std::cout << "###" << count_edge / 2 << std::endl;
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    this->Graph = Graph;
    return Graph;
}

std::vector<std::vector<int>> DataReader::readMotif()
{
    std::vector<std::vector<int>> Motif;
    try {
        std::ifstream inputFile(Motif_File);
        std::string line;
        std::getline(inputFile, line);
        std::istringstream iss(line);
        int motif_size;
        iss >> motif_size >> Motif_Type >> Motif_Count;

        Motif.resize(motif_size, std::vector<int>(motif_size, 0));
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            int tempx, tempy;
            iss >> tempx >> tempy;
            Motif[tempx][tempy] = 1;
            Motif[tempy][tempx] = 1;
        }
    } catch (const std::ifstream::failure& e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    this->Motif = Motif;
    return Motif;
}

int DataReader::getMotif_Type() const
{
    return Motif_Type;
}

int DataReader::getMotif_Count() const
{
    return Motif_Count;
}

int DataReader::getGraph_Size() const
{
    return graph_size;
}
