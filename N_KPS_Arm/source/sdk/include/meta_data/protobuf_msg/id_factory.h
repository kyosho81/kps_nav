#ifndef _ID_FACTORY_WANGHONGTAO_20211230_
#define _ID_FACTORY_WANGHONGTAO_20211230_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
//#include "mapserver/GridMap.h"
#include "meta_data/meta_data.h"


class id_factory
{
public:
	id_factory();
	~id_factory();

	int get_new_id(std::string str_type);
	void set_max_id(std::string str_type, int id );

	std::string get_cargo_type_uuid();
	std::string get_pallet_type_uuid();
	//std::string get_action_type_uuid();

	bool check_cargo_type(std::string str_type);
	bool check_pallet_type(std::string str_type);
	//bool check_action_type(std::string str_type);

	void set_cargo_type_uuid(std::string str_uuid);
	void set_pallet_type_uuid(std::string str_uuid);

protected:
private:

	boost::mutex mx_;
	std::map<std::string,int> m_type_id_;
private:
	std::map<int,std::string> m_cargo_type_;
	std::map<int,std::string> m_pallet_type_;
	//std::map<int,std::string> m_action_type_;
};

typedef boost::serialization::singleton<id_factory> Singleton_ID_Factory;
#define SINGLETON_ID_FACTORY Singleton_ID_Factory::get_mutable_instance()

#endif//_ID_FACTORY_WANGHONGTAO_20211230_
