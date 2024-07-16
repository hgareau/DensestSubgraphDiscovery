#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <algorithm>
#include "CDSDecompose.h"
#include "KList.h"

CDSDecompose::CDSDecompose(std::vector<std::vector<int>> Graph, std::vector<std::vector<int>> Motif, int graph_size, int motif_size, int motif_type)
{
    this->motif_list = motif_list;
        this->Graph = Graph;
        this->Motif = Motif;
        this->graph_size = graph_size;
        this->motif_size = motif_size;
        this->motif_type = motif_type;
        this->motif_degree = motif_degree;
        this->degree.resize(motif_size);

        for (int i = 0; i < motif_size; ++i) {
            int count = 0;
            for (int j = 0; j < motif_size; ++j) {
                if (Motif[i][j] > 0)
                    count++;
            }
            this->degree[i] = count;
        }

        this->Share.resize(graph_size);
        for (int i = 0; i < graph_size; ++i) {
            this->Share[i] = std::unordered_map<int, int>();
        }
}

std::vector<std::vector<double>> CDSDecompose::Decompose()
{
    // A lot of variables are set up

        //max is the maximum motif degree
        long max = 0;
        int motif_num = 0; //the number of motifs in the graph
        //count is used to keep vertex position in result during the peeling algorithm
        int count = 0;
        //mark is an array that keeps track of which vertices have been removed from the graph
        //0's signify a vertex is in the graph, 1's signify it's removed
        std::vector<int> mark(graph_size, 0);
        //map stores a key value pair for every vertex in the graph, with each vertex as a key,
        //and their motif degree in the current (post removal of certain vertices) graph
        std::unordered_map<int, long> map;

        //array_index is UNUSED
        std::vector<int> array_index(graph_size, 0);
        //array of the motif degree of every vertex in the graph
        std::vector<long> array_degree(graph_size);

        //empty array used to create pruned maps
        std::vector<int> new_array(graph_size, 0);
        //empty map used to create pruned maps
        std::vector<int> new_map(graph_size, 0);

        //creates new KList with the full graph and size of the motif
        KList k(Graph, motif_size);
        //ListFast() sets up a bunch of variables in KList k to find the array motif degrees of
        //every vertex
        k.ListFast();
        //we then set array_degree as the results of ListFast(), the motif degrees of every vertex
        array_degree = k.getMotifDegree();

        //NOTE: As far as I can tell, temp_degree is never used. It stores updated degrees and such,
        //but the values stored in it are UNUSED.

        //create a temporary array to store the values of motif_degree
        std::vector<long> temp_degree(graph_size);
        for (int i = 0; i < graph_size; ++i) {
            temp_degree[i] = array_degree[i];
        }

        //This for loop checks every vertex to find the vertex of maximum vertex degree
        //We also set motif_num as the sum of every motif_degree
        for (int i = 0; i < graph_size; ++i) {
            if (max < array_degree[i])
                max = array_degree[i];
            motif_num += array_degree[i];
        }
        //increase max by 1
        max = max + 1;
        //I believe this is because in our results, we have one additional slot for information
        //on the entire graph.

        //divide motif_num (the sum of every motif degree) by motif_size to find the number of
        //motifs in the graph
        motif_num = motif_num / motif_size;

        //result is a data structure used to save the result of the peeling algorithm
        //It consists of arrays for every vertex, with 0 being a special case
        //0 = vertex
        //1 = core value
        //2 = its density in the current graph
        //3 = number of motifs in its current graph
        //4 = unused
        std::vector<std::vector<double>> result(graph_size + 1, std::vector<double>(5));
        //the first array in result is used to store the density of and the number of motifs
        //in the entire graph
        result[0][2] = motif_num / (double)graph_size;
        result[0][3] = motif_num;

        std::vector<long> bin(max + 1, 0);
        //Each slot of bin is a motif_degree
        //This for loop fills those slots with how many vertices have that degree
        for (int i = 0; i < graph_size; ++i) {
            bin[array_degree[i]] += 1;
        }

        long start = 0;
        //Then for every motif degree up to max
        for (int d = 0; d <= max; ++d) {
            //set temporary value num as the number of vertices with motif degree d
            long num = bin[d];
            //set bin to the current value of start
            bin[d] = start;
            //add num to start
            start += num;
        }

        std::vector<int> pos(graph_size + 1, 0); //holds vertex position in bin
        std::vector<int> vert(graph_size + 1, 0); //holds the vertex at that position
        //places the positions and vertices in pos and vert for every vertex
        //and increases the number of vertices with maximum motif degree of that position by 1
        for (int v = 0; v < graph_size; ++v) {
            pos[v] = bin[array_degree[v]];
            vert[pos[v]] = v;
            bin[array_degree[v]] += 1;
        }

        //moves every value in bin up by 1 in the array
        //This is so the max degree numbers are accurate for if they are the number of vertices
        //with *at most* that degree (so all vertices of degree 0, all vertices of degree 0 and 1, etc.)
        for (long d = max; d >= 1; d--) {
            bin[d] = bin[d - 1];
        }
        //sets the number of vertices with max degree of 0 to 1 (?)
        if (bin.size() != 0)
            bin[0] = 1;

        //THIS FOR LOOP
        //for every vertex in the graph
        for (int i = 0; i < graph_size; ++i) {

            //This loop finds the vertex of lowest motif degree, which will be removed this loop
            //as it is the lowest core value.

            //vertex id with lowest motif degree
            int index = 0;
            //the lowest motif degree
            long index_min = 0XFFFFFF;
            //for every vertex's motif degree
            for (int yuu = 0; yuu < array_degree.size(); ++yuu) {
                //if the current minimum motif degree is greater than the motif degree of the current vertex
                //AND mark of vertex yuu = 0 (the vertex is still in the graph)
                if (index_min > array_degree[yuu] && mark[yuu] == 0) {
                    //set index as that vertex and index_min as its degree
                    index = yuu;
                    index_min = array_degree[yuu];
                }
            }

            //increase count by 1
            count++;
            //in the array for vertex count
            result[count][0] = index; //store the current vertex of minimum motif degree
            result[count][1] = array_degree[index]; //store the current minimum motif degree

            //we update whenever the lowest core value is greater than 0.
            //And by update I mean updating the graph to account for removed vertices

            //if the motif degree with minimum degree > 0
            if (array_degree[index] > 0) {
                map = Generate(index, mark, new_array, new_map);

                long delete_count = 0; //counts how many motifs are deleted
                //if map is not empty
                if (!map.empty())
                    //for every (vertex, degree) pair in map
                    for (auto entry : map) {
                        int temp_key = entry.first; //temp_key = vertex
                        long temp_value = entry.second; //temp_value = motif_degree
                        //increase delete_count by the motif degree of this vertex
                        delete_count += temp_value;
                        //subtract the subgraph motif degree from the full graph motif degree
                        //and the temporary array of the same values
                        array_degree[temp_key] -= temp_value;
                        temp_degree[temp_key] -= temp_value;
                    }
                //divide delete_count by the motif_size - 1 to find how many motifs are being
                //deleted
                delete_count = delete_count / (motif_size - 1);

                //subtract delete_count from the number of motifs in the graph
                motif_num -= delete_count;

                //sets the 4th value in count's result array as the number of motifs in the modified
                //subgraph
                result[count][3] = motif_num;
                //if the number of vertices in the graph - the number of vertices checked
                //is > 0, set the 3rd value in count's result array as density of this shell
                //Otherwise, set that value to 0
                if (graph_size - count > 0) {
                    result[count][2] = motif_num / (double)(graph_size - count);
                }
                else {
                    result[count][2] = 0;
                }
            }
            else {
                //sets the 4th value in count's result array as the number of motifs
                result[count][3] = motif_num;
                //if the number of vertices in the graph - the number of vertices checked
                //is > 0, set the 3rd value in count's result array as ___(not exactly sure
                //what this is meant to represent)
                //Otherwise, set that value to 0
                if (graph_size - count > 0) {
                    result[count][2] = motif_num / (double)(graph_size - count);
                }
                else {
                    result[count][2] = 0;
                }
                //sets this to 0 if it's been set below 0
                array_degree[index] = 0;
            }

            //mark that vertex index has been removed OR just visited
            mark[index] = 1;
        }

        //after every vertex gets an array of information, return the array of those arrays
        return result;
}

