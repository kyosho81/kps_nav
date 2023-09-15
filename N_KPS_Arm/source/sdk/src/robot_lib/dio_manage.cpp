#include "Comm/Comm.h"
#include "interface/cfg.hpp"
#include "msg_pump/msg_pump.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "robot/dio_strategy.h"

#include "robot/dio_manage.h"

//#define  SHOW_DATA 1

dio_manage::dio_manage()
{

}

dio_manage::~dio_manage()
{
	
}


void dio_manage::init( std::string str_sub_dev, std::string str_pub_dev  )
{
	

	std::vector<std::string> v_res;
	cComm::SplitString(str_sub_dev , ":" ,v_res);
	auto it = v_res.begin();
	for ( ; it != v_res.end() ; ++it ){
		m_sub_dev_sdi_[*it] = 0;
		m_sub_dev_fai_[*it] = 0;
	}

	cComm::SplitString(str_pub_dev , ":" ,v_res);
	it = v_res.begin();
	for ( ; it != v_res.end() ; ++it ){
		//m_sub_dev_sdi_[*it] = 0;
		m_sub_dev_sdo_[*it] = 0;
		//m_sub_dev_fai_[*it] = 0;
		m_sub_dev_fao_[*it] = 0;
	}


	auto it5 = m_sub_dev_sdi_.begin();
	for ( ; it5 != m_sub_dev_sdi_.end() ; ++it5 ){

		std::string str_pub_msg = PUB_FNC_DI + it5->first;
		END_MSG_SH_POOL(SDI,str_pub_msg);
		boost::function<bool(const SDI &sdi)> sfnc_sdi;
		sfnc_sdi = boost::bind(&dio_manage::call_fnc_sdi,this,it5->first,_1);
		SUB_MSG_SH_POOL(str_pub_msg,sfnc_sdi);
	}

	auto it2 = m_sub_dev_sdo_.begin();
	for ( ; it2 != m_sub_dev_sdo_.end() ; ++it2 ){
		
		std::string str_pub_msg = PUB_FNC_DO + it2->first;
		END_MSG_SH_POOL(SDO,str_pub_msg);
		boost::function<bool(const SDO &sdo)> sfnc_sdo;
		sfnc_sdo = boost::bind(&dio_manage::call_fnc_sdo,this,it2->first,_1);
		SUB_MSG_SH_POOL(str_pub_msg,sfnc_sdo);
	}

	auto it4 = m_sub_dev_fai_.begin();
	for ( ; it4 != m_sub_dev_fai_.end() ; ++it4 ){

		std::string str_pub_msg = PUB_FNC_FAI + it4->first;
		END_MSG_SH_POOL(SFAO,str_pub_msg);
		boost::function<bool(const SFAI &fai)> sfnc_fai;
		sfnc_fai = boost::bind(&dio_manage::call_fnc_fai,this,it4->first,_1);
		SUB_MSG_SH_POOL(str_pub_msg,sfnc_fai);
	}

	auto it3 = m_sub_dev_fao_.begin();
	for ( ; it3 != m_sub_dev_fao_.end() ; ++it3 ){

		std::string str_pub_msg = PUB_FNC_FAO + it3->first;
		END_MSG_SH_POOL(SFAO,str_pub_msg);
		boost::function<bool(const SFAO &fao)> sfnc_fao;
		sfnc_fao = boost::bind(&dio_manage::call_fnc_fao,this,it3->first,_1);
		SUB_MSG_SH_POOL(str_pub_msg,sfnc_fao);
	}
	
	load_binding("");

	dio_strategy::m_fnc_bind_ = m_fnc_bind_;

}

