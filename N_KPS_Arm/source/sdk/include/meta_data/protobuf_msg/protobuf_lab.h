#ifndef _PROTOBUF_LAB_WANGHONGTAO_20191202_
#define _PROTOBUF_LAB_WANGHONGTAO_20191202_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"

#include "protobuf_msg/lab.pb.h"

class protobuf_lab{


public:

	protobuf_lab();
	~protobuf_lab();

	void set_id();
	void set_id(const int &id);
	int get_id();
	void set_pos(const F32 &x,const F32 &y);
	void get_pos(F32 &x, F32 &y);
	void get_pos(SVec &vp);
	void set_lab(const std::string &str);
	std::string get_lab();
	void set_show(const bool &b_show);
	bool get_show();

	bool proto2byte(char* &data,int &len);
	bool byte2proto(char* const data,const int len);

	KPS::mp_lab proto_lab_;


private:
	static int max_id_;
};

#endif//_PROTOBUF_LAB_WANGHONGTAO_20191202_
