#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

// You are given an image with text. Run two segmentation 
// algorithms on image to extract the text and one should be contour based. Compare both segmentation approaches.

Mat src;
RNG rng(12345);

void thresh_callback()
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  threshold( src, threshold_output, 100 , 255, THRESH_BINARY );
  imshow("Threshold_Output", threshold_output);
  findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

  for( int i = 0; i < contours.size(); i++ )
     { 
      approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
      boundRect[i] = boundingRect( Mat(contours_poly[i]) );
      minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
     }

  cvtColor( src, src, CV_GRAY2BGR );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       //drawContours( src, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       rectangle( src, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
       //circle( src, center[i], (int)radius[i], color, 2, 8, 0 );
     }

  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", src );
  waitKey(0);
}

int main( int argc, char** argv)
{
  src = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );

  //cvtColor( , src_gray, CV_BGR2GRAY );
  //blur( src, src, Size(3,3) );

  namedWindow( "Source", CV_WINDOW_AUTOSIZE );
  imshow( "Source", src );

  thresh_callback();

  waitKey(0);
  return(0);
}

