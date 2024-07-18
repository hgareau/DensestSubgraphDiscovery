#include <iostream>
#include <unordered_map>
#include <queue>
#include <climits>
#include <vector>
#include "FindMinCut.h"

/**
* Constructor
* @param FlowNetwork data structure used to record flow network
* @param s source vertex
* @param t sink vertex
*/
FindMinCut::FindMinCut(std::vector<std::unordered_map<int, std::vector<double>>> FlowNetwork, int s, int t)
{
    this->FlowNetwork = FlowNetwork;
    this->s = s;
    this->t = t;
}

/**
* EK algorithm to solve the max-flow problem
* the min-cut(S-T) is saved in the array 'parent'
* S: parent[i] > -1
* T: parent[i] == -1
* @return the value of max flow
*/
double FindMinCut::EdmondsKarp()
{
    // sets parent as a vector the size of the Flow Network
    parent = std::vector<int>(FlowNetwork.size(), -1);
        
    // find the max flow along the shortest path in the graph
    double result = augmentPath(parent);
    double sum = 0;
    std::vector<double> temp;
        
    // while result does NOT equal -1 (aka there are still paths remaining)
    while (result != -1) {
        int cur = t; // set cur (current vertex) as t
            
        // while cur is NOT s (still going back through the current path from s to t)
        while (cur != s) {
            // set temp as the flow/capacity of the edge from cur's parent to cur
            temp = FlowNetwork[parent[cur]][cur];
            // set flow of the edge as its flow - max flow along path
            temp[0] = temp[0] - result;
            // set temp as the flow/capacity of the edge from cur to cur's parent
            temp = FlowNetwork[cur][parent[cur]];
            // set the flow of edge as its flow + max flow along the path
            temp[0] = temp[0] + result;
            // set cur as its parent
            cur = parent[cur];
        }
            
        // add the max flow along the path to sum (which will be max flow in the graph)
        sum += result;
            
        // find the max flow along the next shortest path in the graph
        result = augmentPath(parent);
    }
        
    // returns the maximum flow of the graph
    return sum;
}

/**
* use BFS algorithm to find the augment path. 
* @param parent the array to save the path
* @return the minimum capacity of each edge in the path
*/
//Note: This does two things. Augments parent to be the next shortest traversable
//path from s to t AND returns the max flow that can be sent along this path.
double FindMinCut::augmentPath(std::vector<int> &parent)
{
    // sets max flow as the maximum possible int value so it can be easily reset
    double maxflow = INT_MAX;
        
    // fill the parent vector with -1s
    fill(parent.begin(), parent.end(), -1);
        
    // create a queue of integers and add source to it
    std::queue<int> q;
    q.push(s);
        
    // put source in the position equal to its id in parent
    parent[s] = s;
    std::vector<double> temp;
        
    //This while loop does the BFS until it reaches sink, signaling a finished path
	//Then it sets up this path and the max flow along it
	//while the queue is NOT empty
    while (!q.empty()) {
        // set p as the current vertex
        int p = q.front();
        q.pop();
            
        // if p is the sink
        if (p == t) {
            // while p is NOT s
            while (p != s) {
                // set temp as the parent of p
                temp = FlowNetwork[parent[p]][p];
                // if the maximum flow is greater than the value of p's flow, set maxflow to that flow
                if (maxflow > temp[0])
                    maxflow = temp[0];
                // set p as its parent
                p = parent[p];
            }
            break; // exit the loop for "while queue is empty"
        }
            
        // for every vertex connected to p
        for (auto& entry : FlowNetwork[p]) {
            temp = entry.second; // set temp as the key-value pair of this vertex
            // if the vertex (entry's key) has no parent AND capacity (or flow?) > 0
            if (parent[entry.first] == -1 && temp[0] > 0) {
                // set the vertex as a parent of p
                parent[entry.first] = p;
                // adds the vertex to the queue
                q.push(entry.first);
            }
        }
    }
        
    // if the parent of t is -1 (it has no parent aka no remaining path)
    if (parent[t] == -1) {
        // get the min-cut
        return -1;
    }
        
    // otherwise, return the max flow
    return maxflow;
}

std::vector<int> FindMinCut::getparent()
{
    return parent;
}
