#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

char result[100000];

int main(int argc, char **argv){
    if(argc != 3){
        printf("%s <instance_file> <result_file>\n", argv[0]);
        return 1;
    }
    Instance instance;
    instance.read_file(argv[1]);
    
    FILE *file = fopen(argv[2], "r");
    fscanf(file, "%s", result);

    set<string> oligs;
    int length = strlen(result);
    for(int i = 0; i < length; i++){
        string olig = string(result+i, result+i+10);
        oligs.insert(olig);
    }

    int count = 0;
    for(int i = 0; i < int(instance.oligs.size()); i++){
        if(oligs.count(instance.oligs[i].sequence))
            count++;
    }
    printf("%d\n", count);

    return 0;
}