bool dio_manage::load_binding(std::string str_file)
{
	std::cout<<"dio_manage::load_binding"<<std::endl;
	bind_fnc_DI(DI_FNC_EMERGENCY, DIO_DEV_PLCLUJIE, DI_00);       // x0
	bind_fnc_DI(DI_FNC_CLEAR_ERROR, DIO_DEV_PLCLUJIE, DI_01);     // x1
	bind_fnc_DI(DI_FNC_AUTO_MANUAL, DIO_DEV_PLCLUJIE, DI_02);     // x2
	bind_fnc_DI(DI_FNC_EN_DESH_PROOF, DIO_DEV_PLCLUJIE, DI_03);   // x3
	bind_fnc_DI(DI_FNC_DASH_PROOF_1, DIO_DEV_PLCLUJIE, DI_04);    // x4
	bind_fnc_DI(DI_FNC_FNC_PAYLOADS, DIO_DEV_PLCLUJIE, DI_05);    // x5
	bind_fnc_DI(DI_FNC_STOP_FORKLEFT, DIO_DEV_PLCLUJIE, DI_06);   // x6
	bind_fnc_DI(DI_FNC_STOP_FORKRIGHT, DIO_DEV_PLCLUJIE, DI_07);  // x7


	bind_fnc_DI(DI_FNC_LS_LOW, DIO_DEV_PLCLUJIE, DI_08);          // x10
	bind_fnc_DI(DI_FNC_LS_SLOW, DIO_DEV_PLCLUJIE, DI_09);         // x11
	bind_fnc_DI(DI_FNC_LS_STOP, DIO_DEV_PLCLUJIE, DI_10);		  // x12

//	bind_fnc_DI(DI_FNC_FNC_LIFT_ZERO, DIO_DEV_ONBOARD, DI_02);
//	bind_fnc_DI(DI_FNC_FNC_LIFT_OVER, DIO_DEV_ONBOARD, DI_03);
//	bind_fnc_DI(DI_FNC_BT_CONNECT, DIO_DEV_ONBOARD, DI_04);

// 	bind_fnc_AIF(AIF_FNC_LIFT_POS, DIO_DEV_MUSHINY, AIF_00);
// 	bind_fnc_AIF(AIF_FNC_ROT_POS, DIO_DEV_MUSHINY, AIF_01);
// 	bind_fnc_AIF(AIF_FNC_LIFT_SPEED, DIO_DEV_MUSHINY, AIF_02);
// 	bind_fnc_AIF(AIF_FNC_ROT_SPEED, DIO_DEV_MUSHINY, AIF_03);

	bind_fnc_AIF(AIF_FNC_LIFT_POS, DIO_DEV_EASYWAY, AIF_00);
	bind_fnc_AIF(AIF_FNC_LIFT_SPEED, DIO_DEV_EASYWAY, AIF_01);

	bind_fnc_AOF(AOF_FNC_LIFT_POS, DIO_DEV_MUSHINY, AOF_00);
	bind_fnc_AOF(AOF_FNC_ROT_POS, DIO_DEV_MUSHINY, AOF_01);
	bind_fnc_AOF(AOF_FNC_LIFT_SPEED, DIO_DEV_MUSHINY, AOF_02);
	bind_fnc_AOF(AOF_FNC_ROT_SPEED, DIO_DEV_MUSHINY, AOF_03);

	bind_fnc_DO(DO_FNC_DRV_ENABLE,DIO_DEV_PLCLUJIE,DO_00); // Y0 //no usb
	bind_fnc_DO(DO_FNC_ERROR_LIHGT,DIO_DEV_PLCLUJIE,DO_01);// Y1
	bind_fnc_DO(DO_FNC_LEFT_LIHGT,DIO_DEV_PLCLUJIE,DO_02);  // Y2
	bind_fnc_DO(DO_FNC_RIGHT_LIHGT,DIO_DEV_PLCLUJIE,DO_03); // Y3

	bind_fnc_DO(DO_FNC_AUTO_MANUAL,DIO_DEV_PLCLUJIE,DO_04);// Y4
	bind_fnc_DO(DO_FNC_ONLINE,DIO_DEV_PLCLUJIE,DO_05);     // Y5
	bind_fnc_DO(DO_FNC_BT_CHARGE,DIO_DEV_PLCLUJIE,DO_06);   // Y6

	bind_fnc_DO(DO_FNC_FAST_FORWARD,DIO_DEV_PLCLUJIE,DO_08);// Y10
//	bind_fnc_DO(DO_FNC_SLOW_FORWARD,DIO_DEV_PLCLUJIE,DO_05);

//	bind_fnc_DO(DO_FNC_FAST_BACKWARD,DIO_DEV_PLCLUJIE,DO_06);
//	bind_fnc_DO(DO_FNC_SLOW_BACKWARD,DIO_DEV_PLCLUJIE,DO_07);

//	bind_fnc_DO(DO_FNC_FAST_LEFT,DIO_DEV_PLCLUJIE,DO_08);
//	bind_fnc_DO(DO_FNC_SLOW_LEFT,DIO_DEV_PLCLUJIE,DO_09);
	
//	bind_fnc_DO(DO_FNC_FAST_RIGHT,DIO_DEV_PLCLUJIE,DO_10);
//	bind_fnc_DO(DO_FNC_SLOW_RIGHT,DIO_DEV_PLCLUJIE,DO_11);

//	bind_fnc_DO(DO_FNC_TURN_CW_INP,DIO_DEV_PLCLUJIE,DO_12);
//	bind_fnc_DO(DO_FNC_TURN_CCW_INP,DIO_DEV_PLCLUJIE,DO_13);

	bind_fnc_DO(DO_FNC_TURN_CW,DIO_DEV_PLCLUJIE,DO_09);// Y11
	bind_fnc_DO(DO_FNC_TURN_CCW,DIO_DEV_PLCLUJIE,DO_10);// Y12
	bind_fnc_DO(DO_FNC_LOADING,DIO_DEV_PLCLUJIE,DO_11);// Y13
	

	return true;
}

