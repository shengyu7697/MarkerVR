#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

void usage(const char *progname)
{
    printf("\nThis program is used to create markers\n"
        "Usage: %s num side_pixels\n", progname);
}

void createArUcoMarker(int num, int sidePixels)
{
	Mat outputImage;
	Ptr<Dictionary> markerDictionary = getPredefinedDictionary(PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	char buf[100];

	for (int i = 0; i < num; i++)
	{
		drawMarker(markerDictionary, i, sidePixels, outputImage, 1);
		ostringstream oss;
		string prefix = "4x4Marker_";
		snprintf(buf, sizeof(buf), "%02d", i);
		oss << prefix << buf << ".png";
		cout << oss.str() << endl;
		imwrite(oss.str(), outputImage);
	}
}

int main(int argc, const char *argv[])
{
	int num = 50;
	int sidePixels = 100;

	if (argc < 3) {
		usage(argv[0]);
		return 1;
	}

	num = atoi(argv[1]);
	sidePixels = atoi(argv[2]);

	printf("create %d markers, side pixels: %d\n", num, sidePixels);
	createArUcoMarker(num , sidePixels);
	printf("done.\n");

	return 0;
}
