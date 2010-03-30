#ifndef SBH_LIB_H
#define SBH_LIB_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class Instance{
    public:
        int n;
        int **adjacency_matrix;
        void read_file(string file_path);
        ~Instance();

    private:
        void calculate_adjacency_matrix(vector<string> oligonucleotides);
        int oligonucleotide_distance(string first, string second);
};

#endif
