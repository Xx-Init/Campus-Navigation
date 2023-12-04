#ifndef GRAPH_H
#define GRAPH_H

#include "head.h"

using namespace std;

const int maxSize = 2e4+2;

class Graph{
private:
    int head[maxSize], tot;
    int *vis;  // dfs records whether a location has been visited while traversing
    
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
    
    void dfs(int, int);

public:
    Graph();

    void option();

    void ins_edge(int, int, int); // insert_edge

    void del_edge(int, int); // delete_edge

    void del_place(int); // delete_place

    void print();  // print current place and road information
};

#endif