
#ifndef _SHARED_MAP_KYOSHO_2019_07_08_H_
#define _SHARED_MAP_KYOSHO_2019_07_08_H_

#include <vector>

#include <boost/serialization/singleton.hpp>

#include "interpro_shared/sh_pool.hpp"

#include <RobotStruct.h>

class GridMap;

class shared_map
{
public:

	shared_map();
	~shared_map();

	GridMap* get_global_nav_map();

protected:
private:

	GridMap* global_nav_map_;
};

typedef boost::serialization::singleton<shared_map> Singleton_Shared_Map;

#endif // _SHARED_MAP_KYOSHO_2019_07_08_H_
