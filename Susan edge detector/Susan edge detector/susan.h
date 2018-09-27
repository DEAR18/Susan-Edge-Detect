#pragma once
#include "opencv2/opencv.hpp"
#include "math.h"
#include "vector"

using namespace cv;
using namespace std;

class Usan
{
public:
	Usan() : usan_value(0), core_x(0), core_y(0), direction(0) {};

	//size of USAN area
	float usan_value;

	//center of gravity of USAN area 
	int core_x;
	int core_y;

	//arctan value (radian)
	float direction;
};

//extract edge
Mat Susan(const Mat& input_img, int similar_threshold);

//caculate usan area in the circular mask
Usan Compare(const Mat& img, int x, int y, int similar_threshold);

//non maximum suppression
bool NonMaximumSuppression(const Mat& img, float direction, int x, int y);

