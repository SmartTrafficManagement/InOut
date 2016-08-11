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
	
	Mat threshedImg,blurImg,grayImg;

	//Mat object to grab the frames from the video
	Mat  videoFrame2;
	
	//to store the copies of the frame
	Mat videoFrame2Copy;

	////grab the frames into the Mat object
	//_video >> videoFrame1;

	////copy the frame for other use
	//videoFrame1Copy = videoFrame1.clone();

	////resize the video to 640x360;
	//resize(videoFrame1, videoFrame1, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	_video >> videoFrame2;

	//resize the video to 640x360;
	resize(videoFrame2, videoFrame2, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	//copy the frame for other use
	videoFrame2Copy = videoFrame2.clone();

	absdiff(videoFrame2, _firstFrame, diffFrame);

	//display the frames
	imshow("Video", _firstFrame);

	cvtColor(diffFrame, grayImg, CV_BGR2GRAY);

	GaussianBlur(grayImg, blurImg, Size(5, 5), 0);

	threshold(blurImg, threshedImg, 30, 255.0, CV_THRESH_BINARY);

	imshow("thresh", threshedImg);

	_firstFrame = videoFrame2Copy;

}

void Vehicle::getFirstframe(VideoCapture &video)
{
	_video = video;

	Mat firstFrame;

	_video.read(firstFrame);

	//resize the video to 640x360;
	resize(firstFrame, firstFrame, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	_firstFrame = firstFrame;
}