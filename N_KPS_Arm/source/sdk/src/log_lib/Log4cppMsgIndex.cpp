#include <cassert>
#include <iostream>

#include "Comm/PortDef.h"
#include "Comm/Comm.h"

#include "Log4cppArm.hpp"
#include "log/Log4cppMsgIndex.h"

int log4cpp::log_msg_index::str_pri_to_index( const std::string &str_priority )
{
	if ( SRT_PRO_EMERG == str_priority )
	{
		return INDEX_PRO_EMERG;
	}else if ( SRT_PRO_FATAL == str_priority )
	{
		return INDEX_PRO_FATAL;
	}else if ( SRT_PRO_ALERT == str_priority )
	{
		return INDEX_PRO_ALERT;
	}else if ( SRT_PRO_CRIT == str_priority )
	{
		return INDEX_PRO_CRIT;
	}else if ( SRT_PRO_ERROR == str_priority )
	{
		return INDEX_PRO_ERROR;
	}else if ( SRT_PRO_WARN == str_priority )
	{
		return INDEX_PRO_WARN;
	}
	else if ( SRT_PRO_NOTICE == str_priority )
	{
		return INDEX_PRO_NOTICE;
	}
	else if ( SRT_PRO_INFO == str_priority )
	{
		return INDEX_PRO_INFO;
	}
	else if ( SRT_PRO_DEBUG == str_priority )
	{
		return INDEX_PRO_DEBUG;
	}
	else if ( SRT_PRO_NOTSET == str_priority )
	{
		return INDEX_PRO_NOTSET;
	}
	std::cout<<"err str_pri_to_index"<<std::endl;
	return 0;
}

std::string log4cpp::log_msg_index::index_to_str_pri( const int &ipriority )
{
	if(ipriority == log4cpp::Priority::EMERG){
		return SRT_PRO_EMERG;
	}else if(ipriority == log4cpp::Priority::FATAL){
		return SRT_PRO_FATAL;
	}else if(ipriority == log4cpp::Priority::ALERT){
		return SRT_PRO_ALERT;
	}else if(ipriority == log4cpp::Priority::CRIT){
		return SRT_PRO_CRIT;
	}else if(ipriority == log4cpp::Priority::ERROR){
		return SRT_PRO_ERROR;
	}else if(ipriority == log4cpp::Priority::WARN){
		return SRT_PRO_WARN;
	}else if(ipriority == log4cpp::Priority::NOTICE){
		return SRT_PRO_NOTICE;
	}else if(ipriority == log4cpp::Priority::INFO){
		return SRT_PRO_INFO;
	}else if(ipriority == log4cpp::Priority::DEBUG){
		return SRT_PRO_DEBUG;
	}else if(ipriority == log4cpp::Priority::NOTSET){
		return SRT_PRO_NOTSET;
	}
	std::cout<<"err index_to_str_pri"<<std::endl;
	return "";
}

int log4cpp::log_msg_index::cmbintex_to_pri(const int &cmbindex)
{
	if( cmbindex == INDEX_PRO_EMERG){
		return log4cpp::Priority::EMERG;
	}else if(cmbindex == INDEX_PRO_FATAL){
		return log4cpp::Priority::FATAL;
	}else if(cmbindex == INDEX_PRO_ALERT){
		return log4cpp::Priority::ALERT;
	}else if(cmbindex == INDEX_PRO_CRIT){
		return log4cpp::Priority::CRIT;
	}else if(cmbindex == INDEX_PRO_ERROR){
		return log4cpp::Priority::ERROR;
	}else if(cmbindex == INDEX_PRO_WARN){
		return log4cpp::Priority::WARN;
	}else if(cmbindex == INDEX_PRO_NOTICE){
		return log4cpp::Priority::NOTICE;
	}else if(cmbindex == INDEX_PRO_INFO){
		return log4cpp::Priority::INFO;
	}else if(cmbindex == INDEX_PRO_DEBUG){
		return log4cpp::Priority::DEBUG;
	}else if(cmbindex == INDEX_PRO_NOTSET){
		return log4cpp::Priority::NOTSET;
	}
	std::cout<<"err cmbintex_to_pri"<<std::endl;
	return log4cpp::Priority::NOTSET;
}
