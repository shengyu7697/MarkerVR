#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <opencv2/opencv.hpp>
#include <string>

class DebugWindow
{
public:
	DebugWindow(const std::string& windowname = "DebugWindow");
	~DebugWindow();

	void putText(const std::string& text1, const std::string& text2 = "");
	void show();

private:
	void init();

	cv::Mat mImage;
	std::string mWindowName;
};

#endif // DEBUGWINDOW_H