bool dio_manage::bind_fnc_DI(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index)
{
	return bind_fnc_index(DIO_TYPE_DI,str_fnc, str_dev_nm, i_dio_index);
}
bool dio_manage::bind_fnc_DO(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index)
{
	return bind_fnc_index(DIO_TYPE_DO,str_fnc, str_dev_nm, i_dio_index);
}
bool dio_manage::bind_fnc_AIF(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index)
{
	return bind_fnc_index(DIO_TYPE_FAI,str_fnc, str_dev_nm, i_dio_index);
}

bool dio_manage::bind_fnc_AOF(const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index)
{
	return bind_fnc_index(DIO_TYPE_FAO,str_fnc, str_dev_nm, i_dio_index);
}

bool dio_manage::bind_fnc_index(const std::string &str_type ,const std::string &str_fnc, const std::string &str_dev_nm , int i_dio_index)
{
	boost::mutex::scoped_lock lock(mu_fnc_bind_);
	SDIO_NM_INDEX &sdio_nm_index = m_fnc_bind_[str_fnc];
	sdio_nm_index.str_dev_nm_ = str_dev_nm;
	sdio_nm_index.str_fnc_nm_ = str_fnc;
	sdio_nm_index.i_dio_index_ = i_dio_index;
	sdio_nm_index.str_type_ = str_type;

	return true;
}
int dio_manage::get_bind(std::map<std::string, SDIO_NM_INDEX> &m_fnc_bind){
	boost::mutex::scoped_lock lock(mu_fnc_bind_);
	m_fnc_bind = m_fnc_bind_;
	return m_fnc_bind.size();
}

int dio_manage::get_io_data(std::vector<SDIO_NM_INDEX> &v_data)
{
	v_data.clear();


	std::map<std::string, SDIAI> m_di_ai;
	get_di_ai(m_di_ai);
	std::map<std::string, SAIF> m_fai;
	get_sfai(m_fai);
	std::map<std::string, SAOF> m_fao;
	get_sfao(m_fao);

	std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
	{
		boost::mutex::scoped_lock lock(mu_fnc_bind_);
		m_fnc_bind = m_fnc_bind_;
	}

#if 1
	auto it = m_fnc_bind.begin();
	for ( ; it != m_fnc_bind.end() ; ++it ){

		SDIO_NM_INDEX dio_nm_index = it->second;
		dio_nm_index.str_value_ = "check pub dev:" + dio_nm_index.str_dev_nm_;

		if (dio_nm_index.str_type_ == DIO_TYPE_DI){
			auto it2 = m_di_ai.find(dio_nm_index.str_dev_nm_);
			if (it2 != m_di_ai.end() ){
				SDIAI &di_ai = it2->second;
				if (di_ai.di_[dio_nm_index.i_dio_index_] > 0){
					dio_nm_index.str_value_ = "on";
				}else{
					dio_nm_index.str_value_ = "off";
				}
				
			}
			
		}else if (dio_nm_index.str_type_ == DIO_TYPE_FAI){
			auto it2 = m_fai.find(dio_nm_index.str_dev_nm_);
			if (it2 != m_fai.end() ){
				SAIF &fai = it2->second;
				dio_nm_index.str_value_ =  cComm::ConvertToString(fai.fai_[dio_nm_index.i_dio_index_]);
			}
		}else if (dio_nm_index.str_type_ == DIO_TYPE_FAO){
			auto it2 = m_fao.find(dio_nm_index.str_dev_nm_);
			if (it2 != m_fao.end() ){
				SAOF &fao = it2->second;
				dio_nm_index.str_value_ =  cComm::ConvertToString(fao.fao_[dio_nm_index.i_dio_index_]);
			}
		}
		//dio_nm_index.str_value_ = cComm::ConvertToString(v_data.size());
		v_data.push_back(dio_nm_index);
	}
#endif
	return v_data.size();

}

