
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#define INF INT_MAX


using namespace std;

struct Edge
{
    int a, b, weight;
};

pair<vector<int>, vector<int>> bfs(vector<vector<int>>& graph, int start);
bool dfs(vector<vector<int>>& graph, int v, int finish, vector<int>& visited, vector<int>& path);
vector<int> getPath(vector<int>& from, int finish);
void kruskal_algorithm(int vertexCount, vector<vector<int>>& graph);
void prim_algorithm(int vertexCount, vector<vector<int>>& graph, int start);
pair<vector<int>, vector<int>> bellmanford(int vertexCount, vector<Edge>& edges, int start);
pair<vector<int>, vector<int>> dijkstra(int vertexCount, vector<vector<pair<int, int>>>& graph, int start);
pair<vector<vector<int>>, vector<vector<int>>> floydWarshall(int vertexCount, vector<vector<int>>& graph);
bool DFS(vector<vector<int>>& rGraph, vector<bool>& visited, int source, int sink, vector<int>& parent);
void ford_fulkerson_algorithm(vector<vector<int>>& graph, int source, int sink);
bool BFS(vector<vector<int>>& rGraph, vector<int>& parent, int source, int sink);
void edmonds_karp_algorithm(vector<vector<int>>& graph, int source, int sink);

void writeToFile(int number);

void writeGraphToFile(const vector<vector<int>>& graph);
void writeGraphToFile1(const vector<vector<int>>& graph);
void writeGraphToFile2(const vector<vector<int>>& graph);
void writeGraphToFile3(const vector<Edge>& edges);
void writeGraphToFile4(const vector<vector<pair<int, int>>>& graph);
void writeMinSpanningTreeToFile(const vector<pair<pair<int, int>, int>>& min_spanning_tree);
void writeMinSpanningTreeToFile2(const std::vector<int>& parent, const std::vector<int>& minWeight);
void writePathToFile(const vector<int>& path);
void writeShortestPathsToFile(const vector<Edge>& edges, const vector<int>& dist, const vector<int>& from, int start);
void writeShortestPathsToFile2(const vector<vector<pair<int, int>>>& graph, const vector<int>& dist, const vector<int>& from, int start);
void writeShortestPathsToFile3(int vertexCount, const vector<vector<int>>& dist, const vector<vector<int>>& from, const vector<vector<int>>& graph);

void writeflowMatrixToFile(int vertexCount, const vector<vector<int>>& flowMatrix);

void print_menu();

