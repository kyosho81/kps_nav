
#include "meta_data/meta_data.h"

SSMetaData::SSMetaData(){
	str_para_name_ = "";
	str_describe_ = "";
	str_data_ = "";
	str_max_ = "";
	str_min_ = "";
	b_read_only_ = false;
};

SSMetaData::~SSMetaData()
{

}

meta_base::meta_base(){

}
meta_base::~meta_base(){

}

void meta_bool::init( const std::string &para_name, S32 i_data )
{
	group_name_ = "";
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_BOOL;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(i_data) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_bool::init_type()
{
	mt_type_ = META_TYPE::META_BOOL;
}
void meta_int::init( const std::string &para_name, S32 i_data )
{
	group_name_ = "";
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_I;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(i_data) ;
	mt_data.set_max(INT_MAX);
	mt_data.set_min(INT_MIN);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_int::init_type()
{
	mt_type_ = META_TYPE::META_I;
}

void meta_double::init( const std::string &para_name, F64 f_data )
{
	group_name_ = "";
	init_type();	
	m_data_.clear();


	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_F;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(f_data) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_double::init_type()
{
	mt_type_ = META_TYPE::META_F;
}

void meta_enum::init( const std::string &para_name, S32 i_data ,const std::vector<std::string> &str_list)
{
	group_name_ = "";
	init_type();	
	m_data_.clear();


	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_ENUM;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(i_data) ;
	mt_data.set_list(str_list);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_enum::init_type()
{
	mt_type_ = META_TYPE::META_ENUM;
}



void meta_point::init( const std::string &group_name, F64 x , F64 y )
{
	group_name_ = group_name;
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_F;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = "x";
	mt_data.set_data(x) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
	mt_data.str_para_name_ = "y";
	mt_data.set_data(y);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_point::init_type()
{
	mt_type_ = META_TYPE::META_POINT;
}

void meta_pos::init(const std::string &group_name, F64 x , F64 y , F64 th)
{
	group_name_ = group_name;
	init_type();
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_F;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = "x";
	mt_data.set_data(x) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
	mt_data.str_para_name_ = "y";
	mt_data.set_data(y);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
	mt_data.str_para_name_ = "th";
	mt_data.set_data(th);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_pos::init_type()
{
	mt_type_ = META_TYPE::META_POS;
}

void meta_mt_select::init(const std::string &group_name, std::string str_sel ,const std::vector<std::string> &str_list)
{
	group_name_ = group_name;
	init_type();	
	m_data_.clear();

	std::map<std::string,int> m_sel;
	auto it = str_list.begin();
	for ( ; it != str_list.end() ; ++it ){
		m_sel[*it] = 0;
	}

	std::vector<std::string> v_res;
	cComm::SplitString(str_sel,"#",v_res);
	auto it2 = v_res.begin();
	for ( ; it2 != v_res.end() ; ++it2 ){
		auto it3 = m_sel.find(*it2);
		if ( it3 != m_sel.end() ){
			it3->second = 1;
		}
	}
	
	auto it4 = m_sel.begin();
	for ( ; it4 != m_sel.end() ; ++it4 ){
		SSMetaData mt_data;
		mt_data.mt_type_ = META_TYPE::META_BOOL;
		mt_data.str_describe_ = "";
		mt_data.str_para_name_ = it4->first;
		mt_data.set_data(it4->second) ;
		add_meta_data( mt_data.str_para_name_ ,mt_data );
	}
	
	
}

void meta_mt_select::init_type()
{
	mt_type_ = META_TYPE::META_MT_SEL;
}

void meta_color::init(const std::string &para_name, std::string str_color)
{
	group_name_ = "";
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_COLOR;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(str_color) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_color::init_type()
{
	mt_type_ = META_TYPE::META_COLOR;
}

void meta_str::init( const std::string &para_name, std::string str_data)
{
	group_name_ = "";
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_STR;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(str_data) ;
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_str::init_type()
{
	mt_type_ = META_TYPE::META_STR;
}

void meta_comb::init( const std::string &para_name, std::string str_data ,const std::vector<std::string> &str_list )
{
	group_name_ = "";
	init_type();	
	m_data_.clear();

	SSMetaData mt_data;
	mt_data.mt_type_ = META_TYPE::META_COMB;
	mt_data.str_describe_ = "";
	mt_data.str_para_name_ = para_name;
	mt_data.set_data(str_data) ;
	mt_data.set_list(str_list);
	add_meta_data( mt_data.str_para_name_ ,mt_data );
}

void meta_comb::init_type()
{
	mt_type_ = META_TYPE::META_COMB;
}
