#ifndef MST_H
#define MST_H

#include "head.h"
#include "UF.h"

class MST{
private:
    int *head, tot, numOfEdge, numOfPlace;
    set<int> places;
    struct Edge1{
        int u, v, w;
        bool operator < (const Edge1& o) const{
            return w < o.w;
        }
    }*e1;

    struct Edge2{
        int to, nxt, dis;
    }*e2;

public:
    MST(int);

    ~MST();

    void add(int, int, int);

    void insert(int, int, int);

    void kruskal();

};


#endif