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

/*
 *Implement gradient and Laplacian and apply them on 3 images.  Next, read an image, compute laplacian 
 *of the image, sharpened the image obtained by adding original image and laplacian output, apply sobel
 *gradient on original image as well sharpened image. Analyze these two resulting images. 
 *
 */

Mat laplacian(Mat image)
{
	Size size;
	int n = 3;
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

	int filter[3][3] = {{0, 1, 0},
              {1, -4, 1},
              {0, 1, 0}};
    
    float temp;
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
					temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
				}
			}
			if(temp > 255)
			{
				temp = 255;
			}
			else if(temp < 0)
			{
				temp = 0 ;
			}
			result.at<uchar>(i, j) = (int) temp;
		}
	}
	namedWindow("Laplacian Filter", CV_WINDOW_AUTOSIZE );
	imshow("Laplacian Filter", result);
	waitKey(0);
	return result;
}

Mat sobel_x(Mat image)
{
	Size size;
	int n = 3;
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

	int filter[3][3] = {{-1, 0, 1},
              {-2, 0, 2},
              {-1, 0, 1}};
    
    float temp;
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
					temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
				}
			}
			if(temp > 255)
			{
				temp = 255;
			}
			else if(temp < 0)
			{
				temp = 0 ;
			}
			result.at<uchar>(i, j) = (int) temp;
		}
	}
	namedWindow("sobel_x", CV_WINDOW_AUTOSIZE);
	imshow("soble_x", result);
	waitKey(0);
	return result;
}

Mat sobel_y(Mat image)
{
	Size size;
	int n = 3;
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

	int filter[3][3] = {{1, 2 , 1},
              {0, 0, 0},
              {-1, -2, -1}};
    
    float temp;
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
					temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
				}
			}
			if(temp > 255)
			{
				temp = 255;
			}
			else if(temp < 0)
			{
				temp = 0 ;
			}
			result.at<uchar>(i, j) = (int) temp;
		}
	}
	namedWindow("soble_y", CV_WINDOW_AUTOSIZE );
	imshow("soble_y", result);
	waitKey(0);
	return result;
}

Mat sharp(Mat image)
{
	Size size;
	int n = 3;
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

	int filter[3][3] = {{0, -1, 0},
              {-1, 5, -1},
              {0, -1, 0}};
    
    float temp;
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
					temp += padded_image.at<uchar>(i + k,j + l)*filter[k][l];
				}
			}
			if(temp > 255)
			{
				temp = 255;
			}
			else if(temp < 0)
			{
				temp = 0 ;
			}
			result.at<uchar>(i, j) = (int) temp;
		}
	}
	namedWindow("Sharp", CV_WINDOW_AUTOSIZE );
	imshow("sharp", result);
	waitKey(0);
	return result;
}

Mat add_image(Mat image1, Mat image2)    //for sobel
{
	Size size1, size2;
	size1 = image1.size();
	size2 = image2.size();
	if(size1 != size2)
	{
		cout << "Incompatible image sizes." << endl;
		return image1;
	}
	int i, j, temp;
	Mat result = Mat::ones(size1.height, size1.width, CV_8UC1);
	for(i = 0; i < size1.height; i++)
	{
		for(j = 0; j < size1.width; j++) //given like this in OpenCV documnetation
		{
			temp = sqrt(image1.at<uchar>(i, j)*image1.at<uchar>(i, j) + image2.at<uchar>(i, j)*image2.at<uchar>(i, j));
			if (temp > 255)
				result.at<uchar>(i, j) = 255;
			else
				result.at<uchar>(i, j) = temp;
		}
	}
	imshow("A + B", result);
	waitKey(0);
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
	Mat lap = laplacian(image);
	// waitKey(0);

	// printf("Sobel on original\n");
	Mat soble1 = sobel_x(image);
	// waitKey(0);
	Mat sobel2 = sobel_y(image);
	// waitKey(0);
	add_image(soble1, sobel2);
	// waitKey(0);

	Mat sharp_i = sharp(image);
	// waitKey(0);

	printf("Sobel on sharp\n");
	Mat sobel3 = sobel_x(sharp_i);
	// waitKey(0);
	Mat sobel4 = sobel_y(sharp_i);
	// waitKey(0);
	add_image(sobel3, sobel4);
	// waitKey(0);
	destroyWindow("Original Image");
	return 0;
}