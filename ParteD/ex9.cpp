#include <iostream>
#include <stdio.h>
#include <cmath>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cout << "ERROR!! Different number of inputs." << endl;
        return -1;
    }

    // Read data of the file
    Mat inimg = imread(argv[1]);
    if(inimg.empty()) {
        cout << "ERROR!! Couldn't open image." << endl;
        return -1;
    }

    // Check parameters 
    int option = -1;
    while(option != 0 && option != 1){
        cout << "Choose quantization option (0 for Mid-riser or 1 for Mid-tread): ";
        cin >> option;
    }
    int Amax = inimg.depth() == 0 ? pow(2, 8) : inimg.depth() == 2 ? pow(2, 16) : pow(2, 32);
    int Amin = 0;
    int nLevels = 6;
    double delta = (Amax - Amin) / nLevels;

    Mat outimg = Mat(inimg.rows, inimg.cols, inimg.type());
    for (int i = 0; i < inimg.channels(); i++) {
        for (int x = 0; x < inimg.cols; x++) {
            for (int y = 0; y < inimg.rows; y++) {
                if(option == 0) //Mid-riser quantization
                    outimg.at<Vec3b>(y,x)[i] = delta * (floor((inimg.at<Vec3b>(y, x)[i]/delta)) + 0.5);
                else            //Mid-tread quantization
                    outimg.at<Vec3b>(y, x)[i] = delta * floor((inimg.at<Vec3b>(y, x)[i]/delta) + 0.5); 
            }
        }
    }

    imwrite(argv[2], outimg);

    imshow("Original Image", inimg);
    imshow("Quantized Image", outimg);

    // stop display
    puts("press q or ESC to stop display...");
    int key = waitKey(-1);
    while(true){
        if(key == 'q' || key == 27){
                puts("stoped!");
                break;
            }
    }
    destroyAllWindows();
}