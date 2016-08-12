#pragma once

#include <string>

//opencv headers
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

class Vehicle
{
public:
	
	Vehicle();

	void trackVehicles();
	void getFirstframe(VideoCapture &video);

private:
	
	char _FPS[3];

	VideoCapture _video;
	Mat _firstFrame;
};

