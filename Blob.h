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
	Rect bound;
	double boundWidth;
	double boundHeight;
	vector <Point> contour;
	double AspectRatio;
	double DiagonalSize;
	void getBlobSpecs(vector <Point> hull);
private:
	
};

