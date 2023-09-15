#ifndef _GLOBAL_PATH_WANGHONGTAO_2015_12_10_
#define _GLOBAL_PATH_WANGHONGTAO_2015_12_10_

#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/serialization/singleton.hpp>

#include "RobotStruct.h"


class global_path
{
public:

	global_path();
	~global_path();

	bool update_pipe_global_path(std::string name,U8* data,U32 len);
	void rpc_global_path(std::list<SGridXY> &global_path);

protected:
private:

	boost::mutex pipe_mu_;
	std::string name_;
	U8* p_global_path_;
	U32 global_path_len_;

	void init_global_path();
};


#endif//_GLOBAL_PATH_WANGHONGTAO_2015_12_10_
