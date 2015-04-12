#include <typeinfo>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#define PI 3.14159265
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#define E_val 2.71828



using namespace std;
using namespace cv;

// flags
// ideal_low_pass :1
// ideal_high_pass :2
// gaussian_low_pass :3
// gaussian_high_pass :4
// bw_low_pass :5
// bw_high_pass :6

double gaussianHigh(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);
    return 1.0 - exp((-d*d) / (2*d0*d0));
}
double gaussianLow(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);
    return exp((-d*d) / (2*d0*d0));
}
double bwHigh(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);   // n = 2
    return 1.0/(1 + pow((d0/d),4));
}
double bwLow(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);
    return 1.0/(1 + pow((d/d0),4));
}
double idealHigh(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);
    if(d > d0)
    {
        return 1;
    }
    return 0;
}
double idealLow(double u, double v, double d0)
{
    double d = sqrt(u*u + v*v);
    if(d > d0)
    {
        return 0;
    }
    return 1;
}

Mat createFilter(Size size, double cutoffInPixels, int flag)
{
    Mat filter(size, CV_64F);

    Point center(size.width / 2, size.height / 2);

    
    switch(flag)
    {
        case 1  : //ideal_low
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = idealLow(u - center.y, v - center.x, cutoffInPixels);
                }
            }
           break; 
        case 2  :  //ideal high
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = idealHigh(u - center.y, v - center.x, cutoffInPixels);
                }
            }
           break; 
        case 3  :  //gaussian low
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = gaussianLow(u - center.y, v - center.x, cutoffInPixels);
                }
            }
           break;
        case 4  :  //gaussian high
            printf("here");
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = gaussianHigh(u - center.y, v - center.x, cutoffInPixels);
                }
            }
            break;
        case 5  :  //bw low
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = bwLow(u - center.y, v - center.x, cutoffInPixels);
                }
            }
           break;
        case 6  :  //bw high
           for(int u = 0; u < filter.rows; u++)
            {
                for(int v = 0; v < filter.cols; v++)
                {
                    filter.at<double>(u, v) = bwHigh(u - center.y, v - center.x, cutoffInPixels);
                }
            }
           break;
        default : 
            printf("No such filter");
    }
    //imshow("filter", filter);

    return filter;
}

Mat matrix_multiply(Mat A, Mat B)
{
    Mat result = Mat::zeros(A.size().width , B.size().width, CV_64F);
    A.convertTo(A, CV_64F);
    B.convertTo(B, CV_64F);
    int i,j;
    for(i=0; i<A.size().height; i++)
    {
        for(j=0; j<A.size().width; j++)
        {
            result.at<double>(i,j) = A.at<double>(i,j) * B.at<double>(i,j);
        }
    }   
    namedWindow("multiply_mat",CV_WINDOW_AUTOSIZE);
    imshow("multiply_mat", result);
    waitKey(0);
    return result;
}

Mat fast_dft(Mat I)
{
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    imshow("Input Image"       , I   );    // Show the result
    imshow("FT", magI);
    waitKey();

    //calculating the idft
    // Mat inverseTransform;
    // dft(complexI, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    // normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
    // imshow("Reconstructed", inverseTransform);
    // waitKey();

    // Mat gauss_low = createFilter(complexI.size(), 50.0, 3);
    // Mat ghpf = matrix_multiply(gauss_low, complexI);
    // //Mat ghpf = createGaussianHighPassFilter(complexI);
    // cv::mulSpectrums(complexI,ghpf,complexI,DFT_COMPLEX_OUTPUT);

    // //show_spectrum(complexI,planes,"output");

    // cv::Mat inverseTransform;
    // cv::dft(complexI, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    // normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
    // imshow("Reconstructed", inverseTransform);
    // waitKey();

	return magI;
}



int main(int argc, char** argv)
{
	if( argc != 2)
	{
		cout << "Usage: display_image Image" << endl;
		return -1;
	}
	Mat image = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if ( !image.data )
	{ cout <<  "Could not open or find the image" << endl ; return -1;}
    Mat ft2 = fast_dft(image);
	printf("Keep on pressing enter to load images\n");

	// namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
	// imshow("Original Image", image);
	// waitKey(0);

    Mat low = createFilter(image.size(), 50.0, 1);
//    waitKey(0);
    Mat high = createFilter(image.size(), 50.0, 2);
//    waitKey(0);
    Mat gauss_low = createFilter(image.size(), 50.0, 3);
//    waitKey(0);
    Mat gauss_high = createFilter(image.size(), 50.0, 4);
//    waitKey(0);
    Mat btw_low = createFilter(image.size(), 50.0, 5);
//    waitKey(0);
    Mat btw_high = createFilter(image.size(), 50.0, 6);
//    waitKey(0);

    matrix_multiply(low, ft2);
    matrix_multiply(high, ft2);
    Mat ft = matrix_multiply(gauss_low, ft2);
    matrix_multiply(gauss_high, ft2);
    matrix_multiply(btw_low, ft2);
    matrix_multiply(btw_high, ft2);
	return 0;
}