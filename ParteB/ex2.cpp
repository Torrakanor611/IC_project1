//Compile: g++ ex2.cpp -o ex2

#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
    //Command line arguments processing
    if(argc != 3){
        cout << "\033[1;31mError: Usage sintax is ./p2 <input filename> <output filename>\033[0m" << endl;
        return 0; 
    }

    //Filename variables definition and atribution
    char *ifilename = argv[1];
    char *ofilename = argv[2];
    //Output and input streams definition
    ifstream ifs;
    ofstream ofs;

    //Read input filename
    ifs.open(ifilename);

    //If file does not exist
    if(ifs.fail()){
        cout << "\033[1;31mError: File doesn't exists\033[0m" << endl;
        ifs.close();
        return 0;
    }

    //Read output filename
    ofs.open(ofilename);
    
    char c;
    //Read characters and Write on output file
    while(true){
        ifs >> c;
        if(ifs.eof())
            break;
        ofs << c;
    }

    //Close streams
    ifs.close();
    ofs.close();

    return 0;
}