bool dio_manage::set_di(const std::string &str_dev_nm, const SDI &sdi)
{
	

	boost::mutex::scoped_lock lock(mu_di_ai_);
	//if no exist then create
	std::map<std::string, SDIAI>::iterator it = m_di_ai_.find(str_dev_nm);
	if (it == m_di_ai_.end() ){
		SDIAI di_ai;
		memset(&di_ai,0,sizeof(SDIAI));
		m_di_ai_[str_dev_nm] = di_ai;
		it = m_di_ai_.find(str_dev_nm);
	}
	
	SDIAI &di_ai = it->second;
	di_ai.time_stamp_ = cTimerDiff::total_ms();
	for ( int i = 0 ; i < sdi.used_; ++i){
		int index = sdi.id_[i];
		if (index < MAX_DI){
			di_ai.di_[index] = sdi.di_[i];
		}
	}

	return true;
}

bool dio_manage::set_ai(const std::string &str_dev_nm, const SAI &sai)
{
	boost::mutex::scoped_lock lock(mu_di_ai_);
	//if no exist then create
	std::map<std::string, SDIAI>::iterator it = m_di_ai_.find(str_dev_nm);
	if (it == m_di_ai_.end() ){
		SDIAI di_ai;
		memset(&di_ai,0,sizeof(SDIAI));
		m_di_ai_[str_dev_nm] = di_ai;
		it = m_di_ai_.find(str_dev_nm);
	}

	SDIAI &di_ai = it->second;
	di_ai.time_stamp_ = cTimerDiff::total_ms();

	for ( int i = 0 ; i < sai.used_; ++i){
		int index = sai.id_[i];
		if (index < MAX_AI){
			di_ai.di_[index] = sai.ai_[i];
		}
	}

	return true;
}

bool dio_manage::set_do(const std::string &str_dev_nm, const SDO &sdo)
{
	boost::mutex::scoped_lock lock(mu_do_ao_);
	//if no exist then create
	std::map<std::string, SDOAO>::iterator it = m_do_ao_.find(str_dev_nm);
	if (it == m_do_ao_.end() ){
		SDOAO do_ao;
		memset(&do_ao,0,sizeof(SDOAO));
		m_do_ao_[str_dev_nm] = do_ao;
		it = m_do_ao_.find(str_dev_nm);
	}

	SDOAO &do_ao = it->second;
	do_ao.time_stamp_ = cTimerDiff::total_ms();
	for ( int i = 0 ; i < sdo.used_; ++i){
		int index = sdo.id_[i];
		if (index < MAX_DO){
			do_ao.do_[index] = sdo.do_[i];
		}
	}

	return true;
}

bool dio_manage::set_fai(const std::string &str_dev_nm, const SFAI &sai)
{
	boost::mutex::scoped_lock lock(mu_fai_);
	//if no exist then create
	std::map<std::string, SAIF>::iterator it = m_fai_.find(str_dev_nm);
	if (it == m_fai_.end() ){
		SAIF fai;
		memset(&fai,0,sizeof(SAIF));
		m_fai_[str_dev_nm] = fai;
		it = m_fai_.find(str_dev_nm);
	}

	SAIF &fai = it->second;
	fai.time_stamp_ = cTimerDiff::total_ms();

	for ( int i = 0 ; i < sai.used_; ++i){
		int index = sai.id_[i];
		if (index < MAX_AI){
			fai.fai_[index] = sai.fai_[i];
		}
	}

	return true;
}