std::unordered_map<int, long> CDSDecompose::Generate(int index, std::vector<int> &mark, std::vector<int> &array, std::vector<int> &map_s)
{
    std::vector<int> temp_list; // create temporary vector
        temp_list.push_back(index); // add input vertex to list
        array[index] = 1; // set the value at position index in array as 1
        std::queue<int> queue; // create a queue
        queue.push(index); // add input vertex to queue
        int d = 1; // set integer d=1

        // This while loop fills the values of temp_list.
        // My current guess is that this is to generate which vertices to include in the new graph
        // while the queue is NOT empty AND d+1 <=2
        while (!queue.empty() && d + 1 <= 2) {
            // set temp as first integer of queue and remove it from the queue
            int temp = queue.front();
            queue.pop();
            // d is set as the value in array at position temp
            d = array[temp];
            // for every edge of vertex temp
            for (int i = 0; i < Graph[temp].size(); ++i) {
                // Graph[temp][i] is the vertex connected to temp by edge i
                // if the array value of that vertex = 0, d+1 <= 2 AND
                // that vertex is still in the graph
                if (array[Graph[temp][i]] == 0 && d + 1 <= 2 && mark[Graph[temp][i]] == 0) {
                    queue.push(Graph[temp][i]); // add that vertex to the queue
                    array[Graph[temp][i]] = d + 1; // the array value of that vertex is set to d+1
                    temp_list.push_back(Graph[temp][i]); // add that vertex to our temp_list
                }
            }
        }

        int count = temp_list.size(); // count equals number of vertices in temp_list
        std::vector<int> map_array(count); // map_array has size of same number as above
        int num = 0;
        std::vector<std::vector<int>> new_graph(count); // the new subgraph with the non-pruned vertices
        // This for loop will set up the newly pruned subgraph
        // for every vertex in the new subgraph
        for (int i = 0; i < count; ++i) {
            // sets node as vertex i from our subgraph's list of vertices
            int node = temp_list[i];
            map_array[i] = node; // set current position of map_array to this vertex
            map_s[node] = num; // set position in map_s equal to this vertex as current value of num

            // This will count all the vertices connected to node in this new subgraph
            int temp_count = 0; // temp count = 0
            // for every edge of current vertex node
            for (int j = 0; j < Graph[node].size(); ++j) {
                // Graph[node][j] is the vertex connected to node by edge j
                // if the array value of that vertex does NOT = 0 
                // AND that vertex does NOT equal node
                if (array[Graph[node][j]] != 0 && Graph[node][j] != node) {
                    temp_count++; // increase count by 1
                }
            }
            // This will add all the vertices connected to node to num's array
            // the size of num's array is set to the amount of vertices connected to node
            new_graph[num].resize(temp_count);
            temp_count = 0; // reset temp_count to 0
            // for every edge of vertex node
            for (int j = 0; j < Graph[node].size(); ++j) {
                // Graph[node][j] is the vertex connected to node by edge j
                // if the array value of that vertex does NOT = 0 
                // AND that vertex does NOT equal node
                if (array[Graph[node][j]] != 0 && Graph[node][j] != node) {
                    // sets up all the vertices connected to node in num's array
                    new_graph[num][temp_count] = Graph[node][j];
                    temp_count++;
                }
            }
            num++; // increase num by 1
        }
        // for every vertex in the new subgraph, update their value in array to = 0
        for (int i = 0; i < count; ++i) {
            int update = temp_list[i];
            array[update] = 0;
        }

        // this is setting up vertex connections in some manner, but I don't understand the nature
        // of map_s enough to really figure that out.
        // for every vertex in the new subgraph
        for (int i = 0; i < count; ++i) {
            // for every edge of i
            for (int j = 0; j < new_graph[i].size(); ++j) {
                new_graph[i][j] = map_s[new_graph[i][j]];
            }
        }

        // creates new KList with the subgraph graph and size of the motif
        KList f(new_graph, motif_size);
        // finds motif degrees of all vertices in this subgraph
        // NOTE: this works differently from ListFast, and it has to do with a:0, but I'd rather focus on
        // getting through this than getting deep into another KList function for now
        f.ListOne(0);
        // sets t_a as the list of motif degrees of the vertices in the subgraph
        std::vector<long> t_a = f.getMotifDegree();
        // create new map result which will be returned as final product
        std::unordered_map<int, long> result;
        // for every vertex in the subgraph
        for (int i = 1; i < t_a.size(); ++i) {
            // if vertex i's motif_degree > 0
            if (t_a[i] > 0)
                // add the vertex in map_array and its motif degree to result
                result[map_array[i]] = t_a[i];
        }
        // returns result, which is a map of vertices and their motif degrees in the pruned subgraph
        return result;
}
