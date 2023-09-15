#ifndef _KPS_ARM_KYOSHO_MSG_LOG_PKG_SINGLETON_H_
#define _KPS_ARM_KYOSHO_MSG_LOG_PKG_SINGLETON_H_

#include <fstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "robot/RobotStruct.h"
#include "buffer_con.hpp"
#include "Comm/pattern_thread.h"


typedef struct  _PKG_FILE_HEAD
{
	KPS_VERSION ver_;
	S8 ch_db_[200];
	S8 ch_map_[200];
	S8 ch_yaml_[200];
	S8 ch_lm_[200];
	S8 ch_qr_[200];
	S8 ch_cfg_[200];
	int db_size_;
	int map_size_;
	int yaml_size_;
	int lm_size_;
	int qr_size_;
	int cfg_size_;

}PKG_FILE_HEAD;


class msg_log_pkg
{
public:
	msg_log_pkg();
	~msg_log_pkg();

	void init();
	bool destruct();

	bool package_db(const std::string &str_file);
	bool unpackage_db(const std::string &pkg_file);
	std::string get_unpackage_db_name();
	std::string get_unpackage_map_name();
	std::string get_unpackage_yaml_name();
	std::string get_unpackage_cfg_name();
	std::string get_unpackage_lm_name();
	std::string get_unpackage_qr_name();
protected:
private:
	std::string str_path_;

	SBuffer<std::string> th_path_list_;

	bool b_package_;
	pattern_thread pattern_thread_;
	bool th_run();
	
	bool do_pkg(const std::string &str_db);
	
	bool pkg_db( const std::string &db_file ,const std::string &pkg_file );
	bool pkg_map(const std::string &str_file);
	bool pkg_lm(const std::string &str_file);
	bool pkg_qr(const std::string &str_file);
	bool pkg_cfg();

	std::ofstream fos_;
	bool merge_pkg_file(const std::string &pkg_file);
	
	unsigned long file_size(const char *filename);
	bool decompress_one_file(const char *infilename,const char *outfilename);
	bool compress_one_file(const char *infilename,const char *outfilename);
	
private:
	void set_file_db(const std::string &str_db_name);
	void set_file_map(const std::string &str_map_name);
	void set_file_yaml(const std::string &str_yaml_name);
	void set_file_lm(const std::string &str_lm_name);
	void set_file_qr(const std::string &str_qr_name);
	void set_file_cfg(const std::string &str_cfg_name);
	PKG_FILE_HEAD pkg_file_head_;

	bool merge_file(std::ofstream &fos ,const std::string &str_file);
	bool splite_file(const char* buf,int ilen,const std::string &str_file);
	bool unzip_file(std::string &str_file);

private:
	bool check_ver(const PKG_FILE_HEAD &pkg_file_head);
	std::string str_unpackage_db_name_;
	std::string str_unpackage_map_name_;
	std::string str_unpackage_yaml_name_;
	std::string str_unpackage_cfg_name_;
	std::string str_unpackage_lm_name_;
	std::string str_unpackage_qr_name_;

private:
	void check_del_db(const std::string &str_pkg);
	std::list<std::string> l_pk_db_;
	int max_db_size_;
};


typedef boost::serialization::singleton<msg_log_pkg> Singleton_Msg_Log_PKG;
#define MSG_LOG_PKG Singleton_Msg_Log_PKG::get_mutable_instance()

#endif//_KPS_ARM_KYOSHO_MSG_LOG_PKG_SINGLETON_H_