bool dio_manage::set_fao(const std::string &str_dev_nm, const SFAO &sao)
{
	boost::mutex::scoped_lock lock(mu_fao_);
	//if no exist then create
	std::map<std::string, SAOF>::iterator it = m_fao_.find(str_dev_nm);
	if (it == m_fao_.end() ){
		SAOF fao;
		memset(&fao,0,sizeof(SAOF));
		m_fao_[str_dev_nm] = fao;
		it = m_fao_.find(str_dev_nm);
	}

	SAOF &fao = it->second;
	fao.time_stamp_ = cTimerDiff::total_ms();

	for ( int i = 0 ; i < sao.used_; ++i){
		int index = sao.id_[i];
		if (index < MAX_AO){
			fao.fao_[index] = sao.fao_[i];
		}
	}

	return true;
}

bool dio_manage::get_di_ai(std::map<std::string, SDIAI> &m_di_ai)
{

	boost::mutex::scoped_lock lock(mu_di_ai_);
	m_di_ai = m_di_ai_;

	return true;
}

bool dio_manage::get_di( U8 &data,const std::string &str_fnc,std::map<std::string, SDIAI> &m_di_ai)
{

	std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
	{
		boost::mutex::scoped_lock lock(mu_fnc_bind_);
		m_fnc_bind = m_fnc_bind_;
	}

	std::map<std::string, SDIO_NM_INDEX>::iterator it = m_fnc_bind.find(str_fnc);
	if (it == m_fnc_bind.end() ){
		//no bind pin ignore
		data = 0;
		return true;
	}

	SDIO_NM_INDEX &sdio_nm_index = it->second;

	std::map<std::string, SDIAI>::iterator it2 = m_di_ai.find(sdio_nm_index.str_dev_nm_);
	if (it2 == m_di_ai.end() ){
		return false;
	}

	SDIAI &sdiai = it2->second;
	//check cycle run ok, every thread should have itself
	std::string str_thread_fnc = str_fnc + "_" + cComm::ConvertToString(boost::this_thread::get_id());
	if (sdiai.time_stamp_ != m_stamp_error_[str_thread_fnc].first){
		m_stamp_error_[str_thread_fnc].first = sdiai.time_stamp_;
		m_stamp_error_[str_thread_fnc].second = 0;
	}else{
		m_stamp_error_[str_thread_fnc].second++;
		if (m_stamp_error_[str_thread_fnc].second > 10){
			std::cout<<"get dio dev error,maybe dio dev failed or get so fast!!!"<<sdio_nm_index.str_dev_nm_<<std::endl;
			return false;
		}
	}

	if (sdio_nm_index.i_dio_index_ < MAX_DI ){
		data = sdiai.di_[sdio_nm_index.i_dio_index_];
		return true;
	}
	return false;
}
// search dev name and index from function name
bool dio_manage::get_di( U8 &data,const std::string &str_fnc)
{
	std::map<std::string, SDIAI> m_di_ai;
	
	if(!get_di_ai(m_di_ai)){
		return false;
	}

	return get_di(data,str_fnc, m_di_ai);
}

bool dio_manage::get_sfai(std::map<std::string, SAIF> &m_fai)
{
	boost::mutex::scoped_lock lock(mu_fai_);
	m_fai = m_fai_;

	return true;
}

bool dio_manage::get_fai(F32 &data, const std::string &str_fnc,std::map<std::string, SAIF> &m_fai)
{
	std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
	{
		boost::mutex::scoped_lock lock(mu_fnc_bind_);
		m_fnc_bind = m_fnc_bind_;
	}

	std::map<std::string, SDIO_NM_INDEX>::iterator it = m_fnc_bind.find(str_fnc);
	if (it == m_fnc_bind.end() ){
		return false;
	}

	SDIO_NM_INDEX &sdio_nm_index = it->second;

	std::map<std::string, SAIF>::iterator it2 = m_fai.find(sdio_nm_index.str_dev_nm_);
	if (it2 == m_fai.end() ){
		return false;
	}

	SAIF &sfai = it2->second;
	//check cycle run ok, every thread should have itself
	std::string str_thread_fnc = str_fnc + "_" + cComm::ConvertToString(boost::this_thread::get_id());
	if (sfai.time_stamp_ != m_stamp_error_[str_thread_fnc].first){
		m_stamp_error_[str_thread_fnc].first = sfai.time_stamp_;
		m_stamp_error_[str_thread_fnc].second = 0;
	}else{
		m_stamp_error_[str_thread_fnc].second++;
		if (m_stamp_error_[str_thread_fnc].second > 10){
			std::cout<<"get fai dev error,maybe fai dev failed or get so fast!!!"<<sdio_nm_index.str_dev_nm_<<std::endl;
			return false;
		}
	}

	if (sdio_nm_index.i_dio_index_ < MAX_AI ){
		data = sfai.fai_[sdio_nm_index.i_dio_index_];
		return true;
	}
	return false;
}

