#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <iomanip>
#include <map>

#include <fstream>

#include "Component.h"
#include "ComponentDecom.h"
#include "DensestCore.h"
#include "LocateCore.h"
#include "CDSDecompose.h"
#include "Log.h"
#include "DataReader.h"
#include "MDS.h"
#include "KList.h"
#include "DynamicExactAlgo.h"

using namespace std;

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
    static string dataset_doc;
    static string motif_doc;
    static vector<string> datasets_url;
    static vector<string> motif_url;

    static vector<DataReader> g_data;
    static vector<DataReader> m_data;

    int run() {
        try {
            // For every graph in datasets_url, store its own DataReader.
            // Then call readGraph on that DataReader to store an adjacency list representing
            // the graph in its spot
            for (const auto& dataset : datasets_url) {
                g_data.emplace_back(DataReader(dataset_doc + dataset + ".txt", "holder"));
                g_data.back().readGraph();
            }

            // For every motif in motif_url, store its own DataReader.
            // Then call readMotif on that DataReader to store an adjacency matric representing
            // the motif in its spot
            for (const auto& motif : motif_url) {
                m_data.emplace_back(DataReader("holder", motif_doc + motif + ".txt"));
                m_data.back().readMotif();
            }

            time_t now = time(nullptr);

            now = time(nullptr);

            // Here is where CoreExact and Exact are set up and run.
            // They are run for every chosen motif.
            // They are run in a for loop that goes specifically from CoreExact to Exact.

            DataReader a = DataReader("holder", "holder");

            // Set up the info in 'a'
            a.Graph = g_data[0].Graph;
            a.graph_size = g_data[0].getGraph_Size();
            a.Motif = m_data[0].Motif;
            a.Motif_Count = m_data[0].Motif_Count;
            a.Motif_Type = m_data[0].Motif_Type;

            vector<vector<int>> Graph = a.Graph;
            vector<vector<int>> Motif = a.Motif;

            // Calculate the number of edges
            int counta = 0;
            for (int yui = 0; yui < Graph.size(); ++yui) {
                counta += Graph[yui].size();
            }

            unordered_map<string, vector<int>> dummyList;
            vector<long> dummyVector;
            // Perform the CDS decomposition
            CDSDecompose c(Graph, Motif, a.getGraph_Size(), Motif[0].size(), a.getMotif_Count(), dummyList, dummyVector);
            vector<vector<double>> r_d = c.Decompose();

            // Locate the densest k-core
            LocateCore d(Graph, r_d, a.getGraph_Size());
            DensestCore r_c = d.locate();

            // Maintain the motif degrees of vertices
            KList b(r_c.Graph, a.Motif.size());
            b.ListRecord();

            // Perform the component decomposition
            ComponentDecom f(r_c.Graph, r_c.graph_size, b.Statistic);
            queue<Component> r_q = f.decompose();


            DensestCore my(r_c.Graph, r_c.graph_size, 0, 0, 0, 0, r_c.graph_size);

            // Run the CoreExact algorithm
            DynamicExactAlgo g(r_q, my, Motif[0].size());

            MDS mds = g.DynamicExact();

            // Print the results
            cout << "density: " << mds.densest << endl;
            cout << "Num of Cliques/edges: " << mds.motif_num << endl;
            cout << "Num of Vertices: " << mds.vertex_num << endl;

            return 0;

        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }
    }
};

//Variables to access data sets
string ExactTest::dataset_doc = "C:/Users/hgare/Research Code/DensestSubgraph/datasets/";
string ExactTest::motif_doc = "C:/Users/hgare/Research Code/DensestSubgraph/motif/";
vector<string> ExactTest::datasets_url = { "testGraph1" };
vector<string> ExactTest::motif_url = { "triangle" };
vector<DataReader> ExactTest::g_data;
vector<DataReader> ExactTest::m_data;

int main() {
    ExactTest test;
    return test.run();
}