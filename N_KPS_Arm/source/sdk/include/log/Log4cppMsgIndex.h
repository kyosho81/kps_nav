#ifndef __LOG4CPP_DEF_H__
#define __LOG4CPP_DEF_H__

#define SRT_PRO_EMERG  "EMERG"
#define SRT_PRO_FATAL  "FATAL"
#define SRT_PRO_ALERT  "ALERT"
#define SRT_PRO_CRIT   "CRIT"
#define SRT_PRO_ERROR  "ERROR"
#define SRT_PRO_WARN   "WARN"
#define SRT_PRO_NOTICE "NOTICE"
#define SRT_PRO_INFO   "INFO"
#define SRT_PRO_DEBUG  "DEBUG"
#define SRT_PRO_NOTSET "NOTSET"

#define INDEX_PRO_EMERG  0
#define INDEX_PRO_FATAL  1
#define INDEX_PRO_ALERT  2
#define INDEX_PRO_CRIT   3
#define INDEX_PRO_ERROR  4
#define INDEX_PRO_WARN   5
#define INDEX_PRO_NOTICE 6
#define INDEX_PRO_INFO   7
#define INDEX_PRO_DEBUG  8
#define INDEX_PRO_NOTSET 9



namespace log4cpp{
	class log_msg_index
	{
	public:
		log_msg_index();
		~log_msg_index();

		static int str_pri_to_index(const std::string &str_priority);
		static std::string index_to_str_pri(const int &ipriority);
		static int cmbintex_to_pri(const int &ipriority);
	};


}//namespace log4cpp

#endif//__LOG4CPP_DEF_H__