#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int> > graph;

vector<vector<int> > create_adjacency_matrix(Instance &);
graph create_graph(vector<vector<int> > &);
vector<vector<int> > strongly_connected_components(graph);
void dfs(int, graph &,vector<int> &, vector<int> &);
graph transpose(graph &);
vector<int> topological_sort(graph &);

int main(){
    Instance instance;
    instance.read_file("../instances/positive/9.200+20");

    vector<vector<int> > adjacency_matrix = create_adjacency_matrix(instance);
    graph V = create_graph(adjacency_matrix);
    vector<vector<int> > scc = strongly_connected_components(V);

    vector<int> sorted = topological_sort(V);

    vector<int> distance(V.size(), 0);
    for(int i = 0; i < int(sorted.size()); i++){
        int u = sorted[i];
        for(int j = 0; j < int(V[u].size()); j++){
            distance[u] = max(distance[u], distance[V[u][j]] + 1);
        }
    }

    int max_i = 0;
    for(int i = 0; i < int(sorted.size()); i++){
        if(distance[i] > distance[max_i])
            max_i = i;
    }

    vector<int> solution;
    int u = max_i;
    solution.push_back(u);
    while(!V[u].empty()){
        for(int i = 0; i < int(V[u].size()); i++){
            if(distance[u] == distance[V[u][i]] + 1){
                solution.push_back(V[u][i]);
                u = V[u][i];
                break;
            }
        }
    }


    for(int i = 0; i < int(solution.size()); i++){
        string &o = instance.oligs[solution[i]].sequence;
        if(i == 0)
            printf("%s", o.c_str());
        else
            printf("%c", o[o.size()-1]);
    }
    printf("\n");

    return 0;
}

vector<int> topological_sort(graph &V){
    vector<int> used;
    vector<int> visited(V.size(), 0);
    for(int i = 0; i < int(V.size()); i++)
        if(!visited[i])
            dfs(i, V, visited, used);

    return used;
}

vector<vector<int> > strongly_connected_components(graph V){
    vector<vector<int> > result; 
    int n = V.size();
    vector<int> S;
    vector<int> visited(n, 0);
    vector<int> used;

    for(int i = 0; i < n; i++)if(!visited[i])dfs(i, V, visited, S);
    graph T = transpose(V);
    

    visited.assign(n, 0);
    for(int i = n - 1; i >= 0; i--){
        int u = S[i];
        if(!visited[u]){
            used.clear();
            dfs(u, T, visited, used);
            result.push_back(used);
        }
    }
    return result;
}

void dfs(int u, graph &V, vector<int> &visited, vector<int> &S){
    visited[u] = 1;
    for (int i = 0; i < int(V[u].size()); i++)
        if(!visited[ V[u][i] ])
            dfs(V[u][i], V, visited, S);
    S.push_back(u);
}

graph transpose(graph &V){
    graph T(V.size(), vector<int>());
    for (int i = 0; i < int(V.size()); i++) {
        for (int j = 0; j < int(V[i].size()); j++) {
            T[ V[i][j] ].push_back(i);
        }
    }
    return T;
}


vector<vector<int> > create_adjacency_matrix(Instance &instance){
    vector<Olig> &oligs = instance.oligs;
    int n = instance.oligs.size();
    vector<vector<int> > adjacency_matrix(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            adjacency_matrix[i][j] = oligs[i].distance(oligs[j]);
    return adjacency_matrix;
}

graph create_graph(vector<vector<int> > &adjacency_matrix){
    int n = adjacency_matrix.size();
    graph V(n, vector<int>());
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(adjacency_matrix[i][j] == 1 && i != j){
                V[i].push_back(j);
            }
    return V;
}
