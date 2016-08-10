//c++ headers
#include <iostream>
#include <conio.h>

//opencv headers
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

const int FRAME_HEIGHT = 360;
const int FRAME_WIDTH = 640;
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
	
		//the below method to resize the video does work if
		//you capture the video from the webcam but not if the video is loaded from local computer.

		/*carVideo.set(CV_CAP_PROP_FRAME_WIDTH, 768);
		carVideo.set(CV_CAP_PROP_FRAME_HEIGHT, 576);*/

		//check if the video has ended and display a message to the user
		if (carVideo.get(CV_CAP_PROP_POS_FRAMES) < carVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
		
			//grab the frams into the Mat object
			carVideo >> videoFrame;

			//resize to 640x360;
			resize(videoFrame, videoFrame, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_CUBIC);
			
		}
		else {
		
			cout << "\nVideo ended...\nPress any key to exit the program now!";
			_getch();
			break;
		}

		//wait for some time
		waitKey(20);

		//display the frames
		imshow("Video", videoFrame);
	}
	
	return 0;

}
