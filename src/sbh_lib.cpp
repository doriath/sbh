#include "sbh_lib.h"

Instance::~Instance(){
}

void Instance::read_file(string file_path){
    FILE *file = fopen(file_path.c_str(), "r");
    vector<string> oligonucleotides;
    char str[20];

    fscanf(file, "%d", &n);
    while(fscanf(file, "%s", str) == 1)
        oligonucleotides.push_back(str);

    calculate_adjacency_matrix(oligonucleotides);

    fclose(file);
}

void Instance::calculate_adjacency_matrix(vector<string> oligonucleotides){
    adjacency_matrix = new int *[n];
    for (int i = 0; i < n; i++)
        adjacency_matrix[i] = new int[n];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = oligonucleotide_distance(oligonucleotides[i], oligonucleotides[j]);
        }
    }
}

int Instance::oligonucleotide_distance(string first, string second){
    return 1;
}
