#include <stdio.h>
#include <string.h>
#include <chrono>

#include <zed/Mat.hpp>
#include <zed/Camera.hpp>
#include <zed/utils/GlobalDefine.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace sl::zed;
using namespace std;

int main(int argc, char **argv) {

	Camera* zed;
	zed = new Camera(HD720);

	InitParams parameters;
	parameters.verbose = true;
	ERRCODE err = zed->init(parameters);

	if (err != SUCCESS) {
		cout << errcode2str(err) << endl;
		delete zed;
		return 1;
	}

	int width  = zed->getImageSize().width;
	int height = zed->getImageSize().height;

	cv::Mat imageDisplay(height, width, CV_8UC4);

	char key = ' ';
	bool run = true;
	while (run) {

		bool res = zed->grab(STANDARD, 1, 0, 0);

		slMat2cvMat(zed->retrieveImage(LEFT)).copyTo(imageDisplay);

		cv::imshow("左视图", imageDisplay);

		key = cv::waitKey(20);
		switch (key) {
			case 'q':
			case 'Q':
				run = false;
				break;
			default:
				break;
		}

	}

	imageDisplay.release();
	delete zed;

	return 0;

}
