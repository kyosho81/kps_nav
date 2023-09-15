#ifndef _KPS_ROBOT_PARA_H
#define _KPS_ROBOT_PARA_H


#ifndef Q_MOC_RUN 
#include <boost/serialization/singleton.hpp>
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"
#endif

class robot_remote_para
{
public:

	robot_remote_para();
	~robot_remote_para();

	void init();

	SLaser_para get_laser_para();
	std::vector<SVec> get_robot_shape();
	static std::vector<SVec> get_robot_shape(const std::string &str_robot_shape);

protected:

private:
	//laser para
	void init_laser_para();
	SLaser_para laser_para_;
private:
	//robot shape
	void init_robot_shape();
	std::vector<SVec> v_robot_shape_;

private:
//	bool get_rpc_para_str(std::string &str_value,const std::string &str_para);

// 	template<typename T>
// 	bool get_rpc_para_num(T &value,const std::string &str_para){
// 
// 		std::string str_value;
// 		if(Singleton_XML_Client::get_mutable_instance().get_para(str_value,str_para)){
// 			cComm::ConvertToNum(value,str_value);
// 			return true;
// 		}
// 		return false;
// 	};
	
	//
	boost::mutex mu_para_;
};


typedef boost::serialization::singleton<robot_remote_para> Singleton_remote_para;


#endif // _KPS_ROBOT_PARA_H
