#ifndef MST_H
#define MST_H

#include "head.h"
#include "UF.h"

class MST{
private:
    int *head, tot, numOfEdge, numOfPlace, totNum, *vis;
    unordered_map<int, string> int_to_places; // map from placeID to place name
    set<int> places;
    struct Edge1{
        int u, v, w;
        bool operator < (const Edge1& o) const{ // sort the edges to build a minimum spanning tree
            return w < o.w;
        }
    }*e1;

    struct Edge2{
        int to, nxt, dis;
    }*e2; // for minimum spanning tree

    int ** dis; // store distance

    void dfs_UtoTar(int , int ,int , vector<int>&); // get path from u to tar

    void dfsMST(int, int); // dfs to traverse the MST
public:
    int minDis; // store the shortest distance

    MST(int);

    ~MST();

    void add(int, int, int); // add edge to spaning tree->e2

    void insert(int, string, int, string, int); // insert the required edge into MTS->e1

    void kruskal(); // using kruskal to build minimum spaning tree

    void flody(); // calculate the shortest circuit of all sources

    vector<int> findOptOrder(vector<int>&); // find order of minimum path through all fixed places

    vector<int> getPath(vector<int>&); // get the complete shortest path

    void printMST(); // print the MST
};


#endif