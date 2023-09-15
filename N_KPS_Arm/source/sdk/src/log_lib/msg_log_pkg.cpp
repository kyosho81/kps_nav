#include <cassert>
#include <iostream>

#include "Comm/PortDef.h"
#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "trans_dev/trans_dev.h"
#include "Comm/TimerDiff.h"
#include "Comm/PortDef.h"
#include "Log4cppArm.hpp"
#include "log/Log4cppMsgIndex.h"
#include "interpro_shared/sh_pool.hpp"
#include "zlib/zlib.h"


#include "log/msg_log_pkg.h"


msg_log_pkg::msg_log_pkg():
th_path_list_(20)
{
	str_path_ = ".//pkg_log//";
	max_db_size_ = 5;
}

msg_log_pkg::~msg_log_pkg()
{

}

void msg_log_pkg::init()
{
	memset(&pkg_file_head_,0,sizeof(PKG_FILE_HEAD));
	pkg_file_head_.ver_ = cComm::getVersion();

	Config::getConfig("log_pkg_path",str_path_);
	std::cout<<"log_pkg_path:"<<str_path_<<std::endl;

	b_package_ = true;
	pattern_thread_.run_thread(boost::bind(&msg_log_pkg::th_run,this));

	str_unpackage_db_name_ = "";
	str_unpackage_map_name_ = "";
	str_unpackage_yaml_name_ = "";
	str_unpackage_lm_name_ = "";
	str_unpackage_qr_name_ = "";
	str_unpackage_cfg_name_ = "";
}

bool msg_log_pkg::package_db(const std::string &str_file)
{
	if (!cComm::FileExist(str_file)){
		std::cout<<"package_db file not exist!!"<<str_file<<std::endl;
		return false;
	}
	th_path_list_.put(str_file);
	return true;
}

bool msg_log_pkg::th_run()
{
	std::string str_db_file;
	if( !th_path_list_.get(str_db_file) ){
		SLEEP(500);
		return true;
	}

	if(!do_pkg(str_db_file)){
		std::cout<<"msg_log_pkg err!"<<str_db_file<<std::endl;
	}

	cComm::Del_File(str_db_file);

	return true;

}
bool msg_log_pkg::destruct()
{

	pattern_thread_.destory_thread();
	return true;
}

bool msg_log_pkg::do_pkg(const std::string &str_db)
{
	std::string pkg_name = cComm::Get_FileName(str_db);
	pkg_name = str_path_ + pkg_name + ".dbz";


	if( !pkg_db( str_db, pkg_name) ){
		std::cout<<"pkg_db error:"<<str_db<<std::endl;
		return false;
	}


	std::string str_map_name = ".//407.pgm";
	std::string str_map_path = ".//map//";

	Config::getConfig("dev_map_path",str_map_path);
	Config::getConfig("dev_map_name",str_map_name);
	std::string str_map = str_map_path + str_map_name;

	if (!pkg_map(str_map)){
		std::cout<<"pkg_map error:"<<str_map<<std::endl;
	}

	std::string str_lm = str_map_path + cComm::Get_FileName(str_map) +".lm"; 
	if (!pkg_lm(str_lm)){
		std::cout<<"pkg_lm error:"<<str_lm<<std::endl;
	}

	std::string str_qr = str_map_path + cComm::Get_FileName(str_map) +".qr"; 
	if (!pkg_qr(str_qr)){
		std::cout<<"pkg_qr error:"<<str_qr<<std::endl;
	}
	
	if (!pkg_cfg()){
		std::cout<<"pkg_cfg error"<<std::endl;
		return false;
	}

	pkg_name = cComm::Get_FileName(str_db);
	pkg_name = str_path_ + pkg_name + ".pkg";

	if(merge_pkg_file(pkg_name)){

		check_del_db(pkg_name);

		return true;
	}else{
		return false; 
	}

}

