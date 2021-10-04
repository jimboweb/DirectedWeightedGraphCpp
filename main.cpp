#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;




int distanceNaive(vector<vector<int>> &adj, vector<vector<int> > &weight, int s, int t) {

    bool distChanged=false;
    vector<int> dist;
    vector<int>prev;
    int i;
    for (i=0;i<adj.size();i++){
        dist.push_back(i==s?0:INT_MAX);
        prev.push_back(-1);
    }
    do{
        i=0;
        for(vector<int> u:adj){
            if(dist[i]<INT_MAX){
                for(int j=0;j<u.size();j++){
                    int a = u[j];
                    int e = weight[i][j];
                    if(dist[a]>dist[i]+e){
                        dist[a] = dist[i]+e;
                        prev[a] = i;
                        distChanged = true;
                    }
                }
            }
            i++;
        }
    } while (!distChanged);
    //for(int d:dist) std::cout<<d<<"\n";
    return dist[t];
}

class Node{
public:
    vector<int> adj;
    vector<int> weight;
    int distance = INT_MAX;
    int prev = -1;
    Node(vector<int>, vector<int>, int);
    int index;
};

Node::Node(vector<int>_adj, vector<int> _weight, int _index){
    this->adj = _adj;
    this->weight = _weight;
    this->index=_index;
}



int distance(vector<vector<int> > &adj, vector<vector<int> > &weight, int s, int t) {
    struct comparator
    {
        bool operator()(Node a, Node b){
            return a.distance>b.distance;
        }
    };
    priority_queue<Node, vector<Node>, comparator> h;

    vector<Node> nodes;

    for(int i=0;i<adj.size();i++){
        nodes.push_back(Node(adj[i], weight[i], i));
    }

    nodes[s].distance=0;
    h.push(nodes[s]);

    while(h.size()>0){
        Node u = h.top();
        h.pop();
        for(int i=0;i<u.adj.size();i++){
            Node &endNode = nodes[u.adj[i]];
            if(endNode.distance > u.distance + u.weight[i]){
                endNode.distance = u.distance + u.weight[i];
                endNode.prev = u.index;
                h.push(endNode);
            }
        };
    }

    if(nodes[t].distance<INT_MAX)
        return nodes[t].distance;
    else
        return -1;
}

int main() {
  // n = number of nodes
  // m = number of edges
  // x, y, w = from, to, weight for each edge
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > weight(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x].push_back(y);
    weight[x].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  std::cout << distance(adj, weight, s, t);
}
