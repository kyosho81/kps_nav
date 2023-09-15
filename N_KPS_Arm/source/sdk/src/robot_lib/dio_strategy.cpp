#include <string.h>
#include <iostream>

#include "Comm.h"
#include "msg_pump/msg_pump.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "trans_dev/trans_dev.h"
#include "log/log_client.h"
#include "robot/dio_manage.h"

#include "robot/dio_strategy.h"


std::map<std::string, SDIO_NM_INDEX> dio_strategy::m_fnc_bind_;

dio_strategy::dio_strategy()
{
	
}

dio_strategy::~dio_strategy()
{

}



bool dio_strategy::init()
{

	return true;
}




bool dio_strategy::set_sdi(SDI &sdi ,const int &i_index ,const U8 &value)
{
	if ((sdi.used_ + 1) < MAX_DI){
		sdi.id_[sdi.used_] = sdi.used_;
		sdi.di_[sdi.used_] = value;
		sdi.used_++;
		return true;
	}
	return false;
}




bool dio_strategy::set_fnc_sdi(std::map<std::string,SDI> &m_dev_sdi,std::string str_fnc_di ,const U8 &value)
{
	auto it = m_fnc_bind_.find(str_fnc_di);
	if ( it != m_fnc_bind_.end() ){

		SDIO_NM_INDEX &sdo_nm_index = it->second;
		SDI &sdi =m_dev_sdi[sdo_nm_index.str_dev_nm_];

		return set_sdi(sdi,sdo_nm_index.i_dio_index_,value);
	}
}


bool dio_strategy::pub_fnc_sdi(std::map<std::string,SDI> &m_dev_sdi)
{
	auto it = m_dev_sdi.begin();
	for (  ; it != m_dev_sdi.end() ; ++it ){

		SDI sdi = it->second;
		std::string str_pub_msg = PUB_FNC_DI + it->first;
		PUB_MSG_SH_POOL(str_pub_msg,sdi);
	}
	return true;
}

bool dio_strategy::get_sdi(S32 &value, const SDI &sdi, const int &i_id)
{
	value = 0;

	for ( int i = 0 ; i < sdi.used_ ; ++i){
		if (i_id == sdi.id_[i]){
			value = sdi.di_[i];
			return true;
		}
	}
	return false;
}

bool dio_strategy::set_sdo( SDO &sdo ,const int &i_index ,const U8 &value )
{

	if ( (sdo.used_ + 1) < MAX_DO ){

		sdo.id_[sdo.used_] = i_index;
		sdo.do_[sdo.used_] = value;
		sdo.used_++;

		return true;
	}

	return false;
}



bool dio_strategy::get_sdo( S32 &value , const SDO &sdo , const int &i_id )
{
	for ( int i = 0 ; i < sdo.used_ ; ++i ){
		if( sdo.id_[i] == i_id ){
			value = sdo.do_[i];
			return true;
		}
	}
	
	return false;
}

bool dio_strategy::set_sfao( SFAO &fao ,const int &i_index , const F32 &value)
{
	assert(i_index < MAX_AO);
	if ( (fao.used_ + 1) < MAX_AO ){

		fao.id_[fao.used_] = i_index;
		fao.fao_[fao.used_] = value;
		fao.used_++;

		return true;
	}

	return false;
}

bool dio_strategy::get_sfao( F32 &value , const SFAO &fao , const int &i_id )
{
	for ( int i = 0 ; i < fao.used_ ; ++i ){
		if( fao.id_[i] == i_id ){
			value = fao.fao_[i];
			return true;
		}
	}

	return false;
}

bool dio_strategy::set_sfai( SFAI &fai  ,const int &i_index ,const F32 &value)
{

	if ( (fai.used_ + 1) < MAX_AI ){

		fai.id_[fai.used_] = i_index;
		fai.fai_[fai.used_] = value;
		fai.used_++;

		return true;
	}

	return false;
}
bool dio_strategy::get_sfai( F32 &value , const SFAI &fai , const int &i_id )
{
	for ( int i = 0 ; i < fai.used_ ; ++i ){
		if( fai.id_[i] == i_id ){
			value = fai.fai_[i];
			return true;
		}
	}

	return false;
}


bool dio_strategy::set_fnc_sdo(std::map<std::string,SDO> &m_dev_sdo,std::string str_fnc_do ,const U8 &value)
{
	auto it = m_fnc_bind_.find(str_fnc_do);
	if ( it != m_fnc_bind_.end() ){

		SDIO_NM_INDEX &sdo_nm_index = it->second;
		SDO &sdo =m_dev_sdo[sdo_nm_index.str_dev_nm_];
		
		return set_sdo(sdo,sdo_nm_index.i_dio_index_,value);
	}
}

bool dio_strategy::pub_fnc_sdo(std::map<std::string,SDO> &m_dev_sdo)
{
	std::map<std::string,SDO>::iterator it = m_dev_sdo.begin();
	for (  ; it != m_dev_sdo.end() ; ++it ){

		SDO sdo = it->second;
		std::string str_pub_msg = PUB_FNC_DO + it->first;
		PUB_MSG_SH_POOL(str_pub_msg,sdo);
	}
	return true;
}

bool dio_strategy::set_fnc_sfao(std::map<std::string,SFAO> &m_dev_sfao,std::string str_fnc_sfao ,const F32 &value)
{
	auto it = m_fnc_bind_.find(str_fnc_sfao);
	if ( it != m_fnc_bind_.end() ){

		SDIO_NM_INDEX &sdo_nm_index = it->second;
		SFAO &sfao = m_dev_sfao[sdo_nm_index.str_dev_nm_];

		return set_sfao(sfao,sdo_nm_index.i_dio_index_,value);
	}
}

bool dio_strategy::pub_fnc_sfao(std::map<std::string,SFAO> &m_dev_sfao)
{
	std::map<std::string,SFAO>::iterator it = m_dev_sfao.begin();
	for (  ; it != m_dev_sfao.end() ; ++it ){

		SFAO fao = it->second;
		std::string str_pub_msg = PUB_FNC_FAO + it->first;
		PUB_MSG_SH_POOL(str_pub_msg,fao);
	}
	return true;
}

bool dio_strategy::set_fnc_sfai(std::map<std::string,SFAI> &m_dev_sfai,std::string str_fnc_sfai ,const F32 &value)
{
	auto it = m_fnc_bind_.find(str_fnc_sfai);
	if ( it != m_fnc_bind_.end() ){

		SDIO_NM_INDEX &sdo_nm_index = it->second;
		SFAI &sfai = m_dev_sfai[sdo_nm_index.str_dev_nm_];

		return set_sfai(sfai,sdo_nm_index.i_dio_index_,value);
	}
}

bool dio_strategy::pub_fnc_sfai(std::map<std::string,SFAI> &m_dev_sfai)
{
	auto it = m_dev_sfai.begin();
	for (  ; it != m_dev_sfai.end() ; ++it ){

		SFAI fai = it->second;
		std::string str_pub_msg = PUB_FNC_FAI + it->first;
		PUB_MSG_SH_POOL(str_pub_msg,fai);
	}
	return true;
}



