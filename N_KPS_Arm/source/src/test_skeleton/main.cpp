using namespace std;


#include <iostream>  
#include<vector>
#include<algorithm>
#include <opencv2\opencv.hpp>  
#include <opencv2\highgui\highgui.hpp>  
using namespace std;
using namespace cv;

//轮廓按照面积大小升序排序
bool ascendSort(vector<Point> a, vector<Point> b) {
	return a.size() < b.size();

}

//轮廓按照面积大小降序排序
bool descendSort(vector<Point> a, vector<Point> b) {
	return a.size() > b.size();
}

//自己实现的将灰度图像转为三通道的BGR图像
cv::Mat gray2BGR(cv::Mat grayImg) {
	if (grayImg.channels() == 3)
		return grayImg;
	cv::Mat bgrImg = cv::Mat::zeros(grayImg.size(), CV_8UC3);
	std::vector<cv::Mat> bgr_channels;
	cv::split(bgrImg, bgr_channels);
	bgr_channels.at(0) = grayImg;
	bgr_channels.at(1) = grayImg;
	bgr_channels.at(2) = grayImg;
	cv::merge(bgr_channels, bgrImg);
	return bgrImg;
}

//自定义的drawImage函数的功能类似于OpenCV的drawContours函数
cv::Mat drawImage(cv::Mat image, vector< vector< Point> > pointV) {
	cv::Mat destImage=image.clone();
	if (destImage.channels()==1)
	{
		destImage = gray2BGR(destImage);
	}
	for (size_t i=0;i<pointV.size();i++)
	{
		for (size_t j = 0; j<pointV.at(i).size(); j++)
		{
			cv::Point point = pointV.at(i).at(j);
			destImage.at<Vec3b>(point) = cv::Vec3b(0, 0, saturate_cast<uchar>(255-i*5));
		}

	}
	return destImage;
}
int main() {

	Mat srcImage = imread("D:\\3.jpg");

	namedWindow("Source Image", WINDOW_NORMAL);
	namedWindow("dilate Image", WINDOW_NORMAL);
	namedWindow("sub Image", WINDOW_NORMAL);
	namedWindow("sub skeleton", WINDOW_NORMAL);


	
	//Mat image;  
	//GaussianBlur(imageSource,image,Size(3,3),0);  
	//Canny(image,image,100,250); 
	Mat thresholdImage;
	Mat grayImage;

	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	imshow("Source Image",grayImage);  

	cv::GaussianBlur(grayImage, grayImage, cv::Size(9,9), 1, 1);
	threshold(grayImage, thresholdImage, 254, 255, CV_THRESH_BINARY);

	imshow("Source Image",thresholdImage);   

	int erodeSizeValue = 1;
	Mat element = getStructuringElement(MORPH_CROSS, Size(2*erodeSizeValue + 1, 2*erodeSizeValue + 1));
// 	erode(mask, imgerode, element);     //腐蚀操作
// 	imshow("erode Image",imgerode); 
	cv::Mat imgskel(grayImage.size(),CV_8UC1, Scalar(0));
	cv::Mat imgerode(grayImage.size(),CV_8UC1, Scalar(0));
	cv::Mat imgdilate(grayImage.size(),CV_8UC1, Scalar(0));
	cv::Mat imgsub(grayImage.size(),CV_8UC1, Scalar(0));

	while(1){

		erode(thresholdImage,imgerode,element);

		dilate(imgerode, imgdilate, element);
		imshow("dilate Image",imgdilate); 


		cv::subtract(thresholdImage,imgdilate,imgsub);
		imshow("sub Image",imgsub); 

		
		cv::bitwise_or(imgskel,imgsub,imgskel);
		imshow("sub skeleton",imgskel); 

		thresholdImage = imgerode.clone();

		if (countNonZero(thresholdImage) == 0){
			break;
		}
		waitKey(1000);
	}
	imshow("sub skeleton",imgskel); 
	waitKey(0);

	return 0;
}
