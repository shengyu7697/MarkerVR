#include "MarkerTacker.h"
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace cv;
using namespace aruco;

MarkerTacker::MarkerTacker()
{
	mDictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	mCorners.clear();
	mIds.clear();
	mRvecs.clear();
	mTvecs.clear();
	mCameraMatrix = (Mat_<double>(3, 3) <<
			700, 0, 320,
			0, 700, 240,
			0, 0, 1);
	mDistCoeffs = (Mat_<double>(1, 5) <<
			0, 0, 0, 0, 0);
}

MarkerTacker::~MarkerTacker()
{
}

bool MarkerTacker::processImage(cv::Mat &frame)
{
	detectMarkers(frame, mDictionary, mCorners, mIds);

	if (mIds.size() > 0) {
		estimatePoseSingleMarkers(mCorners, mMarkerLength, mCameraMatrix, mDistCoeffs, mRvecs, mTvecs);

		if(mRvecs.size() > 0) {
			drawDetectedMarkers(frame, mCorners, mIds);
			if (mShowAxis) {
				for (int i = 0; i < mIds.size(); i++)
					drawAxis(frame, mCameraMatrix, mDistCoeffs, mRvecs[i], mTvecs[i], float(0.03));
			}
		}
	}
}
