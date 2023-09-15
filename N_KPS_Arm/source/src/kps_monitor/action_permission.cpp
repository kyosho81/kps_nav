#include <iostream>


#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"

#include "action_permission.h"

action_permission::action_permission()
{

}

action_permission::~action_permission()
{

}

void action_permission::init()
{
	init_map_menu();
	init_gmapping_menu();
	init_ref_menu();
	init_refbag_menu();
	init_bag_menu();
	init_loc_menu();
	init_pro_menu();
	init_protopo_menu();
	init_protools_menu();
	init_roles_menu();
	init_single_menu();
	init_move_menu();
	init_tools();
}

bool action_permission::set_menu(std::string str_group,std::string str_menu,QAction* p_action)
{
	std::string str_gp_nm = mix_action_nm(str_group,str_menu);
	if ( m_gp_nm_paction_.count( str_gp_nm ) ){
		m_gp_nm_paction_[str_gp_nm] = p_action;
		std::cout<<"Warning! menu action multi define!! :"<<str_gp_nm<<std::endl;
		return false;
	}

	m_gp_nm_paction_[str_gp_nm] = p_action;
	return true;
}

int action_permission::get_menu_available(std::string str_group, std::string str_user,std::list<std::pair<QAction*,int>> &l_avail_permission)
{

	std::pair<std::multimap<std::string, SMenu_item>::iterator,std::multimap<std::string, SMenu_item>::iterator> p_res;
	p_res = mt_per_list_.equal_range(str_group);
	std::multimap<std::string, SMenu_item>::iterator it = p_res.first;
	//for each group menu
	for ( ; it != p_res.second ; ++it ){
		
		SMenu_item &sit = it->second;

		//for each user
		std::map<std::string, SMenu_permission>::iterator it2 =  sit.m_permission_.begin();
		for ( ; it2 != sit.m_permission_.end() ; ++it2 ){
			
			SMenu_permission &sp = it2->second;
			//match user
			if ( sp.str_user_ == str_user ){
				//available 
				if (sp.b_available_){

					QAction* p_action = get_ation(str_group,sit.menu_name_);

					if ( p_action){
						l_avail_permission.push_back(std::make_pair( p_action, sp.i_permission_));
					}else{
						std::cout<<"Warning! menu action can't find!! group:"<<str_group<<" name:"<<sit.menu_name_<<std::endl;
					}
					
				}

				break;
			}
		}
	}
	return l_avail_permission.size();
}

void action_permission::init_map_menu()
{
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_OPEN_MAP, MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_SAVEMAP, MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_UPLOAD_MAP, MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_DOWNLOAD_MAP, MENU_USER_ROOT, false, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_DOWNLOAD_MAP_FILE, MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_SAVE_ONBOARD_MAP, MENU_USER_ROOT, false, 0xffffffff);
	set_permission(MENU_ACT_GP_MAP, MENU_ACT_SET_ONBOARD_MAP, MENU_USER_ROOT, true, 0xffffffff);


	
}
void action_permission::init_gmapping_menu(){

	set_permission(MENU_ACT_GP_GMAPPING, MENU_ACT_GP_LOG_BAGIN,   MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_GMAPPING, MENU_ACT_GP_LOG_END,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_GMAPPING, MENU_ACT_GP_UPLOAD_BAG,  MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_GMAPPING, MENU_ACT_GP_BAG_GMAPPING,MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_GMAPPING, MENU_ACT_GP_BAG_CLEARBG, MENU_USER_ROOT, true, 0xffffffff);
}

void action_permission::init_ref_menu()
{
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_OPEN,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_SAVE,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_UPLOAD,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_DOWNLOAD,  MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_ADD,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_DEL,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REF, MENU_ACT_REFLECTOR_SELECT,    MENU_USER_ROOT, true, 0xffffffff);
}

void action_permission::init_refbag_menu()
{
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_BEGIN,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_STOP,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_MAPPING,   MENU_USER_ROOT, false, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_UPLOAD,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_GMAP,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_MODIFY,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_G2O,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_REFBAG, MENU_ACT_REFBAG_LOGEX_CLEARBG,   MENU_USER_ROOT, true, 0xffffffff);

}

void action_permission::init_bag_menu()
{
	set_permission(MENU_ACT_GP_BAG, MENU_ACT_BAG_UPLOAD,       MENU_USER_ROOT, true, 0xffffffff);	
	set_permission(MENU_ACT_GP_BAG, MENU_ACT_BAG_PLABBACK,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_BAG, MENU_ACT_BAG_PLABBACK_EX,  MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_BAG, MENU_ACT_BAG_DYNAMIC_FRAME,MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_BAG, MENU_ACT_BAG_CLEARBG,      MENU_USER_ROOT, true, 0xffffffff);

}

void action_permission::init_loc_menu()
{
	set_permission(MENU_ACT_GP_LOC, MENU_ACT_SHOW_LASER,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_LOC, MENU_ACT_SHOW_PARTICLES, MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_LOC, MENU_ACT_LOCATE,         MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_LOC, MENU_ACT_AUTO_LOCATE,    MENU_USER_ROOT, false, 0xffffffff);

}