int main() {

    int type;
    do
    {
        print_menu();
        cout << "Select algorithm: ";
        cin >> type;
        writeToFile(type);

        switch (type) {
        case 1:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount);
            cout << "Enter the edges of the graph (start finish): " << endl;
            for (int i = 0; i < edgeCount; i++)
            {
                int a, b;
                cin >> a >> b;

                graph[a].push_back(b);
                graph[b].push_back(a);
            }

            writeGraphToFile(graph);

            int start;
            cout << "Enter the start vertex: ";
            cin >> start;

            int finish;
            cout << "Enter the finish vertex: ";
            cin >> finish;

            auto [dist, from] = bfs(graph, start);


            vector<int> path = getPath(from, finish);

            writePathToFile(path);

            for (int v : getPath(from, finish))
            {
                cout << v << " ";
            }
            cout << endl;

            system("python graph_visualization.py");
        }
        break;
        case 2:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount);
            cout << "Enter the edges of the graph (start finish): " << endl;
            for (int i = 0; i < edgeCount; i++)
            {
                int a, b;
                cin >> a >> b;

                graph[a].push_back(b);
                graph[b].push_back(a);
            }

            writeGraphToFile(graph);

            int start;
            cout << "Enter the start vertex: ";
            cin >> start;

            int finish;
            cout << "Enter the finish vertex: ";
            cin >> finish;

            vector<int> visited(vertexCount, 0);
            vector<int> path;

            if (dfs(graph, start, finish, visited, path))
            {
                for (int v : path)
                    cout << v << " ";
                cout << endl;

                writePathToFile(path);
            }
            system("python graph_visualization.py");
        }
        break;
        case 3:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            cout << "Enter the edges (start finish weight): " << endl;
            vector<vector<int>> graph(edgeCount, vector<int>(3));
            for (int i = 0; i < edgeCount; i++)
                cin >> graph[i][1] >> graph[i][2] >> graph[i][0];

            writeGraphToFile1(graph);

            kruskal_algorithm(vertexCount, graph);
            cout << endl;
            system("python graph_visualization.py");
        }
        break;
        case 4:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount, vector<int>(vertexCount, INF));
            cout << "Enter the edges (start finish weight): " << endl;
            for (int i = 0; i < edgeCount; i++) {
                int a, b, weight;
                cin >> a >> b >> weight;
                graph[a][b] = weight;
                graph[b][a] = weight;
            }
            writeGraphToFile2(graph);

            int start;
            cout << "Enter the start vertex: ";
            cin >> start;

            prim_algorithm(vertexCount, graph, start);
            cout << endl;
            system("python graph_visualization.py");
        }
        break;
        case 5:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<Edge> edges(edgeCount);
            cout << "Enter the edges (start finish weight): " << endl;
            for (auto& [a, b, weight] : edges)
            {
                cin >> a >> b >> weight;
            }
            writeGraphToFile3(edges);

            int start;
            cout << "Enter the start vertex: ";
            cin >> start;

            auto [dist, from] = bellmanford(vertexCount, edges, start);

            if (!dist.empty() && !from.empty()) {
                for (int i = 0; i < vertexCount; i++) {
                    if (dist[i] == INF || dist[i] == 0)
                    {
                        cout << "No path from " << start << " to " << i << endl;
                    }
                    else
                    {
                        cout << "Shortest path from " << start << " to " << i << ":" << endl;
                        vector<int> path;
                        int current = i;
                        while (current != start)
                        {
                            path.push_back(current);
                            current = from[current];
                        }
                        path.push_back(start);
                        reverse(path.begin(), path.end());

                        for (int j = 0; j < path.size() - 1; j++)
                        {
                            cout << path[j] << " " << path[j + 1] << " ";
                            for (auto& [a, b, weight] : edges)
                            {
                                if (a == path[j] && b == path[j + 1])
                                {
                                    cout << weight << endl;
                                    break;
                                }
                            }
                        }
                    }

                }

            }

            writeShortestPathsToFile(edges, dist, from, start);
            system("python graph_visualization.py");
        }
        break;
        case 6:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<pair<int, int>>> graph(vertexCount);
            cout << "Enter the edges (start finish weight): " << endl;
            for (int i = 0; i < edgeCount; i++)
            {
                int a, b, weight;
                cin >> a >> b >> weight;

                graph[a].push_back({ b, weight });
            }
            writeGraphToFile4(graph);

            int start;
            cout << "Enter the start vertex: ";
            cin >> start;

            auto [dist, from] = dijkstra(vertexCount, graph, start);

            for (int i = 0; i < vertexCount; i++) {
                if (dist[i] == INF || dist[i] == 0)
                {
                    cout << "No path from " << start << " to " << i << endl;
                }

                else
                {
                    cout << "Shortest path from " << start << " to " << i << ":" << endl;
                    vector<int> path;
                    int current = i;
                    while (current != start)
                    {
                        path.push_back(current);
                        current = from[current];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());

                    for (int j = 0; j < path.size() - 1; j++)
                    {
                        cout << path[j] << " " << path[j + 1] << " ";
                        for (auto& [to, weight] : graph[path[j]])
                        {
                            if (to == path[j + 1])
                            {
                                cout << weight << endl;
                                break;
                            }
                        }
                    }
                }

            }

            writeShortestPathsToFile2(graph, dist, from, start);
            system("python graph_visualization.py");
        }
        break;
        case 7:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount, vector<int>(vertexCount, INF));
            cout << "Enter the edges (start finish weight): " << endl;
            for (int i = 0; i < edgeCount; i++) {
                int a, b, weight;
                cin >> a >> b >> weight;
                graph[a][b] = weight;
            }
            writeGraphToFile2(graph);

            auto [dist, from] = floydWarshall(vertexCount, graph);

            for (int i = 0; i < vertexCount; i++) {
                for (int j = 0; j < vertexCount; j++) {
                    if (i == j) {
                        cout << "No path from " << i << " to " << j << endl;
                    }
                    else {
                        cout << "Shortest path from " << i << " to " << j << ": " << endl;
                        vector<int> path;
                        int current = i;
                        while (current != j) {
                            path.push_back(current);
                            current = from[current][j];
                        }
                        path.push_back(j);

                        for (int k = 0; k < path.size() - 1; k++) {
                            cout << path[k] << " ";
                            for (int l = 0; l < vertexCount; l++) {
                                if (graph[path[k]][l] != INF && l == path[k + 1]) {
                                    cout << path[k + 1] << " " << graph[path[k]][l] << endl;
                                    break;
                                }
                            }
                        }
                    }

                }
            }
            writeShortestPathsToFile3(vertexCount, dist, from, graph);
            system("python graph_visualization.py");
        }
        break;
        case 8: {
            cout << "This algorithm is under development" << endl;
        }
        continue;
        case 9:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount, vector<int>(vertexCount, 0));
            cout << "Enter the edges (start finish weight): " << endl;
            for (int i = 0; i < edgeCount; i++) {
                int a, b, weight;
                cin >> a >> b >> weight;
                graph[a][b] = weight;
            }
            writeGraphToFile2(graph);

            int source, sink;
            cout << "Enter the start vertex: ";
            cin >> source;
            cout << "Enter the finish vertex: ";
            cin >> sink;

            ford_fulkerson_algorithm(graph, source, sink);
            system("python graph_visualization.py");
        }

        break;
        case 10:
        {
            int vertexCount, edgeCount;
            cout << "Enter the number of vertices and edges: ";
            cin >> vertexCount >> edgeCount;

            vector<vector<int>> graph(vertexCount, vector<int>(vertexCount, 0));
            cout << "Enter the edges (start finish weight): " << endl;
            for (int i = 0; i < edgeCount; i++)
            {
                int a, b, weight;
                cin >> a >> b >> weight;
                graph[a][b] = weight;
            }
            writeGraphToFile2(graph);

            int source, sink;
            cout << "Enter the start vertex: ";
            cin >> source;
            cout << "Enter the finish vertex: ";
            cin >> sink;

            edmonds_karp_algorithm(graph, source, sink);
            system("python graph_visualization.py");
        }
        break;
        default:
            cout << "Wrong input!!!\nOnly 1-10 requires";
        }
    } while (type >= 1 && type <= 10);

    return 0;
}

