#ifndef _DIO_MANAGE_KYOSHO_20190220_
#define _DIO_MANAGE_KYOSHO_20190220_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"
#include "robot/dio_def.h"



class dio_manage
{
public:
	dio_manage();
	~dio_manage();
	
	
	void init( std::string str_sub_dev, std::string str_pub_dev = "" );

	bool load_binding(std::string str_file);

	bool bind_fnc_DI(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index);
	bool bind_fnc_DO(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index);
	bool bind_fnc_AIF(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index);
	bool bind_fnc_AOF(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index);
	bool bind_fnc_index(const std::string &str_type , const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index);
	//get bind func and pin to show
	int get_bind(std::map<std::string, SDIO_NM_INDEX> &m_fnc_bind);
	int get_io_data(std::vector<SDIO_NM_INDEX> &v_data);

	bool set_di(const std::string &str_dev_nm, const SDI &sdi);
	bool set_ai(const std::string &str_dev_nm, const SAI &sai);
	bool set_do(const std::string &str_dev_nm, const SDO &sdo);
	bool set_fai(const std::string &str_dev_nm, const SFAI &sai);
	bool set_fao(const std::string &str_dev_nm, const SFAO &sao);

	bool get_di_ai(std::map<std::string, SDIAI> &m_di_ai);
	bool get_di( U8 &data,const std::string &str_fnc,std::map<std::string, SDIAI> &m_di_ai);
	bool get_di(U8 &data,const std::string &str_fnc);
	
	bool get_sfai(std::map<std::string, SAIF> &m_fai);
	bool get_fai( F32 &data, const std::string &str_fnc,std::map<std::string, SAIF> &m_fai);
	bool get_fai( F32 &data, const std::string &str_fnc);
	
	bool get_sdo_ao(std::map<std::string, SDOAO> &m_do_ao);
	bool get_do( U8 &data, const std::string &str_fnc, std::map<std::string, SDOAO> &m_do_ao);
	bool get_do( U8 &data, const std::string &str_fnc);

	bool get_sfao(std::map<std::string, SAOF> &m_fao);
	bool get_fao( F32 &data, const std::string &str_fnc, std::map<std::string, SAOF> &m_fao);
 	bool get_fao( F32 &data, const std::string &str_fnc);

// 	bool pub_sdi_ai(const std::string &str_dev_nm);
// 	bool pub_sdo_ao(const std::string &str_dev_nm);
// 	bool pub_sfai(const std::string &str_dev_nm);
// 	bool pub_sfao(const std::string &str_dev_nm);

//	bool set_fnc_sdo(const SFNC_DO &fnc_sdo);
// 	bool get_do(SDO &sdo);
//	bool get_do_sdo( std::list<SDO> &l_sdo, std::string str_dev);

//	bool pub_di(const SDI &sdi);
private:
	boost::mutex mu_fnc_bind_;
	std::map<std::string,SDIO_NM_INDEX> m_fnc_bind_;
	std::map<std::string,std::pair<U64,int>> m_stamp_error_;
// 	
// 	U64 last_di_ai_stamp_;
// 	int i_plc_di_ai_err_;

	boost::mutex mu_di_ai_;
	std::map<std::string, SDIAI> m_di_ai_;
	
	boost::mutex mu_fai_;
	std::map<std::string, SAIF> m_fai_;

	boost::mutex mu_fao_;
	std::map<std::string, SAOF> m_fao_;
 
	boost::mutex mu_do_ao_;
	std::map<std::string, SDOAO> m_do_ao_;


protected:
private:
// 	bool call_onboard_di_ai( const SDIAI &sdi_ai);
// 	bool call_plclujie_di_ai( const SDIAI &sdi_ai);
// 	bool call_mushiny_di_ai( const SDIAI &sdi_ai);
// 	bool call_mushiny_fai( const SAIF &f_ai);
//	bool call_action_fao( const SAOF &f_ao);

	//do ao
// private:
	std::map<std::string,int> m_sub_dev_sdi_;
	bool call_fnc_sdi(std::string str_dev, const SDI &sdi);

 	std::map<std::string,int> m_sub_dev_sdo_;
	bool call_fnc_sdo(std::string str_dev, const SDO &sdo);


	std::map<std::string,int> m_sub_dev_fao_;
	bool call_fnc_fao(std::string str_dev, const SFAO &fao);

	std::map<std::string,int> m_sub_dev_fai_;
	bool call_fnc_fai(std::string str_dev, const SFAI &fai);
};

typedef boost::serialization::singleton<dio_manage> Singleton_DIO_MANAGE;
#define DIO_MANAGE Singleton_DIO_MANAGE::get_mutable_instance()

#endif//_DIO_MANAGE_KYOSHO_20190220_