bool msg_log_pkg::merge_pkg_file(const std::string &pkg_file)
{
	if (fos_.is_open())
	{
		fos_.close();
	}

	fos_.open(pkg_file.c_str(),std::ios::out | std::ios::trunc | std::ios::binary);
	//fs_.open(file_path.c_str(),std::ios::in | std::ios::binary);
	std::cout<<"open file:"<<pkg_file<<std::endl;

	if(!fos_.is_open()){
		std::cout<<"open pkg file err!"<<pkg_file<<std::endl;
		return false;
	}

	fos_.write((char*)&pkg_file_head_,sizeof(PKG_FILE_HEAD));

	merge_file(fos_,std::string((char*)pkg_file_head_.ch_db_));
	merge_file(fos_,std::string((char*)pkg_file_head_.ch_map_));
	merge_file(fos_,std::string((char*)pkg_file_head_.ch_yaml_));
	merge_file(fos_,std::string((char*)pkg_file_head_.ch_cfg_));
	if (pkg_file_head_.lm_size_){
		merge_file(fos_,std::string((char*)pkg_file_head_.ch_lm_));
	}
	if (pkg_file_head_.qr_size_){
		merge_file(fos_,std::string((char*)pkg_file_head_.ch_qr_));
	}
	

	cComm::Del_File(std::string((char*)pkg_file_head_.ch_db_));
	cComm::Del_File(std::string((char*)pkg_file_head_.ch_map_));
	cComm::Del_File(std::string((char*)pkg_file_head_.ch_yaml_));
	cComm::Del_File(std::string((char*)pkg_file_head_.ch_cfg_));
	cComm::Del_File(std::string((char*)pkg_file_head_.ch_lm_));
	cComm::Del_File(std::string((char*)pkg_file_head_.ch_qr_));

	fos_.close();

	std::cout<<cTimerDiff::get_now()<<" save pkg over! "<<pkg_file<<std::endl;

	return true;
}
unsigned long msg_log_pkg::file_size(const char *filename)
{
	FILE *pFile = fopen(filename, "rb");
	fseek (pFile, 0, SEEK_END);
	unsigned long size = ftell(pFile);
	fclose (pFile);
	return size;
}


bool msg_log_pkg::decompress_one_file(const char *infilename, const char *outfilename)
{

	int num_read = 0;
	char buffer[128] = {0};

	gzFile infile = gzopen(infilename, "rb");
	FILE *outfile = fopen(outfilename, "wb");

	if (!infile || !outfile){
		return false;
	}

	while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
		fwrite(buffer, 1, num_read, outfile);
		memset(buffer,0,128);
	}
	gzclose(infile);
	fclose(outfile);
	return true;
}


bool msg_log_pkg::compress_one_file(const char *infilename,const char *outfilename)
{
	int num_read = 0;
	char inbuffer[128] = {0};
	unsigned long total_read = 0, total_wrote = 0;
	FILE *infile = fopen(infilename, "rb");
	gzFile outfile = gzopen(outfilename, "wb");
	if (!infile || !outfile){
		return false;
	} 

	while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
		total_read += num_read;
		gzwrite(outfile, inbuffer, num_read);
		memset(inbuffer,0,128);
	}
	fclose(infile);
	gzclose(outfile);
	printf("Read %ld bytes, Wrote %ld bytes,"
		"Compression factor %4.2f%%\n",
		total_read, file_size(outfilename),
		(1.0-file_size(outfilename)*1.0/total_read)*100.0);
	return true;
}

bool msg_log_pkg::pkg_db( const std::string &db_file ,const std::string &pkg_file )
{
	if(compress_one_file(db_file.c_str(),pkg_file.c_str())){
		std::stringstream ss;

// 		if(!cComm::Del_File(db_file))
// 		{
// 			std::cout<<"rm db err:"<<db_file<<std::endl;
// 			return false;
// 		}
		set_file_db(pkg_file);
		return true;
	}else{
		std::cout<<"compress file err:"<<db_file<<std::endl;

		return false;
	}
}

