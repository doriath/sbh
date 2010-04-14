#include "sbh_lib.h"

void Instance::read_file(string file_path){
    FILE *file = fopen(file_path.c_str(), "r");
    char str[20];

    fscanf(file, "%d", &n);
    while(fscanf(file, "%s", str) == 1)
        oligs.push_back(Olig(str));

    fclose(file);
}

Olig::Olig(string sequence){
    this->sequence = sequence;
}

void Instance::print_solution(vector<int> &solution){
    for(int i = 0; i < int(solution.size()); i++){
        string &o = oligs[solution[i]].sequence;
        if(i == 0)
            printf("%s", o.c_str());
        else
            printf("%c", o[o.size()-1]);
    }
    printf("\n");
}

/*
This one is invalid when used on words with different lengths (gives unproper results).
We can omit this behaviour, because our words have the same length. :)
*/
int Olig::distance(Olig &olig){
    for (int i = 1; i < int(sequence.size()); i++) {
        bool ok = true;
        for(int j = i; j < int(olig.sequence.size()); j++) {
            if(sequence[j] != olig.sequence[j - i]){
                ok = false;
                break;
            }
        }
        if(ok)
            return i;
    }
    return sequence.size();
}