void print_menu() {
    cout << "Algorithms for working with graphs: " << endl;
    cout << "\t1 - Breadth-First Search" << endl;
    cout << "\t2 - Depth-First Search" << endl;
    cout << "\t3 - Kruskal's Algorithm" << endl;
    cout << "\t4 - Prim's Algorithm" << endl;
    cout << "\t5 - Bellman-Ford Algorithm" << endl;
    cout << "\t6 - Dijkstra's Algorithm" << endl;
    cout << "\t7 - Floyd-Warshall Algorithm" << endl;
    cout << "\t8 - Johnson's Algorithm" << endl;
    cout << "\t9 - Ford-Fulkerson Algorithm" << endl;
    cout << "\t10 - Edmonds-Karp Algorithm\n" << endl;
}


pair<vector<int>, vector<int>> bfs(vector<vector<int>>& graph, int start)
{
    vector<int> dist(graph.size(), INF);
    vector<int> from(graph.size(), -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int to : graph[v])
        {
            if (dist[to] > dist[v] + 1)
            {
                dist[to] = dist[v] + 1;
                from[to] = v;
                q.push(to);
            }
        }
    }
    return { dist, from };
}

vector<int> getPath(vector<int>& from, int finish)
{
    vector<int> path;
    for (int v = finish; v != -1; v = from[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

bool dfs(vector<vector<int>>& graph, int v, int finish, vector<int>& visited, vector<int>& path)
{
    visited[v] = true;
    path.push_back(v);

    if (v == finish)
        return true;

    for (int to : graph[v])
    {
        if (!visited[to])
        {
            if (dfs(graph, to, finish, visited, path))
                return true;
        }
    }
    return false;
}

void kruskal_algorithm(int vertexCount, vector<vector<int>>& graph)
{
    sort(graph.begin(), graph.end());

    vector<int> components(vertexCount + 1);
    for (int i = 1; i <= vertexCount; i++)
        components[i] = i;

    vector<pair<pair<int, int>, int>> min_spanning_tree;

    for (auto& edge : graph)
    {
        int start = edge[1];
        int finish = edge[2];
        int weight = edge[0];
        int comp_start = components[start];
        int comp_finish = components[finish];

        if (comp_start != comp_finish)
        {
            min_spanning_tree.push_back({ { start, finish }, weight });
            for (int i = 1; i <= vertexCount; i++)
                if (components[i] == comp_finish)
                    components[i] = comp_start;
        }
    }

    cout << "Minimum spanning tree:" << endl;
    for (auto& edge : min_spanning_tree)
    {
        cout << edge.first.first << " " << edge.first.second << " " << edge.second << endl;
    }
    writeMinSpanningTreeToFile(min_spanning_tree);
}

void prim_algorithm(int vertexCount, vector<vector<int>>& graph, int start) {
    vector<bool> selected(vertexCount, false);
    vector<int> minWeight(vertexCount, INF);
    vector<int> parent(vertexCount, -1);

    minWeight[start] = 0;
    for (int i = 0; i < vertexCount; i++) {
        int v = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!selected[j] && (v == -1 || minWeight[j] < minWeight[v])) {
                v = j;
            }
        }

        selected[v] = true;
        for (int u = 0; u < vertexCount; u++) {
            if (!selected[u] && graph[v][u] < minWeight[u]) {
                minWeight[u] = graph[v][u];
                parent[u] = v;
            }
        }
    }

    cout << "Minimum spanning tree:" << endl;

    for (int i = 0; i < vertexCount; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " " << i << " " << minWeight[i] << endl;
        }
    }
    writeMinSpanningTreeToFile2(parent, minWeight);
}

