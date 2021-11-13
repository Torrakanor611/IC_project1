#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv){
    if(argc != 2){
        puts("please give input file:");
        puts("Usage: ./histimagefile input_file");
		exit (1);
    }

    Mat image = imread(argv[1], IMREAD_COLOR);
    vector<Mat> bgr_planes;

    split(image, bgr_planes);
    int histSize = 256;
    float range[] = { 0, 256 } ; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    imshow("Image", image);
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0));
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    
    for( int i = 1; i < histSize; i++ ){
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                        Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                        Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                     Scalar( 0, 0, 255), 2, 8, 0  );
    }
    imshow("Histogram RGB color distribuition", histImage );

    Mat image_grey = imread(argv[1], IMREAD_GRAYSCALE );
    Mat grey_hist;
    calcHist(&image_grey, 1, 0, Mat(), grey_hist, 1, &histSize, &histRange, uniform, accumulate);
    imshow("Image in grey scale", image_grey);
    Mat histImage_grey( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0));
    normalize(grey_hist, grey_hist, 0, histImage_grey.rows, NORM_MINMAX, -1, Mat());
    for(int i = 1; i < histSize; i++){
        line(histImage_grey, Point( bin_w*(i-1), hist_h - cvRound(grey_hist.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(grey_hist.at<float>(i)) ),
                        Scalar( 255, 255, 255), 2, 8, 0);
    }
    imshow("Histogram grey scale", histImage_grey);
    
    // stop display
    puts("press q to stop display...");
    int key = waitKey(0);
    while(true){
        if(key == 'q'){
                puts("stoped!");
                break;
            }
    }
    destroyAllWindows();
    return 0;
}