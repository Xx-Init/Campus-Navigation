#include "head.h"
#include "Graph.h"

Graph:: Graph(){
    tot = 0; nodeSz = 0;
    memset(head, 0, sizeof(head));
    V.push_back(Node1{string("ECNU"), true});   // The node of the storage location starts at 1
    options[string("print")] = 1;
    options[string("insert")] = 2;
    options[string("delete")] = 3;
    options[string("compute")] = 4;
    options[string("exit")] = 5;
    importFile();
}

void Graph:: importFile(){
    ifstream ifs;
    ifs.open("map.csv", ios:: in);
    string place1, place2;
    int dis;
    while(ifs>> place1>> place2>> dis){
        cout<< place1<< ' '<< place2<< ' '<< dis<< endl;
        int u = find(V.begin(), V.end(), place1)-V.begin();
        if(u == V.size()) V.push_back(Node1{place1, true}), nodeSz ++;
        int v = find(V.begin(), V.end(), place2)-V.begin();
        if(v == V.size()) V.push_back(Node1{place2, true}), nodeSz ++;
        ins_edge(u, v, dis);
    }
    cout<< "Initialize successfully!\n";
    ifs.close();
}

void Graph:: option(){ // select options and implement the transformation of input information
    string op1, op2;
    cout<< "Press any key to continue!\n";
    char c = getchar();
    print();
    int op3;
    int u, v, w, numOfPlaces;
    string place1, place2;
    cout<< "Please select action:\n1 print: output place and road information.\n";
    cout<< "2 insert: insert place/road information.\n";
    cout<< "3 delete: delete place/road information.\n";
    cout<< "4 compute: compute some information.\n";
    cout<< "5 exit: log out.\n";
    cin>> op1;
    switch (options[op1]){
    case 1:
        print();
        break;
    case 2:
        cout<< "Please select the desired insert action.\n1: place     2: road\n";
        while(cin>> op2){
            if(op2 != "place" && op2 != "road") 
                cout<< "Unknown action! Please select the desired delete action.\n1: place     2: road\n";
            else break;
        };
        if(op2 == "place"){
            cout<< "Please input place\n";
            cin>> place1;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u == V.size()){ 
                V.push_back(Node1{place1, true}); 
                nodeSz ++;
                cout<< "Insert place successully!\n";
            }else{
                if(!V[u].existed){
                    V[u].existed = true;
                    cout<< "Insert place successully!\n";
                }else
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
        print();
        break;
    case 3:
        cout<< "Please select the desired delete action.\n1: place     2: road\n";
        while(cin>> op2){
            if(op2 != "place" && op2 != "road") 
                cout<< "Unknown action! Please select the desired delete action.\n1: place     2: road\n";
            else break;
        };
        if(op2 == "place"){
            cout<< "Please input place\n";
            cin>> place1;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u != V.size())
                del_place(u);
            else
                cout<< "The place does not exist!\n";
        }else{
            cout<< "Please input place1, place2\n";
            cin>> place1>> place2;
            u = find(V.begin(), V.end(), place1)-V.begin();
            if(u == V.size()) V.push_back(Node1{place1, true});
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(v == V.size()) V.push_back(Node1{place2, true});
            del_edge(u, v);
        }
        print();
        break;
    case 4: 
        cout<< "Please select the desired compute action.(Enter an option, such as 1)\n";
        cout<< "1: get the shortest path between two places\n";
        cout<< "2: get the shortest path through a fixed number of locations\n";
        cout<< "3: get the shortest path through a fixed number of locations\n";
        cout<< "4: get the shortest path through a fixed number of locations\n";
        while(cin>> op3){
            if(op3 < 1 || op3 > 4) cout<< "Unknown action! Please try again!\n";
            else break;
        }
        switch (op3){
        case 1:
            cout<< "Please input place1 and place2.\n";
            cin>> place1>> place2;
            u = find(V.begin(), V.end(), place1)-V.begin();
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(u == V.size() || ! V[u].existed){
                cout<< place1<<" does not existed!\n";
                break;
            }else if(v == V.size() || ! V[v].existed){
                cout<< place2<<" does not existed!\n";
                break;
            }
            getShortestPath(u, v);
            break;
        case 2:
            cout<< "Please input place1, place2 and place numbers.\n";
            cin>> place1>> place2>> numOfPlaces;
            u = find(V.begin(), V.end(), place1)-V.begin();
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(u == V.size() || ! V[u].existed){
                cout<< place1<<" does not existed!\n";
                break;
            }else if(v == V.size() || ! V[v].existed){
                cout<< place2<<" does not existed!\n";
                break;
            }
            findPathThroNumPlaces(u, v, numOfPlaces);
            break;
        case 3:
            break;
        case 4:
            break;
        }
        break;
    case 5:
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
                if(i&1) e1[i+1].dis = w;
                else e1[i-1].dis = w;
                cout<< "Insert successfully!\n";
            }else{
                cout<< "The edge has existed, modify successfully!\n";
                e1[i].dis = w;
                if(i&1) e1[i+1].dis = w;
                else e1[i-1].dis = w;
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
}

void Graph::del_edge(int u, int v){
    if(!head[u] || !head[v]) cout<< "The edge connecting "<< V[u].name<< " and "<< V[v].name<< " does not exist!\n ";
    else{
        for(int i = head[u]; i ; i = e1[i].nxt){
            int to = e1[i].to;
            if(to == v){
                if(e1[i].dis == inf)
                    cout<< "The edge connecting "<< V[u].name<< " and "<< V[v].name<< " has been deleted!\n ";
                else{
                    e1[i].dis = inf;
                    if(i&1) e1[i+1].dis = inf;
                    else e1[i-1].dis = inf;
                    cout<< "Delete successfully!\n";
                }
                break;
            }
        }
    }
}

void Graph:: del_place(int u){
    V[u].existed = false;
    for(int i = head[u]; i; i = e1[i].nxt){
        int v = e1[i].to;
        if(e1[i].dis == inf) continue;
        else{
            e1[i].dis = inf;
            if(i&1) e1[i+1].dis = inf;
            else e1[i-1].dis = inf;
        }
    }
    cout<< "Delete place successfully!\n";
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

vector<int> Graph:: getPath(int now){
    vector<int> path;
    while(pre[now] != -1){
        path.push_back(now);
        now = pre[now];
    }
    path.push_back(now);
    return path;
}

void Graph:: dijkstra(int s){
    priority_queue<Node2, vector<Node2>, greater<Node2>> q;
    q.push({0, s});
    while(!q.empty()){
        int u = q.top().v;
        q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = e1[i].nxt){
            int v = e1[i].to, w = e1[i].dis;
            if(dis[v] > dis[u]+w){
                dis[v] = dis[u]+w;
                pre[v] = u;
                q.push({dis[v], v});
            }
        }
    }
}

void Graph:: getShortestPath(int u, int v){
    pre = new int[nodeSz+1];
    dis = new int[nodeSz+1];
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    fill(dis, dis+nodeSz+1, inf);
    fill(pre, pre+nodeSz+1, 0);
    pre[u] = -1;
    dis[u] = 0;
    dijkstra(u);
    if(dis[v] == inf) 
        cout<< "There is no path from "<< V[u].name<< " to "<< V[v].name<< "!\n";
    else{
        cout<< "The shortest path length is "<< dis[v]<< endl;
        vector<int> path = getPath(v);
        int sz = path.size();
        for(int i = sz-1; i > 0; i --){
            cout<<V[path[i]].name<< "->";
        }
        cout<< V[path[0]].name<< endl;
    }
    delete pre;
    delete dis;
    delete vis;
}

void Graph:: print(){   
    printPlaces();
    cout<< "Below is the current road information!\n";
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    for(int i = 1; i <= nodeSz; i ++)   
        if(!vis[i])
            dfs(i, 0);
    cout<< "Finish!\n";
    cout<< "There are "<<nodeSz<< " places!"<< endl;
    delete vis;
}

void Graph:: dfsToFind(int tar, int now, int fa, int num, int numOfPlaces, int dis, int &ans, vector<int>& path){
    if(num == numOfPlaces){
        if(dis < ans && now == tar){
            ans = dis;
            path = getPath(now);
        }
        return;
    }
    vis[now] = 1;
    for(int i = head[now]; i; i = e1[i].nxt){
        int to = e1[i].to;
        if(vis[to]) continue;
        pre[to] = now;
        dfsToFind(tar, to, now, num+1, numOfPlaces, dis+e1[i].dis, ans, path);
    }
    vis[now] = 0;
}

void Graph:: findPathThroNumPlaces(int u, int v, int num){
    int ans = inf;
    vector<int> path;
    pre = new int[nodeSz+1];
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    fill(pre, pre+nodeSz+1, 0);
    pre[u] = -1;
    dfsToFind(v, u, 0, 1, num, 0, ans, path);
    if(path.size()){
        cout<< "The distance of shortest path through "<< num<< " places from "<< V[u].name<< " to "<< V[v].name<< " is "<< ans<< endl;
        cout<< "Below is the shortest path:\n";
        int sz = path.size();
        for(int i = sz-1; i > 0; i --){
            cout<<V[path[i]].name<< "->";
        }
        cout<< V[path[0]].name<< endl;
    }else{
        cout<< "The shortest path through "<< num<< " places from "<< V[u].name<< " to "<< V[v].name<< " does not exist!\n";
    }
    delete pre;
    delete vis;
}

void Graph:: printPlaces(){
    cout<< "Below is the current place information!\n";
    int existCitiesNum = 0;
    for(int i = 1; i <= nodeSz; i ++)
        if(V[i].existed) cout<< V[i].name<< ' ', existCitiesNum ++;
    if(!existCitiesNum) cout<< "No location information!\n";
    else cout<< endl;
}