bool dio_manage::get_fai(F32 &data, const std::string &str_fnc)
{
	std::map<std::string, SAIF> m_fai;

	if(!get_sfai(m_fai)){
		return false;
	}

	return get_fai(data,str_fnc, m_fai);
}

bool dio_manage::get_sdo_ao(std::map<std::string, SDOAO> &m_do_ao)
{
	boost::mutex::scoped_lock lock(mu_do_ao_);
	m_do_ao = m_do_ao_;

	return true;
}

bool dio_manage::get_do(U8 &data, const std::string &str_fnc, std::map<std::string, SDOAO> &m_do_ao)
{
	std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
	{
		boost::mutex::scoped_lock lock(mu_fnc_bind_);
		m_fnc_bind = m_fnc_bind_;
	}

	std::map<std::string, SDIO_NM_INDEX>::iterator it = m_fnc_bind.find(str_fnc);
	if (it == m_fnc_bind.end() ){
		return false;
	}

	SDIO_NM_INDEX &sdio_nm_index = it->second;

	auto it2 = m_do_ao.find(sdio_nm_index.str_dev_nm_);
	if (it2 == m_do_ao.end() ){
		return false;
	}

	SDOAO &sdo_ao = it2->second;
	//check cycle run ok, every thread should have itself
	std::string str_thread_fnc = str_fnc + "_" + cComm::ConvertToString(boost::this_thread::get_id());
	if (sdo_ao.time_stamp_ != m_stamp_error_[str_thread_fnc].first){
		m_stamp_error_[str_thread_fnc].first = sdo_ao.time_stamp_;
		m_stamp_error_[str_thread_fnc].second = 0;
	}else{
		m_stamp_error_[str_thread_fnc].second++;
		if (m_stamp_error_[str_thread_fnc].second > 10){
			std::cout<<"get fai dev error,maybe fai dev failed or get so fast!!!"<<sdio_nm_index.str_dev_nm_<<std::endl;
			return false;
		}
	}

	if (sdio_nm_index.i_dio_index_ < MAX_DO ){
		data = sdo_ao.do_[sdio_nm_index.i_dio_index_];
		return true;
	}
	return false;
}

bool dio_manage::get_do(U8 &data, const std::string &str_fnc)
{
	std::map<std::string, SDOAO> m_do_ao;

	if(!get_sdo_ao(m_do_ao)){
		return false;
	}

	return get_do(data,str_fnc, m_do_ao);
}


 
 bool dio_manage::get_sfao(std::map<std::string, SAOF> &m_fao)
 {
 	boost::mutex::scoped_lock lock(mu_fao_);
 	m_fao = m_fao_;
 
 	return true;
 }
 
 bool dio_manage::get_fao(F32 &data, const std::string &str_fnc,std::map<std::string, SAOF> &m_fao)
 {
 	std::map<std::string, SDIO_NM_INDEX> m_fnc_bind;
 	{
 		boost::mutex::scoped_lock lock(mu_fnc_bind_);
 		m_fnc_bind = m_fnc_bind_;
 	}
 
 	std::map<std::string, SDIO_NM_INDEX>::iterator it = m_fnc_bind.find(str_fnc);
 	if (it == m_fnc_bind.end() ){
 		return false;
 	}
 
 	SDIO_NM_INDEX &sdio_nm_index = it->second;
 
 	auto it2 = m_fao.find(sdio_nm_index.str_dev_nm_);
 	if (it2 == m_fao.end() ){
 		return false;
 	}
 
 	SAOF &sfao = it2->second;
 	//check cycle run ok, every thread should have itself
 	std::string str_thread_fnc = str_fnc + "_" + cComm::ConvertToString(boost::this_thread::get_id());
 	if (sfao.time_stamp_ != m_stamp_error_[str_thread_fnc].first){
 		m_stamp_error_[str_thread_fnc].first = sfao.time_stamp_;
 		m_stamp_error_[str_thread_fnc].second = 0;
 	}else{
 		m_stamp_error_[str_thread_fnc].second++;
 		if (m_stamp_error_[str_thread_fnc].second > 10){
 			std::cout<<"get fai dev error,maybe fai dev failed or get so fast!!!"<<sdio_nm_index.str_dev_nm_<<std::endl;
 			return false;
 		}
 	}
 
 	if (sdio_nm_index.i_dio_index_ < MAX_AO ){
 		data = sfao.fao_[sdio_nm_index.i_dio_index_];
 		return true;
 	}
 	return false;
 }

 bool dio_manage::get_fao(F32 &data, const std::string &str_fnc)
 {
	 std::map<std::string, SAOF> m_fao;

	 if(!get_sfao(m_fao)){
		 return false;
	 }

	 return get_fao(data,str_fnc, m_fao);
 }

