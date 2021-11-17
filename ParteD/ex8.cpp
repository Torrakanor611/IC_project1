//Compile: g++ ex8.cpp -std=c++11 -I/usr/include/python3.8 -lpython3.8 -o ex8

#include <iostream>
#include <vector>
#include <math.h>
#include "AudioFile.h"
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

int main(int argc, char* argv[])
{
    //Command line arguments processing
    if(argc != 2){
        cout << "\033[1;31mError: Usage sintax is ./ex8 <input filename>\033[0m" << endl;
        return 0; 
    }
    char *inputfile = argv[1];
    
    //AudioFile
    AudioFile<double> af;
    af.shouldLogErrorsToConsole(false);
    //Load audiofile
    if(af.load (inputfile) == 0){
        cout << "\033[1;31mERROR: File doesn't exist or otherwise can't load file\033[0m" << endl;
        return 0; 
    }
    //Vectors to plots
    vector<double> originalsamples;
    vector<double> samples;
    vector<int> nums;
    int cnt = 0;

    int option = -1;
    while(option != 0 && option != 1){
        cout << "Choose quantization option (0 for Mid-riser or 1 for Mid-tread):";
        cin >> option;
    }
    

    //Get audiofile metainfo
    int numChannels = af.getNumChannels();
    int numSamples = af.getNumSamplesPerChannel();
    //int bitDeph = af.getBitDepth();

    int Amax = 1, Amin = -1;
    int nLevels = 8;
    double delta = (Amax - Amin) / pow(nLevels, 2);


    for(int j = 0; j < numChannels; j++){
        for(int i = 0; i < numSamples; i++){
            originalsamples.push_back(af.samples[j][i]);

            if(option == 0) //Mid-riser quantization
                af.samples[j][i] = delta * (floor((af.samples[j][i]/delta)) + 0.5);
            else            //Mid-tread quantization
                af.samples[j][i] = delta * floor((af.samples[j][i]/delta) + 0.5);
            
            samples.push_back(af.samples[j][i]);
            nums.push_back(cnt);
            cnt++;
        }
    }

    af.setBitDepth(nLevels);
    af.save("res.wav");

    //Draw the plots
    plt::figure(1);
    plt::plot(nums, originalsamples);
    plt::title("Original File");
    plt::figure(2);
    plt::title("Result File");
    plt::plot(nums, samples);
    plt::show();


    return 0;
}