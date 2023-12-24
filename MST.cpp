#include "head.h"
#include "MST.h"

MST:: MST(int num){
    totNum = num/2;
    minDis = inf;
    head = new int [num+3];
    fill(head, head+num+3, 0);
    numOfEdge = numOfPlace = 0;
    tot = 0;
    e1 = new Edge1 [num+3]; // the original graph
    e2 = new Edge2 [num+3]; // the minimum spainning tree
    dis = new int*[totNum+2];
    for(int i = 0; i < totNum+2; i ++){
        dis[i] = new int [totNum+2];
        fill(dis[i], dis[i]+totNum+2, inf);
    }
}

MST:: ~MST(){
    delete head;
    delete e1;
    delete e2;
    delete dis;
    places.clear();
}

void MST:: insert(int u, string place1, int v, string place2, int w){ 
    if(!places.count(u)) numOfPlace ++, places.insert(u), int_to_places[u] = place1;
    if(!places.count(v)) numOfPlace ++, places.insert(v), int_to_places[v] = place2;
    e1[numOfEdge].u = u;
    e1[numOfEdge].v = v;
    e1[numOfEdge++].w = w;  
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
    // store distance for flody
    UF uf{numOfEdge+10};
    sort(e1, e1+numOfEdge); // sort edge weights (ascending to minimum spanning tree)
    int cnt = 0;
    for(int i = 0 ; i < numOfEdge; i ++){
        int tmp_u = uf.find(e1[i].u), tmp_v = uf.find(e1[i].v);
        if(tmp_u == tmp_v){ // if two points are connected, then the edge is not needed
            continue;
        }
        uf.merge(tmp_u, tmp_v);
        add(e1[i].u, e1[i].v, e1[i].w);
        dis[e1[i].u][e1[i].v] = dis[e1[i].v][e1[i].u] = e1[i].w;
        if(++ cnt == numOfPlace-1){  // the end condition of the loop--the number of edges is the points minus one
            break;
        }
    }
}

void MST:: floyd(){// using floyd to calculate the shortest circuit of all sources
    for (int k = 1; k <= totNum; k++) {
        for (int i = 1; i <= totNum; i++) {
            for (int j = 1; j <= totNum; j++) {
                if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

vector<int> MST:: findOptOrder(vector<int>& places){ // dfs to find the order with the shortest path length
    vector<int> optOrder;
    do{  // traverses all access orders for fixed nodes
        int tmp = 0;
        for(int i = 1; i < places.size(); i ++)
            tmp += dis[places[i-1]][places[i]];
        if(tmp < minDis){
            minDis = tmp;
            optOrder = places;
        }
    }while(next_permutation(places.begin(), places.end())); 
    return optOrder;
}

void MST:: dfs_UtoTar(int u, int fa, int tar, vector<int>& path){ // dfs to find the only path from u to tar
    path.push_back(u);
    if(u == tar) return;
    for(int i = head[u]; i; i = e2[i].nxt){
        int v = e2[i].to;
        if(v == fa) continue;
        dfs_UtoTar(v, u, tar, path);
        if(*path.rbegin() != tar) path.pop_back(); // if the current road can go from u to tar, not change
    }
}

vector<int> MST:: getPath(vector<int>& places){
    vector<int> path;
    path.push_back(places[0]);
    for(int i = 1; i < places.size(); i ++){
        int u = *path.rbegin(), v = places[i];
        path.pop_back();
        dfs_UtoTar(u, 0, v, path);
    }
    return path;
}

void MST:: dfsMST(int u, int fa){
    vis[u] = 1;
    for(int i = head[u]; i; i = e2[i].nxt){
        int v = e2[i].to;
        if(vis[v]) continue;
        cout<< int_to_places[u]<< ' '<< int_to_places[v]<< ' '<< e2[i].dis<< endl;
        dfsMST(v, u);
    }   
}
void MST:: printMST(){
    cout<< "******************** [---Begin---] Outputs the minimum spanning tree ******************** \n";
    cout<< "There are "<< numOfPlace<< " on the minimum spanning tree\n";
    for(auto i: int_to_places){
        cout<< i.second<< ' ';
    }
    cout<< endl;
    vis = new int[totNum+1];
    fill(vis, vis+totNum+2, 0);
    dfsMST(e1[0].u, 0);
    cout<< "******************** [---Finish---] Outputs the minimum spanning tree ******************** \n";

}