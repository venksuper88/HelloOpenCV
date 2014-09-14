/*
 * DisplayImage.cpp
 *
 *  Created on: 13-Sep-2014
 *      Author: viyer
 */

#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;

void showImage(const char* a);
void showVideo(const char* a);
void captureCamera();


int main(int argc, char** argv) {

	if (argc != 2) {

		captureCamera();


	} else {

		namedWindow("Display Image", WINDOW_OPENGL);

		//showImage(argv[1]);
		showVideo(argv[1]);

		cvDestroyWindow("Display Image");
	}
	return 0;
}

void showImage(const char* a) {

	IplImage* img = cvLoadImage(a);
	cvShowImage("Display Image", img);

	waitKey(0);

	cvReleaseImage(&img);
}
void showVideo(const char* a) {

	CvCapture* capture = cvCreateFileCapture(a);
	IplImage* frame;

	while (1) {

		// Need not clean the frame as it just points to
		// the memory allocated in capture structure
		frame = cvQueryFrame(capture);

		if (!frame)
			break;
		cvShowImage("Display Image", frame);
		char c = cvWaitKey(100);

		if (c == 27)
			break;
	}

	cvReleaseCapture(&capture);
}
void captureCamera() {
	VideoCapture vcap(0);

	int frame_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	//double fps = vcap.get(CV_CAP_PROP_FPS);

	VideoWriter video("out.mov", CV_FOURCC('m', 'p', '4', 'v'), 10,
			Size(frame_width, frame_height), true);

	double d = 1;
	for (;;) {

		Mat frame;
		Mat frame_grey;
		vcap >> frame;

		cvtColor(frame,frame_grey,CV_RGB2GRAY);
		frame_grey = frame > 128;
		video << frame_grey;
		imshow("Frame", frame);
		char c = (char) waitKey(33);
		if (c == 27)
			break;

		if (d == 100) {
			break;
		}
		d++;
	}

	video.release();
}
