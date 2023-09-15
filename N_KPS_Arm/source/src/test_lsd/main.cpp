
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
int main()
{
	cout << "hello world" << endl;
	Mat image = imread("d://2022-8-24-10-44-32.png");
	Mat grayImage;
	cvtColor(image,grayImage,CV_BGR2GRAY);
	// Create and LSD detector with standard or no refinement.
	//Canny(grayImage, grayImage, 50, 200, 3); // Apply canny edge//��ѡcanny����
#if 0
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);//��������LSD�㷨������õ���standard��
#else
	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_NONE);
#endif
	double start = double(getTickCount());
	vector<Vec4f> lines_std;
	// Detect the lines
	ls->detect(grayImage, lines_std);//����Ѽ�⵽��ֱ���߶ζ�������lines_std�У�4��float��ֵ���ֱ�Ϊ��ֹ�������
	for (int i = 0; i < lines_std.size(); i++)
	{
		cout << lines_std[i][0] <<" "<< lines_std[i][1]<<" "
			<< lines_std[i][2]<<" "<<lines_std[i][3]<<endl;
	}
	double duration_ms = (double(getTickCount()) - start) * 1000 / getTickFrequency();
	std::cout << "It took " << duration_ms << " ms." << std::endl;
	// Show found lines
	//Mat drawnLines(image);
	ls->drawSegments(image, lines_std);
	namedWindow("Standard refinement",0);
	imshow("Standard refinement", image);
	waitKey(0);
	return 0;
}


// 	cv::Point pt1;
// 	cv::Point pt2;
// 	pt1.x = 10;
// 	pt1.y = 10;
// 	pt2.x = 20;
// 	pt2.y = 20;
// 	line(grayImage, pt1, pt2, CV_RGB(255, 0, 0, ), 1, 8, 0);
