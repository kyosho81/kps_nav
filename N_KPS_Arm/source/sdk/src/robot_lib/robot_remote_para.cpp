#include <iostream>
#include <sstream>

#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "robot/Geometry.h"
#include "interface/xml_rpc_client.h"

#include "robot/robot_remote_para.h"


robot_remote_para::robot_remote_para()
{

}

robot_remote_para::~robot_remote_para()
{

}

void robot_remote_para::init()
{
	init_laser_para();
	init_robot_shape();
}

void robot_remote_para::init_laser_para()
{
	boost::mutex::scoped_lock lock(mu_para_);
	//laser_para_.laser_ip_ = "192.168.1.100";
	laser_para_.laser_dx_ = 0.23;
	laser_para_.laser_dy_ = 0;
	laser_para_.laser_start_angle_ = -135;
	laser_para_.reverse_ = false;
	laser_para_.laser_resolution_ = 0.5;
	laser_para_.laser_range_max_ = 20;
	laser_para_.laser_range_min_ = 0.01;
	
	std::string str_ip = "192.168.1.100";
	Config::getConfig("dev_laser_ip",str_ip);
	Config::getConfig("dev_laser_dx",laser_para_.laser_dx_);
	Config::getConfig("dev_laser_dy",laser_para_.laser_dy_);
	Config::getConfig("dev_laser_start_angle",laser_para_.laser_start_angle_);
	Config::getConfig("dev_laser_reverse",laser_para_.reverse_);
	Config::getConfig("dev_laser_resolution",laser_para_.laser_resolution_);
	Config::getConfig("dev_laser_range_max",laser_para_.laser_range_max_);
	Config::getConfig("dev_laser_range_min",laser_para_.laser_range_min_);

	laser_para_.laser_start_angle_ = Deg2Rad(laser_para_.laser_start_angle_);
	laser_para_.laser_resolution_ = Deg2Rad(laser_para_.laser_resolution_);
	

// 	get_rpc_para_str(str_ip,"dev_laser_ip");
 	memset(laser_para_.ch_laser_ip_,0,500);
 	memcpy(laser_para_.ch_laser_ip_,str_ip.c_str(),str_ip.length() );
// 
// 	get_rpc_para_num(laser_para_.laser_dx_,"dev_laser_dx");
// 	get_rpc_para_num(laser_para_.laser_dy_,"dev_laser_dy");
// 	get_rpc_para_num(laser_para_.laser_start_angle_,"dev_laser_start_angle");
// 	get_rpc_para_num(laser_para_.reverse_,"dev_laser_reverse");
// 	get_rpc_para_num(laser_para_.laser_resolution_,"dev_laser_resolution");
// 	get_rpc_para_num(laser_para_.laser_range_max_,"dev_laser_range_max");
// 	get_rpc_para_num(laser_para_.laser_range_min_,"dev_laser_range_min");
}

SLaser_para robot_remote_para::get_laser_para()
{
	boost::mutex::scoped_lock lock(mu_para_);
	return laser_para_;
}

void robot_remote_para::init_robot_shape()
{
	std::string str_robot_shape = "0.7,-0.38;0.7,0.38;-0.3,0.38;-0.3,-0.38;0.7,-0.38";

	//get_rpc_para_num(str_robot_shape,"dev_robot_shape");
	Config::getConfig("dev_robot_shape",str_robot_shape);

	std::vector<SVec> v_robot_shape;

	v_robot_shape = get_robot_shape(str_robot_shape);
	
	boost::mutex::scoped_lock lock(mu_para_);
	v_robot_shape_ = v_robot_shape;
}
// 
// bool robot_remote_para::get_rpc_para_str(std::string &str_value,const std::string &str_para)
// {
// 	return Singleton_XML_Client::get_mutable_instance().get_para(str_value,str_para);
// }

std::vector<SVec> robot_remote_para::get_robot_shape(const std::string &str_robot_shape){
	
	std::vector<SVec> v_robot_shape;

	std::vector<std::string> v_str_shape;
	cComm::SplitString(str_robot_shape,";",v_str_shape);
	std::vector<std::string>::iterator it = v_str_shape.begin();
	for ( ; it != v_str_shape.end() ; ++it)
	{
		std::string str_tmp = *it;
		std::vector<std::string> v_str_point;
		cComm::SplitString(str_tmp,",",v_str_point);
		SVec vp;
		vp.x_ = 0;
		vp.y_ = 0;
		if ( v_str_point.size() > 1 )
		{
			v_str_point[0] = cComm::trim(v_str_point[0]);
			v_str_point[1] = cComm::trim(v_str_point[1]);
			cComm::ConvertToNum(vp.x_,v_str_point[0]);
			cComm::ConvertToNum(vp.y_,v_str_point[1]);
		}
		v_robot_shape.push_back(vp);
	}
	return v_robot_shape;
}
std::vector<SVec> robot_remote_para::get_robot_shape()
{
	boost::mutex::scoped_lock lock(mu_para_);
	return v_robot_shape_;
}
