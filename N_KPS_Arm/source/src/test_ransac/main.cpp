#include <iostream>
#include <cmath>
#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "geometry/ransac_geo_fitting.h"

using namespace std; 

int main( int argc, char** argv )
{

	SCircle circle_pa;
	std::vector<ransac::Point2D> pointData2;
// 	pointData2.push_back(ransac::Point2D(0,1));
// 	pointData2.push_back(ransac::Point2D(-1,0));
// 	pointData2.push_back(ransac::Point2D(1,0));
// 	pointData2.push_back(ransac::Point2D(0,-2));
	std::fstream fs_;

	if (!fs_.is_open())
	{
		std::cout<<"-----play back file:"<<std::endl;
		std::cout<<"-------------------------0"<<std::endl;
		fs_.open("./1.txt",std::ios::in | std::ios::binary );
	}


	std::string str;
	int itotal_  = 0;
	while(std::getline( fs_ , str)){
		if ((itotal_ % 5) != 0){
			itotal_++;
			continue;
		}
		
		std::vector<std::string> vlist;
		cComm::SplitString( str," ",vlist);
		if( vlist.size() > 5){

			F32 odom_x = 0;
			F32 odom_y = 0;
			F32 odom_th = 0;

			cComm::ConvertToNum(odom_x,vlist[3]);
			cComm::ConvertToNum(odom_y,vlist[4]);
			cComm::ConvertToNum(odom_th,vlist[5]);

			pointData2.push_back(ransac::Point2D(odom_x,odom_y));

			itotal_++;
		}
	}
	itotal_ += 1;
	fs_.close();
	std::cout<<"total bag size:"<<itotal_<<std::endl;

	if( FIT_CIRCLE2( circle_pa , pointData2 , 1.5 , 0.25 ) ){
		std::cout<<"circle radius:"<<circle_pa.radius_<<" px:"<<circle_pa.p_.x_<<" py:"<<circle_pa.p_.y_<<std::endl;
	}
	if (!fs_.is_open())
	{
		std::cout<<"-----play back file:"<<std::endl;
		std::cout<<"-------------------------0"<<std::endl;
		fs_.open("./1.txt",std::ios::in | std::ios::binary );
	}

	VecPosition vO(circle_pa.p_.x_,circle_pa.p_.y_);

	F32 angle = asin( 1.25/ circle_pa.radius_);

	itotal_  = 0;
	while(std::getline( fs_ , str)){
		if ((itotal_ % 5) != 0){
			itotal_++;
			continue;
		}

		std::vector<std::string> vlist;
		cComm::SplitString( str," ",vlist);
		if( vlist.size() > 5){

			F32 odom_x = 0;
			F32 odom_y = 0;
			F32 odom_th = 0;

			cComm::ConvertToNum(odom_x,vlist[3]);
			cComm::ConvertToNum(odom_y,vlist[4]);
			cComm::ConvertToNum( odom_th,cComm::trim_cr(vlist[5]) );

			VecPosition vlaser(odom_x,odom_y);
			VecPosition l2o = vO - vlaser ;
			
			VecPosition vt1 = l2o;
			VecPosition vt2 = l2o;
			vt1.rotate(Rad2Deg(angle));
			vt2.rotate(Rad2Deg(-angle));

			F32 angle_diff1 = VecPosition::angle_diff(Deg2Rad(vt1.getDirection()) , odom_th);
			F32 angle_diff2 = VecPosition::angle_diff(Deg2Rad(vt2.getDirection()) , odom_th);

			std::cout<<"angle diff 1:"<<angle_diff1<<" angle diff 2:"<<angle_diff2<<std::endl;
		}
	}
	fs_.close();
	::system("pause");
}
int main2( int argc, char** argv )
{
	SLine2P line_pa;
	std::vector<ransac::Point2D> pointData;
	pointData.push_back(ransac::Point2D(0,0));
	pointData.push_back(ransac::Point2D(1,1));
	pointData.push_back(ransac::Point2D(2,2));
	pointData.push_back(ransac::Point2D(3,3));
	pointData.push_back(ransac::Point2D(4,4));
	pointData.push_back(ransac::Point2D(5,7));
	if( FIT_LINE( line_pa , pointData ) ){
		//std::cout<<"line a:"<<Rad2Deg(line_pa.angle_)<<" px:"<<line_pa.p_.x_<<" py:"<<line_pa.p_.y_<<std::endl;
		std::cout<<"line p1 x:"<<line_pa.p1_.x_<<" y:"<<line_pa.p1_.y_;
		std::cout<<"line p2 x:"<<line_pa.p2_.x_<<" y:"<<line_pa.p2_.y_<<std::endl;
	}

	SCircle circle_pa;
	std::vector<ransac::Point2D> pointData2;
	pointData2.push_back(ransac::Point2D(0,1));
	pointData2.push_back(ransac::Point2D(-1,0));
	pointData2.push_back(ransac::Point2D(1,0));
	pointData2.push_back(ransac::Point2D(0,-2));

	if( FIT_CIRCLE( circle_pa , pointData2 , 1 ) ){
		std::cout<<"circle radius:"<<circle_pa.radius_<<" px:"<<circle_pa.p_.x_<<" py:"<<circle_pa.p_.y_<<std::endl;
	}


	return 0;
}
