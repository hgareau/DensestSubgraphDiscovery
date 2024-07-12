#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "FindMinCut.h"
#include "FlowNetwork.h"
#include "ExactAlgo.h"

class Exactalgo {
private:
    std::unordered_map<std::string, std::vector<int>> Motif_Record;
    int motif_size;
    int graph_size;
    std::vector<int> Motif_degree;

public:
    Exactalgo(std::map<std::string, std::vector<int>>& map, int motif_size, int graph_size, std::vector<int>& Motif_degree)
        : Motif_Record(map), motif_size(motif_size), graph_size(graph_size), Motif_degree(Motif_degree) {}

    std::vector<int> Exact(double l, double u, long motif_num) {
        FlowNetwork flownetwork(Motif_Record, motif_size, graph_size, Motif_degree);
        double alph = (u + l) / 2;
        double bais = 1.0 / (graph_size * (graph_size - 1));
        if (bais < 0.000000000000001) {
            bais = 0.000000000000001;
        }
        std::unordered_map<std::string, std::vector<int>> Network = flownetwork.Construct(alph);

        FindMinCut compute(Network, Network.size() - 2, Network.size() - 1);
        double res_flow = 0, res_alph = 0;
        std::vector<int> res(graph_size, 1);

        while (u - l > bais) {
            double temp = compute.EdmondsKarp();
            std::cout << "upper_bound: " << u << "   low_bound:" << l << "   next guess:" << alph << std::endl;

            if (temp == motif_num * motif_size) {
                u = alph;
            } else {
                l = alph;
                res_alph = alph;
                res_flow = temp;
                auto temp_array = compute.getparent();
                for (int i = 0; i < graph_size; ++i) {
                    res[i] = temp_array[i];
                }
            }
            alph = (u + l) / 2;
            Network = flownetwork.Update(alph);
        }

        return res;
    }

    std::vector<int> Exact(double l, double u, long motif_num, long n2) {
        FlowNetwork flownetwork(Motif_Record, motif_size, graph_size, Motif_degree);
        double alph = (u + l) / 2;
        double bais = 1.0 / (n2 * (n2 - 1));
        if (bais < 0.000000000000001) {
            bais = 0.000000000000001;
        }
        std::unordered_map<std::string, std::vector<int>> Network = flownetwork.Construct(alph);

        FindMinCut compute(Network, Network.size() - 2, Network.size() - 1);
        double res_flow = 0, res_alph = 0;
        std::vector<int> res(graph_size, 1);

        while (u - l > bais) {
            double temp = compute.EdmondsKarp();
            std::cout << u << " " << l << " " << alph << " " << temp << " " << motif_num * motif_size << std::endl;

            if (temp == motif_num * motif_size) {
                u = alph;
            } else {
                l = alph;
                res_alph = alph;
                res_flow = temp;
                auto temp_array = compute.getparent();
                for (int i = 0; i < graph_size; ++i) {
                    res[i] = temp_array[i];
                }
            }
            alph = (u + l) / 2;
            Network = flownetwork.Update(alph);
        }

        return res;
    }

    bool Try(double l, long motif_num) {
        FlowNetwork flownetwork(Motif_Record, motif_size, graph_size, Motif_degree);
        double alph = l;
        std::unordered_map<std::string, std::vector<int>> Network = flownetwork.Construct(alph);
        FindMinCut compute(Network, Network.size() - 2, Network.size() - 1);
        double temp = compute.EdmondsKarp();

        if (temp == motif_num * motif_size && temp != graph_size * alph * motif_size) {
            return false;
        } else {
            return true;
        }
    }
};
