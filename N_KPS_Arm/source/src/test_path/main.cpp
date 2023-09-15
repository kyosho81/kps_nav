

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#include <stdlib.h>
#include "Comm/Rand.hpp"
#include "Log4cppArm.hpp"
#include "log/log_client.h"

#include "trans_dev/traceroute.h"
#include "Comm.h"
//#include "Log.h"

#include "project/task_rpc_client.h"
#include "project/project_manage.h"

#include "interpro_shared/sh_pool.hpp"

task_rpc_client* task_rpc_client_ = 0;
bool gb_run = true;

void shutdown(int sig)
{



	//	std::cout<<"ctrl c shut down"<<std::endl;

	gb_run = false;

	std::cout<<"test odom ctrl c destructor"<<std::endl;

	return;
}


int create_fix_path( const std::vector<SPathData> &seg_path )
{
	if (seg_path.size() < 0){
		return -1;
	}

	int i_task_id = task_rpc_client_->create_fix_path(seg_path);
	
	return 1;
}
int main(int argc, char *argv[])
{
	REG_POOL(argv);

 	log4cpp::Priority::Value priority = log4cpp::Priority::DEBUG;
 	LOG.getLog(argv[0]).setPriority(priority);  //LOGS_PRIORITY_INFO("planner_tray");
	
	RPC_CONFIG_CLIENT_INIT("127.0.0.1");
	TCP_LOG.set_priority(priority);

	task_rpc_client_ = new task_rpc_client();
	task_rpc_client_->init("127.0.0.1",RPC_TASK_SER_PORT);

	while(gb_run){
		
		
	
		std::cout<<"please input set speed vx vy w:"<<std::endl;
		std::string str;
		std::getline(std::cin,str);

		int node_from = -1;
		int node_to = -1;
		F32 speed = 0;
		int i_ori = ORI_FORWARD;

		std::vector<std::string> v_str;
		cComm::SplitString(str," ",v_str);
		if (v_str.size() > 3){
			
			cComm::ConvertToNum(node_from,v_str[0]);
			cComm::ConvertToNum(node_to,v_str[1]);
			cComm::ConvertToNum(speed,v_str[2]);
			cComm::ConvertToNum(i_ori,v_str[3]);

			std::cout<<"node_from:"<<node_from<<" node_to:"<<node_to<<" speed:"<<speed<<" i_ori:"<<i_ori<<std::endl;

			std::vector<SPathData> seg_path;

			SPathData p_data;
			memset(&p_data,0,sizeof(SPathData));

			SPos p;
			protobuf_node* p_node = 0;
			p_node = PRO_MANAGE.get_node(CURRENT_PRO,node_from);
			if (!p_node){
				return 0;
			}
			p_node->get_pos(p);

			p_data.tn_from_.x_ = p.x_;
			p_data.tn_from_.y_ = p.y_;
			p_data.tn_from_.th_ = p.th_;
			p_data.node_from_ = p_node->get_id();

			p_node = PRO_MANAGE.get_node(CURRENT_PRO,node_to);
			if (!p_node){
				return 0;
			}
			p_node->get_pos(p);

			p_data.tn_to_.x_ = p.x_;
			p_data.tn_to_.y_ = p.y_;
			p_data.tn_to_.th_ = p.th_;
			p_data.node_to_ = p_node->get_id();

			if (ORI_FORWARD == i_ori){
				p_data.orientation_ = 0;
				p_data.speed_ = speed;
			}else if (ORI_BACKWARD == i_ori){
				p_data.orientation_ = 0;
				p_data.speed_ = -speed;
			}else if (ORI_LEFTSHIFT == i_ori){
				p_data.orientation_ = Deg2Rad(90);
				p_data.speed_ = speed;
			}else if (ORI_RIGHTSHIFT == i_ori){
				p_data.orientation_ = -Deg2Rad(90);
				p_data.speed_ = speed;
			}

			protobuf_edge* p_edge = PRO_MANAGE.get_edge(CURRENT_PRO,p_data.node_from_,p_data.node_to_);
			if (p_edge){
				if (ORI_FORWARD == i_ori){
					p_data.speed_ = p_edge->forward_speed();
				}else if (ORI_BACKWARD == i_ori){
					p_data.speed_ = -p_edge->backward_speed();
				}else if (ORI_LEFTSHIFT == i_ori){
					p_data.speed_ = p_edge->leftshift_speed();
				}else if (ORI_RIGHTSHIFT == i_ori){
					p_data.speed_ = p_edge->rightshift_speed();
				}
			}


			p_data.complete_pre_ = 0;

			seg_path.push_back(p_data);
			create_fix_path(seg_path);
		}

		

	}



	SLEEP(2000);
}
