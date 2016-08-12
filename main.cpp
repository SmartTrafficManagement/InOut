//c++ headers
#include <iostream>
#include <conio.h>



//include the created headers
#include "Vehicle.h"


int main()
{
	Vehicle vehicle;

	VideoCapture carVideo;

	//open the video file
	carVideo.open("carVideo.mp4");

	//check if the video was loaded properly
	if (!carVideo.isOpened()) {
		
		cout << "Couldn't load the video!\nExiting the program now..\n";
		return -1;
	}

	//get the first frame from the video stream,may also add some additional error check
	//to check if the video has atleast one frame.
	vehicle.getFirstframe(carVideo);

	while (1) {
	
		//the below method to resize the video does work if
		//you capture the video from the webcam but not if the video is loaded from local computer.

		/*carVideo.set(CV_CAP_PROP_FRAME_WIDTH, 768);
		carVideo.set(CV_CAP_PROP_FRAME_HEIGHT, 576);*/

		//check if the video has ended and display a message to the user
		if (carVideo.get(CV_CAP_PROP_POS_FRAMES) < carVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
		
				vehicle.trackVehicles();
			
		}
		else {
		
			cout << "\nVideo ended...\nPress any key to exit the program now!";
			_getch();
			break;
		}

		//wait for some time between grabbing two successive frames
		waitKey(20);
	}
	
	return 0;

}
