#ifndef _LOCAL_MAP_WANGHONGTAO_2015_12_10_
#define _LOCAL_MAP_WANGHONGTAO_2015_12_10_

#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/serialization/singleton.hpp>

#include "RobotStruct.h"
//#include "amcl/hd_particle.h"


class local_map
{
public:

	local_map();
	~local_map();

	bool update_pipe_local_map(std::string name,U8* data,U32 len);
	void rpc_get_data(U8* &data,int &len);
	void rpc_local_map(std::list<SGridXY> &local_map);

protected:
private:

	boost::mutex pipe_mu_;
	std::string name_;
	U8* p_local_map_;
	U32 local_map_len_;

	void init_local_map();
};


#endif//_LOCAL_MAP_WANGHONGTAO_2015_12_10_
