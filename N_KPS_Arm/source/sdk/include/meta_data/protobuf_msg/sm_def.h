#ifndef _STATE_MACHINE_DEF_WANGHONGTAO_20211230_
#define _STATE_MACHINE_DEF_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"

class sm_def
{
public:
	sm_def();
	~sm_def();

	typedef enum{
		PD_NONE = 0,
		PD_IDLE = 1,
		PD_INIT_PT = 2,
		PD_BOOK_PT = 3,
		PD_BOOK_PT_OK = 4,
		PD_PRODUCE = 5,
		PD_PAUSE = 6,
		PD_WAIT_GET = 7,
		PD_BOOK_GET = 8,
		PD_ERROR = 9
	}PD_STA;

	typedef enum{
		CS_NONE = 0,
		CS_IDLE = 1,
		CS_BOOK_PT = 2,
		CS_BOOK_PT_OK = 3,
		CS_CONSUME = 4,
		CS_PAUSE = 5,
		CS_WAIT_GET = 6,
		CS_BOOK_GET = 7,
		CS_ERROR = 8
	}CS_STA;


	typedef enum{
		PC_NON = 0,
		PC_IDLE = 1,
		PC_BOOK_PUT = 2,
		PC_BOOK_PUT_OK = 3,
		PC_PROCESS = 4,
		PC_PAUSE = 5,
		PC_BOOK_GET = 6,
		PC_BOOK_GET_OK = 7,
		PC_ERROR = 8
	}PC_STA;

	typedef enum{
		CH_NONE = 0,
		CH_IDLE = 1,
		CH_BOOK_OCCUPY = 2,
		CH_OCCUPY = 3,
		CH_CHECK_CHARGE = 4,
		CH_CHARGE = 5,
		CH_CHECK_OVER = 6,
		CH_ERROR = 7
	}CH_STA;

	typedef enum{
		ST_NONE = 0,
		ST_IDLE = 1,
		ST_BOOK_PUT = 2,
		ST_BOOK_PUT_OK = 3,
		ST_OCCUPY = 4,
		ST_BOOK_GET = 5,
		ST_BOOK_GET_OK = 6,
		ST_ERROR = 7
	}ST_STA;

	std::string get_pd_str( PD_STA sta );
	std::string get_cs_str( CS_STA sta );
	std::string get_pc_str( PC_STA sta );
	std::string get_st_str( ST_STA sta );
	std::string get_ch_str( CH_STA sta );

protected:
private:
	void init();
	
	std::map<int,std::string> m_pd_str_;
	std::map<int,std::string> m_cs_str_;
	std::map<int,std::string> m_pc_str_;
	std::map<int,std::string> m_st_str_;
	std::map<int,std::string> m_ch_str_;
};

typedef boost::serialization::singleton<sm_def> Singleton_SM_Def;
#define SINGLETON_SM_DEF Singleton_SM_Def::get_mutable_instance()

#endif//_STATE_MACHINE_DEF_WANGHONGTAO_20211230_
