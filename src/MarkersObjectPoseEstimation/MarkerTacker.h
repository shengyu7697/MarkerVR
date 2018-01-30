#ifndef MARKER_TACKER_H
#define MARKER_TACKER_H

#include <opencv2/core/mat.hpp>
#include <opencv2/aruco.hpp>
#include <vector>

class MarkerTacker
{
public:
	MarkerTacker();
	~MarkerTacker();
	bool processImage(cv::Mat &frame);

private:
	cv::Ptr<cv::aruco::Dictionary> mDictionary;
	std::vector<std::vector<cv::Point2f> > mCorners;
	std::vector<int> mIds;
	std::vector<cv::Vec3d> mRvecs, mTvecs;
	/*const*/ cv::Mat mCameraMatrix;
	/*const*/ cv::Mat mDistCoeffs;
	float mMarkerLength = 0.026;
	bool mShowAxis = true;


};

#endif // MARKER_TACKER_H
