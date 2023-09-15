#ifndef _KPS_ACTION_PERMISSION_H_
#define _KPS_ACTION_PERMISSION_H_


#ifndef Q_MOC_RUN 
#include "robot/RobotStruct.h"
#include "action_menu_def.h"
#endif

///////////////////////////////////
// group   menu      user  available    permission
// gmap    openmap   root  true         0xff
// gmap    savemap   root  true         0xff
// ref     refmap    root  true         0xff
// ref     refmap    usr   true         0

typedef struct _SMenu_item
{
	// group   menu
	std::string menu_group_;
	std::string menu_name_;

	//user  available    permission
	std::map<std::string,SMenu_permission> m_permission_;

}SMenu_item;

class QAction;

class action_permission
{
public:
	action_permission();
	~action_permission();

	void init();

	bool set_menu( std::string str_group,std::string str_menu,QAction* p_action);
	int get_menu_available(std::string str_group, std::string str_user, std::list<std::pair<QAction*,int>> &l_avail_permission );

protected:
private:

	void init_map_menu();
	void init_gmapping_menu();
	void init_ref_menu();
	void init_refbag_menu();
	void init_bag_menu();
	void init_loc_menu();
	void init_pro_menu();
	void init_protopo_menu();
	void init_protools_menu();
	void init_roles_menu();
	void init_single_menu();
	void init_move_menu();
	void init_tools();

private:
	std::string mix_action_nm(std::string str_group,std::string str_menu);
	bool splite_action_nm(std::string &str_group,std::string &str_menu,std::string str_gp_menu);
	QAction* get_ation(std::string str_group,std::string str_menu);
	
	//group name , point to action
	std::map<std::string,QAction*> m_gp_nm_paction_;

private:

	bool set_permission(std::string str_group,std::string str_menu,std::string str_user, bool b_available , int i_permission);
	//menu group_name , < user , availabel ,permission> 
	std::multimap<std::string, SMenu_item> mt_per_list_;


};

#endif // _KPS_ACTION_PERMISSION_H_
