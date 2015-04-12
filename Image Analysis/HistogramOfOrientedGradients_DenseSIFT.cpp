#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"


// Q.2 HOG(Also called as Dense SIFT)
// As discussed SIFT in the class. If we remove the key point detection stage, and choose a set of points
 // defined using a uniform grid, it's called Dense SIFT. You have to extract the HOG features using these 
 // predefined set of points. For obtaining features, use the same block/sub-block arrangement as David Lowe 
 // (leading to feature vector of size 128). There should be 8x8 predefined key-points. Use cosine distance 
 // measure to obtain match-scores (you can use in-built function for distance measure).

 // Experiment protocol: Use first four images of every person as the enrollment templates, and remaining as
 // query samples. When comparing a query image against all the enrollment images, the one which has the highest
 //  match-scores (least distance score) with query is declared the predicted match. And, the corresponding 
 //  label is predicted for the query sample. Using this method report the accuracy of both the approaches.

// Dataset: Orl dataset, 64x64 version from www.cad.zju.edu.cn/home/dengcai/Data/FaceData.html

using namespace cv;
using namespace std;


int threshold (int i, int j) {
  if (i >= j)
    return 0;
  else
    return 1;
}


vector<int> histogram (Mat image) {
  std::vector<int> histogram(256);
  for (int i=0; i<image.rows; i++) 
  {
    for (int j=0; j<image.cols; j++) 
    {
      int index = (int)image.at<uchar>(i,j);
      histogram[index] +=1;
    }
  }
  return histogram;
}

double chi_square_distance (vector<int> vector1, vector<int> vector2) {
  int sub = 0;
  double result = 0.0;
  double add =0.0;
  for (int i=0; i< vector1.size(); i++) {
    sub = vector1[i]-vector2[i];
    add = (double)(vector1[i]+vector2[i]);
    if (sub != 0)
      result += sub*sub/add;
  }
  return result;
}


vector<int> lbp (Mat image) {
  Size s = image.size();
  Mat lbp_image = Mat::zeros(s.height, s.width, CV_8UC1);
  int i, j, center;
  double temp;

  for (i=1; i<s.height-1; i++) 
  {
    for (j=1; j<s.width-1; j++) 
    {
      center = image.at<uchar>(i,j);
      temp = pow(2,0)*threshold(center, image.at<uchar>(i,j-1)) + pow(2,1)*threshold(center, image.at<uchar>(i+1,j-1)) + pow(2,2)*threshold(center, image.at<uchar>(i+1,j)) + pow(2,3)*threshold(center, image.at<uchar>(i+1,j+1)) + pow(2,4)*threshold(center, image.at<uchar>(i,j+1)) + pow(2,5)*threshold(center, image.at<uchar>(i-1,j+1)) + pow(2,6)*threshold(center, image.at<uchar>(i-1,j)) + pow(2,7)*threshold(center, image.at<uchar>(i-1,j-1));
      lbp_image.at<uchar>(i,j) = (int)temp;
    }
  }

  imshow("Pattern Image", lbp_image);
  waitKey(0);

  Mat lbp_patch;
  vector<int> features, tempMat;
  int rows = lbp_image.rows/16;
  int columns = lbp_image.cols/16;
  for (int i=0; i<columns; i++) 
  {
    for (int j=0; j<rows; j++) 
    {
      Mat lbp_patch = lbp_image(Rect(16*i, 16*j, 16, 16));
      tempMat = histogram(lbp_patch);
      if (i==0 && j==0) 
      {
        features = tempMat;   //adding histogram for first patch
      }
      else {
        features.insert(features.end(), tempMat.begin(), tempMat.end());
      }
    }
  }
  return features;
}





// This function is taken from internet (http://stackoverflow.com/questions/9743485/natural-sort-of-directory-filenames-in-c)
bool compareNat(const std::string& a, const std::string& b) {
  if (a.empty())
      return true;
  if (b.empty())
      return false;
  if (std::isdigit(a[0]) && !std::isdigit(b[0]))
      return true;
  if (!std::isdigit(a[0]) && std::isdigit(b[0]))
      return false;
  if (!std::isdigit(a[0]) && !std::isdigit(b[0])) {
      if (a[0] == b[0])
          return compareNat(a.substr(1), b.substr(1));
      return (std::toupper(a[0]) < std::toupper(b[0]));
  }
  std::istringstream issa(a);
  std::istringstream issb(b);
  int ia, ib;
  issa >> ia;
  issb >> ib;
  if (ia != ib)
      return ia < ib;

  std::string anew, bnew;
  std::getline(issa, anew);
  std::getline(issb, bnew);
  return (compareNat(anew, bnew));
}

int main (int argc, char **argv) {
  int i, j;

  Mat image;
  vector<int> features;
  vector<vector<int> > feature_gallery;
  vector<string> files_gallery = vector<string>();
  vector<string> files_probe = vector<string>();

  string fileName;
  if (argc < 3)
    {cout<<"Usage: ./q2 Image_gallery Image_probe\n"; return -1;}
  
  DIR *dp_gallery, *dp_probe;                      
  struct dirent *dir_gallery, *dir_probe;           
  if ((dp_gallery = opendir(argv[1])) == NULL) {
    cout<<"No such folder "<< argv[1]<<"\n";
  }
  if ((dp_probe = opendir(argv[2])) == NULL) {
    cout<<"No such folder "<< argv[2]<<"\n";
  }
  
  while ((dir_gallery = readdir(dp_gallery)) != NULL) { 
    files_gallery.push_back(string(dir_gallery->d_name));
  }

  while ((dir_probe = readdir(dp_probe)) != NULL) { 
    files_probe.push_back(string(dir_probe->d_name));
  }
  std::sort(files_gallery.begin(), files_gallery.end(), compareNat);
  std::sort(files_probe.begin(), files_probe.end(), compareNat);
  
  for (i=0; i< files_gallery.size(); i++) {  
    if (files_gallery[i][0] != '.') {
      fileName = files_gallery[i]; 
      image = imread(argv[1] + files_gallery[i], CV_LOAD_IMAGE_GRAYSCALE);
      if (!image.data) {
        cout<<"Could not read image"<<endl;
        return -1;
      }
      features = lbp(image);
      feature_gallery.push_back(features);
    }
  }

  int accuracy = 0;

  int flag = 0;

  for (i=0; i< files_probe.size(); i++) 
  {
    if(i%6 == 0)           // For one match per object
    {
      flag = 0;
    }

    if (files_probe[i][0] != '.') 
    {

      fileName = files_probe[i]; 
      image = imread(argv[2] + files_probe[i], CV_LOAD_IMAGE_GRAYSCALE);
      imshow("input",image);
      if (!image.data) {
        cout<<"Could not read image"<<endl;
        return -1;
      }
      features = lbp(image);

      double min_chi_distance = chi_square_distance(features, feature_gallery[0]);
      int best_match = 0;
      double chi_distance;

      for (j=0; j< feature_gallery.size(); j++)
      {
        chi_distance = chi_square_distance(features, feature_gallery[j]);
        
        if( chi_distance < min_chi_distance)
        {
          min_chi_distance = chi_distance;
          best_match = j;

        }
      }

      if (best_match/4 == i/6)
      {
        accuracy += 1;
        flag = 1;
      }
    }
  }
  cout << (accuracy/240.0)*100 << endl;

  return 0;
}


