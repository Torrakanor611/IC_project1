//Compile: g++ ex3.cpp -o ex3

#include <iostream>
#include "AudioFile.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Command line arguments processing
    if(argc != 3){
        cout << "\033[1;31mError: Usage sintax is ./p3 <input filename> <output filename>\033[0m" << endl;
        return 0; 
    }
    char *inputfile = argv[1];
    char *outputfile = argv[2];

    //Audiofile Object
    AudioFile<double> af;
    //Load audiofile
    af.load (inputfile);
    //Get numSamples per Channel
    int numSamples = af.getNumSamplesPerChannel();
    //Get num Channels
    int numChannels = af.getNumChannels();
    
    AudioFile<double> output;
    // Set both the number of channels and number of samples per channel of output
    output.setAudioBufferSize (numChannels, numSamples);
    // Set the number of samples per channel of output
    output.setNumSamplesPerChannel (numSamples);
    // Set the number of channels of output
    output.setNumChannels (numChannels);
    // Set Sample Rate
    output.setSampleRate(af.getSampleRate());
    // Set Bit Depth
    output.setBitDepth(af.getBitDepth());
    
    //Buffer to store samples
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(numChannels);
    for(int i = 0; i < numChannels; i++)
        buffer[i].resize(numSamples);

    //Copy samples from one buffer to another
    for(int j = 0; j < numChannels; j++){
        for(int i = 0; i < numSamples; i++){
            buffer[j][i] = af.samples[j][i];

        }
    }

    //Set audiobuffer
    output.setAudioBuffer(buffer);
    output.save(outputfile);
    cout << "\033[1;34mCopy Successfully!\033[0m" << endl;

    return 0;
}