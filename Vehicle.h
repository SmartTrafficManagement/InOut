#pragma once

#include <string>
#include <iostream>

#include "Blob.h"

class Vehicle
{
public:
	
	Vehicle();

	void trackVehicles();
	void getFirstframe(VideoCapture &video);

private:

	Blob _blob;
	vector <Blob> _Blob;

	char _FPS[3];

	VideoCapture _video;
	
	Mat _firstFrame;
	vector <vector<Point>> _contours;
	vector <vector<Point>> _carBlobs;
	Mat convexImg;

	void _extractCars(vector < vector<Point> > &convexHulls);
};

