#include<bits/stdc++.h>
#include<list>
#define INF 1000000005
using namespace std;

struct Spot{
    int node;
    int path_cost;
    Spot(){};
    Spot (int _node, int _path_cost){
        node=_node;
        path_cost=_path_cost;
    }
    bool operator <(const Spot & a)const{
        return path_cost<a.path_cost;
    }
    bool operator>(const Spot & a)const {
        return path_cost>a.path_cost;
    }
};
int cost[1000];
int dis[1000];
int vis[1000];
int parDijk[1000];
int parBfs[1000];
vector <int>adj[1000],adjw[1000];
int n,e;
priority_queue<Spot,vector<Spot>,greater<Spot>>pq;
queue <int>q;

void init(int src){
    for(int i=1;i<=n;i++){
        cost[i]=INF;
        vis[i]=0;
    }
    cost[src]=0;
    parDijk[src]=src;
    pq.push(Spot(src,0));
}
void dijkstra(int src){
    init(src);
    int u,v,w;
    while(!pq.empty()){
        u=pq.top().node;
        pq.pop();
        if(vis[u]==1)continue;
        vis[u]=1;
        for(int i=0;i<adj[u].size();i++){
            v=adj[u][i];
            w=adjw[u][i];
            if((cost[u]+w)<=cost[v]){
                cost[v]=cost[u]+w;
                parDijk[v]=u;
                pq.push(Spot(v,cost[v]));
            }
        }
    }
}
void printPath(int u,int d,bool visited[],int path[],int costRtn[],int cost,int path_ind){
    visited[u]=true;
    path[path_ind]=u;
    costRtn[path_ind]=cost;
    path_ind++;
    if(u==d){
        int sum=0;
        for(int i=0;i<path_ind;i++){
            cout<<path[i];
            if(i<(path_ind-1))cout<<"->";
            sum+=costRtn[i];
        }
        cout<<"="<<sum<<endl;

    }
    else{
        for(int i=0;i<adj[u].size();++i){
            int x=adj[u][i];
            int y=adjw[u][i];
            if(!visited[x]){
                printPath(x,d,visited,path,costRtn,y,path_ind);
            }
        }
    }
    path_ind--;
    visited[u]=false;
}
void printAllPaths(int s,int d){
    bool visited[n];
    int path[n];
    int costRtn[n];
    int path_ind=0;

    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    printPath(s,d,visited,path,costRtn,0,path_ind);
}
void initBFS(int src){
    for(int i=1;i<=n;i++)dis[i]=0;
    parBfs[src]=src;
    q.push(src);
}
void BFS(int src){
    initBFS(src);
    int u,v,w;
    while(q.size()!=0){
        u=q.front();
        q.pop();
        for(int i=0;i<adj[u].size();i++){
            w=adjw[u][i];
            v=adj[u][i];
            if(dis[v]==0){
                dis[v]=dis[u]+w;
                parBfs[v]=u;
                q.push(v);
            }
        }
    }
}
int maxSpotroute(){
    int routeLnt=0,lastDest=1;
    for(int i=n;i>1;i--){
        int x=i;
        int cnt=1;
        while(x!=1){
            x=parDijk[x];
            cnt++;
        }
        if(cnt==routeLnt && cost[i]<cost[lastDest])
        {
            routeLnt=cnt;
            lastDest=i;
        }
        else if(cnt>routeLnt){
            routeLnt=cnt;
            lastDest=i;
        }
    }
    return lastDest;
}
void allSpotroute(){
    int routeLnt=0;
    cout<<"\nAll routes:"<<endl;
    for(int i=n;i>1;i--){
        int x=i;
        stack<int>visit;
        while(x!=1){
            visit.push(x);
            x=parDijk[x];
        }
        visit.push(1);
        int y;
        while(!visit.empty()){
            y=visit.top();
            visit.pop();
            cout<<y;
            if(y!=i)cout<<"->";
        }
        cout<<"="<<cost[i]<<endl;
    }
}
int main(){
    scanf("%d %d",&n,&e);
    int u,v,w;
    for(int i=0;i<e;i++){
        scanf("%d %d %d",&u,&v,&w);
        adj[u].push_back(v);
        adj[v].push_back(u);
        adjw[u].push_back(w);
        adjw[v].push_back(w);
    }
    dijkstra(1);
    BFS(1);

    int x=maxSpotroute();
    int lastDest=x;
    stack<int>visit;
    while(x!=1){
        visit.push(x);
        x=parDijk[x];
    }
    visit.push(1);
    cout<<"1. Visiting cost: "<<cost[lastDest]<<endl;
    cout<<"2. Return cost"<<endl;
    cout<<"\t"<<"Short distance: ";
    cout<<dis[lastDest]<<endl;
    cout<<"\t"<<"Low cost: "<<cost[lastDest]<<endl;
    cout<<"\nVisiting route: ";
    int y;
    while(!visit.empty()){
        y=visit.top();
        visit.pop();
        cout<<y;
        if(y!=lastDest)cout<<"->";
    }
    cout<<endl;
    x=lastDest;
    cout<<"Shortest time route: ";
    while(x!=1){
        cout<<x<<"->";
        x=parBfs[x];
    }
    cout<<"1"<<endl;
    cout<<"Minimum cost route: ";
    x=lastDest;
    while(x!=1){
        cout<<x<<"->";
        x=parDijk[x];
    }
    cout<<"1"<<endl;
    int more;
    cout<<"\n";

    cout<<"1. Other return routes."<<endl;
    cout<<"2. All visiting routes."<<endl;
    cout<<"3. Find another return path."<<endl;
    cin>>more;
    if(more==1){
        cout<<endl<<"Other return routes: "<<endl;
        printAllPaths(lastDest,1);
    }
    else if(more==2){
        allSpotroute();
    }
    else if(more==3){
        cout<<"Enter spot: ";
        int a;
        cin>>a;
        cout<<endl;
        printAllPaths(a,1);
    }
    return 0;
}
