#ifndef _KEYGEN_KYOSHO_20230303_H
#define _KEYGEN_KYOSHO_20230303_H

#include <string>
#include <vector>

#include "Comm/tollage.h"

#define KEYERR_N 0
#define KEYERR_B -1
#define KEYERR_S -2
#define KEYERR_T -3
#define KEYERR_M -4
#define KEYERR_D -5

#define KG_AMCL           "amcl"
#define KG_REFLECTOR      "reflector"
#define KG_MV_FIX         "move_fix"
#define KG_MV_DY          "move_dy"
#define KG_LOOPCLOSURE    "loopclosure"
#define KG_DY_LOC         "dynamic_loc"
#define KG_CHASSIS_2WD    "chassis_2wd"
#define KG_CHASSIS_FORK   "chassis_fork"
#define KG_CHASSIS_OMI    "chassis_omi"
#define KG_CHASSIS_MUT    "chassis_mut"

class keygen
{
public:
	keygen();
	~keygen();

	
	std::string init_token();
	
	int check_token(std::string str_enc);
	bool check_fuc(std::string str_fnc);
	bool set_err();

protected:
private:

	

	tollage tg_;
	
	std::string str_begin_time_;
	S64 cur_time_;
	std::string str_reg_fuc_;
	std::string str_token_;

private:
	std::string get_fuc();
	
	bool set_act(std::string str_reg_fuc);
	bool check_time();

	boost::mutex mu_fnc_;
    bool b_amcl_;
    bool b_reflector_;
    bool b_move_fix_;
    bool b_move_dy_;
    bool b_dynamic_loc_;
    bool b_chassis_2wd_;
    bool b_chassis_fork_;
    bool b_chassis_omi_;
    bool b_chassis_mut_;

	std::map<std::string,std::string> m_key_val_;
	void export_sn(std::map<std::string,std::string> &m_key_val);
};



#endif //_KEYGEN_KYOSHO_20230303_H

