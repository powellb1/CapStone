/**
 * @function moments_demo.cpp
 * @brief Demo code to calculate moments
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SerialStream.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

using namespace cv;
using namespace std;
using namespace LibSerial;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
int *rubiks, *simon, *etch;
int iRubiks = 0;
int iSimon = 0;
int iEtch = 0;
int threshHold = 10000;
char abuffer[] = {'1'};
char *datum = abuffer;



/// Function header
void thresh_callback(int, void* );
int whatObj(vector<Moments> mu, int* rubiks, int* etch, int* simon);
bool WriteData(char *buffer, unsigned int nbChar);

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load source image and convert it to gray
  //src = imread( argv[1], 1 );
  VideoCapture capture;
   capture.open( -1 );

rubiks=&iRubiks;
simon=&iSimon;
etch=&iEtch;
  if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
     while( capture.read(src) )
     {


   //-- 3. Apply the classifier to the frame
       if( src.empty() )
       { 
  printf(" --(!) No captured frame -- Break!");
            break;
        }
  /// Convert image to gray and blur it
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

         int c = waitKey(10);
       if( (char)c == 'c' ) { break; }
  }
  return(0);
}

/**
 * @function thresh_callback
 */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;  
  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Get the moments
  vector<Moments> mu(contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }

  ///  Get the mass centers:
  vector<Point2f> mc( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00) , static_cast<float>(mu[i].m01/mu[i].m00) ); }

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
     {
	if(mu[i].m00>1000)
	{
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
       circle( drawing, mc[i], 4, color, -1, 8, 0 );
	}
     }

  /// Show in a window




threshHold = whatObj(mu,rubiks,etch,simon);
  /// Calculate the area with the moments 00 and compare with the result of the OpenCV function
  //printf("\t Info: Area and Contour Length \n");
  for( size_t i = 0; i< contours.size(); i++ )
     {
	if(mu[i].m00>threshHold)
	{
       //printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", (int)i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
       circle( drawing, mc[i], 4, color, -1, 8, 0 );
	}
	
     }
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
 if((*rubiks==10) || (*simon==10) || (*etch==10))
 {
	*simon=0;
	*etch=0;
	*rubiks=0;


	getchar();
 }
}

int whatObj(vector<Moments> mu, int* rubiks, int* etch, int* simon)
{
int k=0;
for( size_t i =0; i<mu.size(); i++)
{
if(mu[i].m00>1000)
k++;

}
if(k==4)
{
(*etch)++;
printf("Etch! %d\n",*etch);

return 1000;
}

k=0;

for( size_t i =0; i<mu.size(); i++)
{
if(mu[i].m00>2500)
k++;

}

if(k==18)
{
(*rubiks)++;
printf("Rubik's cube! %d\n",*rubiks);

return 2500;
}
k=0;

for( size_t i =0; i<mu.size(); i++)
{
if(mu[i].m00>1500)
k++;

}

if(k==10)
{
(*simon)++;
printf("Simon! %d\n",*simon);
return 1500;
}
}

bool WriteData(char *buffer, unsigned int nbChar)
{
DWORD bytesSend;

if(!WriteFile(hSerial, (void *)buffer, nbChar, &bytesSend, 0))
{
return false;
}
else
return true;

}


