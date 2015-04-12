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

Mat scale(Mat image, float Sx, float Sy)
{
	Size size;
	size = image.size();
	int i, j;
	int i_old,j_old;
	Mat result = Mat::ones((Sy*size.width), (Sx*size.height), CV_8UC1);
	for(i = 0; i < (Sy*size.width); i++)
	{
		i_old = (i/Sy);
		for(j = 0; j < (Sx*size.height); j++)
		{
			j_old = (j/Sx);
			if(i_old < 0 || j_old < 0 || i_old >= size.width || j_old >= size.height)
			{
				result.at<uchar>(i, j) = 0;
			}
			else
			{
				result.at<uchar>(i, j) = image.at<uchar>(i_old, j_old);
			}
		}
	}

	imshow("Scaled", result);
	return result;
}

Mat translate(Mat image, float dx, float dy)
{
	Size size;
	size = image.size();
	int i, j;
	int i_new, j_new;

	Mat result = Mat::ones((size.width + dy), (size.height + dx), CV_8UC1);

	for (i = 0; i < size.height; i++)
    {
	    i_new = i + dy;
	    for (j = 0; j < size.width; j++)
        {
		    j_new = j + dx;
		    result.at<uchar>(i_new, j_new) = image.at<uchar>(i, j);
        }
	}
	imshow("Translated", result);
	return result;
}

// Mat rotate_alternate(Mat img, float angle)
// {
// 	Mat image = translate(img, 100, 100);
// 	Size size;
// 	size = image.size();
// 	int i, j;
// 	int i_old,j_old;

// 	Mat result = Mat::ones(4*size.height, 4*size.width, CV_8UC1);

// 	for(i = 0; i < 4*size.height; i++)
// 	{
// 		for(j = 0; j < 4*size.width; j++)
// 		{
//   			i_old = (i*cos(angle*PI/180)) + (j*sin(angle*PI/180)) ;
//   			j_old = (j*cos(angle*PI/180)) - (i*sin(angle*PI/180)) ;
// 			if(i_old <  0 || j_old < 0 || i_old > size.width || j_old > size.height)
// 			{
// 			 	result.at<uchar>(i, j) = 0;
// 			}
// 			else
// 			{
// 			  result.at<uchar>(i, j) = image.at<uchar>(i_old, j_old);
// 			}
			
// 		}
// 	}
// 	imshow("Rotated", result);
// 	return result;
// }

Mat rotate(Mat image, float angle)
{
	Size size;
	size = image.size();
	int i, j;
	int a = (image.rows / 2);
    int b = (image.cols / 2);
	int i_new,j_new;

	Mat result = Mat::ones((int)(size.height),(int)(size.width), CV_8UC1);

	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
  			i_new = (((i-a)*cos(angle*PI/180)) - ((j-b)*sin(angle*PI/180)) + a);
  			j_new = (((j-b)*cos(angle*PI/180)) + ((i-a)*sin(angle*PI/180)) + b);
			if(i_new <  0 || j_new < 0 || i_new >= (int)(size.width) || j_new >= (int)(size.height))
			{
			 	//Do nothing 
			}
			else
			{
			  result.at<uchar>(i_new, j_new) = image.at<uchar>(i, j);

			}
			
		}
	}
	imshow("Rotated", result);
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
	int option;
	int data1, data2;
	float sx,sy;
	float angle;
	if ( !image.data )
	{ cout <<  "Could not open or find the image" << endl ; return -1;}
	
	printf("\nRotation: 1, Translation: 2, Scaling: 3, Affine: 4, Exit: 5\n");
	scanf("%d", &option);
	switch(option)
	{
	    case 1  :
	    	printf("Rotate anti-clockwise by angle (in degrees): ");
	    	scanf("%f",&angle);
	        rotate(image, angle);
	        namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
			imshow("Original Image", image);
			waitKey(0);
	        destroyWindow("Original Image");
	    	break; 
	    case 2  :
	    	printf("Translate along X-direction by (within 1000px): ");
	    	scanf("%d",&data1);
	    	printf("Translate along Y-direction by (within 500px): ");
	    	scanf("%d",&data2);
	        translate(image, data1, data2);
	        namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
			imshow("Original Image", image);
			waitKey(0);
	        destroyWindow("Original Image");
	        break; 
	    case 3  :
	    	printf("Scale along X-direction by (within 0.5 and 5): ");
	    	scanf("%f",&sx);
	    	printf("Scale along Y-direction by (within 0.5 and 5): ");
	    	scanf("%f",&sy);
	        scale(image, sx, sy);
	        namedWindow("Original Image", CV_WINDOW_AUTOSIZE );
			imshow("Original Image", image);
			waitKey(0);
	        destroyWindow("Original Image");
	        break; 
	    case 4  :
	        printf("Scale along X-direction by (within 0.5 and 5): ");
	    	scanf("%f",&sx);
	    	printf("Scale along Y-direction by (within 0.5 and 5): ");
	    	scanf("%f",&sy);
	    	printf("Rotate anti-clockwise by angle (in degrees): ");
	    	scanf("%f",&angle);
	    	printf("Translate along X-direction by (within 1000px): ");
	    	scanf("%d",&data1);
	    	printf("Translate along Y-direction by (within 500px): ");
	    	scanf("%d",&data2);
	    	rotate((scale((translate(image, data1, data2)), sx,sy)), angle);
	    	// scale(translate(rotate(image, angle), data1, data2), sx, sy);
	    	imshow("Original Image", image);
	    	waitKey(0);
	        destroyWindow("Original Image");
	        break; 
	    case 5  :
	    	exit(0);
	        break; 
	    default : 
	    	destroyWindow("Original Image");
	    	printf("Enter correct option");
	}
	return 0;
}
