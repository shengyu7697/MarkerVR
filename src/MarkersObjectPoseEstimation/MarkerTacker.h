#ifndef MARKER_TACKER_H
#define MARKER_TACKER_H

#include <opencv2/core/mat.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

class MarkerObject
{
public:
	std::vector<int> ids;
	std::vector< std::vector<cv::Point2f> > corners;
	std::vector<cv::Vec3d> positionToCenter; // local location
	std::vector<cv::Vec3d> orientationToCenter; // euler
};

class MarkerTacker
{
public:
	MarkerTacker();
	~MarkerTacker();
	bool processImage(cv::Mat &frame);

private:
	cv::Ptr<cv::aruco::Dictionary> mDictionary;
	std::vector<cv::Vec3d> mRvecs, mTvecs;
	/*const*/ cv::Mat mCameraMatrix;
	/*const*/ cv::Mat mDistCoeffs;
	float mMarkerLength = 0.026; // Marker 的黑色邊長
	bool mShowAxis = true;

	// for debug
	bool mPrintIds = false;

	//MarkerObject mo;

	// 預先定義好的 cube ids 與 其他資訊
	std::vector<int> cubeIds;
	std::vector<cv::Vec3d> cubePosToCenter;
	std::vector<cv::Vec3d> cubeOriToCenter;

	// 最後計算出來的 Pose
	cv::Vec3d mCubePos;
	cv::Vec3d mCubeOri;
};

#endif // MARKER_TACKER_H
