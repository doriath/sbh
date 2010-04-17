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
	
	//do calculations

    return 0;
}
