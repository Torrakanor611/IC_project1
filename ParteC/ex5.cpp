//Compile: g++ ex5.cpp -std=c++11 -I/usr/include/python3.8 -lpython3.8 -o ex5

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <ctype.h>
#include <numeric>
#include <tgmath.h>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

int main(int argc, char* argv[])
{
    //Command line arguments processing
    if(argc != 2){
        cout << "\033[1;31mError: Usage sintax is ./p4 <input filename>\033[0m" << endl;
        return 0;
    }
    char *inputfile = argv[1];

    //Map to store characters and their respective number of occurences
    map<char, int> m;
    //Vectors to draw the plot 
    vector<int> values;
    vector<string> letters;
    vector<int> nums;
    //Output and input streams definition
    ifstream ifs;

    //Open file
    ifs.open(inputfile);

    //If file does not exist
    if(ifs.fail()){
        cout << "\033[1;31mError: File doesn't exists\033[0m" << endl;
        ifs.close();
        return 0;
    }
    
    char c;
    //Read file characters
    int i = 0;
    while(true){        
        ifs >> c;
        if(ifs.eof())
            break;
        
        //Insert key in map or update it's occurence
        if(int(c) >= 0){
            if(m.count(c) == 0){
                m[c] = 1;
                letters.push_back(string(1, c));
                nums.push_back(i);
                i++;
            }
            else
                m[c]++;
        }
    }

    //Close data stream
    ifs.close();
    
    //Sort letters alphabetically
    sort(letters.begin(), letters.end());
    
    //Update values vector for plot displaying 
    for(string s : letters)
        values.push_back(m[s[0]]);

    //Calculate entropy    
    int total = accumulate(values.begin(), values.end(), 0);
    double prob, inf, entropy = 0;
    for(int v : values){
        prob = (double)v / (double)total;
        inf = log(prob);
        entropy += (prob*inf);
    };
    entropy = -1*entropy;
    cout << "\033[1;34mEntropy: " << entropy << "\033[0m" << endl;
    
    //Draw the plot
    plt::xticks(nums, letters);
    plt::bar(nums, values);
    plt::xlabel("Characters in the file");
    plt::ylabel("Number of occurences");
    plt::show();

    return 0;
}