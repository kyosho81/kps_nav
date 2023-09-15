
#include "interpro_shared/sh_pool.hpp"

#include "interface/view_data.h"


view_data::view_data()
{
	std::cout<<"view_data!"<<std::endl;
}


view_data::~view_data()
{
	END_PIPE_SH_POOL(str_sub_pipe_);
}

void view_data::init()
{
	boost::function<bool (std::string name,U8* data,U32 len)> fnc;
	fnc = boost::bind(&view_data::call_pipe,this,_1,_2,_3);
	str_sub_pipe_ = pub_view_data::sub_view_pipe(fnc);
}

bool view_data::call_pipe(std::string name,U8* data,U32 len)
{
	SView_Data vd;
	memset(&vd,0,sizeof(SView_Data));
	int ilen = 200;
	cComm::String2Charlist((S8*)vd.name_,ilen,name);

	if (len >0 ){
		vd.uc_data_ = new U8[len];
	}

	if (vd.uc_data_){
		memcpy(vd.uc_data_,data,len);
		vd.ilen_ = len;

		buffer_list_.put(vd);
	}else{
		std::cout<<"view_data::call_pipe new ptr err!"<<std::endl;
	}
	

	return true;
}

bool view_data::get_view_data(std::string &name,U8* &data,int &len)
{
	SView_Data vd;
	memset(&vd,0,sizeof(SView_Data));

	if ( buffer_list_.size() ){
		buffer_list_.get(vd);

		cComm::Char2String(name,(U8*)vd.name_);

		data = vd.uc_data_;
		len = vd.ilen_;

		return true;
	}
	return false;
}

bool view_data::get_view_data(std::vector<SView_Data> &v_data)
{
	SView_Data vd;
	memset(&vd,0,sizeof(SView_Data));

	while ( buffer_list_.size() > 0){
	
		buffer_list_.get(vd);
		v_data.push_back(vd);
		
	}

	if (v_data.size() > 0){
		return true;
	}
	return false;
	
}
