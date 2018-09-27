#include "susan.h"

Mat Susan(const Mat& input_img, int similar_threshold)
{
	int width = input_img.cols;
	int higth = input_img.rows;
	Mat output_img(higth, width, CV_8UC1, Scalar::all(255));
	int geometric_threshold = 36;
	Usan usan;

	//move circular mask on the image
	for (int i = 3; i < higth - 3; i++)
	{
		for (int j = 3; j < width - 3; j++)
		{
			usan = Compare(input_img, i, j, similar_threshold);
			float edge_response = geometric_threshold - usan.usan_value;
			if (geometric_threshold - usan.usan_value < 0) edge_response = 0;
			if (edge_response == 0) output_img.at<uchar>(i, j) = 255;

			//it can be commented to compare the effect of SUSAN with or without non maximum suppression
			else if(NonMaximumSuppression(input_img, usan.direction, i, j) != true) output_img.at<uchar>(i, j) = 255;

			else output_img.at<uchar>(i, j) = 0;
		}
	}

	return(output_img);
}

Usan Compare(const Mat& img, int x, int y, int similar_threshold)
{
	int offset_x[37] =
	{
				-1, 0, 1,
			-2, -1, 0, 1, 2,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
			-2, -1, 0, 1, 2,
				-1, 0, 1
	};
	int offset_y[37] =
	{
			  -3,-3,-3,
		   -2,-2,-2,-2,-2,
		-1,-1,-1,-1,-1,-1,-1,
		0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1,
		   2, 2, 2, 2, 2,
			  3, 3, 3
	};
	Usan usan;
	float weighted_x_sum = 0;
	float weighted_y_sum = 0;
	int similar_count = 0;
	float intra_x = 0;
	float intra_y = 0;
	for (int k = 0; k < 37; k++)
	{
		int difference = img.at<uchar>(x + offset_x[k], y + offset_y[k]) - img.at<uchar>(x, y);
		if (abs(difference) < similar_threshold) similar_count++;
		float index = -1 * pow((float)difference / similar_threshold, 6);
		float compare = exp(index);
		usan.usan_value += compare;
		float weighted_x = (x + offset_x[k]) * compare;
		float weighted_y = (y + offset_y[k]) * compare;
		weighted_x_sum += weighted_x;
		weighted_y_sum += weighted_y;
		
		//caculated for intra pixel case
		intra_x += pow(offset_x[k], 2) * compare;
		intra_y += pow(offset_y[k], 2) * compare;
	}

	//caculate center of gravity of USAN area
	usan.core_x = weighted_x_sum / usan.usan_value;
	usan.core_y = weighted_y_sum / usan.usan_value;

	//caculate orientation (inter pixel case)
	if (similar_count > 18 && (usan.core_x + usan.core_y - x - y) > 1)
	{
		usan.direction = atan((usan.core_y - y) / (usan.core_x - x));
	}

	//caculate orientation (intra pixel case)
	if (similar_count < 18 || (usan.core_x + usan.core_y - x - y) < 1)
	{
		usan.direction = atan(intra_y / intra_x);
	}

	return(usan);
}

bool NonMaximumSuppression(const Mat& img, float direction, int x, int y)
{
	bool max_flag = true;

	//horizontal direction
	if (direction > -0.393 && direction < 0.393)
	{
		int gradient = abs(img.at<uchar>(x, y + 1) - img.at<uchar>(x, y));
		int neighbor_gradient1 = abs(img.at<uchar>(x, y + 1) - img.at<uchar>(x, y + 1));
		int neighbor_gradient2 = abs(img.at<uchar>(x, y) - img.at<uchar>(x, y - 1));
		if (gradient < neighbor_gradient1 || gradient < neighbor_gradient2) max_flag = false;
	}

	//45¡ãdirection
	else if (direction > -1.178 && direction <= -0.393)
	{
		int gradient = abs(img.at<uchar>(x - 1, y + 1) - img.at<uchar>(x, y));
		int neighbor_gradient1 = abs(img.at<uchar>(x - 2, y + 2) - img.at<uchar>(x - 1, y + 1));
		int neighbor_gradient2 = abs(img.at<uchar>(x, y) - img.at<uchar>(x + 1, y - 1));
		if (gradient < neighbor_gradient1 || gradient < neighbor_gradient2) max_flag = false;
	}

	//-45¡ãdirection
	else if (direction >= 0.393 && direction < 1.178)
	{
		int gradient = abs(img.at<uchar>(x + 1, y + 1) - img.at<uchar>(x, y));
		int neighbor_gradient1 = abs(img.at<uchar>(x + 2, y + 2) - img.at<uchar>(x + 1, y + 1));
		int neighbor_gradient2 = abs(img.at<uchar>(x, y) - img.at<uchar>(x - 1, y - 1));
		if (gradient < neighbor_gradient1 || gradient < neighbor_gradient2) max_flag = false;
	}

	//vertical direction
	else
	{
		int gradient = abs(img.at<uchar>(x + 1, y) - img.at<uchar>(x, y));
		int neighbor_gradient1 = abs(img.at<uchar>(x + 2, y) - img.at<uchar>(x + 1, y));
		int neighbor_gradient2 = abs(img.at<uchar>(x, y) - img.at<uchar>(x - 1, y));
		if (gradient < neighbor_gradient1 || gradient < neighbor_gradient2) max_flag = false;
	}
	return (max_flag);
}
