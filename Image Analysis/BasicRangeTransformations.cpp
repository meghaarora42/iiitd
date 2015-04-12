#include <typeinfo>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <math.h>
#define PI 3.14159265
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

Mat compliment_image(Mat image)
{
	Size size;
	size = image.size();
	int i, j, temp;
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
				result.at<uchar>(i, j) = 255 - image.at<uchar>(i, j) ;
		}
	}
	namedWindow("Image Negative", CV_WINDOW_AUTOSIZE );
	imshow("Image Negative", result);
	waitKey(1);
	return result;
}

Mat power_law(Mat image, int c, float gamma)
{
	Size size;
	size = image.size();
	int i, j, temp;
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
				result.at<uchar>(i, j) = c*(pow((image.at<uchar>(i, j)/255.0),gamma))*255;
		}
	}
	namedWindow("Power Law", CV_WINDOW_AUTOSIZE );
	imshow("Power Law", result);
	waitKey(1);
	return result;
}

Mat contrast_stretch(Mat image)
{
	Size size;
	size = image.size();
	int i, j, temp;
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			if(image.at<uchar>(i, j) < 75)
				result.at<uchar>(i, j) = 0;
			else if(image.at<uchar>(i, j) > 175)
				result.at<uchar>(i, j) = 255;
			else
				result.at<uchar>(i, j) = image.at<uchar>(i, j);
		}
	}
	namedWindow("Contrast Stretched", CV_WINDOW_AUTOSIZE );
	imshow("Contrast Stretched", result);
	waitKey(1);
	return result;
}


Mat log_transformation(Mat image, int c)
{
	Size size;
	size = image.size();
	int i, j;
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
				result.at<uchar>(i, j) = c*(log(image.at<uchar>(i, j) + 1));
		}
	}
	namedWindow("Log Transformation", CV_WINDOW_AUTOSIZE );
	imshow("Log Transformation", result);
	waitKey(1);
	return result;
}

int main(int argc, char** argv)
{
	if( argc != 2)
	{
		cout << "Usage: display_image Image_1" << endl;
		return -1;
	}
	Mat image = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if ( !image.data )
	{ cout <<  "Could not open or find the image" << endl ; return -1;}
	compliment_image(image);
	power_law(image, 1, 1.5 );    // c , gamma
	contrast_stretch(image);
	log_transformation(image, 20);
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
	imshow("Original Image", image);
	waitKey(0);
	destroyWindow("Original Image");
	return 0;
}