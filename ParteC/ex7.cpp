#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void RGB(Mat *image);
void YCbCr();
void GRAY(Mat *image);

int main(int argc, char **argv){
    if(argc != 2){
        puts("please give input file:");
        puts("Usage: ./bin/ex7 <input_file>");
		exit (1);
    }

    Mat image = imread(argv[1], IMREAD_COLOR);
    RGB(&image);
    Mat image_gray = imread(argv[1], IMREAD_GRAYSCALE);
    GRAY(&image_gray);
    
    int r, g, b;
    for(int y = 0; y < image.rows; y++){
        for(int x = 0; x < image.cols; x++){
            cv::Vec3d bgr = image.at<cv::Vec3b>(y,x);
            b = bgr[0];
            g = bgr[1];
            r = bgr[2];
            
        }
    }
    
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
    
    return 0;
}

void RGB(Mat *image){
    vector<Mat> bgr_planes;
    split(*image, bgr_planes);
    int histSize = 256;
    float range[] = { 0, 256 } ; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    imshow("Original RGB", *image);
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
    imshow("Histogram RGB color distribuition", histImage);
}

void GRAY(Mat *image){
    int histSize = 256;
    float range[] = { 0, 256 } ; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true; bool accumulate = false;
     int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat gray_hist;
    calcHist(image, 1, 0, Mat(), gray_hist, 1, &histSize, &histRange, uniform, accumulate);
    imshow("GRAY scale", *image);
    Mat histImage_gray( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0));
    normalize(gray_hist, gray_hist, 0, histImage_gray.rows, NORM_MINMAX, -1, Mat());
    for(int i = 1; i < histSize; i++){
        line(histImage_gray, Point( bin_w*(i-1), hist_h - cvRound(gray_hist.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(gray_hist.at<float>(i)) ),
                        Scalar( 255, 255, 255), 2, 8, 0);
    }
    imshow("Histogram GRAY scale", histImage_gray);
}