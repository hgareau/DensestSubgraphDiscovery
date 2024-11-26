#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "DataReader.h"

using namespace std;

DataReader::DataReader(string Graph_File, string Motif_File)
{
    this->Graph_File = Graph_File;
    this->Motif_File = Motif_File;
}

//Sets up Adjacency List representative of the graph based on the properly formatted
//input graph
vector<vector<int>> DataReader::readGraph()
{
    vector<vector<int>> Graph;
    long count_edge = 0;
    try {
        ifstream inputFile(Graph_File);
        string line;
        int vertex = 0;

        getline(inputFile, line);
        istringstream iss(line);
        int graph_size;
        iss >> graph_size;

        Graph.resize(graph_size);
        this->graph_size = graph_size;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            int vertex;
            iss >> vertex;
            vector<int> edges;
            int edge;
            while (iss >> edge) {
                edges.push_back(edge);
                count_edge++;
            }
            Graph[vertex] = edges;
        }
        cout << "###" << count_edge / 2 << endl;
    } catch (const ifstream::failure& e) {
        cerr << "Exception opening/reading/closing file\n";
    }
    this->Graph = Graph;
    return Graph;
}

//Sets up adjacency matrix representative of the motif based on the properly formatted
//input file
vector<vector<int>> DataReader::readMotif()
{
    vector<vector<int>> Motif;
    try {
        ifstream inputFile(Motif_File);
        string line;
        getline(inputFile, line);
        istringstream iss(line);
        int motif_size;
        iss >> motif_size >> Motif_Type >> Motif_Count;

        Motif.resize(motif_size, vector<int>(motif_size, 0));
        while (getline(inputFile, line)) {
            istringstream iss(line);
            int tempx, tempy;
            iss >> tempx >> tempy;
            Motif[tempx][tempy] = 1;
            Motif[tempy][tempx] = 1;
        }
    } catch (const ifstream::failure& e) {
        cerr << "Exception opening/reading/closing file\n";
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
