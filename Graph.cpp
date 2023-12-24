#include "head.h"
#include "Graph.h"
#include "MST.h"

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
    try{
        ifs.open("map.csv", ios:: in);
        if (!ifs.is_open()) {
            throw runtime_error("Error opening file: map.csv");
        }
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
    }catch(const exception &e) {
        cerr << "Exception: " << e.what() << endl;
        exit(0);
        // handle the exception, close the file if it's open, and perform any other necessary cleanup.
    }
}

void Graph:: option(){ // select options and implement the transformation of input information
    string op1, op2;
    cout<< "Press any key to continue!\n";
    char c = getchar();
    c = getchar();
    print();
    int op3;
    int u, v, w, numOfPlaces, numOfConstraint;
    bool flag;
    string place1, place2;
    vector<int> placesID;
    unordered_map<int, vector<int> > constraints;
    cout<< "                            -------------------------------------------\n";
    cout<< "                           |Please select action:                      |\n";
    cout<< "                           |1 print: output place and road information.|\n";
    cout<< "                           |2 insert: insert place/road information.   |\n";
    cout<< "                           |3 delete: delete place/road information.   |\n";
    cout<< "                           |4 compute: compute some information.       |\n";
    cout<< "                           |5 exit: log out.                           |\n";
    cout<< "                            -------------------------------------------\n";
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
            cin>> place1>> place2;
            // validate and ensure that w is an integer
            while (!(cin >> w)) {
                cerr << "Invalid input for distance. Please enter a valid integer.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
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
        cout<< "                            ---------------------------------------------------------------------\n";
        cout<< "                           |Please select the desired compute action.(Enter an option, such as 1)|\n";  
        cout<< "                           |1: get the shortest path between two places                          |\n"; // task 4
        cout<< "                           |2: get the shortest path through a fixed number of locations         |\n"; // task 5
        cout<< "                           |3: get path from a minimum spanning tree                             |\n"; // task 6
        cout<< "                           |4: find topologically constrained shortest paths                     |\n"; // task 7
        cout<< "                            ---------------------------------------------------------------------\n";
        while(true) {
            if(cin >> op3){
                if (op3 < 1 || op3 > 4) 
                    cerr << "The number must be between 1 and 4. Please try again!\n";
                else break;
            }else{
                cerr << "Invalid input! Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
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
            cin>> place1>> place2;
            while (!(cin >> numOfPlaces)) {
                cerr << "Invalid input for numOfPlaces. Please enter a valid integer.\n";
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            u = find(V.begin(), V.end(), place1)-V.begin();
            v = find(V.begin(), V.end(), place2)-V.begin();
            if(u == V.size() || ! V[u].existed){
                cout<< place1<<" does not exist!\n";
                break;
            }else if(v == V.size() || ! V[v].existed){
                cout<< place2<<" does not exist!\n";
                break;
            }
            findPathThroNumPlaces(u, v, numOfPlaces);
            break;
        case 3:
            cout<< "Please enter the required number of locations!\n";
            while (!(cin >> numOfPlaces)) {
                cerr << "Invalid input for numOfPlaces. Please enter a valid integer.\n";
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            cout<< "Please enter the locations!\n";
            placesID.clear();
            flag = true;
            for(int i = 0; i < numOfPlaces; i ++){
                cin>> place1; 
                u = find(V.begin(), V.end(), place1)-V.begin();
                if(u == V.size()){
                    flag = false;
                    break;
                }
                placesID.push_back(u);
            }
            if(inConnectedGraph(placesID) && flag){
                buildMST(placesID);
            }else cout<< "There are places that cannot be reached (or do not exist)!\n";
            break;
        case 4:
            cout<< "Please enter the required number of locations!\n";
            while (!(cin >> numOfPlaces)) {
                cerr << "Invalid input for numOfPlaces. Please enter a valid integer.\n";
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            cout<< "Please enter the locations!\n";
            placesID.clear();
            flag = true;
            for(int i = 0; i < numOfPlaces; i ++){
                cin>> place1; 
                u = find(V.begin(), V.end(), place1)-V.begin();
                if(u == V.size()){
                    flag = false;
                    break;
                }
                placesID.push_back(u);
            }
            if(!(inConnectedGraph(placesID) && flag)){
                cout<< "There are places that cannot be reached (or do not exist)!\n";
                break;
            }
            flag = false;
            constraints.clear();
            cout<< "Please enter the number of constraint!\n";
            while (!(cin >> numOfConstraint)) {
                cerr << "Invalid input for numOfPlaces. Please enter a valid integer.\n";
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            cout<< "Please enter the constrains!\n";
            for(int i = 0; i < numOfConstraint; i ++){
                cin>> place1>> place2;
                u = find(V.begin(), V.end(), place1)-V.begin();
                v = find(V.begin(), V.end(), place2)-V.begin();
                if(u == V.size() || v == V.size() || find(placesID.begin(), placesID.end(), u) == placesID.end() || find(placesID.begin(), placesID.end(), v) == placesID.end()){
                    cout<< "There are places that do not exist (or do not in placesID)!\n";
                    break;
                }
                constraints[v].push_back(u);
            }
            findPathWithConstraint(placesID, constraints);
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
// task 3
void Graph:: ins_edge(int u, int v, int w){
    bool found = false;
    V[u].existed = true;
    V[v].existed = true;
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
// task 3
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
// task 2
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
// task 1
void Graph:: dfs1(int u, int fa){ // dfs to traverse all edge
    vis[u] = 1;
    for(int i = head[u]; i; i = e1[i].nxt){
        int v = e1[i].to;
        if(v == fa || vis[v]) continue;
        if(e1[i].dis == inf) continue;
        cout<< V[u].name<< ' '<< V[e1[i].to].name<< ' '<< e1[i].dis<< endl;
        dfs1(v, u);
    }
}
// task 4 5 7
vector<int> Graph:: getPath(int now){  // according to "pre" to get path
    vector<int> path;
    while(pre[now] != -1){
        path.push_back(now);
        now = pre[now];
    }
    path.push_back(now);
    return path;
}
// task 4
void Graph:: dijkstra(int s){ // the classical dijkstra algorithm to find single source shortest path
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
// task 4
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
        cout<< "******************** [---Begin---] Outputs the shortest path ******************** \n";
        cout<< "The shortest path length is "<< dis[v]<< endl;
        vector<int> path = getPath(v);
        int sz = path.size();
        for(int i = sz-1; i > 0; i --){
            cout<<V[path[i]].name<< "->";
        }
        cout<< V[path[0]].name<< endl;
        cout<< "******************** [---Finish---] Outputs the shortest path ******************** \n";
    }
    delete pre;
    delete dis;
    delete vis;
}
// task 1
void Graph:: print(){   
    cout<< "******************** [---Begin---] Outputs information about roads and locations ******************** \n";
    printPlaces();
    cout<< "Below is the current road information!\n";
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    for(int i = 1; i <= nodeSz; i ++)   
        if(!vis[i])
            dfs1(i, 0);
    cout<< "******************** [---Finish---] Outputs information about roads and locations ******************** \n";
    delete vis;
}
// task 5
void Graph:: dfsToFind(int tar, int now, int fa, int num, int numOfPlaces, int dis, int &ans, vector<int>& path){
    if(num == numOfPlaces){
        if(dis < ans && now == tar){ //if n locations are traversed to reach the tar and the distance is shorter
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
// task 5
void Graph:: findPathThroNumPlaces(int u, int v, int num){ // find shortest path through n locations from u to v
    int ans = inf;
    vector<int> path;
    pre = new int[nodeSz+1];
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    fill(pre, pre+nodeSz+1, 0);
    pre[u] = -1;
    dfsToFind(v, u, 0, 1, num, 0, ans, path); // dfs
    if(path.size()){
        cout<< "******************** [---Begin---] Outputs the shortest path through n places ******************** \n";
        cout<< "The distance of shortest path through "<< num<< " places from "<< V[u].name<< " to "<< V[v].name<< " is "<< ans<< endl;
        cout<< "Below is the shortest path:\n";
        int sz = path.size();
        for(int i = sz-1; i > 0; i --){
            cout<<V[path[i]].name<< "->";
        }
        cout<< V[path[0]].name<< endl;
        cout<< "******************** [---Finish---] Outputs the shortest path through n places ******************** \n";
    }else{
        cout<< "The shortest path through "<< num<< " places from "<< V[u].name<< " to "<< V[v].name<< " does not exist!\n";
    }
    delete pre;
    delete vis;
}
// task 1
void Graph:: printPlaces(){
    cout<< "Below is the current place information!\n";
    int existCitiesNum = 0;
    for(int i = 1; i <= nodeSz; i ++)
        if(V[i].existed) cout<< V[i].name<< ' ', existCitiesNum ++;
    if(!existCitiesNum) cout<< "No location information!\n";
    else cout<< "\nThere are "<<existCitiesNum<< " places!"<< endl;
}
// task 6
void Graph:: dfs2(int u){ // simple dfs to determine connectivity
    vis[u] = 1;
    for(int i = head[u]; i; i = e1[i].nxt){
        int v = e1[i].to;
        if(vis[v] || e1[i].dis == inf) continue;
        dfs2(v);
    }
}
// task 6
bool Graph:: inConnectedGraph(vector<int>& placesID){ 
    if(!placesID.size()) return false;
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    int root = placesID[0];
    dfs2(root);
    bool isConnected = true;
    for(auto i: placesID){
        if(!vis[i]){isConnected = false; break;}
    }
    delete vis;
    return isConnected;
}

// task 6
void Graph:: buildMST(vector<int>& places){
    MST T{tot}; 
    queue<int> q;
    set<int> st1, st2;
    vector<int> path;
    q.push(places[0]); // put the required edge into MTS->e1
    while(!q.empty()){ // using bfs to traverse all edges
        int u = q.front(); q.pop(); 
        st1.insert(u);
        st2.insert(u);
        for(int i = head[u]; i; i = e1[i].nxt){
            int v = e1[i].to, w = e1[i].dis;
            if(w == inf) continue; 
            if(st1.find(v) == st1.end()){
                T.insert(u, V[u].name, v, V[v].name, w);
                if(st2.find(v) == st2.end()) q.push(v);
                st2.insert(v);
            }
        }
    }
    T.kruskal(); // build MST
    T.printMST(); // print MST
    T.floyd(); // calculate the shortest circuit of all sources
    places = T.findOptOrder(places); // find the shortest path and get the orders
    path = T.getPath(places); // according to visiting order to get path 
    cout<< "******************** [---Begin---] Outputs the shortest path on the minimum spanning tree ******************** \n";
    cout<< "On the minimum spanning tree, the length of the shortest path through the "<< places.size()<<" desired locations is "<< T.minDis<< endl;
    cout<< "Here is the shortest path:\n"<< V[path[0]].name;
    for(int i = 1; i < path.size(); i ++) cout<< "->"<< V[path[i]].name;
    cout<< endl;
    cout<< "******************** [---Finish---] Outputs the shortest path on the minimum spanning tree ******************** \n";
}
// task 7
bool Graph:: isAllVisited(vector<int>& placesID){  // check whether all fixed places have been visited
    for(auto place: placesID)
        if(!vis[place]) return false;
    return true;
} 
// task 7
void Graph:: dfsWithConstraint(int u, int end, int dis, int &ans, vector<int>& path, vector<int>& placesID, unordered_map<int, vector<int> >& constraints){
    vis[u] = 1;
    if(u == end){
        if(isAllVisited(placesID) && dis < ans){ // if all places have been visited and the distance is shorter than best so far
            path = getPath(u);
            ans = dis;
        }
        vis[u] = 0;
        return;
    }
    for(int i = head[u]; i; i = e1[i].nxt){
        int to = e1[i].to;
        if(vis[to]) continue;
        bool preHaveVis = true;
        for(auto j: constraints[to]){  //check if all pre_places have been visited
            if(!vis[j]){
                preHaveVis = false;
                break;
            }
        }
        if(!preHaveVis) continue;
        pre[to] = u;
        dfsWithConstraint(to, end, dis+e1[i].dis, ans, path, placesID, constraints);
    }
    vis[u] = 0;
}

// task 7
void Graph:: findPathWithConstraint(vector<int>& placesID, unordered_map<int, vector<int> >& constraints){
// placesID: all places need to visit;   constraint: constraints on location access order
    int startPlace = placesID[0], endPlace = *placesID.rbegin();
    int ans = inf;
    pre = new int[nodeSz+1];
    vis = new int[nodeSz+1];
    fill(vis, vis+nodeSz+1, 0);
    fill(pre, pre+nodeSz+1, 0);
    pre[startPlace] = -1;
    vector<int> path;
    dfsWithConstraint(startPlace, endPlace, 0, ans, path, placesID, constraints);
    if(path.size()){
        cout<< "******************** [---Begin---] Outputs the shortest path through fixed places with constraint ********************\n";
        cout<< "The distance of shortest path through all fixed places from "<< V[startPlace].name<< " to "<< V[endPlace].name<< " is "<< ans<< endl;
        cout<< "Below is the shortest path(All the places we passed):\n";
        int sz = path.size();
        for(int i = sz-1; i > 0; i --){
            cout<<V[path[i]].name<< "->";
        }
        cout<< V[path[0]].name<< endl;
        cout<< "Below is the shortest path(All fixed places):\n";
        int tmp = 0;
        for(int i = sz-1; i >= 0; i --){
            if(find(placesID.begin(), placesID.end(), path[i]) != placesID.end()){
                if(tmp != placesID.size()-1) cout<<V[path[i]].name<< "->", tmp ++;
                else{cout<< V[path[i]].name<< endl; break;}
            }
        }
        cout<< "******************** [---Finish---] Outputs the shortest path through fixed places with constraint ********************\n";
    }else{
        cout<< "There is not legal way to visited all fixed places with constaint!\n";
    }

    delete vis;
    delete pre;
}