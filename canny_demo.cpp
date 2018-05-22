#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  std::string source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    Scalar squareColor = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
   
    double maxHullRatio = 0.8 * 3.1415 / 4.0;
    const double MIN_SPOT_AREA = 30.0;    
    const double MIN_DICE_AREA = 30.0;    

    for(unsigned i = 0; i < contours.size(); i++ ) {
        vector<Point> contour = contours[i];
        vector<Point> output;
        approxPolyDP(contour, output, 0.01*arcLength(contour, true),true);
        vector<Point> hull;
        convexHull( Mat(contour), hull); 
        double area = contourArea(contour);
        double hullSize = contourArea(hull);
        if ((output.size() > 8) && (area > MIN_SPOT_AREA) && (area/hullSize > maxHullRatio)) {
            drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
        }
        if ((output.size() < 8) && area > MIN_DICE_AREA) {
            drawContours(drawing, contours, i, squareColor, 2, 8, hierarchy, 0, Point());
        }
    }

    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}
