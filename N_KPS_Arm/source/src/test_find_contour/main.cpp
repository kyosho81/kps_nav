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

	Mat srcImage = imread("D:\\2.jpg");

	imshow("Source Image",srcImage);  
	//Mat image;  
	//GaussianBlur(imageSource,image,Size(3,3),0);  
	//Canny(image,image,100,250); 
	Mat thresholdImage;
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	threshold(grayImage, thresholdImage, 0, 255, CV_THRESH_OTSU + THRESH_BINARY_INV);
	cv::Mat mask = thresholdImage.clone();
	imshow("mask Image",mask); 

	cv::Mat imgerode;
	int erodeSizeValue = 8;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2*erodeSizeValue + 1, 2*erodeSizeValue + 1));
// 	erode(mask, imgerode, element);     //腐蚀操作
// 	imshow("erode Image",imgerode); 

 	cv::Mat imgdilate;
 	dilate(mask, imgerode, element);
 	imshow("dilate Image",imgerode); 

	vector<vector<Point>> contours;  
	vector<Vec4i> hierarchy;  
	findContours(imgerode,contours,hierarchy,RETR_LIST,CHAIN_APPROX_SIMPLE,Point());  


	//cv::findContours(imgerode, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	contours.erase(std::remove_if(contours.begin(), contours.end(), 
		[](const std::vector<cv::Point>& c){return cv::contourArea(c) < 400; }), contours.end());


	Mat imageContours=Mat::zeros(imgerode.size(),CV_8UC1);  
	Mat Contours=Mat::zeros(imgerode.size(),CV_8UC1);  //绘制  
	
	for(int i=0;i<contours.size();i++)  
	{  
		//contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数  
		for(int j=0;j<contours[i].size();j++)   
		{  
			//绘制出contours向量内所有的像素点  
			Point P=Point(contours[i][j].x,contours[i][j].y);  
			Contours.at<uchar>(P)=255;  
		}  

		//输出hierarchy向量内容  
		char ch[256];  
		sprintf(ch,"%d",i);  
		string str=ch;  
		//std::cout<<"hierarchy:" <<str<<" eleum："<<std::endl<<hierarchy[i]<<std::endl<<std::endl;  

		//绘制轮廓  
		//drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  

		cv::drawContours(imageContours, contours, i, cv::Scalar(255), 1,8);
		imshow("Contours Image",imageContours); //轮廓
		
		waitKey(0);
		imageContours=Mat::zeros(mask.size(),CV_8UC1);
	}  
//	imshow("Contours Image",imageContours); //轮廓  
	imshow("Point of Contours",Contours);   //向量contours内保存的所有轮廓点集  
	waitKey(0);


// 	Mat srcImage = imread("D:\\2.jpg");
// 	cv::imshow("srcImage", srcImage);
// 	Mat thresholdImage;
// 	Mat grayImage;
// 	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
// 	threshold(grayImage, thresholdImage, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
// 	cv::Mat mask = thresholdImage.clone();
// 	//(1)CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE
// 	vector< vector< Point> > contours1;
// 	findContours(mask, contours1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
// 	cv::Mat destImage = drawImage(mask, contours1);
// 	imshow("destImage", destImage);
// 	cv::waitKey(0);
// 
// 	//(2)CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE
// 	vector< vector< Point> > contours2; 
// 	findContours(mask, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
// 	cv::Mat destImage2 = drawImage(mask, contours2);
// 	imshow("destImage2", destImage2);
// 
// 	//(3)CV_RETR_LIST, CV_CHAIN_APPROX_NONE
// 	vector< vector< Point> > contours3; 
// 	findContours(mask, contours3, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
// 	cv::Mat destImage3 = drawImage(mask, contours3);
// 	imshow("destImage3", destImage3);
// 
// 
// 	//(4)CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE
// 	vector< vector< Point> > contours4;
// 	findContours(mask, contours4, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
// 	cv::Mat destImage4 = drawImage(mask, contours4);
// 	imshow("destImage4", destImage4);
// 
// 
// 	//cv::Mat imge2 = gray2BGR(mask);
// 	//drawContours(imge2, contours4, -1, cv::Scalar(0, 0, 255), 1);
// 	//cv::fillConvexPoly(mask, contours1.at(0), cv::Scalar(255, 255, 255));
// 	cv::waitKey(0);
	return 0;
}
