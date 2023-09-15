#include <assert.h>

#include "Comm/configs.h"

config_it::config_it( const config_it &c_it )
{
	str_name_ = c_it.str_name_;
	type_ = c_it.type_;
	str_data_ = c_it.str_data_;
	str_seg_ = c_it.str_seg_;
	str_des_ = c_it.str_des_;

	memcpy(ch_max_,c_it.ch_max_,20);
	memcpy(ch_min_,c_it.ch_min_,20);
	memcpy(ch_data_,c_it.ch_data_,20);

}

bool config_it::decode( std::string str )
{
	std::vector<std::string> v_res;
	std::string str_value;
	cComm::SplitString(str," ",v_res);

	std::map<std::string,std::string> m_name_value;

	std::vector<std::string>::iterator it = v_res.begin();
	for ( ; it != v_res.end() ; ++it){
		if( split_name_value(str_name_, str_value, *it )){
			m_name_value[str_name_] = str_value;
		}
	}
	std::map<std::string,std::string>::iterator it2 = m_name_value.find("name");
	if (it2 == m_name_value.end() )
	{
		return false;
	}else{
		str_name_ = it2->second;
	}
	

	it2 = m_name_value.find("type");
	std::string str_seg = m_name_value["seg"];

	if (it2 == m_name_value.end() )
	{
		return false;
	}
	if ( it2->second == "string" )
	{
		set_value(str_value);
		//set_sconfig(m_name_value["name"],str_value);
	}else if(it2->second == "int"){
		int data = 0 ;
		int max = 0 ;
		int min = 0 ;

		if (m_name_value.size() != 9 )
		{
			cComm::ConvertToNum(data,m_name_value["data"]);
			cComm::ConvertToNum(max,m_name_value["dmax"]);
			cComm::ConvertToNum(min,m_name_value["dmin"]);
		}else{
			U8 ch_tmp[10] = {0};
			memset(ch_tmp,0,10);
			int ilen = 10;
			cComm::replace_str(m_name_value["dhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
			assert( sizeof(int ) == ilen);
			memcpy(&data,ch_tmp,ilen);


			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["mhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
			assert( sizeof(int ) == ilen);
			memcpy(&min,ch_tmp,ilen);

			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["xhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
			assert( sizeof(int ) == ilen);
			memcpy(&max,ch_tmp,ilen);
			
		}
		set_min(min);
		set_max(max);

		set_value(data);

	}else if(it2->second == "float"){
		float data = 0 ;
		float max = 0 ;
		float min = 0 ;

		if (m_name_value.size() != 9 )
		{
			cComm::ConvertToNum(data,m_name_value["data"]);
			cComm::ConvertToNum(max,m_name_value["dmax"]);
			cComm::ConvertToNum(min,m_name_value["dmin"]);
		}else{
			U8 ch_tmp[10] = {0};
			memset(ch_tmp,0,10);
			int ilen = 10;
			cComm::replace_str(m_name_value["dhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
			assert( sizeof(float ) == ilen);
			memcpy(&data,ch_tmp,ilen);


			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["mhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
			assert( sizeof(float ) == ilen);
			memcpy(&min,ch_tmp,ilen);

			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["xhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
			assert( sizeof(float ) == ilen);
			memcpy(&max,ch_tmp,ilen);

		}
		set_min(min);
		set_max(max);

		set_value(data);
	}else if(it2->second == "double"){
		double data = 0 ;
		double max = 0 ;
		double min = 0 ;

		if (m_name_value.size() != 9 )
		{
			cComm::ConvertToNum(data,m_name_value["data"]);
			cComm::ConvertToNum(max,m_name_value["dmax"]);
			cComm::ConvertToNum(min,m_name_value["dmin"]);
		}else{
			U8 ch_tmp[10] = {0};
			memset(ch_tmp,0,10);
			int ilen = 10;
			cComm::replace_str(m_name_value["dhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
			assert( sizeof(double ) == ilen);
			memcpy(&data,ch_tmp,ilen);


			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["mhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
			assert( sizeof(double ) == ilen);
			memcpy(&min,ch_tmp,ilen);

			ilen = 10;
			memset(ch_tmp,0,10);
			cComm::replace_str(m_name_value["xhex"],"-"," ");
			cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
			assert( sizeof(double ) == ilen);
			memcpy(&max,ch_tmp,ilen);

		}
		set_min(min);
		set_max(max);

		set_value(data);
	}
	set_seg(str_seg);
	return true;
}

std::string config_it::code()
{
	std::stringstream ss;
	ss<<"name"<<SEPARATE_NAME_VALUE<< get_al_name()<<" "<<*this;
	return ss.str();
}

configs::configs(){

}

configs::~configs(){

	std::list<config_it*>::iterator it = l_all_paras_.begin();
	for ( ; it != l_all_paras_.end() ; ++it){
		SDelete(*it);
	}
	m_all_paras_.clear();
	l_all_paras_.clear();
}
bool configs::load(const std::string &str_file, const bool &b_merge){
	if (!b_merge)
	{
		std::list<config_it*>::iterator it = l_all_paras_.begin();
		for ( ; it != l_all_paras_.end() ; ++it){
			SDelete(*it);
		}
		m_all_paras_.clear();
		l_all_paras_.clear();
	}

	std::ifstream iff;
	iff.open(str_file.c_str(),std::ios::in | std::ios::binary);

	if (!iff.is_open())
	{
		return false;
	}
	std::string str;
	std::vector<std::string> v_res;
	std::string str_name;
	std::string str_value;
	std::map<std::string,std::string> m_name_value;
	while( std::getline(iff,str) ){

		cComm::SplitString(str," ",v_res);
		m_name_value.clear();
		std::vector<std::string>::iterator it = v_res.begin();
		for ( ; it != v_res.end() ; ++it){
			if( config_it::split_name_value(str_name, str_value, *it )){
				m_name_value[str_name] = str_value;
			}
		}

		std::map<std::string,std::string>::iterator it2 = m_name_value.find("type");
		std::string str_seg = m_name_value["seg"];
		

		if (it2 == m_name_value.end() )
		{
			std::cout<<"type err"<<std::endl;
			return false;
		}

		std::cout<<m_name_value["name"]<<" :"<<m_name_value["data"]<<std::endl;

		if ( it2->second == "string" )
		{
			set_sconfig(m_name_value["name"],str_value);
			
		}else if(it2->second == "int"){
			int data = 0 ;
			int max = 0 ;
			int min = 0 ;

			if (m_name_value.size() != 9 )
			{
				std::cout<<"new insert value!"<<std::endl;
				cComm::ConvertToNum(data,m_name_value["data"]);
				cComm::ConvertToNum(max,m_name_value["dmax"]);
				cComm::ConvertToNum(min,m_name_value["dmin"]);
			}else{
				U8 ch_tmp[10] = {0};
				memset(ch_tmp,0,10);
				int ilen = 10;
				cComm::replace_str(m_name_value["dhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
				assert( sizeof(int ) == ilen);
				memcpy(&data,ch_tmp,ilen);
				

				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["mhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
				assert( sizeof(int ) == ilen);
				memcpy(&min,ch_tmp,ilen);

				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["xhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
				assert( sizeof(int ) == ilen);
				memcpy(&max,ch_tmp,ilen);


			}
			

			init_config(m_name_value["name"],data,min,max);
		}else if(it2->second == "float"){
			float data = 0 ;
			float max = 0 ;
			float min = 0 ;

			if (m_name_value.size() != 9 )
			{
				std::cout<<"new insert value!"<<std::endl;
				cComm::ConvertToNum(data,m_name_value["data"]);
				cComm::ConvertToNum(max,m_name_value["dmax"]);
				cComm::ConvertToNum(min,m_name_value["dmin"]);
			}else{
				U8 ch_tmp[10] = {0};
				memset(ch_tmp,0,10);
				int ilen = 10;
				cComm::replace_str(m_name_value["dhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
				assert( sizeof(float ) == ilen);
				memcpy(&data,ch_tmp,ilen);

				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["mhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
				assert( sizeof(float ) == ilen);
				memcpy(&min,ch_tmp,ilen);

				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["xhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
				assert( sizeof(float ) == ilen);
				memcpy(&max,ch_tmp,ilen);

			}
			init_config(m_name_value["name"],data,min,max);

		}else if(it2->second == "double"){
			double data = 0 ;
			double max = 0 ;
			double min = 0 ;

			if (m_name_value.size() != 9 )
			{
				std::cout<<"new insert value!"<<std::endl;
				cComm::ConvertToNum(data,m_name_value["data"]);
				cComm::ConvertToNum(max,m_name_value["dmax"]);
				cComm::ConvertToNum(min,m_name_value["dmin"]);
			}else{
				U8 ch_tmp[10] = {0};
				memset(ch_tmp,0,10);
				int ilen = 10;
				cComm::replace_str(m_name_value["dhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["dhex"]);
				assert( sizeof(double ) == ilen);
				memcpy(&data,ch_tmp,ilen);


				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["mhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["mhex"]);
				assert( sizeof(double ) == ilen);
				memcpy(&min,ch_tmp,ilen);

				ilen = 10;
				memset(ch_tmp,0,10);
				cComm::replace_str(m_name_value["xhex"],"-"," ");
				cComm::HexStringToByte(ch_tmp,ilen,m_name_value["xhex"]);
				assert( sizeof(double ) == ilen);
				memcpy(&max,ch_tmp,ilen);

			}
			init_config(m_name_value["name"],data,min,max);
		}else{
			std::cout<<"load decode err!"<<str<<" type:"<<it2->second<<std::endl;
			assert(false);
		}
		set_seg(m_name_value["name"],str_seg);
	}
	iff.close();
	return true;
}
bool configs::save(const std::string &str_file){
	std::ofstream off;
	off.open(str_file.c_str(),std::ios::out | std::ios::trunc | std::ios::binary);

	if (!off.is_open())
	{
		return false;
	}
	std::list<config_it*>::iterator it = l_all_paras_.begin();
	for ( ; it != l_all_paras_.end() ; ++it){

		config_it* t = *it;
		
		off<<"name"<<SEPARATE_NAME_VALUE<< t->get_al_name()<<" "<<*t;
	}
	off.flush();
	off.close();

	return true;

}

std::multimap<std::string,config_it*>::iterator configs::get_seg_para_it( const std::string &str_name)
{
	std::multimap<std::string,config_it*>::iterator it = mt_seg_paras_.begin();
	for (  ; it != mt_seg_paras_.end() ; ++it){
		if ( it->second->get_name() == str_name )
		{
			return it;
		}
	}
	return mt_seg_paras_.end();
}

bool configs::set_seg(const std::string &str_para_name, const std::string &str_seg)
{
	//step 1 set config_it segment
	//and check old segment is same as current segment
	config_it* p = 0;
	boost::unordered_map<std::string, config_it* >::iterator it = m_all_paras_.find(str_para_name);
	if ( it != m_all_paras_.end()){
		p = ( it->second );
		if (p->get_seg() == str_seg)
		{
			return true;
		}else{
			p->set_seg(str_seg);
		}

	}else{
		return false;
	}
	//reflash segment para multimap
	//if b_same_seg == false means toto:
	//1 earse old seg
	//2 insert into new seg
	std::multimap<std::string,config_it*>::iterator it2 = get_seg_para_it(str_para_name);
	
	if ( it2 != mt_seg_paras_.end())
	{
		//always erase it and insert new one
		p = it2->second;
		mt_seg_paras_.erase(it2);
	}

	mt_seg_paras_.insert(std::make_pair(str_seg,p));

	return true;
}

bool configs::init_config( const std::string str_decode )
{
	config_it c_it("remote");
	c_it.decode(str_decode);
	return init_config(c_it);
}

bool configs::init_config( config_it &c_it )
{
	std::string str = c_it.get_name();
	boost::unordered_map<std::string, config_it*>::iterator it = m_all_paras_.find(str);
	if ( it != m_all_paras_.end()){
		config_it* ct = ( it->second );
		return false;
	}
	config_it* c = new config_it(c_it);

	m_all_paras_[str] = c;
	l_all_paras_.push_back(c);
	return true;
}

bool configs::set_whole_config(const std::string &str_para_name,const std::string str_decode)
{
	boost::unordered_map<std::string, config_it* >::iterator it = m_all_paras_.find(str_para_name);
	if ( it != m_all_paras_.end()){
		config_it* ct = ( it->second );
		ct->decode(str_decode);
		return true;
	}
	return false;
}


