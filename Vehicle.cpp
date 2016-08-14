#include "Vehicle.h"

const int FRAME_HEIGHT = 360;
const int FRAME_WIDTH = 640;

Vehicle::Vehicle()
{
}


void Vehicle::trackVehicles() 
{
	Blob _blob;
	vector <Blob> _Blob;

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
	//imshow("Video", _firstFrame);

	threshold(diffFrame, threshedImg, 30, 255.0, CV_THRESH_BINARY);

	//dilate and erode for better results
	dilate(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));
	dilate(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));
	erode(threshedImg, threshedImg, getStructuringElement(CV_SHAPE_RECT, Size(5, 5)));

	//clone the threshed image because finding contors will change the image
	threshedImgCopy = threshedImg.clone();

	//find the contours

	findContours(threshedImgCopy, _contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	Mat contoursImg(threshedImgCopy.size(), CV_8UC3, Scalar(0,0,0));

	drawContours(contoursImg, _contours, -1, Scalar(255, 255, 255), -1);

	vector < vector<Point> > _convexHulls(_contours.size());

	////extract the convex hulls out of the contours
	for (int j=0; j < _contours.size(); j++) {

		convexHull(_contours[j], _convexHulls[j]);
	}

	convexImg=Mat(_firstFrame.size(), CV_8UC3, Scalar(0, 0, 0));

	//extract the cars out of the video
	_extractCars(_convexHulls, _blob,_Blob);

	imshow("Contours", contoursImg);

	imshow("thresh", threshedImg);

	//_Blob.clear();
	//_existingBlob.clear();
	_firstFrame = videoFrame2.clone();

	isFirstFrame = false;

	frameCount++;

}

void Vehicle::getFirstframe(VideoCapture &video, vector <Blob> existingBlob)
{
	_video = video;

	_existingBlob = existingBlob;
	//sprintf(_FPS, "%d", _video.get(CV_CAP_PROP_FPS));

	Mat firstFrame;

	_video.read(firstFrame);

	//resize the video to 640x360;
	resize(firstFrame, firstFrame, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);

	_firstFrame = firstFrame;

	isFirstFrame = true;

	frameCount = 2;
}

void Vehicle::_extractCars(vector < vector<Point> > &convexHulls, Blob &_blob, vector <Blob> &_Blob)
{


	//get the blob and calculate its specifications like height,width etc.
	for (int i = 0; i < _contours.size(); i++) {
	
		_blob.getBlobSpecs(convexHulls[i]);
		//store the blobs that qualify minimum requiremnet.
		if (_blob.bound.area() >= 600 && _blob.boundWidth >= 100 && _blob.boundWidth<250 &&
			_blob.AspectRatio >= 0.7&&_blob.AspectRatio <= 1.2&&
			_blob.boundHeight > 50&&_blob.boundHeight<=350 && _blob.DiagonalSize > 100.0) {
		
					_Blob.push_back(_blob);
			}
	
	}

	
	//clear the convexhull vector to add new values
	convexHulls.clear();

	for (int i = 0; i < _Blob.size(); i++) {
	
		convexHulls.push_back(_Blob[i].contour);

	}

	drawContours(convexImg, convexHulls, -1, Scalar(255, 255, 255), -1);

	imshow("Blobs", convexImg);

	for (int i = 0; i < _Blob.size(); i++) {

		rectangle(_firstFrame, _Blob[i].bound, Scalar(0, 255, 0), 2);

	}

	imshow("Video", _firstFrame);
	
	//try to match the next frame blobs with the current frame blobs
	if (isFirstFrame == true) {

		for (int i = 0; i < _Blob.size(); i++) {
		
			_existingBlob.push_back(_Blob[i]);
		}
	}
	else {
	
		_matchExistingFrameBlobwWithCurrentFrameBlob(_existingBlob,_Blob);
	}

	drawBlobInfoOnImage(_existingBlob, _firstFrame);

	
	imshow("Video", _firstFrame);
	
}

void Vehicle::_matchExistingFrameBlobwWithCurrentFrameBlob(vector <Blob> &existingBlob, vector <Blob> &currentBlob)
{
	for (int i = 0; i < existingBlob.size(); i++) {
	
		//add some boolean
		existingBlob[i].blnCurrentMatchFoundOrNewBlob = false;

		existingBlob[i].predictNextPosition();
	}

	for (int i = 0; i < currentBlob.size(); i++) {
	
		int indexOfMinDist = 0;
		
		double minDist = 10000.0;
		
		for (unsigned int i = 0; i < existingBlob.size(); i++) {
		
			if (existingBlob[i].existingStillBeingTracked == true) {
			
				double distance = distanceBetweenPoints(currentBlob[i].centerPositions.back(), existingBlob[i].predictedNextPosition);
				
				if (distance < minDist) {
				
					minDist = distance;
					indexOfMinDist = i;
				}
			
			}
		}

		if (minDist < currentBlob[i].DiagonalSize*1.15) {
		
			addBlobToExistingBlobs(currentBlob[i],existingBlob,indexOfMinDist);
		}
		else {
		
			addNewBlob(currentBlob[i], existingBlob);
		}
	}
	
	for (int i = 0; i < existingBlob.size(); i++) {
	
		if (existingBlob[i].blnCurrentMatchFoundOrNewBlob == false) {
			existingBlob[i].intNumOfConsecutiveFramesWithoutAMatch++;
		}

		if (existingBlob[i].intNumOfConsecutiveFramesWithoutAMatch >= 5) {
			existingBlob[i].existingStillBeingTracked = false;
		}


	}
}

double Vehicle::distanceBetweenPoints(Point point1, Point point2) {

	int intX = abs(point1.x - point2.x);
	int intY = abs(point1.y - point2.y);

	return(sqrt(pow(intX, 2) + pow(intY, 2)));
}

void Vehicle::addBlobToExistingBlobs(Blob &current_blob, vector<Blob> &existing_blob, int minDistIndex)
{
	existing_blob[minDistIndex].contour = current_blob.contour;
	existing_blob[minDistIndex].bound = current_blob.bound;

	existing_blob[minDistIndex].centerPositions.push_back(current_blob.centerPositions.back());

	existing_blob[minDistIndex].DiagonalSize = current_blob.DiagonalSize;
	existing_blob[minDistIndex].AspectRatio = current_blob.AspectRatio;

	existing_blob[minDistIndex].existingStillBeingTracked = true;
	existing_blob[minDistIndex].blnCurrentMatchFoundOrNewBlob = true;

}

void Vehicle::addNewBlob(Blob &current_blob, vector <Blob> &existing_blob) 
{
	current_blob.blnCurrentMatchFoundOrNewBlob = true;

	existing_blob.push_back(current_blob);
}

void Vehicle::drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {

	for (unsigned int i = 0; i < blobs.size(); i++) {

		if (blobs[i].existingStillBeingTracked == true) {
			cv::rectangle(imgFrame2Copy, blobs[i].bound, Scalar(0,0,255), 2);

			int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
			double dblFontScale = blobs[i].DiagonalSize / 60.0;
			int intFontThickness = (int)std::round(dblFontScale * 1.0);

			cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, Scalar(0,255,0), intFontThickness);
			
		}
	}
}