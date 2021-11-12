//Compile: g++ p4.cpp -o p4 $(pkg-config --libs --cflags opencv4)

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    //Command line arguments processing
    if(argc != 3){
        cout << "\033[1;31mError: Usage sintax is ./p4 <input filename> <output filename>\033[0m" << endl;
        return 0;
    }
    char *inputfile = argv[1];
    char *outputfile = argv[2];

    //Read the image file
    Mat image = imread(inputfile);

    //Check if image exists
    if(image.empty()){
        cout << "\033[1;31mError: Could not open image\033[0m" << endl;
        return 0;
    }

    //Create output image object
    Mat output(image.rows, image.cols, image.type());

    //Acessing image pixels and copy them to the new image
    for(int i=0; i < image.rows; i++){
        for(int j=0 ; j < image.cols; j++)
            output.ptr<Vec3b>(i)[j] = Vec3b(image.ptr<Vec3b>(i)[j][0], image.ptr<Vec3b>(i)[j][1], image.ptr<Vec3b>(i)[j][2]);
    }

    //Show image on window
    namedWindow("Output image", WINDOW_NORMAL);
    resizeWindow("Output image", 1050, 650);
    imshow("Output image", output);
    waitKey(0);
    destroyWindow("Output image");

    //Save output image
    imwrite(outputfile ,output);    

    return 0;

}