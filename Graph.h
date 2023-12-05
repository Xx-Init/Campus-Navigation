#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"

using namespace std;

const int maxSize = 2e4+2;

class Graph{
private:
    int head[maxSize], tot; // use adjacency lists to store graphs
    int *vis, *pre, *dis;  
    // vis: dfs records whether a location has been visited while traversing
    // pre: used to output the shortest path
    // dis: used to output the shortest distance
    struct Node1{
        string name;
        bool existed;
        bool operator == (const string &name){ // overloaded operation
            return (this->name == name);
        }
    };
    
    vector<Node1> V;  // record the name of the place and whether the place has not been deleted
    int nodeSz; // the number of node
    
    struct Edge1{
        int to, nxt, dis;
    }e1[maxSize<< 1];
    
    unordered_map<string, int> options;
    
    void dfs(int, int); // dfs traverses the graph

    void dijkstra(int); // dijkstra algorithm is used to calculate the shortest path

    void showPath(int); // show path

    struct Node2{ // used for dijkstra algorithm
        int dis, v;
        bool operator > (const Node2& o) const{
            return dis > o.dis;
        }
    }; 

public:
    Graph();

    void option();

    void ins_edge(int, int, int); // insert_edge

    void del_edge(int, int); // delete_edge

    void del_place(int); // delete_place

    void getShortestPath(int, int); // compute the shortestpath
    
    void print();  // print current place and road information
};

#endif