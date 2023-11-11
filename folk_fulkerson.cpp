#include <iostream>
#include <queue>
#include <cstring>
#include <sstream>
#include <fstream>
#include <chrono>

#define maxN 101

using namespace std;
using namespace std::chrono;

int graph[maxN][maxN];

bool BFS(int ways[maxN][maxN], int * parent, bool * visited, int n, int s, int t){

    queue<int> q;

    parent[s] = -1;
    q.push(s);

    while (!q.empty()) {

        int u = q.front();
        q.pop();

        for (int i = 0; i < n ; ++i) {
            if (!visited[i] && ways[u][i] > 0) {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    return visited[t];
}

bool DFS(int rGraph[maxN][maxN], int * parent, bool * visited, int n, int x, int t){

    // cout << x << " ";
    if(x == t) return true;
    visited[x] = true;

    for(int i = 0; i < n; ++i){
        if(rGraph[x][i] > 0 && !visited[i]){
            parent[i] = x;
            if(DFS(rGraph, parent, visited, n, i, t))
                return true;
        }
    }
    return false;

}

int FordFulkerson(int graph[maxN][maxN], int n, int s, int t){

    int rGraph[maxN][maxN];
    int parent[maxN];
    bool visited[maxN];

    // Replicate the graph for residual one
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            rGraph[i][j] = graph[i][j];

    int max_flow = 0;

    // while(BFS(rGraph, parent, visited, n, s, t)){ 
    while(DFS(rGraph, parent, visited, n, s, t)){
        memset(visited, false, sizeof(visited));
        int path_flow = 0xfffffff; // Current flow to add on the max flow later

        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void extractIntegerWords(string str){
    stringstream ss;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found, start = -1, end = -1, capacity = -1, i = 0;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;
        /* Checking the given word is integer or not */
        stringstream(temp) >> found;
        if (i == 0) {
            start = found;
            i++;
        } else if (i == 1) {
            end = found;
            i++;
        } else {
            capacity = found;
            i++;
        }
        /* To save from space at the end of string */
        temp = "";

    }
    // cout << start << " " << end << " " << capacity << endl;
    graph[start][end] = capacity;
    // cout << endl;
}

int main() {
    cout << "Starting..." << endl;
    int i = 0, n = 0;
    fstream newfile;
    newfile.open("data/input.txt",ios::in); 
    if (newfile.is_open()){ 
        string tp;
        while(getline(newfile, tp)){ 
            if (i == 0) n = stoi(tp);
            else {
                extractIntegerWords(tp);
            }
            i++;
        }
        newfile.close(); 
    }

    auto start = high_resolution_clock::now();
    cout << "Max Flow: " << FordFulkerson(graph, n, 0, n-1) << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    cout << "Ending..." << endl;
    return 0;
}
