#include "Vehicle.h"

const int FRAME_HEIGHT = 360;
const int FRAME_WIDTH = 640;

Vehicle::Vehicle()
{
}


void Vehicle::trackVehicles() 
{
	//Mat object to store the diffrence of the frame
	Mat diffFrame;
	
	Mat threshedImg;

	//Mat object to grab the frames from the video
	Mat  videoFrame2;
	
	//to store the copies of the frame
	Mat videoFrame2Copy, videoFrame1Copy,threshedImgCopy;

	_video >> videoFrame2;

	//resize the video to 640x360;
	resize(videoFrame2, videoFrame2, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	//copy the frame for other use
	videoFrame2Copy = videoFrame2.clone();
	videoFrame1Copy = _firstFrame.clone();

	cvtColor(videoFrame1Copy, videoFrame1Copy, CV_BGR2GRAY);
	cvtColor(videoFrame2Copy, videoFrame2Copy, CV_BGR2GRAY);

	GaussianBlur(videoFrame1Copy, videoFrame1Copy, Size(5, 5), 0);
	GaussianBlur(videoFrame2Copy, videoFrame2Copy, Size(5, 5), 0);

	absdiff(videoFrame2Copy, videoFrame1Copy, diffFrame);

	//calcute the FPS
	//putText(_firstFrame, _FPS, Point(600, 100), CV_FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 8);
	
	//display the frames
	imshow("Video", _firstFrame);

	threshold(diffFrame, threshedImg, 30, 255.0, CV_THRESH_BINARY);

	//dilate and erode for better results
	dilate(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));
	dilate(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));
	erode(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));

	//clone the threshed image because finding contors will change the image
	threshedImgCopy = threshedImg.clone();

	//find the contours
	vector <vector<Point>> contours;

	findContours(threshedImgCopy, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	Mat contoursImg(threshedImgCopy.size(), CV_8UC3, Scalar(0,0,0));

	for (int i = 0; i < contours.size(); i++) {

		Moments moment = moments(contours[i]);
		if (moment.m00 > 5000) {
			drawContours(contoursImg, contours, i, Scalar(255, 255, 255), -1);
		}
	}

	imshow("Contours", contoursImg);

	imshow("thresh", threshedImg);

	_firstFrame = videoFrame2;

}

void Vehicle::getFirstframe(VideoCapture &video)
{
	_video = video;

	
	//sprintf(_FPS, "%d", _video.get(CV_CAP_PROP_FPS));

	Mat firstFrame;

	_video.read(firstFrame);

	//resize the video to 640x360;
	resize(firstFrame, firstFrame, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	_firstFrame = firstFrame;
}