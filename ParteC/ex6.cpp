#include <iostream>
#include <stdio.h>
#include <sndfile.h>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
    
    if(argc != 2) {
        printf("ERROR!! Different number of inputs.");
        return -1;
    }

    SNDFILE *infile;
    SF_INFO sfinfo;
    int k, readcount;
    vector<short> chs;
    short ch[2];

	if (! (infile = sf_open (argv[1], SFM_READ, &sfinfo))) {
        printf ("Error!! Could not open file : %s\n", argv[1]) ;
        return -1;
	}

	while ((readcount = (int) sf_readf_short (infile, ch, 1)) > 0) {
        chs.push_back(ch[0]);
        chs.push_back(ch[1]);
    }

	sf_close (infile) ;

    map<short, int> map_aud;

    for(int i = 0; i < chs.size(); i++) {
        map_aud[chs[i]]++;
    }

    double entropy = 0;
    double p;
    for(auto i : map_aud) {
        cout << i.first << " -> " << i.second << endl;
        p = (double) i.second / (double) chs.size();
        entropy += p * (-log2(p));
    }
    cout << "\nEntropy: " << entropy << endl;
    
    return 0;
}