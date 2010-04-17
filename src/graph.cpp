#include "graph.h"

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


adjacency_matrix create_adjacency_matrix(Instance &instance, int &min_level){
	min_level = 200; //FIXME - it should be a value that exceeds the length of the longest oligonucleotid in library
    vector<Olig> &oligs = instance.oligs;
    int n = instance.oligs.size();
    adjacency_matrix adjacency_matrix(n, vector<int>(n));

    for(int i = 0; i < n; i++)
	{
        for(int j = 0; j < n; j++)
		{
            adjacency_matrix[i][j] = oligs[i].distance(oligs[j]);
			if (i==j) adjacency_matrix[i][j] = min_level;
			if (adjacency_matrix[i][j] < min_level) min_level = adjacency_matrix[i][j];
		}
	}
    return adjacency_matrix;
}

adjacency_list create_adjacency_list(vector<vector<int> > &adjacency_matrix, int edge_level){
    int n = adjacency_matrix.size();
    adjacency_list V(n, vector<int>());
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(adjacency_matrix[i][j] == edge_level && i != j){
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
