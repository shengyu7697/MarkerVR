#include <iostream>
#include <string>
#include <unistd.h>
#include "MarkerManager.h"

using namespace std;

int main(void)
{
	MarkerManager markerManager;

	while (markerManager.isRunning()) {
		usleep(100*1000);
	}

	printf("end\n");

	return 0;
}
