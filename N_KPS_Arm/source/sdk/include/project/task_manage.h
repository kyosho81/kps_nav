#ifndef _TASK_MANAGE_KYOSHO_20150906_
#define _TASK_MANAGE_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "Comm/Rand.hpp"

#include "project/task_base.h"

namespace octomap {
	class OcTree;
}

class task_manage
{
public:
	task_manage();
	~task_manage();

	void init();
	void sim_init_msg();

	void get_sim_init(SPos &init_sim_pos);
	void set_sim_init(SPos init_sim_pos);

	int create_rand_path(std::list<int> &l_path);
	int create_specified_path(std::list<int> &l_path , const SPos &specified_pos);
	int create_charge_path( const SPos &charge_pos, F32 vx);
	int create_open_ctl(XmlRpc::XmlRpcValue params);
	int create_fix_path(XmlRpc::XmlRpcValue params);
	int create_fork(XmlRpc::XmlRpcValue params);

	int create_task_act(XmlRpc::XmlRpcValue params);


	int do_task_list();
	void update_task_feedback();
	int get_task_feedback(std::vector<task_feadback> &v_task_feadback, int i_task_id);

	int force_complete(int i_task_id = -1);
	int redo(int i_task_id = -1);
	int remove_task(int i_task_id = -1);

protected:

private:

	bool update_mv_status( const SRunStatus &sta );
	bool update_amcl_pos(const SPos &amcl_pos);
	bool update_odom(const SOdomSpeed &odomspeed);
	THSafe<SPos> th_cur_pos_;
	THSafe<SOdomSpeed> th_odom_pos_;

private:
	int max_id_ ;
	F32 range_tolerance_;
	int increase_range_;
	octomap::OcTree* octree_;
	int init_node_octo();
	int get_close_pos(F32 nx,F32 ny,int multiple);
	int get_close_pos(F32 nx,F32 ny,F32 range_t);

	int last_node_id_;
	int i_next_node_;
	int i_current_node_;
	MyRand rand_;
	int rand_next_node(int i_node_id);

	int i_total_task_id_;

	int create_seg_path(std::vector<SPathData> &seg_path,const std::list<int> &l_path);
	int cov_odom2xml( XmlRpc::XmlRpcValue& params, const std::vector<SPathData> &seg_path);

	//std::map<int,task_path_run*> m_sub_id_RunStatus;
private:
	int insert_task_map(task_base* p_task);
	int insert_task_map(int task_id, task_base* p_task);
	boost::mutex mu_task_all_;
	std::map<int,task_base*> mt_task_all_;

private:
	boost::mutex mu_task_feadback_;
	std::map<int,task_feadback> m_task_feadback_;

	F32 rand_path_speed_;

private:
	//simulation data
	SPos init_sim_pos_;
	//int sub_id_mv_status_;
	int sub_id_amcl_pos_;
	//int sub_id_odom_;

	bool b_sim_moudule_;
};

typedef boost::serialization::singleton<task_manage> Singleton_Task_Manage;
#define TASK_MANAGE Singleton_Task_Manage::get_mutable_instance()

#endif//_TASK_MANAGE_KYOSHO_20150906_
