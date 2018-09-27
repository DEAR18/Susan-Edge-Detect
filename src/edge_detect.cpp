#include "susan.h"
#include "iostream"


int main()
{
	Mat img = imread("C:/Users/smu_z/Desktop/Hello/c++/opencv tutorial/Susan edge detector/lena.jpg", IMREAD_GRAYSCALE);
	//Mat img = imread("C:/Users/smu_z/Desktop/Hello/c++/opencv tutorial/Susan edge detector/T.jpg", IMREAD_GRAYSCALE);
	//namedWindow("image", 0);
	imshow("image", img);
	waitKey(1000);

	Mat edge_img = Susan(img, 30);
	imshow("edge_image", edge_img);
	waitKey(0);

	return(0);
}

