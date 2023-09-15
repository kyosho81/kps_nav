//#include "interprocess/shared_pool.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "mapserver/MapPath.h"


#include "interface/global_path.h"

global_path::global_path()
{
	init_global_path();
}
global_path::~global_path()
{

}

void global_path::init_global_path()
{
	boost::mutex::scoped_lock lock(pipe_mu_);
	p_global_path_ = new U8[PIPE_BUFFER_SIZE];
	memset(p_global_path_,0,PIPE_BUFFER_SIZE);
	name_ = "";
	global_path_len_ = 0;
}

bool global_path::update_pipe_global_path( std::string name,U8* data,U32 len )
{
	std::cout<<"update global path from planner tray! begin"<<std::endl;
	if(len > PIPE_BUFFER_SIZE){
		return true;
	}

	boost::mutex::scoped_lock lock(pipe_mu_);
	memset(p_global_path_,0,PIPE_BUFFER_SIZE);
	memcpy(p_global_path_,data,len);
	name_ = name;
	global_path_len_ = len;

	std::cout<<"update global path from planner tray! over"<<std::endl;

	return true;
}

void global_path::rpc_global_path( std::list<SGridXY> &global_path )
{
	path_package pp;

	{
		boost::mutex::scoped_lock lock(pipe_mu_);
		pp.Decoder(p_global_path_,global_path_len_);
	}
	
	pp.getPoint(global_path);

	std::list<SGridXY>::iterator it = global_path.begin();
	int i = 0;
	for(; it != global_path.end() ; ++it){
		SGridXY &gxy(*it);
		std::cout<<"index:"<<i++<<" x:"<<gxy.x_<<" y:"<<gxy.y_<<" value:"<<int(gxy.value_)<<std::endl;
	}
}












