// eyetoy.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;
Mat perframe(Mat frame2, Mat M);
Mat frame1;
int X, Y;

int main(int argc, char** argv)
{
	
	char key;

	VideoCapture cap;
	if (!cap.open(0))
		return 0;
	X = cap.get(3);
	Y = cap.get(4);
	Mat M(Y, X, CV_8UC3, Scalar::all(0));
	Mat outputFrame, foutputFrame;
	Mat frame3;
	cap >> frame1;
	while (1){
		Mat frame2;
		cap >> frame2;
		M = perframe(frame2, M);
		frame2.copyTo(outputFrame, M);

		flip(outputFrame, foutputFrame, 1);
		key = cvWaitKey(1);
		if (char(key) == 27)
			break;
		frame2 = foutputFrame;
		imshow("Webcam", frame2);
	}
	return 0;
}

Mat perframe(Mat frame2, Mat M){
	Mat diff;
	absdiff(frame1, frame2, diff);
	float pixelsc;
	
	//USE THRESHOLD and MASK functions to optimize -- This is what the function actually does
	float threshold = 25;
	for (int x = 1; x < X; x++){
		for (int y = 1; y < Y; y++){
			Vec3b pixel = diff.at<Vec3b>(y, x);
			pixelsc = sqrt(pixel[0] * pixel[0] + pixel[1] * pixel[1] + pixel[2] * pixel[2]);
			if (pixelsc>threshold){
				//need to remove mask from x,y i.e. from M 
				M.at<Vec3b>(y, x)[0] = 255;
				M.at<Vec3b>(y, x)[1] = 255;
				M.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
	frame1 = frame2;//frame1 = frame2.clone()
	return M;
}