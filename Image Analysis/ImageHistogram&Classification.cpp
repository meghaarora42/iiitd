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

int hist(Mat image)
{
	Size size;
	size = image.size();
	int i, j, temp;
	int hist_data[256] = {0};
	for(i = 0; i < size.height; i++)
	{
		for(j = 0; j < size.width; j++)
		{
			hist_data[(int)image.at<uchar>(i, j)]+=1;
		}
	}

	// for(i = 0; i < 256; i++)
	// {
	// 	printf("%d ", hist_data[i]);

	// }

    //Finding mean
    float mean = 0, sum = 0, deviation = 0, dev_sum = 0;
    for(i = 0; i < 256; i++)
	{
		sum += hist_data[i]*i;
	}
	mean = sum/(size.height * size.width);
	for(i = 0; i < 256; i++)
	{
		dev_sum += (pow(mean - i, 2))*hist_data[i];
	}
	deviation = pow(dev_sum/(size.height * size.width), 0.5);
	if(mean <= 100)
		printf("Mean: %f -> Dark Image\n",mean);
	else if(mean >= 155)
		printf("Mean: %f -> Light/bright Image\n",mean);
	else
	{
		if(deviation >= 50.0)
		{
			printf("Deviation: %f ->High Contrast Image\n",deviation);
		}
		else
		{
			printf("Deviation: %f ->Low Contrast Image\n",deviation);
		}
	}
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
    int max = hist_data[0];
    for(int i = 1; i < 256; i++){
        if(max < hist_data[i]){
            max = hist_data[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows using max intensity calculated above
 
    for(int i = 0; i < 255; i++){
        hist_data[i] = ((double)hist_data[i]/max)*histImage.rows;
    }
 
    // draw the intensity line for histogram
    for(int i = 0; i < 255; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - hist_data[i]), Scalar(0,0,0), 1, 8, 0);
    }
 
    // display histogram
    namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Histogram", histImage);
    namedWindow("Image", CV_WINDOW_AUTOSIZE);
    imshow("Image", image);
    waitKey();
    return 1;
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
	{ cout <<  "Could not open or find the image." << endl ; return -1;}
	hist(image);
	imshow("Image", image);
	waitKey(0);
	destroyWindow("Image");
	return 0;
}