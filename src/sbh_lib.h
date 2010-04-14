#ifndef SBH_LIB_H
#define SBH_LIB_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Represents oligonucleotide
 */
class Olig{
    public:
        string sequence;
        Olig(string sequence);
        int distance(Olig &olig);
};

/**
 * Represents instance of SBH problem.
 * It contains the sequence length and oligonucleotides.
 */
class Instance{
    public:
        int n;
        vector<Olig> oligs;
        void read_file(string file_path);
        void print_solution(vector<int> &solution);
    private:
};


#endif
