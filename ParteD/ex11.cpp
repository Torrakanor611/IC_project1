#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
    if(argc != 3){
        puts("please give original and transformed file:");
        puts("Usage: ./bin/ex11 <original_file> <transformed_file>");
		exit (1);
    }
    // open both files
    Mat orig(imread(argv[1]));
    if(orig.empty()){
        cout << "Could not open or find the original image!\n" << endl;
        cout << "exiting..." << endl;
        return -1;
    }
    Mat trans(imread(argv[2]));
    if(trans.empty()){
        cout << "Could not open or find the transformed image!\n" << endl;
        cout << "exiting..." << endl;
        return -1;
    }

    // distortion
    double D[orig.channels()];
    int N = orig.rows * orig.cols;
    double aux = 0, sigPower;
    double max = INT_MIN;
    double min = INT_MAX;
    int mAbsError = INT_MIN;
    for(int ch = 0; ch < orig.channels(); ch++){
        aux = 0;
        for(int y = 0; y < orig.rows; y++)
            for(int x = 0; x < orig.cols; x++){
                // calcute signal power
                aux += pow(trans.at<Vec3b>(y, x)[ch] - orig.at<Vec3b>(y, x)[ch], 2);
                sigPower += pow(trans.at<Vec3b>(y, x)[ch], 2);
                // get highest and lost
                if(trans.at<Vec3b>(y, x)[ch] > max)
                    max = trans.at<Vec3b>(y, x)[ch];
                if(trans.at<Vec3b>(y, x)[ch] < min)
                    min = trans.at<Vec3b>(y, x)[ch];
                // calculate max absolute error
                if(abs(trans.at<Vec3b>(y, x)[ch] - orig.at<Vec3b>(y, x)[ch]) > mAbsError)
                    mAbsError = abs(trans.at<Vec3b>(y, x)[ch] - orig.at<Vec3b>(y, x)[ch]);
            }
        D[ch] = aux / (double) N;
    }
    for(int i = 0; i < orig.channels() - 1; i++)
        D[0] = D[i] + D[i+1];
    // SNR = sigPower / D[0]
    double SNR = 10 * log10(sigPower / D[0]);
    double PSNR = 10 * log10(max - min / D[0]);
    printf("SNR = %f dB\n", SNR);
    printf("PSNR = %f db\n", PSNR);
    printf("max. absolute per pixel error = %d\n", mAbsError);

    // show both images
    imshow("Original", orig);
    imshow("Transformada", trans);

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

// I understood that SNR is the ratio of signal power to noise power and can be used to measure the effect of noise added to images. Likewise, in PSNR, we take the square of the peak value in the image (in case of an 8 bit image, the peak value is 255) and divide it by the mean square error. Both SNR and PSNR are used to measure the quality of an image after the reconstruction and higher the value (SNR or PSNR) better is the reconstruction.