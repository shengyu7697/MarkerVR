#ifndef MARKER_MANAGER_H
#define MARKER_MANAGER_H

#include <opencv2/core/mat.hpp>
#include <thread>
#include "MarkerTacker.h"

class MarkerManager
{
public:
	MarkerManager();
	~MarkerManager();
	bool isRunning();

private:
	cv::Mat mFrame;
	std::thread mThread;
	bool mRunning = true;
	MarkerTacker mTacker;

	void imageThread();
};

#endif // MARKER_MANAGER_H
