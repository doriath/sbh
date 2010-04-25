#include "sbh_lib.h"
#include "graph.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

bool remove_edge(adjacency_list &V);
vector<int> calc(adjacency_list &V);
vector<int> simple_calc(adjacency_list &V);

int main(int argc, char **argv){
    if(argc != 2){
        printf("%s <instance_file>\n", argv[0]);
        return 1;
    }

    Instance instance;
    instance.read_file(argv[1]);
	string result;

	while (instance.oligs.size() != 1)
	{
		int min_level;
		adjacency_matrix adjacency_matrix = create_adjacency_matrix(instance, min_level);
		adjacency_list V = create_adjacency_list(adjacency_matrix, min_level);
		
		vector<int> solution = calc(V);
		result = instance.get_solution(solution);
		instance.remove_solution_nodes(solution);

		instance.oligs.insert(instance.oligs.begin(), result);
	}
	vector<int> sol(1,0);
	instance.print_solution(sol);

    return 0;
}

vector<int> simple_calc(adjacency_list &V){
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
    return solution;
}

vector<int> calc(adjacency_list &V){
    while(remove_edge(V));
    return simple_calc(V);
}

bool remove_edge(adjacency_list &V){
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
    vector<vector<int> > best(V.size());
    for(int i = 0; i < int(sorted.size()); i++){
        int s = sorted[i];
        for(int k = 0; k < int(scc[s].size()); k++){
            int u = scc[s][k];
            distance[u] = 0;
            for(int j = 0; j < int(V[u].size()); j++){
                int v = V[u][j];
                if(scc_number[v] != scc_number[u])
                    distance[u] = max(distance[u], distance[v] + 1);
            }
        }
        if(scc[s].size() > 1){
            int max_i = scc[s][0];
            for(int k = 0; k < int(scc[s].size()); k++){
                int u = scc[s][k];
                if(distance[u] > distance[max_i])
                    max_i = u;
            }
            vector<int> tmp;
            for(int j = 0; j < int(V[max_i].size()); j++)
                if(scc_number[ V[max_i][j] ] != scc_number[max_i])
                    tmp.push_back(V[max_i][j]);
            
            V[max_i] = tmp;

            return true;
        }
    }
    return false;
}
