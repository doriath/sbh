#include "sbh_lib.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

char result[1000];

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
	int repeats = 0;
    for(int i = 0; i < length - 9; i++){
        string olig = string(result+i, result+i+10);
		if (oligs.find(olig) != oligs.end()) repeats++;
        oligs.insert(olig);
    }

    int count = 0;
	int countNotListed = 0;
    for(int i = 0; i < int(instance.oligs.size()); i++){
        if(oligs.count(instance.oligs[i].sequence))
		{
            count++;
		}
		else
		{
			countNotListed++;
		}
    }
    printf("%d %d %d %d\n", length, count, int(instance.oligs.size()) - count, repeats);

    return 0;
}
