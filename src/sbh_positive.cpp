#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<vector<int> > adjacency_list;
typedef vector<vector<int> > adjacency_matrix;

adjacency_matrix create_adjacency_matrix(Instance &);
adjacency_list create_adjacency_list(adjacency_matrix &);
vector<vector<int> > strongly_connected_components(adjacency_list &);
void dfs(int, adjacency_list &,vector<int> &, vector<int> &);
adjacency_list transpose(adjacency_list &);
vector<int> topological_sort(adjacency_list &);
void print_graph_in_dot_format(adjacency_list &);
void print_solution(Instance &instance, vector<int> &solution);

int main(int argc, char **argv){
    Instance instance;
    instance.read_file(argv[1]);

    adjacency_matrix adjacency_matrix = create_adjacency_matrix(instance);
    adjacency_list V = create_adjacency_list(adjacency_matrix);

    
    vector<int> sorted = topological_sort(V);
    vector<int> distance(sorted.size(), -1);

    for(int i = 0; i < int(sorted.size()); i++){
        int u = sorted[i];
        distance[u] = 0;
        for(int j = 0; j < int(V[u].size()); j++){
            int v = V[u][j];
            distance[u] = max(distance[u], distance[v] + 1);
        }
    }
    vector<int>::iterator max_it = max_element(distance.begin(), distance.end());

    vector<int> solution;
    int u = max_it - distance.begin();
    solution.push_back(u);
    while(distance[u] != 0){
        int v = 0;
        for(int i = 0; i < V[u].size(); i++)if(distance[u] == distance[V[u][i]] + 1){v = V[u][i]; break;}
        u = v;
        solution.push_back(u);
    }
    print_solution(instance, solution);

/*
    vector<vector<int> > scc = strongly_connected_components(V);
    
    vector<int> scc_number(V.size());
    for(int i = 0; i < int(scc.size()); i++)
        for(int j = 0; j < int(scc[i].size()); j++)
            scc_number[scc[i][j]] = i;

    adjacency_list SCC(scc.size(), vector<int>());
    for(int i = 0; i < int(V.size()); i++)
        for(int j = 0; j < int(V[i].size()); j++)
            if(scc_number[i] != scc_number[V[i][j]])
                SCC[ scc_number[i] ].push_back( scc_number[V[i][j]] );

    vector<int> sorted = topological_sort(SCC);
    vector<int> distance(V.size(), 0);
    vector<int> used(V.size(), 0);
    vector<int> next;
    vector<vector<int> > best(V.size());
    for(int i = 0; i < int(sorted.size()); i++){
        int u = sorted[i];
        for(int j = 0; j < int(scc[u].size()); j++){
            int v = scc[u][j];
            next.assign(V.size(), -1);
            distance[v] = calculate(v, V, scc_number, distance, used, next);
            best[v] = next;
        }
    }

    int max_i = 0;
    for(int i = 0; i < int(distance.size()); i++){
        if(distance[i] > distance[max_i])
            max_i = i;
    }

    vector<int> solution;
    int u = max_i;
    int x = u;
    solution.push_back(u);
    while(best[x][u] != -1){
        if(scc_number[u] != scc_number[best[x][u]]){
            u = best[x][u];
            x = u;
        }else
            u = best[x][u];
        solution.push_back(u);
    }
    */
}

void print_solution(Instance &instance, vector<int> &solution){
    for(int i = 0; i < int(solution.size()); i++){
        string &o = instance.oligs[solution[i]].sequence;
        if(i == 0)
            printf("%s", o.c_str());
        else
            printf("%c", o[o.size()-1]);
    }
    printf("\n");
}

vector<int> topological_sort(adjacency_list &V){
    vector<int> used;
    vector<int> visited(V.size(), 0);
    for(int i = 0; i < int(V.size()); i++)
        if(!visited[i])
            dfs(i, V, visited, used);

    return used;
}

vector<vector<int> > strongly_connected_components(adjacency_list &V){
    vector<vector<int> > result; 
    int n = V.size();
    vector<int> S;
    vector<int> visited(n, 0);
    vector<int> used;

    for(int i = 0; i < n; i++)if(!visited[i])dfs(i, V, visited, S);
    adjacency_list T = transpose(V);
    

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

void dfs(int u, adjacency_list &V, vector<int> &visited, vector<int> &S){
    visited[u] = 1;
    for (int i = 0; i < int(V[u].size()); i++)
        if(!visited[ V[u][i] ])
            dfs(V[u][i], V, visited, S);
    S.push_back(u);
}

adjacency_list transpose(adjacency_list &V){
    adjacency_list T(V.size(), vector<int>());
    for (int i = 0; i < int(V.size()); i++) {
        for (int j = 0; j < int(V[i].size()); j++) {
            T[ V[i][j] ].push_back(i);
        }
    }
    return T;
}


adjacency_matrix create_adjacency_matrix(Instance &instance){
    vector<Olig> &oligs = instance.oligs;
    int n = instance.oligs.size();
    adjacency_matrix adjacency_matrix(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            adjacency_matrix[i][j] = oligs[i].distance(oligs[j]);
    return adjacency_matrix;
}

adjacency_list create_adjacency_list(vector<vector<int> > &adjacency_matrix){
    int n = adjacency_matrix.size();
    adjacency_list V(n, vector<int>());
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(adjacency_matrix[i][j] == 1 && i != j){
                V[i].push_back(j);
            }
    return V;
}

void print_graph_in_dot_format(adjacency_list &V){
    printf("digraph G{\n");
    for(int i = 0; i < int(V.size()); i++){
        for(int j = 0; j < int(V[i].size()); j++){
            printf("%d -> %d;\n",i, V[i][j]);
        }
    }
    printf("}\n");
}
