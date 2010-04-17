#include "sbh_lib.h"
#include "graph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char **argv){
    Instance instance;
    instance.read_file(argv[1]);

	int min_level;
    adjacency_matrix adjacency_matrix = create_adjacency_matrix(instance, min_level);
    adjacency_list V = create_adjacency_list(adjacency_matrix, 1);

    print_graph_in_dot_format(V);
    return 0;
}
