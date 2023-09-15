
#include "meta_data/group_data.h"


group_data::group_data()
{
	v_group_.push_back("GP_A");
	v_group_.push_back("GP_B");
	v_group_.push_back("GP_C");
	v_group_.push_back("GP_D");
	v_group_.push_back("GP_E");
	v_group_.push_back("GP_F");
	v_group_.push_back("GP_G");
	v_group_.push_back("GP_H");
	v_group_.push_back("GP_I");

	str_delimiter_ = "#";
}
//get select group map 
//out put: map string group name , map int selected
//int put: str_sel_group like "GP_A#GP_C"
//         v_group all group name in it
int group_data::get_group_map(std::map<std::string,int> &m_group,std::string str_sel_group,std::vector<std::string> v_group)
{
	auto it = v_group.begin();
	for ( ; it != v_group.end() ; ++it ){
		m_group[*it] = 0 ;
	}
	std::vector<std::string> v_res;
	cComm::SplitString(str_sel_group,str_delimiter_,v_res);

	auto it2 = v_res.begin();
	for ( ; it2 != v_res.end() ; ++it2){
		auto it3 = m_group.find(*it2);
		if ( it3 != m_group.end()){
			it3->second = 1;
		}
	}
	return m_group.size();
}

bool group_data::check_group_name(std::string str_group)
{
	str_group = cComm::trim(str_group);
	auto it = v_group_.begin();
	for ( ; it != v_group_.end() ; ++it ){
		if( str_group == *it ){
			return true;
		}
	}
	return false;
}