bool msg_log_pkg::pkg_map(const std::string &str_file)
{
	memset(pkg_file_head_.ch_map_,0,sizeof(pkg_file_head_.ch_map_));
	pkg_file_head_.map_size_ = 0;

	memset(pkg_file_head_.ch_yaml_,0,sizeof(pkg_file_head_.ch_yaml_));
	pkg_file_head_.yaml_size_ = 0;

	if (!cComm::FileExist(str_file)){

		std::cout<<"map no exist:"<<str_file<<std::endl;
		return false;
	}
	std::string str_zmap = str_path_ + cComm::Get_FileName(str_file) +"." + cComm::Get_FileType(str_file) + "z";

	if(!compress_one_file(str_file.c_str(),str_zmap.c_str())){
		std::cout<<"compress file err:"<<str_file<<std::endl;
		return false;
	}
	set_file_map(str_zmap);

	if (cComm::Get_FileType(str_file) == "pgm"){
		std::string str_yaml = cComm::Get_FilePath(str_file)  + cComm::Get_FileName(str_file) + ".yaml";
		std::string str_yamlz = str_path_ + cComm::Get_FileName(str_file) + ".yamlz";
		if(!compress_one_file(str_yaml.c_str(),str_yamlz.c_str())){
			std::cout<<"compress file err:"<<str_yaml<<std::endl;
			return false;
		}else{
			set_file_yaml(str_yamlz);
		}
	}
	

	return true;
	
}

bool msg_log_pkg::pkg_cfg()
{
	

	std::string str_cfg = ".//cfg//kps_config.cfg";
	if (!cComm::FileExist(str_cfg)){
		std::cout<<"cfg no exist:"<<str_cfg<<std::endl;
		return false;
	}

	std::string str_cfgz = str_path_ + "kps_config.cfgz";
	if(!compress_one_file(str_cfg.c_str(),str_cfgz.c_str())){
		std::cout<<"compress file err:"<<str_cfg<<std::endl;
		return false;
	}else{
		set_file_cfg(str_cfgz);
	}

	return true;
}

void msg_log_pkg::set_file_db( const std::string &str_db_name )
{
	pkg_file_head_.db_size_ = file_size(str_db_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_db_,ilen,str_db_name);
	
}

void msg_log_pkg::set_file_map( const std::string &str_map_name )
{
	pkg_file_head_.map_size_ = file_size(str_map_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_map_,ilen,str_map_name);
}

void msg_log_pkg::set_file_yaml( const std::string &str_yaml_name )
{
	pkg_file_head_.yaml_size_ = file_size(str_yaml_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_yaml_,ilen,str_yaml_name);
}
void msg_log_pkg::set_file_lm( const std::string &str_lm_name )
{
	pkg_file_head_.lm_size_ = file_size(str_lm_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_lm_,ilen,str_lm_name);
}
void msg_log_pkg::set_file_qr( const std::string &str_qr_name )
{
	pkg_file_head_.qr_size_ = file_size(str_qr_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_qr_,ilen,str_qr_name);
}
void msg_log_pkg::set_file_cfg( const std::string &str_cfg_name )
{
	pkg_file_head_.cfg_size_ = file_size(str_cfg_name.c_str());
	int ilen = 200;
	cComm::String2Charlist(pkg_file_head_.ch_cfg_,ilen,str_cfg_name);
}

bool msg_log_pkg::merge_file( std::ofstream &fos ,const std::string &str_file)
{
	if (!cComm::FileExist(str_file))
	{
		std::cout<<"merge_file no exist!:"<<str_file<<std::endl;
		return false;
	}
	

	FILE *infile = fopen(str_file.c_str(), "rb");
	fseek (infile, 0, SEEK_END);
	unsigned long size = ftell(infile);


	fseek (infile, 0, SEEK_SET);
	char buf[1024]={0};
	unsigned long iread = 0 ; 
	int num_read = 0 ;
	while ((num_read = fread(buf, 1, sizeof(buf), infile)) > 0) {
		iread += num_read;
		fos.write(buf,num_read);
		memset(buf,0,1024);
	}


	fclose(infile);
	assert(iread == size);

	return true; 
}

