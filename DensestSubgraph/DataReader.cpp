#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "DataReader.h"

class DataReader {
private:
    std::string Graph_File;
    std::string Motif_File;
    int Motif_Type = 0;
    int Motif_Count = 1;
    int graph_size = 0;
    std::vector<std::vector<int>> Graph;
    std::vector<std::vector<int>> Motif;

public:
    DataReader(const std::string& Graph_File, const std::string& Motif_File) 
        : Graph_File(Graph_File), Motif_File(Motif_File) {}

    std::vector<std::vector<int>> readGraph() {
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

    std::vector<std::vector<int>> RereadGraph(const std::string& aaa) {
        std::vector<std::vector<int>> Graph;
        try {
            std::ifstream inputFile(Graph_File);
            std::string line;
            int vertex = 0;
            long count_edge = 0;

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

            std::ofstream of(aaa, std::ofstream::out | std::ofstream::trunc);
            of << graph_size << "\n";
            for (int i = 0; i < graph_size; ++i) {
                of << i;
                std::vector<int> temp_array = Graph[i];
                std::sort(temp_array.begin(), temp_array.end());
                for (int j : temp_array) {
                    of << " " << j;
                }
                of << "\n";
            }
        } catch (const std::ifstream::failure& e) {
            std::cerr << "Exception opening/reading/closing file\n";
        } catch (const std::ofstream::failure& e) {
            std::cerr << "Exception opening/writing/closing file\n";
        }
        this->Graph = Graph;
        return Graph;
    }

    std::vector<std::vector<int>> readMotif() {
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

    int getMotif_Type() const {
        return Motif_Type;
    }

    int getMotif_Count() const {
        return Motif_Count;
    }

    int getGraph_Size() const {
        return graph_size;
    }
};
