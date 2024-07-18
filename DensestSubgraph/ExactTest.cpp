#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>
#include <map>

#include "Component.h"
#include "ComponentDecom.h"
#include "DensestCore.h"
#include "LocateCore.h"
#include "CDSdecompose.h"
#include "Log.h"
#include "DataReader.h"
#include "MDS.h"
#include "KList.h"
#include "DynamicExactAlgo.h"

/*
 * This class tests the Exact and CoreExact algorithms on the inputted dataset(s) with chosen motif(s)
 * 
 * The datasets are graphs, represented as adjacency lists
 * 
 * Motifs are the "shape" we're testing the density of. So an edge is a shape which is just
 * 2 nodes with an edge containing them.
 * 
 * Explanations of how graphs and motifs are stored as text files can be found in DataReader.
 */
class ExactTest {
public:
    static std::string dataset_doc;
    static std::string motif_doc;
    static std::vector<std::string> datasets_url;
    static std::vector<std::string> motif_url;

    static std::vector<DataReader> g_data;
    static std::vector<DataReader> m_data;

    static int main(int argc, char* argv[]) {
        try {
            // For every graph in datasets_url, store its own DataReader.
            // Then call readGraph on that DataReader to store an adjacency list representing
            // the graph in its spot
            for (const auto& dataset : datasets_url) {
                g_data.emplace_back(DataReader(dataset_doc + dataset + ".txt", nullptr));
                g_data.back().readGraph();
            }

            // For every motif in motif_url, store its own DataReader.
            // Then call readMotif on that DataReader to store an adjacency matric representing
            // the motif in its spot
            for (const auto& motif : motif_url) {
                m_data.emplace_back(DataReader(nullptr, motif_doc + motif + ".txt"));
                m_data.back().readMotif();
            }

            DataReader a(nullptr, nullptr);
            std::time_t now = std::time(nullptr);
            std::cout << std::put_time(std::localtime(&now), "%d-%b-%Y %H:%M:%S") << " " << datasets_url[0] << std::endl;

            now = std::time(nullptr);
            std::cout << std::put_time(std::localtime(&now), "%d-%b-%Y %H:%M:%S") << " " << datasets_url[0] << std::endl;

            // Here is where CoreExact and Exact are set up and run.
            // They are run for every chosen motif.
            // They are run in a for loop that goes specifically from CoreExact to Exact.

            // Assuming the necessary data structures are already set up
            std::vector<DataReader> g_data = { /* ... */ };
            std::vector<DataReader> m_data = { /* ... */ };
            a = DataReader(0, 0);

            // Set up the info in 'a'
            a.Graph = g_data[0].Graph;
            a.graph_size = g_data[0].getGraph_Size();
            a.Motif = m_data[0].Motif;
            a.Motif_Count = m_data[0].Motif_Count;
            a.Motif_Type = m_data[0].Motif_Type;

            std::vector<std::vector<int>> Graph = a.Graph;
            std::vector<std::vector<int>> Motif = a.Motif;

            // Calculate the number of edges
            int counta = 0;
            for (int yui = 0; yui < Graph.size(); ++yui) {
                counta += Graph[yui].size();
            }

            // Perform the CDS decomposition
            CDSDecompose c(Graph, Motif, a.getGraph_Size(), Motif[0].size(), a.getMotif_Count());
            std::vector<std::vector<double>> r_d = c.Decompose();

            // Locate the densest k-core
            LocateCore d(Graph, r_d, a.getGraph_Size());
            DensestCore r_c = d.locate();

            // Maintain the motif degrees of vertices
            KList b(r_c.Graph, a.Motif.size());
            b.ListRecord();

            // Perform the component decomposition
            ComponentDecom f(r_c.Graph, r_c.graph_size, b.Statistic);
            std::queue<Component> r_q = f.decompose();

            // Run the CoreExact algorithm
            DynamicExactAlgo g(r_q, r_c, Motif[0].size());
            MDS mds = g.DynamicExact();

            //This has to do with Printing in C++
            // Print the results
            std::cout << "density: " << mds.densest << std::endl;
            std::cout << "Num of Cliques/edges: " << mds.motif_num << std::endl;
            std::cout << "Num of Vertices: " << mds.vertex_num << std::endl;

            return 0;

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
};

std::string ExactTest::dataset_doc = "./datasets/";
std::string ExactTest::motif_doc = "./motif/";
std::vector<std::string> ExactTest::datasets_url = { "graph" };
std::vector<std::string> ExactTest::motif_url = { "edge" };
std::vector<DataReader> ExactTest::g_data;
std::vector<DataReader> ExactTest::m_data;