bool msg_log_pkg::unpackage_db(const std::string &pkg_file)
{
	memset(&pkg_file_head_,0,sizeof(PKG_FILE_HEAD));
	pkg_file_head_.ver_ = cComm::getVersion();

	str_unpackage_db_name_ = "";
	str_unpackage_map_name_ = "";
	str_unpackage_yaml_name_ = "";
	str_unpackage_lm_name_ = "";
	str_unpackage_qr_name_ = "";
	str_unpackage_cfg_name_ = "";

	PKG_FILE_HEAD pkg_file_head;
	memset(&pkg_file_head,0,sizeof(PKG_FILE_HEAD));

	std::ifstream fis;

	fis.open(pkg_file.c_str(),std::ios::in | std::ios::binary);
	

	if(!fis.is_open()){

		std::cout<<"open pkg file err :"<<pkg_file<<std::endl;
		return false;
	}

	fis.read((char*)&pkg_file_head,sizeof(PKG_FILE_HEAD));

	if (!check_ver(pkg_file_head)){
		std::cout<<"check ver err !!"<<std::endl;
		return false;
	}
// 	str_unpackage_db_name_ = (char*)pkg_file_head.ch_db_;
// 	str_unpackage_map_name_ = (char*)pkg_file_head.ch_map_;
// 	str_unpackage_yaml_name_ = (char*)pkg_file_head.ch_yaml_;
// 	str_unpackage_cfg_name_ = (char*)pkg_file_head.ch_cfg_;

	//create dbz file
	std::string str_file_nm = (char*)pkg_file_head.ch_db_;
	char* ch_data = new char[pkg_file_head.db_size_];
	fis.read(ch_data,pkg_file_head.db_size_);
	splite_file(ch_data,pkg_file_head.db_size_,str_file_nm);
	delete[] ch_data;
	ch_data = 0;
	unzip_file(str_file_nm);
	str_unpackage_db_name_ = str_file_nm;
	

	//create mapz file
	str_file_nm = (char*)pkg_file_head.ch_map_;
	ch_data = new char[pkg_file_head.map_size_];
	fis.read(ch_data,pkg_file_head.map_size_);
	splite_file(ch_data,pkg_file_head.map_size_,str_file_nm);
	delete[] ch_data;
	ch_data = 0;
	unzip_file(str_file_nm);
	str_unpackage_map_name_ = str_file_nm;

	//create yamlz file
	if (pkg_file_head.yaml_size_ > 0){
		str_file_nm = (char*)pkg_file_head.ch_yaml_;
		ch_data = new char[pkg_file_head.yaml_size_];
		fis.read(ch_data,pkg_file_head.yaml_size_);
		splite_file(ch_data,pkg_file_head.yaml_size_,str_file_nm);
		delete[] ch_data;
		ch_data = 0;
		unzip_file(str_file_nm);
		str_unpackage_yaml_name_ = str_file_nm;

	}

	//create cfgz file
	str_file_nm = (char*)pkg_file_head.ch_cfg_;
	ch_data = new char[pkg_file_head.cfg_size_];
	fis.read(ch_data,pkg_file_head.cfg_size_);
	splite_file(ch_data,pkg_file_head.cfg_size_,str_file_nm);
	delete[] ch_data;
	ch_data = 0;
	unzip_file(str_file_nm);
	str_unpackage_cfg_name_ = str_file_nm;


	if (pkg_file_head.lm_size_){
		str_file_nm = (char*)pkg_file_head.ch_lm_;
		ch_data = new char[pkg_file_head.lm_size_];
		fis.read(ch_data,pkg_file_head.lm_size_);
		splite_file(ch_data,pkg_file_head.lm_size_,str_file_nm);
		delete[] ch_data;
		ch_data = 0;
		unzip_file(str_file_nm);
		str_unpackage_lm_name_ = str_file_nm;
	}

	if (pkg_file_head.qr_size_){
		str_file_nm = (char*)pkg_file_head.ch_qr_;
		ch_data = new char[pkg_file_head.qr_size_];
		fis.read(ch_data,pkg_file_head.qr_size_);
		splite_file(ch_data,pkg_file_head.qr_size_,str_file_nm);
		delete[] ch_data;
		ch_data = 0;
		unzip_file(str_file_nm);
		str_unpackage_qr_name_ = str_file_nm;
	}

	fis.close();

	return true;
}

