
#include "popen.h"

#include "iostream"

#ifdef _WINDOWS
#include <WinSock2.h> 
#include "Iphlpapi.h" 
#pragma comment(lib,"Iphlpapi.lib")
#endif

#include "Comm/Comm.h"
#include "Comm/bmd5.hpp"

#include "Comm/tollage.h"

#define AMCL_NOODS         "20190311"
#define FIX_PATH_NOODS     "20210701"
#define DYNAMIC_PATH_NOODS "20200501"
#define DYNAMIC_LOC_NOODS  "20230308"
#define CHASSIS_MUT_NOODS  "20230309"

tollage::tollage(){

	str_noods = "";
	str_mac_ = "";

}
tollage::~tollage(){

}

std::string tollage::get_mac(){

	if( str_mac_.length() > 0 ){
		return str_mac_;	
	}

	std::string str_rec ;
#ifndef _WINDOWS
	if(str_rec.length() < 12){
		//system::cmd("ifconfig enp88s0 | grep ''ether'' | awk '{print $2}'",str_rec);
		system::cmd("ifconfig",str_rec);
	}
	std::vector<std::string> v_res;
	cComm::SplitString(str_rec,"\n",v_res);
	auto it = v_res.begin();	
	for( ; it != v_res.end() ;  ){

		std::vector<std::string> vr;
		cComm::SplitString(*it,":",vr);
		if((vr.size() == 2) && (cComm::PatternCount(*it,"::") == 0 )){
			
			*it = cComm::trim_n(vr[0]);
			//std::cout<<*it<<std::endl;
			++it;
		}else{
			it = v_res.erase(it);
		}	
	}
	std::stringstream ss_res;
	it = v_res.begin();	
	for( ; it != v_res.end() ; ++it ){
		str_rec = "";
		std::stringstream ss;
		ss<<"ifconfig "<<*it<<" | grep ''ether'' | awk '{print $2}'";
		//std::cout<<"cmd:"<<ss.str()<<std::endl;
		system::cmd(ss.str(),str_rec);	
		
		str_rec = cComm::trim_n(str_rec);
		//std::cout<<str_rec<<std::endl;
		if(str_rec.length() > 0){
			ss_res << str_rec + ";";
			//std::cout<<str_mac_<<std::endl;
		}
		
	}

	str_mac_ = ss_res.str();
#else
	U8 mac[8]={0};

	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO(); 
	unsigned long stSize = sizeof(IP_ADAPTER_INFO); 
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize); 
	if (ERROR_BUFFER_OVERFLOW == nRel) 
	{ 
		delete pIpAdapterInfo; 
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize]; 
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);     
	} 
	if (ERROR_SUCCESS == nRel) 
	{ 
		while (pIpAdapterInfo) 
		{ 
			memcpy(mac,pIpAdapterInfo->Address,8);
			break;//获取到第一个网卡的MAC 
		} 
	} 
	if (pIpAdapterInfo)delete pIpAdapterInfo; 

	str_mac_ = cComm::ByteToHexString(mac,8);

