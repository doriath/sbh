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

/*
This function uses only one loop and is little bit faster in most case scenario.
To be honest - on words with length == 10 the difference is unnoticeable...
Tested on different scenarios and it should work correct.
*/
/*
int Olig::distance(Olig &olig){
	int current = 1;
	int distance = 1;
    for (int i = 1; i < int(sequence.size()); i++)
	{
		if (sequence[i] != olig.sequence[i-distance])
		{
			distance += current;
			if (sequence[i] == olig.sequence[i-distance+1])
			{
				distance--;
			}
			current = 1;
		}
		else current++;
    }
    return distance;
}
*/
