#include <string.h>
#include "robot/process_bar.h"

process_bar::process_bar()
{
	memset(&process_bar_,0,sizeof(SProcess_Bar));
	set_name("unknownbar");
	set_current(0);
	set_max(0);
}

process_bar::~process_bar()
{

}

void process_bar::set_name( std::string str_nm )
{
	memset(&process_bar_.name_,0,200);
	memcpy(process_bar_.name_,str_nm.c_str(),str_nm.length());
}

void process_bar::set_max( const U32 &imax )
{
	process_bar_.max_step_ = imax;
}

void process_bar::set_current( const U32 &icurrent )
{
	process_bar_.current_step_ = icurrent;
}

SProcess_Bar process_bar::get_bar()
{
	return process_bar_;
}

