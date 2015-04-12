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

using namespace std;
using namespace cv;


Mat gaussian(Mat image, int n, double sigma)
{
	Size size;
	size = image.size();
	int i, j,k,l;
	Mat padded_image = Mat::zeros(size.width + (n - 1), size.height + (n -1), CV_8UC1);
	int padding_size = n/2;
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			padded_image.at<uchar>(i + padding_size, j + padding_size) = image.at<uchar>(i, j);
		}
	}


	double filter [n][n];
    int rad = n / 2;
    double b = 0, sum = 0;
    for (i = -rad; i <= rad; i++)
    {
        for (j = -rad; j <= rad; j++)
        {
            filter[i + rad][j + rad] = (1/(2*PI*sigma*sigma))*exp(-1*((i*i+j*j)/(2*sigma*sigma)));
            sum += filter[i + rad][j + rad];
        }
    }
    double temp;
	Mat result = Mat::ones(size.width, size.height, CV_8UC1);
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			if(((i > 100 && i< 138) && (j> 85 && j < 130)) || ((i > 89 && i< 99) && (j> 182 && j < 202)) || ((i > 101 && i< 128) && (j> 195 && j < 207)))
			{
				temp = 0;
				for(k = 0; k < n;k++)
				{
					for(l = 0; l < n;l++)
					{
						temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
					}
				}
				if(temp > 255)
				{
					temp = 255;
				}
				result.at<uchar>(i, j) = (int) temp;
			}
			else
			{
				result.at<uchar>(i, j) = padded_image.at<uchar>(i + padding_size, j + padding_size);
			}
			// temp = 0;
			// 	for(k = 0; k < n;k++)
			// 	{
			// 		for(l = 0; l < n;l++)
			// 		{
			// 			temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
			// 		}
			// 	}
			// 	if(temp > 255)
			// 	{
			// 		temp = 255;
			// 	}
			// 	result.at<uchar>(i, j) = (int) temp;
		}
	}
	namedWindow("Gaussian Filter", CV_WINDOW_AUTOSIZE );
	imshow("Gaussian Filter", result);
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
	// gaussian(image, 3, 0.8);
	// waitKey(0);
	gaussian(image, 11, 1.5);
	waitKey(0);
	// gaussian(image, 17, 3);
	// waitKey(0);
	destroyWindow("Original Image");
	return 0;
}