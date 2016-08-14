#pragma once

#include <string>
#include <iostream>

#include "Blob.h"

class Vehicle
{
public:
	
	Vehicle();

	void trackVehicles();
	void getFirstframe(VideoCapture &video, vector <Blob> existingBlob);
	void addBlobToExistingBlobs(Blob &current_blob,vector<Blob> &existing_blob,int minDistIndex);
	void addNewBlob(Blob &current_blob,vector <Blob> &existing_blob);
	void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
private:

	vector <Blob> _existingBlob(10);

	bool isFirstFrame;
	int frameCount;
	char _FPS[3];

	VideoCapture _video;
	
	Mat _firstFrame;
	vector <vector<Point>> _contours;
	vector <vector<Point>> _carBlobs;
	Mat convexImg;

	void _extractCars(vector < vector<Point> > &convexHulls ,Blob &_blob,vector <Blob> &_Blob);
	void _matchExistingFrameBlobwWithCurrentFrameBlob(vector <Blob> &existingBlob, vector <Blob> &currentBlob);
	double distanceBetweenPoints(Point point1, Point point2);
};
