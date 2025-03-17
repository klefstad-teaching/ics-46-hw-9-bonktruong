#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int num = G.numVertices;
    vector<int> distance(num, INF);
    previous.assign(num, -1);
    vector<bool> visited(num, false);

    struct Node {
        int vertex;
        int weight;

        Node(int v, int w) : vertex(v), weight(w) {}
        bool operator>(const Node& other) const {
            return weight > other.weight;
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> priority_q;

    priority_q.push(Node(source, 0));
    distance[source] = 0;

    while (!priority_q.empty()) {
        Node current = priority_q.top();
        priority_q.pop();

        int u = current.vertex;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                priority_q.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;

    if (distances[destination] == INF) {
        return path;
    }

    stack<int> s;
    for (int at = destination; at != -1; at = previous[at]) {
        s.push(at);
    }

    while (!s.empty()) {
        path.push_back(s.top());
        s.pop();
    }

    return path;
}

void print_path(const vector<int>& v, int total) {
    if (total == INF) {
        cout << "No path exists." << endl;
        return;
    }

    for (size_t i = 0; i < v.size(); ++i)  {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
