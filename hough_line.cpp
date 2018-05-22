#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "hough_line.h"

using namespace cv;
using namespace std;

void help()
{
 cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
         "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

Mat houghLine(Mat src)
{
 if(src.empty()) {
     help();
     cout << "src empty" << endl;
     return src;
 }

 Mat dst, cdst;
 Canny(src, dst, 50, 200, 3);
 cvtColor(dst, cdst, CV_GRAY2BGR);

 vector<Vec4i> lines; 
 HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
 for( size_t i = 0; i < lines.size(); i++ ) {
   Vec4i l = lines[i];
   line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
 }
 return cdst;
}