#endif
	

	CMD5 md5;
	str_mac_ = md5.MD5String( str_mac_.c_str() );

	return str_mac_;
}
std::string tollage::get_key(){
	
	std::string str_rec = "" ;

	#ifndef _WINDOWS
	int result=888;
	if(-1==(result=gethostid()))
	{
		std::cout<<"gethostid err"<<std::endl;;
		return str_rec;
	}
	//printf("hosid is :%d\n",result);
	

	//std::::system("ifconfig eth0 | grep "HWaddr" | awk '{print $5}'");
	
	//system::cmd("ifconfig eth0 | grep ''HWaddr'' | awk '{print $5}'",str_rec);
	//if(str_rec.length() < 12){
	//	system::cmd("ifconfig eth0 | grep ''ether'' | awk '{print $2}'",str_rec);
	//}
	//if(str_rec.length() < 12){
	//	system::cmd("ifconfig enp88s0 | grep ''ether'' | awk '{print $2}'",str_rec);
	//}
	
	str_rec = get_mac();


	str_rec = mix(result,str_rec);
	//str_rec += native_uuid();
	str_rec = md5(str_rec);
	#else
	
	str_rec = get_mac();

	#endif
	return str_rec;
}
std::string tollage::get_sn(){

	str_sn_ = get_key();

	//std::cout<<"!!!!!!!!!!!!!!!!!serial number!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
	//std::cout<<str_sn_<<std::endl;
	//std::cout<<"!!!!!!!!!!!!!!!!!serial number!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
	return str_sn_;
}
std::string tollage::mix(int hostid, std::string str_mac){
	std::stringstream ss;

	std::vector<std::string> vres;
	cComm::SplitString(str_mac,":",vres);
	std::vector<std::string>::iterator it = vres.begin();
	for( ; it != vres.end() ; ++it){
		ss<<*it;
	}
	str_mac = ss.str();

	ss.str("");
	ss<<hostid;

	std::string strA = "";
	std::string strB = "";
	if(ss.str().length() > str_mac.length()){
		strA = ss.str();
		strB = str_mac;
	}else{
		strA = str_mac;
		strB = ss.str();
	}
	//std::cout<<"strA:"<<strA<<" len:"<<strA.length()<<std::endl;
	//std::cout<<"strB:"<<strB<<" len:"<<strB.length()<<std::endl;

	ss.str("");
	for(int i = 0 ; i < strA.length() ; ++i){

		ss<<strA.substr( i, 1);
		//std::cout<<"sub index:"<<i<<" "<<ss.str()<<std::endl;
		if( i < strB.length()){

			ss<<strB.substr( i, 1);
			//std::cout<<"sub2 index:"<<i<<" "<<ss.str()<<std::endl;
		}

	}

	return ss.str();
}
void tollage::string2char(std::string theString,char re[])
{
	strcpy(re,theString.c_str());
}
int32_t tollage::linuxshell(const char *cmd, std::vector<std::string> &resvec) {
	resvec.clear();
#ifndef _WINDOWS
	FILE *pp = popen(cmd, "r");
	if (!pp) {
		return -1;
	}
	char tmp[1024];
	while (fgets(tmp, sizeof(tmp), pp) != NULL) {
		if (tmp[strlen(tmp) - 1] == '\n') {
			tmp[strlen(tmp) - 1] = '\0';
		}
		resvec.push_back(tmp);
	}
	pclose(pp);
#endif
	return resvec.size();
}
std::string tollage::md5(std::string str_key){


	std::string str_res;
#ifdef _WINDOWS
	CMD5 md5;
	str_res = md5.MD5String( str_key.c_str() );
	//std::cout<<"md5:"<<str_res<<std::endl;

#else
	std::vector<std::string> res;
	std::string com01 = "echo -n '";
	std::string com02 = str_key;
	std::string com03 = "'|md5sum|cut -d ' ' -f1";
	std::string resCom = com01 + com02 +com03;
	//cout<<resCom<<endl;


	char shellcommand[2000];
	string2char(resCom,shellcommand);
	//std::cout<<shellcommand<<std::endl;

	int count = linuxshell(shellcommand,res);
	if(res.size() > 0){
		str_res = res[0];
	}
	//std::cout<<"md5 str_res:"<<str_res<<std::endl;
#endif
	return str_res;
}
bool tollage::check(std::string str_md5 ,bool b_show ){

	str_md5 = cComm::trim(str_md5);
	str_md5 = cComm::trim_n(str_md5);
	str_md5 = cComm::trim_cr(str_md5);

//	std::cout<<"tollage::check!!!!!!"<<str_md5<<std::endl;

	//get_key without noods
	std::string str_res = get_key();

	str_res = md5( str_res + get_noods());

	if(b_show){
		std::cout<<"hack sn:"<<str_res<<std::endl;
	}else{
		get_sn();
	}

	if( str_res == str_md5 ){
		return true;
	}else{
		return false;
	}
}
void tollage::set_fun_location(){
	str_noods += AMCL_NOODS;
}

void tollage::set_fun_fix_path()
{
	str_noods += FIX_PATH_NOODS;
}

void tollage::set_fun_dynamic_path(){
	str_noods += DYNAMIC_PATH_NOODS  ;
}

void tollage::set_fun_dynamic_loc()
{
	str_noods += DYNAMIC_LOC_NOODS  ;
}


void tollage::set_fun_chassis_mut()
{
	str_noods += CHASSIS_MUT_NOODS  ;
}

std::string tollage::get_noods(){
	return str_noods;
}

std::string tollage::native_uuid()
{
#ifdef _WINDOWS
#else
	std::string str_rec;
	system::cmd("sudo ls /dev/disk/by-uuid",str_rec);
	str_rec = cComm::trim(str_rec);
	str_rec = cComm::trim_n(str_rec);
	std::vector<std::string> v_res;
	cComm::SplitString(str_rec,"\n",v_res);
	if(v_res.size() > 1 ){
		std::cout<<"uuid"<<v_res[1]<<std::endl;
		return v_res[1];
	}
#endif
	return "";
}

