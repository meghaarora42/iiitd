#include <typeinfo>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>


using namespace std;
using namespace cv;

Mat averaging_filter(Mat image , int n)
{
	Size size;
	size = image.size();
	int i, j,k,l, temp;
	Mat padded_image = Mat::zeros(size.width + (n - 1), size.height + (n -1), CV_8UC1);
	int padding_size = n/2;
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			padded_image.at<uchar>(i + padding_size, j + padding_size) = image.at<uchar>(i, j);
		}
	}
	Mat filter = Mat::ones(n,n,CV_8UC1);
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			temp = 0;
			for(k = 0; k < n;k++)
			{
				for(l = 0; l < n;l++)
				{
					temp += padded_image.at<uchar>(i + k,j + l)*filter.at<uchar>(k,l);
				}
			}
			if(temp/(n*n) > 255)
			{
				temp = 255;
			}
			result.at<uchar>(i, j) = temp/(n*n);
		}
	}
	namedWindow("Averaging Filter", CV_WINDOW_AUTOSIZE );
	imshow("Averaging Filter", result);
	waitKey(1);
	return result;
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
	printf("Keep on pressing enter to load images\n");
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
	imshow("Original Image", image);
	waitKey(0);
	averaging_filter(image, 3);
	waitKey(0);
	averaging_filter(image, 5);
	waitKey(0);
	averaging_filter(image, 11);
	waitKey(0);
	destroyWindow("Original Image");
	return 0;
}