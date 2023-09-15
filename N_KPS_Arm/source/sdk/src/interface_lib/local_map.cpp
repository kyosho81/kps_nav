//#include "interprocess/shared_pool.hpp"
#include "interpro_shared/sh_pool.hpp"
#include "mapserver/MapPath.h"


#include "interface/local_map.h"

local_map::local_map()
{
	init_local_map();
}
local_map::~local_map()
{

}

void local_map::init_local_map()
{
	boost::mutex::scoped_lock lock(pipe_mu_);
	p_local_map_ = new U8[PIPE_BUFFER_SIZE];
	memset(p_local_map_,0,PIPE_BUFFER_SIZE);
	name_ = "";
	local_map_len_ = 0;
}

bool local_map::update_pipe_local_map( std::string name,U8* data,U32 len )
{
	if(len > PIPE_BUFFER_SIZE){
		std::cout<<"!!!!!!!!!!local_map::update_pipe_local_map LEN err:"<<len<<std::endl;
		return true;
	}

	boost::mutex::scoped_lock lock(pipe_mu_);
	memset(p_local_map_,0,PIPE_BUFFER_SIZE);
	memcpy(p_local_map_,data,len);
	name_ = name;
	local_map_len_ = len;
	std::cout<<"put local map:"<<name<<" len:"<<len<<std::endl;

	return true;
}
void local_map::rpc_get_data(U8* &data,int &len){
	assert(!data);
	len = 0;
	if (local_map_len_ < 1)
	{
		return ;
	}
	data = new U8[local_map_len_];

	boost::mutex::scoped_lock lock(pipe_mu_);
	memcpy(data,p_local_map_,local_map_len_);
	len = local_map_len_;

}
void local_map::rpc_local_map( std::list<SGridXY> &local_map )
{
	path_package pp;
	{
		boost::mutex::scoped_lock lock(pipe_mu_);
		pp.Decoder(p_local_map_,local_map_len_);
	}
	
	pp.getPoint(local_map);
	std::cout<<"get local map:"<< local_map.size()<<std::endl;
}












