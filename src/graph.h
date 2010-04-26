#ifndef GRAPH_H
#define GRAPH_H

#include "sbh_lib.h"
#include <vector>
using namespace std;

typedef vector<vector<int> > adjacency_list;
typedef vector<vector<int> > adjacency_matrix;

adjacency_matrix create_adjacency_matrix(Instance &, int &);
adjacency_matrix create_adjacency_matrix_relative(Instance &, int &);
adjacency_list create_adjacency_list(adjacency_matrix &, int);
vector<vector<int> > strongly_connected_components(adjacency_list &);
void dfs(int, adjacency_list &,vector<int> &, vector<int> &);
adjacency_list transpose(adjacency_list &);
vector<int> topological_sort(adjacency_list &);
void print_graph_in_dot_format(adjacency_list &);

#endif
