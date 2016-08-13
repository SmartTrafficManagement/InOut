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
	void addBlobToExistingBlobs(Blob &current_blob,vector<Blob> &existing_blob,int minDistIndex);
	void addNewBlob(Blob &current_blob,vector <Blob> &existing_blob);

private:

	vector <Blob> _existingBlob;

	bool isFirstFrame = true;

	char _FPS[3];

	VideoCapture _video;
	
	Mat _firstFrame;
	vector <vector<Point>> _contours;
	vector <vector<Point>> _carBlobs;
	Mat convexImg;

	void _extractCars(vector < vector<Point> > &convexHulls);
	void _matchExistingFrameBlobwWithCurrentFrameBlob(vector <Blob> &existingBlob, vector <Blob> &currentBlob);
	double distanceBetweenPoints(Point point1, Point point2);
};

