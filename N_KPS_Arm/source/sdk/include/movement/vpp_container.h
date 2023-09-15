#ifndef _VPP_CONTAINER_WANGHONGTAO_2017_05_26_
#define _VPP_CONTAINER_WANGHONGTAO_2017_05_26_

#include <vector>
#include <map>
#include <boost/thread.hpp>

#include "MyDefine.h"
#include "TimerDiff.h"
#include "RobotStruct.h"

#include "vpp/vector_path_planner.h"


typedef struct _SPath_Para
{
	S32 max_count_;
	F32 Vx_;
	F32 Vw_;
	F32 sim_max_len_;
	F32 dx_;

}SPath_Para;


class vpp_container{

public:
	vpp_container();
	~vpp_container();

	void init();
	std::vector<SPath_VW> getPathVW(const F32 &Vx);

private:
	void init_para(std::string str_sim_path,const S32 &path_count,const F32 &dx);
	std::vector<SPath_Para> v_path_para_;

private:
	void init_mvpp();
	std::map<int,vector_path_planner> m_vpp_;

};


#endif//_VPP_CONTAINER_WANGHONGTAO_2017_05_26_
