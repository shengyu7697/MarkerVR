#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

void createArUcoMarker()
{
	Mat outputImage;
	Ptr<Dictionary> markerDictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

	for (int i = 0; i < 9; i++)
	{
		drawMarker(markerDictionary, i, 100, outputImage, 1);
		ostringstream oss;
		string prefix = "4x4Marker_";
		oss << prefix << i << ".png";
		imwrite(oss.str(), outputImage);
	}
}

int main(void)
{
	createArUcoMarker();

	return 0;
}
