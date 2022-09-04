/**
***
***	Author:		Nilton Jose Rizzo
***	Date:			08/01/2019
***	Git:			git@gitlab.com:ufrrj/opencv.git
***	LICENSE:		see LICENSE file
***
***
***	OpenCV How-to by examples
***
*** Functions from OpenCV:
***
***   imread		Read image from file
***	namedWindow	Create a new window do show a image
***   imshow		Show Image on Window
***   waitkey		Wait a key pressed 
***	cvtColor		Transform image from one color space to another
***
*** Methods
***
***	Mat::empty()	Return true if image is empty, else return false
***
***	In vi/vim editors use tabstop=3
***	In geany editor use preferences->Editor->Ident
***		set width to 	3
***		type				tab
**/

#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


////</
	#include "opencv2/imgproc.hpp"
	#include "opencv2/imgcodecs.hpp"
	#include "opencv2/highgui.hpp"
	#include <iostream>
////>/

/**
*** Open the namespaces
**/
using namespace std;
using namespace cv;

int main(int argc, char** argv ) {
////</
	 cv::CommandLineParser parser(argc, argv,
                               "{@input   |lena.jpg|input image}"
                               "{ksize   k|1|ksize (hit 'K' to increase its value at run time)}"
                               "{scale   s|1|scale (hit 'S' to increase its value at run time)}"
                               "{delta   d|0|delta (hit 'D' to increase its value at run time)}"
                               "{help    h|false|show help message}");
  cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
  parser.printMessage();
  cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";
////>/

Mat		image;		// Image object
Mat		gray;			// Destination image in GRAY color space
string	filename;	// Image file name

	filename = "../imagens/imagem_01.jpg";

	// Read image from disk
	image = imread(filename);

	// Check if image was loaded
	if ( image.empty() ){
		cerr << "Image [ " << filename << " ] not found!" << endl;
		cerr << "Quitting!" << endl;
		exit (-1);
	}
////</
	  // First we declare the variables we are going to use
	Mat src, src_gray;
	Mat grad;
	const String window_name = "Sobel Demo - Simple Edge Detector";
	int ksize = parser.get<int>("ksize");
	int scale = parser.get<int>("scale");
	int delta = parser.get<int>("delta");
	int ddepth = CV_16S;
////>/

	// Create a window for display.
	namedWindow( "Original Image", WINDOW_NORMAL); 

	// Show our image ins , image );                
	imshow( "Original Image", image );                

	////</
	Mat grad_x, grad_y;
	////>/
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);

	// Create a window for display.
	namedWindow( "GRAY Image", WINDOW_NORMAL); 

	// Show our image ins , image );                
	imshow( "GRAY Image", gray );                

	waitKey(0);			// Wait for any key was pressed and return
							// the key code pressed or -1 if no key pressed
							// Parameter
							// =0 - Wait for until key pressed
							// >0 - Wait by N miliseconds and return
	return 0;

}