pair<vector<int>, vector<int>> bellmanford(int vertexCount, vector<Edge>& edges, int start)
{
    vector<int> emptyVector;
    vector<int> dist(vertexCount, INF);
    dist[start] = 0;
    vector<int> from(vertexCount, -1);

    for (int i = 0; i < vertexCount - 1; i++)
    {
        for (auto& [a, b, weight] : edges)
        {
            if (dist[a] != INF && dist[b] > dist[a] + weight)
            {
                dist[b] = dist[a] + weight;
                from[b] = a;
            }
        }
    }

    for (auto& [a, b, weight] : edges)
    {
        if (dist[a] != INF && dist[b] > dist[a] + weight)
        {
            cout << "Negative cycle detected!" << endl;
            return { emptyVector, emptyVector };
        }
    }
    return { dist, from };

}

pair<vector<int>, vector<int>> dijkstra(int vertexCount, vector<vector<pair<int, int>>>& graph, int start)
{
    vector<int> dist(vertexCount, INF);
    dist[start] = 0;
    vector<int> from(vertexCount, -1);
    vector<bool> visited(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        int nearest = -1;
        for (int v = 0; v < vertexCount; v++)
            if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v]))
                nearest = v;

        visited[nearest] = true;

        for (auto& [to, weight] : graph[nearest])
        {
            if (dist[to] > dist[nearest] + weight)
            {
                dist[to] = dist[nearest] + weight;
                from[to] = nearest;
            }
        }
    }
    return { dist, from };
}


