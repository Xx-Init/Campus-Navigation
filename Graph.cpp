#include "head.h"
#include "Graph.h"

using namespace std;

Graph:: Graph(){
    tot = 0; nodeSz = 0;
    memset(head, 0, sizeof(head));
    V.push_back(Node1{string("ECNU"), true});   // The node of the storage location starts at 1
    options[string("print")] = 1;
    options[string("insert")] = 2;
    options[string("delete")] = 3;
    options[string("exit")] = 4;
}

void Graph:: option(){
    string op1, op2;
    int u, v, w;
    string place1, place2;
    cout<< "Please select action:\n1 print: output place and road information\n";
    cout<< "2 insert: insert place/road information\n";
    cout<< "3 delete: delete place/road information\n";
    cout<< "4 exit: log out\n";
    cin>> op1;
    switch (options[op1]){
    case 1:
        print();
        break;
    case 2:
        cout<< "Please select the desired insert action\n1: place     2: road\n";
        cin>> op2;
        if(op2 == "place"){
            cout<< "Please input place\n";
            cin>> place1;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u == V.size()){ 
                V.push_back(Node1{place1, true}); 
                nodeSz ++;
                cout<< "Insert place successully!\n";
            }else{
                cout<< "The place has existed!\n";
            }
        }else{
            cout<< "Please input place1, place2 and distance\n";
            cin>> place1>> place2>> w;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u == V.size()){ V.push_back(Node1{place1, true}); nodeSz ++;}
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(v == V.size()){ V.push_back(Node1{place2, true}); nodeSz ++;}
            ins_edge(u, v, w);
        }
        break;
    case 3:
        cout<< "Please select the desired delete action\n1: place     2: road\n";
        cin>> op2;
        if(op2 == "place"){
            cout<< "Please input place\n";
        }else{
            cout<< "Please input place1, place2\n";
            cin>> place1>> place2;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u == V.size()) V.push_back(Node1{place1, true});
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(v == V.size()) V.push_back(Node1{place2, true});
            del_edge(u, v);
        }
        break;
    case 4:
        cout<< "Exit successfully!\n";
        exit(0);
    default:
        cout<< "Unknown operation! Please enter the correct instructions!\n";
    }
    cout<< endl;
}

void Graph:: ins_edge(int u, int v, int w){
    bool found = false;
    for(int i = head[u]; i; i = e1[i].nxt){
        int to = e1[i].to;
        if(to == v){
            if(e1[i].dis == inf){
                e1[i].dis = w;
                cout<< "Insert successfully!\n";
            }else{
                cout<< "The edge has existed, modify successfully!\n";
                e1[i].dis = w;
            }
            found = true;
            break;
        }    
    }
    if(!found){
        cout<< "Insert successfully!\n";
        e1[++ tot].nxt = head[u];
        e1[tot].to = v;
        e1[tot].dis = w;
        head[u] = tot;

        e1[++ tot].nxt = head[v];
        e1[tot].to = u;
        e1[tot].dis = w;
        head[v] = tot;
    }
    print();
}

void Graph::del_edge(int u, int v){
    if(!head[u] || !head[v]) cout<< "The edge connecting "<< V[u].name<< " and "<< V[v].name<< " does not exist!\n ";
    else{
        bool exist = true;
        for(int i = head[u]; i && exist; i = e1[i].nxt){
            int to = e1[i].to;
            if(to == v){
                if(e1[i].dis == inf)
                    cout<< "The edge connecting "<< V[u].name<< " and "<< V[v].name<< " has been deleted!\n ";
                else
                    e1[i].dis = inf, cout<< "Delete successfully!\n";
                exist = false;
                break;
            }
        }
        for(int i = head[v]; i && exist; i = e1[i].nxt){
            int to = e1[i].to;
            if(to == u){
                e1[i].dis = inf;
                break;
            }
        }
    }

    print(); 
}

void Graph:: dfs(int u, int fa){
    vis[u] = 1;
    for(int i = head[u]; i; i = e1[i].nxt){
        int v = e1[i].to;
        if(v == fa || vis[v]) continue;
        if(e1[i].dis == inf) continue;
        cout<< V[u].name<< ' '<< V[e1[i].to].name<< ' '<< e1[i].dis<< endl;
        dfs(v, u);
    }
}

void Graph:: print(){   
    cout<< "Below is the current place information!\n";
    for(int i = 1; i <= nodeSz; i ++){
        cout<< V[i].name<< ' ';
    }
    cout<< "\nBelow is the current place information!\n";
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    for(int i = 1; i <= nodeSz; i ++)   
        if(!vis[i])
            dfs(i, 0);
    cout<< "Finish!\n";
    delete vis;
}