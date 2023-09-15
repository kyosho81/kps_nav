#ifndef _DIO_STRATEGY_WANGHONGTAO_20221210_
#define _DIO_STRATEGY_WANGHONGTAO_20221210_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include "buffer_con.hpp"
#include "robot/dio_def.h"

class dio_strategy
{
public:
	dio_strategy();
	~dio_strategy();

	static bool init();
	static std::map<std::string, SDIO_NM_INDEX> m_fnc_bind_;
	
	//static bool set_sdi(SDI &di , const SDIAI &sdiai , const int &i_id);
	static bool get_sdi(S32 &value, const SDI &sdi, const int &i_id);

	static bool set_sdi(SDI &sdi ,const int &i_index ,const U8 &value);

	static bool set_fnc_sdi(std::map<std::string,SDI> &m_dev_sdi,std::string str_fnc_di ,const U8 &value);
	static bool pub_fnc_sdi(std::map<std::string,SDI> &m_dev_sdi);

public:
	
	static bool set_sdo(SDO &sdo ,const int &i_index ,const U8 &value);
	static bool get_sdo(S32 &value , const SDO &sdo , const int &i_id);
	
	//static bool set_fnc_sdo(SFNC_DO &fnc_sdo ,std::string str_fnc_do ,const U8 &value);
	static bool set_fnc_sdo(std::map<std::string,SDO> &m_dev_sdo,std::string str_fnc_do ,const U8 &value);
	static bool pub_fnc_sdo(std::map<std::string,SDO> &m_dev_sdo);

public:

	static bool set_fnc_sfao(std::map<std::string,SFAO> &m_dev_sfao,std::string str_fnc_sfao ,const F32 &value);
	static bool pub_fnc_sfao(std::map<std::string,SFAO> &m_dev_sfao);

	static bool set_fnc_sfai(std::map<std::string,SFAI> &m_dev_sfai,std::string str_fnc_sfai ,const F32 &value);
	static bool pub_fnc_sfai(std::map<std::string,SFAI> &m_dev_sfai);

public:

	static bool set_sfao( SFAO &fao ,const int &i_index , const F32 &value);
	static bool get_sfao( F32 &value , const SFAO &fao , const int &i_id  );

	static bool set_sfai( SFAI &fai  ,const int &i_index ,const F32 &value );
	static bool get_sfai( F32 &value , const SFAI &fai , const int &i_id );

	//static bool set_fnc_sfai(SFNC_FAI &fnc_sfai ,std::string str_fnc_fai ,const F32 &value);

protected:
private:

	

};

#endif //_DIO_STRATEGY_WANGHONGTAO_20221210_