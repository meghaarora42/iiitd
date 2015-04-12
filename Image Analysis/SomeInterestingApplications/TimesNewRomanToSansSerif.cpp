#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//Convert Times New Roman font text into Sans Serif font using morphological operations.


using namespace std;
using namespace cv;


Mat erosion_dst, dilation_dst;

void thinningGuoHallIteration(cv::Mat& im, int iter)  //Guo thinning referred from internet
{
    cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1); 

    for (int i = 1; i < im.rows; i++)
    {
        for (int j = 1; j < im.cols; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1); 
            uchar p9 = im.at<uchar>(i-1, j-1);

            int C  = (!p2 & (p3 | p4)) + (!p4 & (p5 | p6)) +
                     (!p6 & (p7 | p8)) + (!p8 & (p9 | p2));
            int N1 = (p9 | p2) + (p3 | p4) + (p5 | p6) + (p7 | p8);
            int N2 = (p2 | p3) + (p4 | p5) + (p6 | p7) + (p8 | p9);
            int N  = N1 < N2 ? N1 : N2;
            int m  = iter == 0 ? ((p6 | p7 | !p9) & p8) : ((p2 | p3 | !p5) & p4);

            if (C == 1 && (N >= 2 && N <= 3) & (m == 0))
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
}


void thinningGuoHall(cv::Mat& im)
{
    im /= 255;

    cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
    cv::Mat diff;

    do {
        thinningGuoHallIteration(im, 0);
        thinningGuoHallIteration(im, 1);
        cv::absdiff(im, prev, diff);
        im.copyTo(prev);
    } 
    while (cv::countNonZero(diff) > 0);

    im *= 255;
}

Mat Erosion(Mat src, int erosion_size)
{
  int erosion_type;
  Mat element = getStructuringElement( MORPH_RECT,   //MORPH_CROSS, MORPH_ELLIPSE
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  erode( src, erosion_dst, element );
  imshow( "Erosion", erosion_dst );
  waitKey(0);
  return erosion_dst;
}


Mat Dilation(Mat src, int dilation_size)
{
  int i,j;

  Mat element = getStructuringElement( MORPH_RECT,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );

  dilate( src, dilation_dst, element );
  
  Size size;
  size = dilation_dst.size();

  imshow( "Dilation", dilation_dst );
  waitKey(0);
  return dilation_dst;
}

int main( int argc, char** argv )
{
	if( argc != 3)
	{
		cout << "Usage: display_image Image" << endl;
		return -1;
	}

    Mat src = imread( argv[1] );

    if ( !src.data )
    { cout <<  "Could not open or find the image" << endl ; return -1;}

    imshow("Original Image", src);
    waitKey(0);

    Mat desired_output = imread(argv[2]);
	
    cv::Mat src_t = cv::imread(argv[2]);
    if (src.empty())
        return -1;

    cv::Mat temp;
    cv::cvtColor(src_t, temp, CV_BGR2GRAY);
    bitwise_not ( temp, temp );
    thinningGuoHall(temp);
    imshow("After thinning", temp);
    waitKey(0);

    bitwise_not ( temp, temp );
    Mat eroded = Erosion(temp, 2);
    Mat dilated = Dilation(eroded, 2);
    imshow("Final", eroded);
    imshow("Desired Image", desired_output);
    waitKey(0);
    return 0;
  }


