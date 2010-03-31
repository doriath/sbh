#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int dfs(int u, vector<int> V[], int color[]){
    int size = 1;
    color[u] = 1;
    for(int i = 0; i < int(V[u].size()); i++)
        if(!color[V[u][i]])
            size += dfs(V[u][i], V, color);
    return size;
}

int main(){
    Instance instance;
    instance.read_file("../instances/positive/9.200+20");

    vector<Olig> &oligs = instance.oligs;
    int n = instance.oligs.size();
    int adjacency_matrix[n][n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            adjacency_matrix[i][j] = oligs[i].distance(oligs[j]);
 
    vector<int> V[n];
    int in_deg[n], out_deg[n];
    memset(in_deg, 0, sizeof(in_deg));
    memset(out_deg, 0, sizeof(out_deg));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(adjacency_matrix[i][j] == 1){
                V[i].push_back(j);
                in_deg[j]++;
                out_deg[i]++;
            }

    for(int i = 0; i < n; i++){
        if(in_deg[i] == 0)printf("in = 0 for %d\n", i);
        if(out_deg[i] == 0)printf("out = 0 for %d\n", i);
    }

    int color[n];
    memset(color, 0, sizeof(color));
    for(int i = 0; i < n; i++)if(!color[i]){
        printf("Size: %d\n", dfs(i, V, color));
    }

    return 0;
}
