/*
 * DisplayImage.cpp
 *
 *  Created on: 13-Sep-2014
 *      Author: viyer
 */

#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;

int main( int argc, char** argv )
{
  Mat image;
  image = imread( argv[1], 0 );

  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }

  namedWindow( "Display Image", WINDOW_OPENGL );
  imshow( "Display Image", image );

  waitKey(0);

  return 0;
}


