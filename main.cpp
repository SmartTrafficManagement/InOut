//c++ headers
#include <iostream>

//opencv headers
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture carVideo;

	//open the video file
	carVideo.open("carVideo.mp4");

	//Mat object to grab the frames from the video
	Mat videoFrame;

	//check if the video was loaded properly
	if (!carVideo.isOpened()) {
		
		cout << "Couldn't load the video!\nExiting the program now..\n";
		return -1;
	}

	while (1) {
	
		//grab the frams into the Mat object
		carVideo >> videoFrame;

		//display the frames
		imshow("Video", videoFrame);

		//wait for some time
		waitKey(20);
	}

}
