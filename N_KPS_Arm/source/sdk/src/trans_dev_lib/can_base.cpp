#include "../Comm/Comm.h"

#include "trans_dev/can_base.h"

can_base::can_base()
{

}

can_base::~can_base()
{
	
}

bool can_base::init( S32 baud_rate )
{
	if ( !close_device() ){
		return false;
	}

	std::string str_rec_can_id = "181;182;183;184;281;282;283;284;381;382;383;384;581;582;583;584;";

	if (!set_rec_can_id(str_rec_can_id)){
		return false;
	}

	baud_rate_ = baud_rate;

	return open_device();
}

bool can_base::check_rec_can_id(U32 i_can_id)
{
	if (m_can_id_.count(i_can_id)){
		return true;
	}
	return false;
}

bool can_base::reset_driver()
{
	std::cout<<"can_base::reset_driver error!"<<std::endl;
	return false;
}

bool can_base::set_rec_can_id(std::string str_can_id)
{
	m_can_id_.clear();

	std::vector<std::string> v_id;
	cComm::SplitString(str_can_id,";",v_id);

	std::vector<std::string>::iterator it = v_id.begin();
	for (; it != v_id.end() ; ++it)
	{
		U32 i_can_id = 0;
		const char *buf= (*it).c_str();

		sscanf(buf, "%x", &i_can_id);

		m_can_id_[i_can_id] = 0;
	}

	if(m_can_id_.empty())
	{
		std::cout<<"CAN receive ID Empty!!!!!"<<std::endl;
		return false;
	}else{
		std::map<U32, int>::iterator it_id = m_can_id_.begin();

		std::cout<<"CAN receive ID:";
		for( ; it_id != m_can_id_.end(); ++it_id)
		{
			std::cout<<" 0x"<<std::hex<<it_id->first;
		}
		std::cout<<std::endl;
		return true;
	}
}
void can_base::set_rec_can_id(std::map<U32,int> m_can_id)
{
	m_can_id_ = m_can_id;
}
int can_base::get_rec_can_id(std::map<U32,int> &m_can_id)
{
	m_can_id = m_can_id_;
	return m_can_id_.size();
}

bool can_base::bind_rec( boost::function<int(const SCanframe &frame )> fnc_call_back )
{
	fnc_call_back_ = fnc_call_back;
	return true;
}

bool can_base::send(U32 can_index, std::vector<SCanframe> &frame_list, U8 send_type)
{
	std::cout<<"can_base::send error!"<<std::endl;
	return false;
}
