#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
    Instance instance;
    instance.read_file("../instances/positive/9.200+20");

    printf("%d\n", instance.n);
    for (int i = 0; i < 10; i++) {
        printf("%s\n", instance.oligs[i].sequence.c_str());
    }

    int adjacency_matrix[instance.n][instance.n];
    vector<Olig> &oligs = instance.oligs;
    for(int i = 0; i < instance.n; i++)
        for(int j = 0; j < instance.n; j++)
            adjacency_matrix[i][j] = oligs[i].distance(oligs[j]);
    
    for(int i = 0; i < instance.n; i++)
        for(int j = 0; j < instance.n; j++)
            if(adjacency_matrix[i][j] == 1)
                printf("%s %s\n", oligs[i].sequence.c_str(), oligs[j].sequence.c_str());

    return 0;
}
