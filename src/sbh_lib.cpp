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
