#include <boost/thread.hpp>
#include <ctime>

#include "Comm.h"
#include "interface/rpc_config_client.h"
#include "schedule.h"

pschedule::pschedule()
{

}


pschedule::~pschedule()
{

}

void pschedule::init(rpc_config_client* cfg_rpc)
{
	//boost::gregorian::date d3 = boost::gregorian::from_string("2021-5-25");
	//boost::posix_time::ptime p2 = boost::posix_time::time_from_string("2021-5-25 02:00:00");
//	boost::posix_time::ptime p2 = boost::posix_time::from_iso_string("20210525T020000");
// 	boost::gregorian::date d3 = p2.date();
// 	std::stringstream ss;
// 	ss<<boost::posix_time::to_iso_string(p2);
// 	std::cout<<ss.str()<<std::endl;
//	boost::posix_time::from_iso_string("20210525T090000");
//	SDT sdt;
//	memset(&sdt,0,sizeof(SDT));
// 	sdt.pt_from_ = boost::posix_time::from_iso_string("20210525T090000");
// 	sdt.pt_to_ = boost::posix_time::from_iso_string("20210525T170000");
// 	sdt.str_time_from_ = "090000";
// 	sdt.str_time_to_ = "180000";
// 	set_week_bit(sdt.i_week_ ,eWEEK::WEEK_MON);
// 	set_week_bit(sdt.i_week_ ,eWEEK::WEEK_TUE);
// 	set_week_bit(sdt.i_week_ ,eWEEK::WEEK_WEN);
// 	set_week_bit(sdt.i_week_ ,eWEEK::WEEK_THU);
// 	set_week_bit(sdt.i_week_ ,eWEEK::WEEK_FIR);
// 
// 	insert_schedule(eTASK::SCHE_PARK,sdt);

 	std::string str;
	cfg_rpc->get_configs(str,"wander_schedule");
	decode(str);
	cfg_rpc->get_configs(str,"charge_schedule1");
	decode(str);
	cfg_rpc->get_configs(str,"charge_schedule2");
	decode(str);
}

bool pschedule::check_schedule(eTASK task_type)
{
	boost::gregorian::date d1 = boost::gregorian::day_clock::local_day();
	int i_week = d1.day_of_week();

	boost::posix_time::ptime pt(boost::posix_time::second_clock::local_time());


	std::multimap<eTASK,SDT>::iterator it = mt_sdt_.begin();
	for ( ; it != mt_sdt_.end() ; ++it ){

		if (it->first == task_type){

			if(check_on_duty(i_week,pt,it->second)){
				return true;
			}	
		}
	}
	
	return false;

	
}

void pschedule::set_week_bit(int &i_week, eWEEK week)
{
	i_week |= 1<<week;
}

void pschedule::cls_week_bit(int &i_week, eWEEK week)
{
	i_week &= ~(1<<week);
}

bool pschedule::chk_week_bit(int i_week, eWEEK week)
{
	if( i_week & (1<<week) ){
		return true;
	}
	return false;

}

bool pschedule::check_on_duty(int i_week, boost::posix_time::ptime pt, const SDT &sdt)
{
	if ( chk_week_bit(sdt.i_week_, eWEEK(i_week) )){

		std::stringstream ss;
	
		std::string str_now = boost::posix_time::to_iso_string(pt);
		int newPos = -1;
		if( (newPos = str_now.find ("T", 0)) != std::string::npos ){
			str_now = str_now.substr( 0 , newPos ); 
		}
		ss<<str_now<<"T"<<sdt.str_time_from_;
		std::cout<<"time_from:"<<ss.str();
		boost::posix_time::ptime pt_from = boost::posix_time::from_iso_string(ss.str());
		ss.str("");
		ss<<str_now<<"T"<<sdt.str_time_to_;
		std::cout<<"time_to:"<<ss.str();
		boost::posix_time::ptime pt_to = boost::posix_time::from_iso_string(ss.str());
		boost::posix_time::time_period ts(pt_from,pt_to);
		if ( ts.contains(pt) ){
			return true;
		}
	}
	return false;
}


bool pschedule::insert_schedule(eTASK task_type , SDT sdt)
{
	mt_sdt_.insert(std::make_pair(task_type,sdt));
	return true;
}
bool pschedule::decode(std::string str){
	SDT sdt;
	memset(&sdt,0,sizeof(SDT));

	std::vector<std::string> vres;
	cComm::SplitString(str,";",vres);

	if (vres.size() < 3){
		return false;
	}
	//week
	std::vector<std::string> vres2;
	cComm::SplitString(vres[0],",",vres2);
	if (vres2.size() < 7){
		return false;
	}
	
	if (vres2[0] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_MON);
	}
	if (vres2[1] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_TUE);
	}
	if (vres2[2] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_WEN);
	}
	if (vres2[3] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_THU);
	}
	if (vres2[4] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_FIR);
	}
	if (vres2[5] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_STA);
	}
	if (vres2[6] == "1"){
		set_week_bit(sdt.i_week_ ,eWEEK::WEEK_SUN);
	}

	cComm::SplitString(vres[1],",",vres2);
	if (vres2.size() < 2){
		return false;
	}
	sdt.str_time_from_ = vres2[0];
	sdt.str_time_to_ = vres2[1];

	int task_type = SCHE_NONE;
	cComm::ConvertToNum(task_type,vres[2]);
	insert_schedule(eTASK(task_type),sdt);

}

