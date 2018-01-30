// https://docs.opencv.org/3.3.1/d5/dae/tutorial_aruco_detection.html

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

const Mat cameraMatrix = (Mat_<double>(3, 3) <<
		700, 0, 320,
		0, 700, 240,
		0, 0, 1);
const Mat distCoeffs = (Mat_<double>(1, 5) <<
		0, 0, 0, 0, 0);

int main(void)
{
	Mat frame;
	Ptr<Dictionary> dictionary;
	vector<vector<Point2f> > corners;
	vector<int> ids;
	vector<Vec3d> rvecs, tvecs;
	float markerLength = 0.026;
	bool showAxis = true;

	//VideoCapture cap(0);
	VideoCapture cap("data/id0-8_1.mkv");

	dictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	corners.clear();
	ids.clear();
	rvecs.clear();
	tvecs.clear();
	while (cap.isOpened()) {
		cap.read(frame);

		if (!frame.data) {
			printf("frame.data is empty !!!\n");
			break;
		}

		detectMarkers(frame, dictionary, corners, ids);

		if (ids.size() > 0) {
			estimatePoseSingleMarkers(corners, markerLength, cameraMatrix, distCoeffs, rvecs, tvecs);

			if(rvecs.size() > 0)
			{
				drawDetectedMarkers(frame, corners, ids);
				if (showAxis) {
					for (int i = 0; i < ids.size(); i++)
						drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], float(0.03));
				}
			}
		}

		imshow("frame", frame);
		int key = waitKey(10);
		if (key == 27 || key == 'q')
			break;
	}

	return 0;
}
