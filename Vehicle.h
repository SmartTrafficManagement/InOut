#pragma once

//opencv headers
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

class Vehicle
{
public:
	
	Vehicle();

	void trackVehicles();
	void getFirstframe(VideoCapture &video);

private:
	
	VideoCapture _video;
	Mat _firstFrame;
};