bool msg_log_pkg::splite_file(const char* buf,int ilen,const std::string &str_file)
{
// 	std::stringstream ss;
// 	ss<<str_file<<"_uz";
	std::ofstream fos;
	fos.open(str_file.c_str(),std::ios::out | std::ios::trunc | std::ios::binary);
	//fs_.open(file_path.c_str(),std::ios::in | std::ios::binary);
	std::cout<<"create zip file:"<<str_file<<std::endl;

	if(!fos.is_open()){
		std::cout<<"create zip file err!"<<str_file<<std::endl;
		return false;
	}

	fos.write(buf,ilen);
	fos.close();
}

bool msg_log_pkg::unzip_file(std::string &str_file)
{
	std::string str_unzip_name = cComm::Get_FileType(str_file);
	str_unzip_name = str_unzip_name.substr(0,str_unzip_name.length() -1);
	str_unzip_name = str_path_ + cComm::Get_FileName(str_file) + "." + str_unzip_name;
	
	if (decompress_one_file(str_file.c_str(),str_unzip_name.c_str())){
		std::cout<<"decompress file:"<<str_file<<std::endl;
		cComm::Del_File(str_file);
		str_file = str_unzip_name;
		return true;
	}else{
		cComm::Del_File(str_file);
		std::cout<<"decompress file err:"<<str_file<<std::endl;
		return false;
	}
	
}

bool msg_log_pkg::check_ver(const PKG_FILE_HEAD &pkg_file_head)
{
	if( (pkg_file_head_.ver_.v_main_ != pkg_file_head.ver_.v_main_ ) || 
		(pkg_file_head_.ver_.v_sub_1_ != pkg_file_head.ver_.v_sub_1_) ||
		(pkg_file_head_.ver_.v_sub_2_ != pkg_file_head.ver_.v_sub_2_) ){
			return false;
	}else{
		return true;
	}
}

std::string msg_log_pkg::get_unpackage_db_name()
{
	return str_unpackage_db_name_;
}

std::string msg_log_pkg::get_unpackage_map_name()
{
	return str_unpackage_map_name_;
}


std::string msg_log_pkg::get_unpackage_yaml_name()
{
	return str_unpackage_yaml_name_;
}

std::string msg_log_pkg::get_unpackage_cfg_name()
{
	return str_unpackage_cfg_name_;
}
std::string msg_log_pkg::get_unpackage_lm_name()
{
	return str_unpackage_lm_name_;
}

std::string msg_log_pkg::get_unpackage_qr_name()
{
	return str_unpackage_qr_name_;
}
void msg_log_pkg::check_del_db( const std::string &str_pkg )
{
	l_pk_db_.push_back(str_pkg);
	if (l_pk_db_.size() > max_db_size_)
	{
		std::string pkg = l_pk_db_.front();
		cComm::Del_File(pkg);
		l_pk_db_.pop_front();
	}
	
}

bool msg_log_pkg::pkg_lm( const std::string &str_file )
{
	memset(pkg_file_head_.ch_lm_,0,sizeof(pkg_file_head_.ch_lm_));
	pkg_file_head_.lm_size_ = 0;


	if (!cComm::FileExist(str_file)){

		std::cout<<"lm map no exist:"<<str_file<<std::endl;
		return false;
	}
	std::string str_zmap = str_path_ + cComm::Get_FileName(str_file) +"." + cComm::Get_FileType(str_file) + "z";

	if(!compress_one_file(str_file.c_str(),str_zmap.c_str())){
		std::cout<<"compress file err:"<<str_file<<std::endl;
		return false;
	}
	set_file_lm(str_zmap);
	
	return true;
}

bool msg_log_pkg::pkg_qr( const std::string &str_file )
{
	memset(pkg_file_head_.ch_qr_,0,sizeof(pkg_file_head_.ch_qr_));
	pkg_file_head_.qr_size_ = 0;


	if (!cComm::FileExist(str_file)){

		std::cout<<"qr map no exist:"<<str_file<<std::endl;
		return false;
	}
	std::string str_zmap = str_path_ + cComm::Get_FileName(str_file) +"." + cComm::Get_FileType(str_file) + "z";

	if(!compress_one_file(str_file.c_str(),str_zmap.c_str())){
		std::cout<<"compress file err:"<<str_file<<std::endl;
		return false;
	}
	set_file_qr(str_zmap);

	return true;
}















