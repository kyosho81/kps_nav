#ifndef _OPENCV_SUBDIV_KYOSHO_20210406_
#define _OPENCV_SUBDIV_KYOSHO_20210406_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc.hpp>

#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

namespace cv{
	class Subdiv2D;
}
namespace octomap {
	class OcTree;
}

class subdiv
{
public:
	subdiv();
	~subdiv();

	int subdiv_2d(std::vector<std::pair<int,int>> &pair_edge,const std::map<int,SPos> &pt);
	int locate_edge(cv::Point2f &sp);

protected:
private:
	cv::Subdiv2D* p_subdiv_2d_;
	octomap::OcTree* octree_;
	int max_id_;

	int get_index_from_pos(F32 nx,F32 ny);
	F32 tolerance_;

	bool check_edge_exist(const int &src,const int &dst,std::vector<std::pair<int,int>> &pair_edge);
	

};


#endif//_OPENCV_SUBDIV_KYOSHO_20210406_
