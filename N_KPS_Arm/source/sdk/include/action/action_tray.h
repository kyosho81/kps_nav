#ifndef _ACTION_TRAY_KYOSHO_20220711_
#define _ACTION_TRAY_KYOSHO_20220711_


#include <string>
#include <map>
#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

class device_base;

class action_tray
{
public:
	action_tray();
	~action_tray();

	void init( bool b_sim = false );
	
	bool create_fork_action();
	bool create_lift_action();
	bool create_ref_forbidden_action();
	bool create_charge();

	void pub_sta();

protected:
	bool insert_device(device_base* p_device);

	

private:
	bool b_sim_;
	bool s_run_path( std::string name,U8* data,U32 len );
	bool s_mv_status( const SRunStatus &sta );
	bool s_heart_beat(const SHeartBeat &hb);

private:
	//int i_action_id_;
	std::map<int,device_base*> m_device_exaction_base_;
};

typedef boost::serialization::singleton<action_tray> Singleton_Action_Tray;
#define ACTION_TRAY Singleton_Action_Tray::get_mutable_instance()

#endif //_ACTION_TRAY_KYOSHO_20220711_