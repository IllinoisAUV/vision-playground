#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "laplace.h"
#include <string>

using namespace cv;

Mat laplace(Mat &src)
{
  Mat src_gray, dst;
  int kernel_size = 3;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  if( !src.data )
    { return src; }

  /// Remove noise by blurring with a Gaussian filter
  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Apply Laplace function
  Mat abs_dst;

  Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( dst, abs_dst );

  return abs_dst;
}

