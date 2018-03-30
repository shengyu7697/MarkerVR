#include "DebugWindow.h"

using namespace std;
using namespace cv;

DebugWindow::DebugWindow(const std::string& windowname)
	: mWindowName(windowname)
{
	init();
}

DebugWindow::~DebugWindow() 
{
}

void DebugWindow::init()
{
	mImage = Mat(Size(600, 200), CV_8UC3); // grayscale
	mImage.setTo(Scalar(0)); // black
	namedWindow(mWindowName, WINDOW_AUTOSIZE);
	moveWindow(mWindowName, 1200, 100);
	imshow(mWindowName, mImage);
}

void DebugWindow::putText(const string& text1, const string& text2)
{
	int y = 25;
	mImage.setTo(Scalar(0));
	cv::putText(mImage, text1, {10, y}, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255));
	if (!text2.empty())
		cv::putText(mImage, text2, {10, y+25}, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255));
}

void DebugWindow::show()
{
	imshow(mWindowName, mImage);
	//waitKey(0);
}
