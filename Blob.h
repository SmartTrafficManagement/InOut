#pragma once

//opencv headers
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

class Blob
{
public:
	
	Blob();
	
	int intNumOfConsecutiveFramesWithoutAMatch;

	void getBlobSpecs(vector <Point> hull);
	void predictNextPosition();

	Rect bound;
	
	double boundWidth;
	double boundHeight;
	
	vector <Point> contour;
	
	double AspectRatio;
	double DiagonalSize;
	
	vector <Point> centerPositions;
	Point predictedNextPosition;

	bool existingStillBeingTracked;
	bool blnCurrentMatchFoundOrNewBlob;

private:
	
};

