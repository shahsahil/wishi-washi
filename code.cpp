
#include "stdafx.h"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	char key;
	VideoCapture cap;
	if (!cap.open(0))
		return 0;
	int X = cap.get(3);
	int Y = cap.get(4);
	int x, y;
	Mat M(Y, X, CV_8UC3, Scalar::all(0));
	Mat frame1;
	int count(0);
	cap >> frame1;
	while (1){
		imshow("Webcam", M);
		Mat frame2;
		cap >> frame2;
		//checking the difference between two frames
		for (x = 1; x < X; x++){
			for (y = 1; y < Y; y++){
				if (frame1.at<cv::Vec3b>(y, x)[0]> frame2.at<cv::Vec3b>(y, x)[0] + 4 || frame1.at<cv::Vec3b>(y, x)[0] < frame2.at<cv::Vec3b>(y, x)[0] - 4 || frame1.at<cv::Vec3b>(y, x)[1] > frame2.at<cv::Vec3b>(y, x)[1] + 4 || frame1.at<cv::Vec3b>(y, x)[1] < frame2.at<cv::Vec3b>(y, x)[1] - 4 || frame1.at<cv::Vec3b>(y, x)[2] > frame2.at<cv::Vec3b>(y, x)[2] + 4 || frame1.at<cv::Vec3b>(y, x)[2] < frame2.at<cv::Vec3b>(y, x)[2] - 4){
					M.at<cv::Vec3b>(y, x)[0] = frame2.at<cv::Vec3b>(y, x)[0];
					M.at<cv::Vec3b>(y, x)[1] = frame2.at<cv::Vec3b>(y, x)[1];
					M.at<cv::Vec3b>(y, x)[2] = frame2.at<cv::Vec3b>(y, x)[2];
				}
			}
		}
		frame1=frame2;//frame1 = frame2.clone();
		key = cvWaitKey(1);
		if (char(key) == 27)
			break;
	}
	return 0;
}