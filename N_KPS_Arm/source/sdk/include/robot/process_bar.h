#ifndef _PROCESSBAR_KYOSHO_20180906_
#define _PROCESSBAR_KYOSHO_20180906_

#include <map>
#include <string>


#include "RobotStruct.h"

class process_bar
{
public:
	process_bar();
	~process_bar();
	
	void set_name(std::string str_nm);
	void set_max(const U32 &imax);
	void set_current(const U32 &icurrent);

	SProcess_Bar get_bar();

protected:
private:

	SProcess_Bar process_bar_;
};

#endif//_PROCESSBAR_KYOSHO_20180906_
