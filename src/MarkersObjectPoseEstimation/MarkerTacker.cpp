#include "MarkerTacker.h"
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "RotationUtil.h"

using namespace cv;
using namespace aruco;

MarkerTacker::MarkerTacker()
{
	mDictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	mRvecs.clear();
	mTvecs.clear();
	mCameraMatrix = (Mat_<double>(3, 3) <<
			700, 0, 320,
			0, 700, 240,
			0, 0, 1);
	mDistCoeffs = (Mat_<double>(1, 5) <<
			0, 0, 0, 0, 0);

	//cubeIds = {4, 5, 6, 7, 8, 9};
	cubeIds = {20, 21, 22, 23, 24, 25};

	cubePosToCenter = {
		cv::Vec3d(0, 0, -0.0155), // -1.55cm
		cv::Vec3d(0, 0, -0.0155),
		cv::Vec3d(0, 0, -0.0155),
		cv::Vec3d(0, 0, -0.0155),
		cv::Vec3d(0, 0, -0.0155),
		cv::Vec3d(0, 0, -0.0155)
	};
	/*cubePosToCenter = {
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0)
	};*/

	/*cubeOriToCenter = {
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, -90, 0),
		cv::Vec3d(0, -180, 0),
		cv::Vec3d(0, 90, 0),
		cv::Vec3d(90, 0, 0),
		cv::Vec3d(90, 0, 0)
	};
	*/
	cubeOriToCenter = {
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, -90, 0),
		cv::Vec3d(0, -180, 0),
		cv::Vec3d(0, 90, 0),
		cv::Vec3d(90, 0, 0),
		cv::Vec3d(0, 0, 0),
		cv::Vec3d(0, 0, 0)
	};
}

MarkerTacker::~MarkerTacker()
{
}

bool MarkerTacker::processImage(cv::Mat &frame)
{
	std::vector<int> measuredIds;
	std::vector< std::vector<cv::Point2f> > measuredCorners;
	detectMarkers(frame, mDictionary, measuredCorners, measuredIds);

	// 檢查偵測出來的 Markers 有沒有屬於 MarkerObject 的, 有的話加進入, 已便後續處理.
	std::vector<int> markersObjIds;
	std::vector< std::vector<cv::Point2f> > markersObjCorners;
	for (int i = 0; i < measuredIds.size(); i++) {
		if (mPrintIds) printf("%d ", measuredIds[i]);

		//if (measuredIds[i] >= 4 && measuredIds[i] <= 9) { // paper cube
		if (measuredIds[i] >= 20 && measuredIds[i] <= 29) { // paper cube
			markersObjIds.push_back(measuredIds[i]);
			markersObjCorners.push_back(measuredCorners[i]);
		}
	}
	if (mPrintIds) printf("\n");

	if (mPrintIds) printf("%d %ld\n", __LINE__, markersObjIds.size());

	// calc MarkerObject pose and update
	if (markersObjIds.size() > 0) {
		estimatePoseSingleMarkers(markersObjCorners, mMarkerLength, mCameraMatrix, mDistCoeffs, mRvecs, mTvecs);

		if(mRvecs.size() > 0) {
			drawDetectedMarkers(frame, markersObjCorners, markersObjIds);

			for (int i = 0; i < markersObjIds.size(); i++) {
				// 針對每個 MarkerObject 裡的 Markers 做各自的旋轉,
				// 求出 Object 的中心點 (平均每個 Markers 的 position)
				// paper cube
				for (int j = 0; j < cubeIds.size(); j++) {
					if (markersObjIds[i] == cubeIds[j]) {
						Matx33d rot;  // rotation matrix
						Rodrigues(mRvecs[i], rot);
						mTvecs[i] = mTvecs[i] + rot * cubePosToCenter[j]; // 沿著物件中心的法向量 扣掉 距離
						rodriguesRotateByEulerAngles(mRvecs[i], cubeOriToCenter[j]);
					}
				}

				if (mShowAxis)
					drawAxis(frame, mCameraMatrix, mDistCoeffs, mRvecs[i], mTvecs[i], float(0.03));

				// TODO update pose
				// 方法一 取其中一個
				mCubePos = mTvecs[0];
				mCubeOri = mRvecs[0];

				float pos[3], euler[3];
				pos[0] = mCubePos[0];
				pos[1] = mCubePos[1];
				pos[2] = mCubePos[2];
				rodrigues2Euler(mRvecs[0], euler);

				//printf("P(%f, %f, %f) E(%f, %f, %f)\n", mCubePos[0], mCubePos[1], mCubePos[2], euler[0], euler[1], euler[2]);
				printf("%f, %f, %f, %f, %f, %f\n", mCubePos[0], mCubePos[1], mCubePos[2], euler[0], euler[1], euler[2]);
				spc.sendPose(pos, euler, true);

				// 方法二 平均
				//mCubePos = avg(mTvecs);
				//mCubeOri = avg(mRvecs);
			}
		}
	}

	return true;
}
