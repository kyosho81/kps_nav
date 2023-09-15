#ifndef _K_MEANS_KYOSHO_20190220_
#define _K_MEANS_KYOSHO_20190220_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

typedef struct Point{
	float x;
	float y;
	float th;
	int cluster;
	Point (){}
	Point (float fx,float fy,float fa,int c){
		x = fx;
		y = fy;
		th = fa;
		cluster = c;
	}
}point;

class k_means
{

public:
	k_means();
	~k_means();

	void add_data(const float &fx, const float &fy , const float &fa);
	void clear();
	bool cluster(const int &k);
	const std::map<int, std::vector<std::vector<point>::iterator>>& get_data();

protected:
private:
	void cal_data(std::vector<point> &dataset,const int &k);

	float squareDistance(point a,point b);
	std::vector<point> v_dataset_;
	std::map< int, std::vector<std::vector<point>::iterator> > m_cluster_;
};


#endif//_K_MEANS_KYOSHO_20190220_
