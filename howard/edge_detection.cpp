#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sobel.h"
#include "hough_line.h"
#include "laplace.h"

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
  Mat src, drawing;
  src = imread( argv[1]);
  Mat laplace = laplace(src);

  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", laplace );
  waitKey(0);
  return(0);
}