bool dio_manage::call_fnc_sdi(std::string str_dev, const SDI &sdi)
{
	boost::mutex::scoped_lock lock(mu_di_ai_);
	auto it2 = m_di_ai_.find( str_dev );
	if (it2 == m_di_ai_.end() ){
		SDIAI sdiai;
		memset(&sdiai,0,sizeof(SDIAI));
		m_di_ai_[str_dev] = sdiai; 
		it2 = m_di_ai_.find( str_dev );
	}
	SDIAI &sdiai = it2->second;
	sdiai.time_stamp_ = cTimerDiff::total_ms();

	//each setting sfao 
	for ( int i = 0 ; i < sdi.used_; ++i){
		sdiai.di_[sdi.id_[i]] = sdi.di_[i];
	}

	return true;
}


bool dio_manage::call_fnc_sdo(std::string str_dev, const SDO &sdo)
{
	boost::mutex::scoped_lock lock(mu_do_ao_);
	auto it2 = m_do_ao_.find( str_dev );
	if (it2 == m_do_ao_.end() ){
		SDOAO sdoao;
		memset(&sdoao,0,sizeof(SDOAO));
		m_do_ao_[str_dev] = sdoao; 
		it2 = m_do_ao_.find( str_dev );
	}

	SDOAO &sdoao = it2->second;
	sdoao.time_stamp_ = cTimerDiff::total_ms();

	//each setting sfao 
	for ( int i = 0 ; i < sdo.used_; ++i){
		sdoao.do_[sdo.id_[i]] = sdo.do_[i];
	}

	return true;
}

bool dio_manage::call_fnc_fao(std::string str_dev, const SFAO &fao)
{

	//aof container
	boost::mutex::scoped_lock lock(mu_fao_);
	auto it2 = m_fao_.find( str_dev );
	if (it2 == m_fao_.end() ){
		SAOF saof;
		memset(&saof,0,sizeof(SAOF));
		m_fao_[str_dev] = saof; 
		it2 = m_fao_.find( str_dev );
	}

	SAOF &saof = it2->second;
	saof.time_stamp_ = cTimerDiff::total_ms();

	//each setting sfao 
	for ( int i = 0 ; i < fao.used_; ++i){
		saof.fao_[fao.id_[i]] = fao.fao_[i];
	}

	return true;
}

bool dio_manage::call_fnc_fai(std::string str_dev, const SFAI &fai)
{
	//aif container
	boost::mutex::scoped_lock lock(mu_fai_);
	auto it2 = m_fai_.find( str_dev );
	if (it2 == m_fai_.end() ){
		SAIF saif;
		memset(&saif,0,sizeof(SAIF));
		m_fai_[str_dev] = saif; 
		it2 = m_fai_.find( str_dev );
	}
	SAIF &saif = it2->second;
	saif.time_stamp_ = cTimerDiff::total_ms();

	//each setting sfao 
	for ( int i = 0 ; i < fai.used_; ++i){
		saif.fai_[fai.id_[i]] = fai.fai_[i];
	}

	return true;
}





