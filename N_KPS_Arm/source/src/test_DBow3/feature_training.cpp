
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "DBoW3/DBoW3.h"

#include "Comm/Comm.h"

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
    // read the image 
    cout<<"reading images... "<<endl;
    vector<Mat> images; 
    for ( int i=0; i<10; i++ )
    {
        string path = "./data/img/ch12/"+cComm::ConvertToString(i+1)+".png";
        images.push_back( imread(path) );
    }
    // detect ORB features
    cout<<"detecting ORB features ... "<<endl;
    Ptr< Feature2D > detector = ORB::create();
    vector<Mat> descriptors;
	vector<Mat>::iterator it = images.begin();
    for ( ; it !=images.end() ; ++it )
    {
		Mat &image(*it);
        vector<KeyPoint> keypoints; 
        Mat descriptor;
        detector->detectAndCompute( image, Mat(), keypoints, descriptor );
		//std::cout<<"----------"<<descriptor<<std::endl;
        descriptors.push_back( descriptor );
    }
    
    // create vocabulary 
    cout<<"creating vocabulary ... "<<endl;
    DBoW3::Vocabulary vocab;
    vocab.create( descriptors );
    cout<<"vocabulary info: "<<vocab<<endl;
    vocab.save( "vocabulary.yml.gz" );
    cout<<"done"<<endl;
    
    return 0;
}