pair<vector<vector<int>>, vector<vector<int>>> floydWarshall(int vertexCount, vector<vector<int>>& graph) {
    vector<vector<int>> dist(vertexCount, vector<int>(vertexCount, INF));
    vector<vector<int>> from(vertexCount, vector<int>(vertexCount, -1));

    for (int i = 0; i < vertexCount; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (graph[i][j] != INF) {
                dist[i][j] = graph[i][j];
                from[i][j] = j;
            }
        }
    }

    for (int k = 0; k < vertexCount; k++) {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    from[i][j] = from[i][k];
                }
            }
        }
    }

    cout << "Shortest distance matrix:" << endl;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            }
            else {
                cout << dist[i][j] << " \t";
            }
        }
        cout << endl;
    }

    return { dist, from };
}


bool DFS(vector<vector<int>>& rGraph, vector<bool>& visited, int source, int sink, vector<int>& parent) {
    visited[source] = true;
    if (source == sink) {
        return true;
    }
    for (int v = 0; v < static_cast<int> (rGraph.size()); v++) {
        if (!visited[v] && rGraph[source][v] > 0) {
            parent[v] = source;
            if (DFS(rGraph, visited, v, sink, parent)) {
                return true;
            }
        }
    }
    return false;
}


void ford_fulkerson_algorithm(vector<vector<int>>& graph, int source, int sink) {

    vector<vector<int>> rGraph = graph;
    vector<vector<int>> flowMatrix(graph.size(), vector<int>(graph.size(), 0));

    int maxFlow = 0;

    while (true) {
        vector<bool> visited(graph.size(), false);
        vector<int> parent(graph.size(), -1);

        if (!DFS(rGraph, visited, source, sink, parent)) {
            break;
        }

        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
            flowMatrix[u][v] += pathFlow;
            flowMatrix[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "Maximum flow: " << maxFlow << endl;

    cout << "Flow matrix:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (flowMatrix[i][j] < 0)
                flowMatrix[i][j] = 0;
            cout << "\t" << flowMatrix[i][j];
        }
        cout << endl;
    }
    writeflowMatrixToFile(graph.size(), flowMatrix);
}

bool BFS(vector<vector<int>>& rGraph, vector<int>& parent, int source, int sink) {

    vector<bool> visited(rGraph.size(), false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < static_cast<int> (rGraph.size()); v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[sink];
}

void edmonds_karp_algorithm(vector<vector<int>>& graph, int source, int sink) {
    vector<vector<int>> rGraph = graph;
    vector<vector<int>> flowMatrix(graph.size(), vector<int>(graph.size(), 0));

    vector<int> parent(rGraph.size(), -1);

    int maxFlow = 0;

    while (BFS(rGraph, parent, source, sink)) {
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
            flowMatrix[u][v] += pathFlow;
            flowMatrix[v][u] -= pathFlow;
        }
        maxFlow += pathFlow;
    }

    cout << "Maximum flow: " << maxFlow << endl;

    cout << "Flow matrix:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (flowMatrix[i][j] < 0)
                flowMatrix[i][j] = 0;
            cout << "\t" << flowMatrix[i][j];
        }
        cout << endl;
    }
    writeflowMatrixToFile(graph.size(), flowMatrix);
}

void writeToFile(int number) {
    ofstream file("algorithm.txt");

    file << number << endl;

    file.close();
}


void writeGraphToFile(const vector<vector<int>>& graph) {
    ofstream file("graph1.txt");

    if (file.is_open()) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                file << i << " " << graph[i][j] << endl;
            }
        }
        file.close();
    }
}


void writeGraphToFile1(const vector<vector<int>>& graph) {
    ofstream file("graph1.txt");

    if (file.is_open()) {
        for (const auto& edge : graph) {
            file << edge[1] << " " << edge[2] << " " << edge[0] << endl;
        }
        file.close();
    }
}

void writeGraphToFile2(const vector<vector<int>>& graph) {
    ofstream file("graph1.txt");

    if (file.is_open()) {

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                if (graph[i][j] != 0 && graph[i][j] != INF) {
                    file << i << " " << j << " " << graph[i][j] << endl;
                }
            }
        }
        file.close();
    }
}

