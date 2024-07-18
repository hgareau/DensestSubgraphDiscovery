#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "KList.h"
#include "KCore.h"

    KList::KList(std::vector<std::vector<int>> graph, int k)
    {
        GenGraph = graph;
        this->graph = std::move(graph);
        this->k = k;
        graph_size = static_cast<int>(this->graph.size());
        order.resize(graph_size);
        degree.resize(graph_size);
        label.resize(graph_size, k);
        motif_degree.resize(graph_size, 0);
        Adjlist.resize(graph_size);
    }

    //sets up order[]
    void KList::getListingOrder()
    {
        // KCore and decompose() gets an array of the k-core values for every vertex in the graph
        // (This is not CDS decomp though, it's for edges not motifs)
        std::vector<int> temp_arr = KCore(GenGraph).obtainReverseCoreArr();

        // for every vertex in the graph
        for (int i = 0; i < graph_size; ++i) {
            // set this vertex's order to its core value + 1
            order[temp_arr[i]] = i + 1;
        }
    }

    // This will set up graph[][] as a DAG
    // A DAG is a directed graph with no loops
    void KList::GenerateDAG()
    {
        // Need to create a new adjacency list such that no loops exist
        // for every vertex in the graph, set up
        for (int i = 0; i < graph_size; ++i) {
            int count = 0; // reset count to = 0
            // for every edge from i to j
            for (int j = 0; j < GenGraph[i].size(); ++j) {
                // if order of i is < the order of the vertex connected to i
                if (order[i] < order[GenGraph[i][j]]) {
                    count++; // increase count by 1
                }
            }
            std::vector<int> arr(count); // set size of arr[] to count
            degree[i] = count; // set the degree of vertex i to count
            count = 0; // reset count to 0
            // for every edge from i to j
            for (int j = 0; j < GenGraph[i].size(); ++j) {
                // if order of i is < the order of the vertex connected to i
                if (order[i] < order[GenGraph[i][j]]) {
                    // add the vertex connected to i to arr at current count position
                    arr[count] = GenGraph[i][j];
                    count++; // increase count by 1
                }
            }
            // set list of vertices i points to as arr
            graph[i] = arr;
        }
    }

    //The only difference between this and Listing is the setup of Statistic,
    //which is a map of all the motifs
    void KList::ListingRecord(int k, std::vector<int> c, std::vector<int> arr)
    {
        //if our motif is edge OR the motif size has been reduced to 2
            if(k==2) {
//                  cout<<">>>"<<endl;
                    std::string a=""; //initialize blank string
                    //for every element of c
                    for(int m=0;m<c.size();++m) {
                            //concatenate each element of c + a space inbetween them
                            a+=std::to_string(c[m])+" ";
                    }
                    int multi=0; //initialize multi as 0
                    //for every vertex in arr
                    for(int i=0;i<arr.size();++i) {
                            int temp=arr[i]; //get the vertex as temp
                            //for every vertex connected to temp in the DAG
                            for(int j=0;j<degree[temp];++j) {
//                                  cout<<a+to_string(temp)+" "+to_string(graph[temp][j])<<endl;
                                    //concatenate vertex temp and the vertex connected to it in the DAG to a
                                    a=a+std::to_string(temp)+" "+std::to_string(graph[temp][j]);
                                    multi++; //increase multi by 1
                                    motif_num++; //increase the number of motifs by 1
                                    motif_degree[graph[temp][j]]++; //increase the motif degree of the vertex
                                                                    //connected to temp in the DAG by 1
                                    motif_degree[temp]++; //increase the motif degree of temp by 1
                                    //initialize temp_arr as size of the motif + 1 (?)
                                    std::vector<int> temp_arr(this->k+1);
                                    //add every element of c to temp_arr
                                    for(int m=0;m<c.size();++m) {
                                            temp_arr[m]=c[m];
                                    }
                                    //append the vertex temp, the vertex connected to temp, and 1 to the
                                    //end of temp_arr
                                    temp_arr[this->k-2]=temp;
                                    temp_arr[this->k-1]=graph[temp][j];
                                    temp_arr[this->k]=1;
                                    //cout<<temp_arr[k]<<" "<<k<<endl;
                                    //add the current string a paired with this temp_arr to Statistic
                                    this->Statistic[a] = temp_arr;
                            }
                    }
                    //for every element of c
                    for(int m=0;m<c.size();++m) {
                            int temp=c[m]; //set temp as the element at position m in c
                            motif_degree[temp]+=multi; //add multi to the motif degree of temp
                    }
                    
            }else {
                    //for every element in arr (every vertex in the DAG)
                    for(int i=0;i<arr.size();++i) {
                            int temp=arr[i]; //set temp as the current vertex
                            //int count=0;

                            /*
                             * This for loop sets up arr_n as all the vertices connected to this iteration's
                             * vertex that are in motifs of equal size to this iteration's motif size.
                             */

                            //initialize empty ArrayList arr_n
                            std::vector<int> arr_n;
                            //for every edge connected to temp
                            for(int j=0;j<graph[temp].size();++j) {
                                    //cout<<"****"<<graph[temp][j]<<" "<<" "<<label[graph[temp][j]]<<" "<<k<<endl;
                                    //if the element at the position of the vertex connected to temp by this edge
                                    //in label equals k
                                    if(label[graph[temp][j]]==k) {
                                            label[graph[temp][j]]=k-1; //reduce it by 1
                                            
                                            //count++;
                                            //add that vertex to arr_n
                                            arr_n.push_back(graph[temp][j]);
                                    }                                               
                            }

                            /*
                             * This for loop is a bit more complex, but while I don't understand the intracasies
                             * of it, I can tell its general purpose.
                             * This loop, for every vertex connected to temp (with the correct "current" motif size)
                             * sets the vertex's regular degree, that is to say, its "edge" degree. How many vertices
                             * it is connected to.
                             */

                            //for every vertex in arr_n
                            for(int j=0;j<arr_n.size();++j) {
                                    //int count=0;
                                    //set arr_temp as the vertex at position j in arr_n
                                    int arr_temp=arr_n[j];
                                    int index=0; //set index as 0
                                    //while the number of edges of arr_temp - 1 is greater than index
                                    //REMINDER: graph is the DAG
                                    for(int m=graph[arr_temp].size()-1;m>index;--m) {
                                        //if the element at the position of the vertex connected to arr_temp by edge m
                                        //is equal to k - 1
                                        //ONLY DOES FOLLOWING WHEN CONNECTED VERTEX = K - 1
                                        if(label[graph[arr_temp][m]]==k-1) {
                                                //while index is less than m AND
                                                //the element at the position of the vertex connected to arr_temp by edge index
                                                //is equal to k - 1, increase index by 1
                                                while(index<m&&label[graph[arr_temp][index]]==k-1) {
                                                        index++;
                                                }
                                                //Once of those statments is not true, check if the second one is now false
                                                //If it is...
                                                if(label[graph[arr_temp][index]]!=k-1) {
                                                        //set temp1 as the vertex connected to arr_temp by edge m
                                                        int temp1=graph[arr_temp][m];
                                                        //swap the vertices of the edges connecting arr_temp to m and index
                                                        graph[arr_temp][m]=graph[arr_temp][index];
                                                        graph[arr_temp][index]=temp1;
                                                        
                                                }
                                        }
                                    }
                                    //if the number of edges of arr_temp doesn't equal 0
                                    //AND the element of lebel at the position of the vertex connected to arr_temp
                                    //by edge index = k - 1
                                    if(graph[arr_temp].size()!=0&&label[graph[arr_temp][index]]==k-1)
                                            index++; //increase index by 1
                                    degree[arr_temp]=index; //set the degree of arr_temp to index
                            }

                            /*
                             * The final thing for this vertex is a recursive call.
                             * It adds the vertex to c, then does a recursive call with:
                             * k - 1 ("current" motif size)
                             * c (which contains only vertices added by this and other recursive calls)
                             * arr_n (all the vertices connected to the vertex with the same "current"
                             * motif size)
                             * After this recursive call however, label and c are returned to normal
                             */

                            //add the current vertex of arr to c
                            c.push_back(arr[i]);
                            //recursively call ListingRecord with the number of vertices in the motif reduced by 1,
                            //and the modified lists c and arr_n
                            ListingRecord(k-1,c,arr_n);
                            //remove the vertex that was added to c
                            c.pop_back();
                            //for every vertex in arr_n
                            for(int j=0;j<arr_n.size();++j) {
                                    //set arr_temp as the current vertex
                                    int arr_temp=arr_n[j];
                                    //set label value of arr_temp as k
                                    label[arr_temp]=k;
                            }
                    }
            }
    }

    //This is a recursive function that finds the number of motifs in the graph and the motif degree
    //of every vertex
    void KList::Listing(int k, std::vector<int> c, std::vector<int> arr)
    {
        //if our motif is edge OR the motif size has been reduced to 2
            if(k==2) {
                    
                    std::string a=""; //initialize blank string

                    //for every element of c
                    for(int m=0;m<c.size();++m) {
                            //concatenate each element of c + a space inbetween them
                            a+=std::to_string(c[m])+" ";
                    }
                    int multi=0; //initialize multi as 0
                    //for every vertex in arr
                    for(int i=0;i<arr.size();++i) {
                            int temp=arr[i]; //get the vertex as temp
                            //for every vertex connected to temp in the DAG
                            for(int j=0;j<degree[temp];++j) {
//                                  cout<<a+to_string(temp)+" "+to_string(graph[temp][j])<<endl;
                                    multi++; //increase multi by 1
                                    motif_num++; //increase motif_num by 1
                                    motif_degree[graph[temp][j]]++; //increase the motif degree of the vertex
                                                                    //connected to temp in the DAG by 1
                                    motif_degree[temp]++; //increase the motif degree of temp by 1
                            }
                    }
                    //for every element of c
                    for(int m=0;m<c.size();++m) {
                            int temp=c[m]; //set temp as the element at position m in c
//                          cout<<c[m]<<"####"<<endl;
                            motif_degree[temp]+=multi; //add multi to the motif degree of temp
                    }
                    
            }else { //if our motif is NOT edge
                    
                    //for every vertex in arr
                    for(int i=0;i<arr.size();++i) {
                            int temp=arr[i]; //set temp as the current vertex
                            //int count=0;
                            
                            //initialize new Array List arr_n
                            std::vector<int> arr_n;
                            //for every edge of temp in the DAG
                            for(int j=0;j<graph[temp].size();++j) {
                                    //cout<<"****"<<graph[temp][j]<<" "<<" "<<label[graph[temp][j]]<<" "<<k<<endl;
                                    //if the element at the position of the vertex connected to temp by this edge
                                    //in label equals k
                                    if(label[graph[temp][j]]==k) {
                                            label[graph[temp][j]]=k-1; //reduce it by 1
                                            
                                            //count++;
                                            //then add the connected vertex to arr_n
                                            arr_n.push_back(graph[temp][j]);
                                    }                                               
                            }
                            
                            //for every vertex in arr_n
                            for(int j=0;j<arr_n.size();++j) {
                                    //int count=0;
                                    //set arr_temp as the vertex at position j in arr_n
                                    int arr_temp=arr_n[j];
                                    int index=0; //initialize index as 0
                                    //while the number of edges of arr_temp - 1 is greater than index
                                    //REMINDER: graph is the DAG
                                    for(int m=graph[arr_temp].size()-1;m>index;--m) {
                                            //if the element at the position of the vertex connected to arr_temp by edge m
                                            //is equal to k - 1
                                            if(label[graph[arr_temp][m]]==k-1) {
                                                    //while index is less than m AND
                                                    //the element at the position of the vertex connected to arr_temp by edge index
                                                    //is equal to k - 1, increase index by 1
                                                    while(index<m&&label[graph[arr_temp][index]]==k-1) {
                                                            index++;
                                                    }
                                                    //if the element at the position of the vertex connected to arr_temp by edge index
                                                    //is NOT equal to k - 1
                                                    if(label[graph[arr_temp][index]]!=k-1) {
                                                            //set temp1 as the vertex connected to arr_temp by edge m
                                                            int temp1=graph[arr_temp][m];
                                                            //swap the vertices of the edges connecting arr_temp to m and index
                                                            graph[arr_temp][m]=graph[arr_temp][index];
                                                            graph[arr_temp][index]=temp1;
                                                            
                                                    }
                                            }
                                    }
                                    //if the number of edges of arr_temp doesn't equal 0
                                    //AND the element of lebel at the position of the vertex connected to arr_temp
                                    //by edge index = k - 1
                                    if(graph[arr_temp].size()!=0&&label[graph[arr_temp][index]]==k-1)
                                            index++; //increase index by 1
                                    degree[arr_temp]=index; //set the degree of arr_temp to index
                            }
                            //add the current vertex of arr to c
                            c.push_back(arr[i]);
                            //recursively call Listing with the number of vertices in the motif reduced by 1,
                            //and the modified lists c and arr_n
                            Listing(k-1,c,arr_n);
                            //Then remove that vertex from c
                            c.pop_back();
                            //for every vertex in arr_n
                            for(int j=0;j<arr_n.size();++j) {
                                    //set arr_temp as the current vertex
                                    int arr_temp=arr_n[j];
                                    //set label value of arr_temp as k
                                    label[arr_temp]=k;
                            }
                    }
            }
    }

    //map always = 0?
    //This is another algorithm for finding the motif degrees of every vertex
    //However, this is different as it is based around one node, map.
    //What it changes I'm unsure of. I can understand the code, but I don't understand
    //what it's doing really.
    void KList::Listing(int k, std::vector<int> &c, std::vector<int> &arr, int map)
    {
        //if our motif is edge OR the motif size has been reduced to 2
        if(k==2) {
            bool onenode=false; //set this boolean as false
            std::string a=""; //initialize this blank string
            //for every element of c
            for(int m=0;m<c.size();++m) {
                //concatenate each element of c + a space inbetween them
                a+=std::to_string(c[m])+" ";
                //if element m of c = the value map
                if(c[m]==map) {
                    //set boolean to true
                    onenode=true;
                }
            }
            int multi=0; //initialize multi as 0
            //for every element of arr
            for(int i=0;i<arr.size();++i) {
                //set temp as vertex i in arr
                int temp=arr[i];
                //for every edge connected to temp
                for(int j=0;j<degree[temp];++j) {
                    //if: the onenode boolean is true OR temp vertex is the same as map
                    //OR the vertex connected to temp by edge j is the same as map
                    if(onenode||temp==map||graph[temp][j]==map) {
                        multi++; //increase multi by 1
                        motif_num++; //increase number of motifs by 1
                        //increase the motif degrees of vertex temp and the vertex
                        //connected to it by edge j by 1
                        motif_degree[graph[temp][j]]++;
                        motif_degree[temp]++;
                    }
                }
            }
            //for every element in c
            for(int m=0;m<c.size();++m) {
                int temp=c[m]; //set temp as the element at position m in c
                motif_degree[temp]+=multi; //increase temp's motif degree by multi
            }
        } else {
            //for every vertex in arr
            for(int i=0;i<arr.size();++i) {
                //set temp as vertex i in arr
                int temp=arr[i];
                //int count=0;
                //initialize a new vector
                std::vector<int> arr_n;
                //for every edge of temp
                for(int j=0;j<graph[temp].size();++j) {
                    //if the element at the position of the vertex connected to temp by this edge
                    //in label equals k
                    if(label[graph[temp][j]]==k) {
                        label[graph[temp][j]]=k-1; //reduce it by 1
                        //count++;
                        //then add the connected vertex to arr_n
                        arr_n.push_back(graph[temp][j]);
                    }                                               
                }
                //for every vertex in arr_n
                for(int j=0;j<arr_n.size();++j) {
                    //int count=0;
                    //get vertex j in arr_n
                    int arr_temp=arr_n[j];
                    int index=0; //set index to 0
                    //while the number of edges of arr_temp - 1 is greater than index
                    //REMINDER: graph is the DAG
                    for(int m=graph[arr_temp].size()-1;m>index;--m) {
                        //if the element at the position of the vertex connected to arr_temp by edge m
                        //is equal to k - 1
                        if(label[graph[arr_temp][m]]==k-1) {
                            //while index is less than m AND
                            //the element at the position of the vertex connected to arr_temp by edge index
                            //is equal to k - 1, increase index by 1
                            while(index<m&&label[graph[arr_temp][index]]==k-1) {
                                index++;
                            }
                            //if the element at the position of the vertex connected to arr_temp by edge index
                            //is NOT equal to k - 1
                            if(label[graph[arr_temp][index]]!=k-1) {
                                //set temp1 as the vertex connected to arr_temp by edge m
                                int temp1=graph[arr_temp][m];
                                //swap the vertices of the edges connecting arr_temp to m and index
                                graph[arr_temp][m]=graph[arr_temp][index];
                                graph[arr_temp][index]=temp1;
                            }
                        }
                    }
                    //if the number of edges of arr_temp in the DAG does NOT equal 0
                    //AND the label value at the position equal to the vertex connected to
                    //arr_temp by index = k-1
                    if(graph[arr_temp].size()!=0&&label[graph[arr_temp][index]]==k-1)
                        index++; //increase index by 1
                    degree[arr_temp]=index; //set the degree of arr_temp as index
                }
                //add vertex i in arr to c
                c.push_back(arr[i]);
                //recursive call with updated values
                Listing(k-1,c,arr_n,map);
                //remove vertex i from c
                c.pop_back();
                //for every vertex in arr_n
                for(int j=0;j<arr_n.size();++j) {
                    //set arr_temp as vertex j in arr_n
                    int arr_temp=arr_n[j];
                    label[arr_temp]=k; //set the label value of arr_temp as k
                }
            }
        }
    }

    // finds the motif degrees of every vertex
    void KList::ListFast()
    {
        // sets up order[] to be filled with the core value of every vertex + 1
        getListingOrder();
        // sets up graph as an adjacency list. A modified version of GenGraph (the original graph)
        // such that no loops exist in it
        GenerateDAG();
        // generate new array lists c and arr
        std::vector<int> c;
        std::vector<int> arr;
        // for every vertex in the graph, put its own vertex number in its slot
        for (int i = 0; i < graph_size; ++i) {
            arr.push_back(i);
        }
        // Modifies certain variables
        Listing(k, c, arr);
    }

    // This method sets up then runs ListingRecord.
    // This finds the number of motifs in the graph, the motif degree of every vertex, and the map Statistic
    // of every vertex
    void KList::ListRecord()
    {
        // sets up order[] to be filled with the core value of every vertex + 1
        getListingOrder();
        // sets up graph as an adjacency list. A modified version of GenGraph (the original graph)
        // such that no loops exist in it
        GenerateDAG();
        // generate new array lists c and arr
        std::vector<int> c;
        std::vector<int> arr;
        // for every vertex in the graph, put its own vertex number in its slot
        for (int i = 0; i < graph_size; ++i) {
            arr.push_back(i);
        }
        // Modifies certain variables
        ListingRecord(k, c, arr);
    }

    void KList::ListOne(int a)
    {
        // sets up order[] to be filled with the core value of every vertex + 1
        getListingOrder();
        // sets up graph as an adjacency list. A modified version of GenGraph (the original graph)
        // such that no loops exist in it
        GenerateDAG();
        // generate new array lists c and arr
        std::vector<int> c;
        std::vector<int> arr;
        // for every vertex in the graph, put its own vertex number in its slot
        for (int i = 0; i < graph_size; ++i) {
            arr.push_back(i);
        }
        // Modifies certain variables
        Listing(k, c, arr, a);
    }

    int KList::getMotifNum()
    {
        return motif_num;
    }

    std::vector<long> KList::getMotifDegree()
    {
        return motif_degree;
    }
