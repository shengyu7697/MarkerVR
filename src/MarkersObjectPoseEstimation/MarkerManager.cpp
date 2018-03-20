#include "MarkerManager.h"
#include <opencv2/opencv.hpp>

using namespace cv;

MarkerManager::MarkerManager()
{
	mThread = std::thread(&MarkerManager::imageThread, this);
}

MarkerManager::~MarkerManager()
{
	mRunning = false;
	if (mThread.joinable())
		mThread.join();
}

void MarkerManager::imageThread()
{
	VideoCapture cap(0);
	//VideoCapture cap("data/id0-8_1.mkv");

	while (mRunning) {

		if (!cap.isOpened()) {
			break;
		}

		cap.read(mFrame);

		if (!mFrame.data) {
			printf("frame.data is empty !!!\n");
			break;
		}

		if (!mTacker.processImage(mFrame)) {
			printf("processImage failed !\n");
			break;
		}

		// TODO
		// handler() // update pose 

		imshow("frame", mFrame);
		int key = waitKey(10);
		if (key == 27 || key == 'q')
			break;

	}
	mRunning = false;
}

bool MarkerManager::isRunning()
{
	return mRunning;
}