void action_permission::init_pro_menu()
{
	set_permission(MENU_ACT_PRO_FILE, MENU_ACT_PROFILE_OPEN,         MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_FILE, MENU_ACT_PROFILE_SAVE,         MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_FILE, MENU_ACT_PROFILE_UPLOAD,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_FILE, MENU_ACT_PROFILE_DOWNLOAD,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_FILE, MENU_ACT_PROFILE_SET_ONBOARD,  MENU_USER_ROOT, true, 0xffffffff);
}

void action_permission::init_protopo_menu()
{
	set_permission(MENU_ACT_PRO_TOPOL, MENU_ACT_PROTOPO_NODE,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOPOL, MENU_ACT_PROTOPO_EDGE,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOPOL, MENU_ACT_PROTOPO_RAND_EDGE,  MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOPOL, MENU_ACT_PROTOPO_RANGE,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOPOL, MENU_ACT_PROTOPO_RECT,		MENU_USER_ROOT, true, 0xffffffff);

}

void action_permission::init_protools_menu()
{
	set_permission(MENU_ACT_PRO_TOOLS, MENU_ACT_PROTOOLS_SELECT,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOOLS, MENU_ACT_PROTOOLS_ALIGN,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_TOOLS, MENU_ACT_PROTOOLS_DEL,         MENU_USER_ROOT, true, 0xffffffff);
	
}

void action_permission::init_roles_menu()
{
	set_permission(MENU_ACT_PRO_ROLE, MENU_ACT_PROROLE_PRODUCER,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_ROLE, MENU_ACT_PROROLE_CONSUMER,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_ROLE, MENU_ACT_PROROLE_PROCESSER,   MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_ROLE, MENU_ACT_PROROLE_STORAGE,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_ROLE, MENU_ACT_PROROLE_CHARGE,      MENU_USER_ROOT, true, 0xffffffff);

}

void action_permission::init_single_menu()
{
	set_permission(MENU_ACT_PRO_SINGLE, MENU_ACT_PROSINGLE_WANDER,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_PRO_SINGLE, MENU_ACT_PROSINGLE_AUTO_COV,   MENU_USER_ROOT, true, 0xffffffff);

}

void action_permission::init_move_menu()
{
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_CCW,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_CW,       MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_FRONT,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_BACK,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_STOP,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_LEFT,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_RIGHT,    MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_ORI,      MENU_USER_ROOT, false, 0xffffffff);
	set_permission(MENU_ACT_GP_MOVE, MENU_ACT_MV_SHOW,     MENU_USER_ROOT, true, 0xffffffff);
}

void action_permission::init_tools()
{
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_SEARCH_PATH,     MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_ADD_QRCODE,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_EXP_QRCODE,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_IMP_QRCODE,      MENU_USER_ROOT, true, 0xffffffff);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_SHOW_EX_REF,     MENU_USER_ROOT, false, 0xffffffff);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_DYNAMIC_LOC,     MENU_USER_ROOT, false, 0x0);
	set_permission(MENU_ACT_GP_TOOLS, MENU_ACT_TOOLS_SCAN_MATCH,      MENU_USER_ROOT, false, 0x0);
}

std::string action_permission::mix_action_nm(std::string str_group,std::string str_menu)
{
	return str_group + "#" + str_menu;
}

bool action_permission::splite_action_nm(std::string &str_group,std::string &str_menu,std::string str_gp_menu)
{
	std::vector<std::string> v_res;
	cComm::SplitString(str_gp_menu,"#",v_res);
	if ( v_res.size() > 1 ){
		str_group = v_res[0];
		str_menu = v_res[1];
		
		return true;
	}
	return false;
}

QAction* action_permission::get_ation(std::string str_group,std::string str_menu)
{
	std::string str_gp_nm = mix_action_nm(str_group,str_menu);

	std::map<std::string, QAction *>::iterator it = m_gp_nm_paction_.find(str_gp_nm);
	if ( it != m_gp_nm_paction_.end() ){ 
		return it->second;
	}
	return 0;
}

bool action_permission::set_permission(std::string str_group,std::string str_menu,std::string str_user, bool b_available , int i_permission)
{
	bool b_res = true;

	//std::string str_gp_nm = mix_action_nm(str_group,str_menu);

	SMenu_item sit;
	sit.menu_group_ = str_group;
	sit.menu_name_ = str_menu;

	if (sit.m_permission_.count(str_user)){
		std::cout<<"Warning! menu user multi define!! :"<<str_user<<std::endl;
		b_res = false;
	}

	SMenu_permission &sp = sit.m_permission_[str_user];
	sp.str_user_ = str_user;
	sp.b_available_ = b_available;
	sp.i_permission_ = i_permission;

	
	mt_per_list_.insert(std::make_pair(str_group,sit));

	return true;
	
}
