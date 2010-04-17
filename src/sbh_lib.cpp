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

string Instance::get_solution(vector<int> &solution){
	string result;
	Olig old_olig = oligs[solution[0]];
	Olig new_olig = oligs[solution[0]];
	result.append(new_olig.sequence.c_str());
    for(int i = 1; i < int(solution.size()); i++){
		old_olig = new_olig;
        new_olig = oligs[solution[i]];
		result.append(new_olig.sequence.substr(old_olig.sequence.length() - old_olig.distance(new_olig)));
    }
	return result;
}

int Olig::distance(Olig &olig){
    for (int i = 1; i < int(sequence.size()); i++) {
        bool ok = true;
		int count = 0;
        for(int j = i; j < int(sequence.size()); j++) {
            if(sequence[j] != olig.sequence[j - i]){
                ok = false;
                break;
            }
			count++;
        }
		if(ok && count != olig.sequence.size())
            return i;
    }
    return sequence.size();
}

void Instance::remove_solution_nodes(vector<int> solution){
	sort(solution.begin(), solution.end());
	reverse(solution.begin(), solution.end());
    for(int i = 0; i < int(solution.size()); i++){
		oligs.erase(oligs.begin() + solution[i]);
    }
}