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
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 20;
int max_thresh = 255;
RNG rng(12345);
int *rubiks, *simon, *etch;
int iRubiks = 0;
int iSimon = 0;
int iEtch = 0;
int threshHold = 10000;
FILE *file;
char ardFlag;
int USB;
struct termios tty;
struct termios tty_old;

/// Function header
void thresh_callback(int, void*);
vector<int> whatObj(vector<double> area, vector<double> arcs, int* rubiks, int* etch, int* simon);
bool findLarger(double d1, double d2);

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
	ardFlag = 'F';
	USB = open("/dev/ttyACM0",O_RDWR|O_NOCTTY);
	memset (&tty, 0 , sizeof tty);
	tty_old=tty;
	cfsetospeed(&tty, (speed_t)9600);
	cfsetispeed(&tty, (speed_t)9600);
	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;        // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;       // no flow control
	tty.c_cc[VMIN]      =   1;                  // read doesn't block
	tty.c_cc[VTIME]     =   0;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( USB, TCIFLUSH );

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

		//createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
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
	findContours( canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Get the moments
	vector<Moments> mu(contours.size() );
	vector<double> area(contours.size());
	vector<double> areaSorted(contours.size());
	vector<double> arcs(contours.size());
	vector<double> arcSorted(contours.size());
	for( size_t i = 0; i < contours.size(); i++ )
	{ 
		mu[i] = moments( contours[i], false ); 
		area[i] = contourArea(contours[i]);	
		arcs[i] = arcLength( contours[i], true );
	}

	//areaSorted=area;
	//arcSorted = arcs;
	//sort(arcSorted.begin(),arcSorted.end());
	//reverse(arcSorted.begin(),arcSorted.end());
	//sort(areaSorted.begin(),areaSorted.end());
	//reverse(areaSorted.begin(),areaSorted.end());
	//cout<<"Area vecotr length: "<<area.size()<<endl;

	if(area.size()==0 || arcs.size()==0)
		return;
	//cout<<"Contour with biggest area: "<< *max_element(area.begin(),area.end())<<endl;

	//for(int i = 0;i<9;i++)
	//{
	//	cout<<areaSorted[i]<<endl;
	//}	

	///  Get the mass centers:
	vector<Point2f> mc( contours.size() );
	for( size_t i = 0; i < contours.size(); i++ )
	{ mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00) , static_cast<float>(mu[i].m01/mu[i].m00) ); }

	/// Draw contours
	vector<int> needDrawing = whatObj(area, arcs,rubiks,etch,simon);
	if(needDrawing.size()==0)
	return;
	//threshHold=200;
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	
	//for( size_t i = 0; i< contours.size(); i++ )
	for(size_t i = 0; i< needDrawing.size(); i++) 
	{
			//cout<<area[i]<<endl;
			//if(area[i]>4000 && area[i]<5000)
			//{
			//cout<<area[i]<<endl;
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( drawing, contours, (int)needDrawing[i], color, 2, 8, hierarchy, 0, Point() );
			circle( drawing, mc[needDrawing[i]], 4, color, -1, 8, 0);
			//drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
			//circle( drawing, mc[i], 4, color, -1, 8, 0 );
			//}

	}

	namedWindow( "Contours", WINDOW_AUTOSIZE );
	imshow( "Contours", drawing );

	if(*rubiks==10)
	{
		*simon=0;
		*etch=0;
		*rubiks=0;
		write( USB, "2", 1 );
		int n = 0;
		char buf = '\0';
		cout<<"sending out 2"<<endl;
		/* Whole response*/
		do
		{
			read( USB, &buf, 1 );
		}
		while(buf!='K');
		//response.append( &buf );
		cout <<"Char from Arduino: "<<buf<<endl;
		tcflush(USB, TCIFLUSH);

	}
	if(*simon==10)
	{
		*simon=0;
		*etch=0;
		*rubiks=0;
		write( USB, "3", 1 );


		int n = 0;
		char buf = '\0';
		/* Whole response*/
		std::string response;

		do
		{
			read( USB, &buf, 1 );
		}
		while(buf!='K');
		//response.append( &buf );

		cout <<"Char from Arduino: "<<buf<<endl;


	}

	if(*etch==10)
	{
		*simon=0;
		*etch=0;
		*rubiks=0;
		write( USB, "1", 1 );


		int n = 0;
		char buf = '\0';

		/* Whole response*/
		std::string response;

		do
		{
			read( USB, &buf, 1 );
		}
		while(buf!='K');
		//response.append( &buf );

		cout <<"Char from Arduino: "<<buf<<endl;

	}


	
}

vector<int> whatObj(vector<double> area, vector<double> arcs, int* rubiks, int* etch, int* simon)
{
	int s = 0;
	int e = 0;
	int r = 0;
	vector<int> eIdx;
	vector<int> sIdx;
	vector<int> rIdx;


	for( size_t i =0; i<area.size(); i++)
	{

		if(area[i]>70&&area[i]<200)
		{
			e++;
			eIdx.push_back(i);
		}	
		if(area[i]>4000 && area[i]<5000)
		{
			r++;
			rIdx.push_back(i);
		}
		if((area[i]>200 &&area[i]<300)|| (area[i]>7000 && area[i] <8000)||(area[i]>11000))
		{
			s++;
			sIdx.push_back(i);
		}

		//if(area[i]>1000)
		//	k++;
		
	}
	cout<<"e: "<<e<<"\tr: "<<r<<"\ts: "<<s<<endl;

	if(r==9)
	{
		(*rubiks)++;
		*etch=0;
		*simon=0;
		printf("Rubik's cube! %d\n",*rubiks);
		return rIdx;

	}

	else if(s==3)
	{
		(*simon)++;
		*etch=0;
		*rubiks=0;
		printf("Simon! %d\n",*simon);
		return sIdx;
		
	}
	else if(e==1)
	{
		(*etch)++;
		*simon=0;
		*rubiks=0;
		printf("Etch! %d\n",*etch);
		return eIdx;
	}
	vector<int> emptyVector;
	return emptyVector;


}

bool findLarger(double d1, double d2)
{
return d1<d2;
}
