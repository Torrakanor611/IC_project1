#include <iostream>
#include <stdio.h>
#include <sndfile.h>
#include <vector>
#include <map>
#include <cmath>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;


void showHisto(map<short, int> ch, string title) {
    vector<int> samples;
    vector<int> occur;

    for(auto i : ch) {
        samples.push_back(i.first);
        occur.push_back(i.second);
    }
    plt::bar(samples, occur);
    plt::xlabel("Samples ");
    plt::ylabel("Number of occurences");
    plt::title(title);
}

int main(int argc, char **argv) {
    
    if(argc != 2) {
        printf("ERROR!! Different number of inputs.");
        return -1;
    }

    // Read data of an audio file
    SNDFILE *infile;
    SF_INFO sfinfo;
    int readcount;
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

    // Calculate the entropy
    map<short, int> map_aud;

    for(int i = 0; i < (int) chs.size(); i++) {
        map_aud[chs[i]]++;
    }

    double entropy = 0;
    double p;
    for(auto i : map_aud) {
        p = (double) i.second / (double) chs.size();
        entropy += p * (-log2(p));
    }
    cout << "\nEntropy: " << entropy << endl;

    // Calculate the histogram of an audio sample
    map<short, int> map_ch0;
    map<short, int> map_ch1;
    map<short, int> map_mono;

    for(int i = 0; i < (int) chs.size()/2; i+=2) {
        map_ch0[chs[i]]++;
        map_ch1[chs[i+1]]++;
        map_mono[(chs[i] + chs[i+1]) / 2]++;

    }

    //Draw the plot
    plt::figure(1);
    showHisto(map_ch0, "Channel 0");

    plt::figure(2);
    showHisto(map_ch1, "Channel 1");

    plt::figure(3);
    showHisto(map_mono, "Mono Version)");

    plt::show();
    
    return 0;
}