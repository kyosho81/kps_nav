#ifndef _VIEW_DATA_WANGHONGTAO_2020_12_21_
#define _VIEW_DATA_WANGHONGTAO_2020_12_21_

#include <boost/serialization/singleton.hpp>

#include <string>
#include "Comm/buffer_con.hpp"

#include "RobotStruct.h"

#define VIEW_DATA_CIRCULAR_BUF_SIZE 100000

class view_data
{
public:

	view_data();
	~view_data();

	void init();

	bool get_view_data(std::string &name,U8* &data,int &len);
	bool get_view_data(std::vector<SView_Data> &v_data);

protected:
private:

	bool call_pipe(std::string name,U8* data,U32 len);
	std::string str_sub_pipe_;

	CSBuffer<SView_Data,VIEW_DATA_CIRCULAR_BUF_SIZE> buffer_list_;

};

typedef boost::serialization::singleton<view_data> Singleton_View_Data;

#endif//_VIEW_DATA_WANGHONGTAO_2020_12_21_
