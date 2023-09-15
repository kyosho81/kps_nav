#ifndef _PCA_KYOSHO_20190220_
#define _PCA_KYOSHO_20190220_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

class pca
{
public:
	pca();
	~pca();

	std::vector<Sxy> get_range();
	SVec pca2d( std::vector<SVec> &vec, const std::list<SPos> &data );


	std::vector<Sxy> block_range_;

protected:
private:
};


typedef boost::serialization::singleton<pca> Singleton_PCA;

#endif//_PCA_KYOSHO_20190220_
