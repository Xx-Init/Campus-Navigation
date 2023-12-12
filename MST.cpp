#include "head.h"
#include "MST.h"

MST:: MST(int num){
    head = new int [num+3];
    numOfEdge = numOfPlace = 0;
    tot = 0;
    e1 = new Edge1 [num+3];
    e2 = new Edge2 [num+3];
}

MST:: ~MST(){
    delete head;
    delete e1;
    delete e2;
    places.clear();
}

void MST:: insert(int u, int v, int w){
    if(!places.count(u)) numOfPlace ++, places.insert(u);
    if(!places.count(v)) numOfPlace ++, places.insert(v);
    e1[numOfEdge ++].u = u;
    e1[numOfEdge].v = v;
    e1[numOfEdge].w = w;  
}

void MST:: add(int u, int v, int w){
    e2[++ tot].nxt = head[u];
    e2[tot].to = v;
    e2[tot].dis = w;
    head[u] = tot;

    e2[++ tot].nxt = head[v];
    e2[tot].to = u;
    e2[tot].dis = w;
    head[v] = tot;
}

void MST:: kruskal(){
    UF uf{numOfEdge+10};
    sort(e1, e1+numOfEdge); //将边的权值排序(升序为最小生成树)
    int cnt = 0;
    for(int i = 0 ; i < numOfEdge; i ++){
        cout<< e1[i].u<< ' '<< e1[i].v<< endl;
        int tmp_u = uf.find(e1[i].u), tmp_v = uf.find(e1[i].v);
        if(tmp_u == tmp_v){ //若出现两个点已经联通了，则说明这一条边不需要了
            continue;
        }
        uf.merge(tmp_u, tmp_v);
        add(e1[i].u, e1[i].v, e1[i].w);
        if(++ cnt == numOfPlace-1){  //循环结束条件，及边数为点数减一时
            break;
        }
    }
}