#ifndef _TOLLAGE_KYOSHO_20110903_
#define _TOLLAGE_KYOSHO_20110903_


class tollage{

public:
	tollage();
	~tollage();

	bool check(std::string str_md5, bool b_show = false );
	std::string get_sn();
	std::string mix(int hostid, std::string str_mac);
	std::string md5(std::string str_key);

	void set_fun_location();
	void set_fun_fix_path();
	void set_fun_dynamic_path();
	void set_fun_dynamic_loc();
	void set_fun_chassis_mut();

	std::string get_noods();
	std::string get_key();

	std::string get_mac();
	
	std::string str_sn_;
private:

	std::string str_mac_;
	
	void string2char(std::string theString,char re[]);
	int32_t linuxshell(const char *cmd, std::vector<std::string> &resvec);

	std::string str_noods;
	
	//new key describe
private:
	std::string native_uuid();
};

#endif//_TOLLAGE_KYOSHO_20110903_
