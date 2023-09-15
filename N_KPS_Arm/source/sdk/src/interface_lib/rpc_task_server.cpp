#include <assert.h>

#include "Comm/PortDef.h"
#include "Comm/configs.h"
#include "robot/msg_def.h"

#include "interface/rpc_task_server.h"

int map_tools::i_max_prohibit_path_ = 12288;
SBuffer<int> map_tools::th_reflash_(1);
bool map_tools::b_sim_ = false;

rpc_task_server::rpc_task_server()
{
	set_onboard_project_ = 0;
	create_rand_path_ = 0;
	create_specified_path_ = 0;
	create_charge_path_ = 0;
	create_open_ctl_ = 0;
	create_fix_path_ = 0;
	create_fork_ = 0 ;
	create_task_act_ = 0;

	get_feadback_ = 0;
	remove_task_ = 0;
	force_complete_= 0;
	redo_ = 0;

	get_sim_init_pos_= 0 ;

	b_sim_ = false;
}

rpc_task_server::~rpc_task_server()
{
	SDelete(set_onboard_project_);
	SDelete(get_feadback_);
	SDelete(create_rand_path_);
	SDelete(create_specified_path_);
	SDelete(create_charge_path_);
	SDelete(create_fix_path_);
	SDelete(create_fork_);
	SDelete(create_task_act_);

	SDelete(create_open_ctl_);
	SDelete(remove_task_);
	SDelete(force_complete_);
	SDelete(redo_);

	SDelete(get_sim_init_pos_);
}


bool rpc_task_server::init(int i_task_rpc_port , bool b_sim )
{
	b_sim_ = b_sim;
	
	map_tools::b_sim_ = b_sim;
	map_tools::sub_reflash_over();

	init_s();

	//XmlRpc::setVerbosity(0);

	if (s_.bindAndListen(i_task_rpc_port))
	{
		// Enable introspection
		s_.enableIntrospection(true);
		// Wait for requests indefinitely
		boost::thread th(boost::bind(&rpc_task_server::th_rpc_,this));
	}else{
		std::cout<<"task rpc server init err !!!!port:"<<i_task_rpc_port<<std::endl;
		return false;
	}
	return true;
}
void rpc_task_server::th_rpc_(void){

	std::cout<<"rpc_task_server thread run!"<<std::endl;
	s_.work(-1.0);
	std::cout<<"rpc_task_server thread end!"<<std::endl;
}

void rpc_task_server::destruct()
{
	s_.close();
}

void rpc_task_server::init_s()
{
	set_onboard_project_ = new set_onboard_project(&s_);
	create_rand_path_ = new create_rand_path(&s_);
	create_specified_path_ = new create_specified_path(&s_);
	create_charge_path_ = new create_charge_path(&s_);
	create_open_ctl_ = new create_open_ctl(&s_);
	create_fix_path_ = new create_fix_path(&s_);
	create_fork_ = new create_fork(&s_);
	create_task_act_ = new create_task_act(&s_);

	get_feadback_ = new get_feadback(&s_);
	remove_task_ = new remove_task(&s_);
	force_complete_ = new force_complete(&s_);
	redo_ = new redo(&s_);

	get_sim_init_pos_ = new get_sim_init_pos(&s_);
}

void map_tools::set_amcl_run(const bool &run)
{
	SReflash_map reflash;
	if (run)
	{
		reflash.ref_type_ = SReflash_map::AMCL_RUN;
	}else{
		reflash.ref_type_ = SReflash_map::AMCL_STOP;
	}

	//shared_pool::Publish(shared_pool::name(),"reflash_map",reflash);
	PUB_MSG_SH_POOL("reflash_map",reflash);
}
void map_tools::set_map_lock( const bool &block )
{
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		if (block)
		{
			g_map->lock();
		}else{
			g_map->unlock();
		}

	}

}
void map_tools::set_map_fill( const int &value )
{
	GridMap* g_map = MAP_SERVER.GetGridMap(SHARED_AMCL_MAP);
	if (g_map)
	{
		g_map->fill(value);
	}
}
void map_tools::set_map_reflash()
{
	SReflash_map reflash;
	reflash.ref_type_ = SReflash_map::AMCL_REFLASH;
	//shared_pool::Publish(shared_pool::name(),"reflash_map",reflash);
	PUB_MSG_SH_POOL("reflash_map",reflash);
}

void map_tools::draw_prohibit_path(GridMap* prohibit_map,  const Sxy &p1 , const Sxy &p2){

	if (!prohibit_map){
		return;
	}
	VecPosition v1(p1.x_,p1.y_);
	VecPosition v2(p2.x_,p2.y_);

	VecPosition v12 = v2 - v1;
	int icount = v12.getMagnitude() / 0.05;
	icount = cComm::Min(icount,i_max_prohibit_path_);
	v12 = VecPosition( 0.05 ,v12.getDirection(),POLAR);


	for ( int i = 1; i < icount ; ++i )
	{
		v2 = v1 + v12 * i;
		prohibit_map->setgrid( F32(v2.getX()), F32(v2.getY()), MAP_OCCUPY_MAX);
	}
}

bool map_tools::reflash_map_over()
{
	if (map_tools::b_sim_){
		return true;
	}

	//pub from device_amcl::reflash_map(
	int i_reflash_map_over;

	for ( int i = 0 ; i < 500 ; ++i){
		if (th_reflash_.get(i_reflash_map_over)){
			th_reflash_.clear();
			std::cout<<cTimerDiff::get_now_ms()<<" device_amcl::reflash_map over!"<<std::endl;
			return true;
		}else{
			std::cout<<cTimerDiff::get_now_ms()<<" wait for device_amcl::reflash_map over!"<<std::endl;
			SLEEP(200);
		}
	}
	return false;
}

void map_tools::sub_reflash_over()
{
	if (b_sim_){
		return ;
	}

	END_MSG_SH_POOL( int,PUB_REFLASH_MAP_OVER);
	boost::function<bool( const int &reflash )> fnc_reflash;
	fnc_reflash = boost::bind(&map_tools::call_back,_1);
	SUB_MSG_SH_POOL(PUB_REFLASH_MAP_OVER,fnc_reflash);

}

bool map_tools::call_back( const int &reflash )
{
	th_reflash_.put(reflash);

	return true;
}