void writeGraphToFile3(const vector<Edge>& edges) {
    ofstream file("graph1.txt");

    if (file.is_open()) {
        for (const auto& [a, b, weight] : edges) {
            file << a << " " << b << " " << weight << endl;
        }
        file.close();
    }
}

void writeGraphToFile4(const vector<vector<pair<int, int>>>& graph) {
    ofstream file("graph1.txt");

    if (file.is_open()) {
        for (int i = 0; i < graph.size(); i++)
        {
            for (const auto& edge : graph[i]) {
                file << i << " " << edge.first << " " << edge.second << endl;
            }
        }
        file.close();
    }

}

void writePathToFile(const vector<int>& path) {
    ofstream file("graph2.txt");

    if (file.is_open()) {
        for (int i = 0; i < path.size()-1; i++) {
            file << path[i] << " " << path[i + 1] << endl;
        }
        file.close();
    }
}

void writeMinSpanningTreeToFile(const vector<pair<pair<int, int>, int>>& min_spanning_tree) {
    ofstream file("graph2.txt");

    if (file.is_open()) {
        for (const auto& edge : min_spanning_tree) {
            file << edge.first.first << " " << edge.first.second << " " << edge.second << endl;
        }
        file.close();
    }
}

void writeMinSpanningTreeToFile2(const vector<int>& parent, const vector<int>& minWeight) {
    ofstream file("graph2.txt");

    if (file.is_open()) {
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] != -1) {
                file << parent[i] << " " << i << " " << minWeight[i] << endl;
            }
        }
    }
    file.close();
}

void writeShortestPathsToFile(const vector<Edge>& edges, const vector<int>& dist, const vector<int>& from, int start) {
    ofstream file("graph2.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < dist.size(); i++) {
        if (i != start && dist[i] != INF) {
            vector<int> path;
            int current = i;
            while (current != start)
            {
                path.push_back(current);
                current = from[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            for (int j = 0; j < path.size() - 1; j++) {
                for (const auto& [a, b, weight] : edges) {
                    if (a == path[j] && b == path[j + 1]) {
                        file << path[j] << " " << path[j + 1] << " " << weight << endl;
                        break;
                    }
                }
            }
        }
    }

    file.close();
}

void writeShortestPathsToFile2(const vector<vector<pair<int, int>>>& graph, const vector<int>& dist, const vector<int>& from, int start) {
    ofstream file("graph2.txt");

    for (int i = 0; i < dist.size(); i++) {
        if (i != start && dist[i] != INF) {
            vector<int> path;
            int current = i;
            while (current != start)
            {
                path.push_back(current);
                current = from[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            for (int j = 0; j < path.size() - 1; j++) {
                file << path[j] << " " << path[j + 1] << " ";
                for (const auto& edge : graph[path[j]])
                {
                    if (edge.first == path[j + 1])
                    {
                        file << edge.second << endl;
                        break;
                    }
                }
            }
        }
    }

    file.close();
}

void writeShortestPathsToFile3(int vertexCount, const vector<vector<int>>& dist, const vector<vector<int>>& from, const vector<vector<int>>& graph) {
    ofstream file("graph2.txt");

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (i != j) {
                vector<int> path;
                int current = i;
                while (current != j) {
                    path.push_back(current);
                    current = from[current][j];
                }
                path.push_back(j);

                for (int k = 0; k < path.size() - 1; k++) {
                    file << path[k] << " ";
                    for (int l = 0; l < vertexCount; l++) {
                        if (graph[path[k]][l] != INF && l == path[k + 1]) {
                            file << path[k + 1] << " " << graph[path[k]][l] << endl;
                            break;
                        }
                    }
                }
            }
        }
    }
    file.close();
}

void writeflowMatrixToFile(int vertexCount, const vector<vector<int>>& flowMatrix) {
    ofstream file("graph2.txt");

    if (file.is_open()) {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertexCount; j++)
            {
                if (flowMatrix[i][j] != 0)
                    file << i << " " << j << " " << flowMatrix[i][j] << endl;
            }
        }
        file.close();
    }
}
