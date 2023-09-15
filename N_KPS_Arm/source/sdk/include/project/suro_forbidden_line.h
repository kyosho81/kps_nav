#ifndef _SURO_FORBIDDEN_LINE_KYOSHO_20200919_
#define _SURO_FORBIDDEN_LINE_KYOSHO_20200919_

#include <map>
#include <list>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"

class suro_forbidden_line
{
public:
	suro_forbidden_line();
	~suro_forbidden_line();

	bool load(const std::string &str_file);
	int get_forbidden_lines(std::list<SLine2P> &l_forbidden_lines);

protected:
private:

	std::list<SLine2P> l_forbidden_lines_;
};


#endif//_SURO_FORBIDDEN_LINE_KYOSHO_20200919_
