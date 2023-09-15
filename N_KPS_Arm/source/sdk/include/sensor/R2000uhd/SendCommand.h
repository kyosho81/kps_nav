/*
 * SendCommand.h
 *
 *  Created on: Jan 19, 2018
 *      Author: dl
 */

#ifndef SENDCOMMAND_H_
#define SENDCOMMAND_H_

#include <string>
#include "Comm/MyDefine.h"

#include "R2000uhd/CHttpClient.h"
#include "R2000uhd/DataConvert.h"

class SendCommand {
public:
	SendCommand();
	virtual ~SendCommand();

	std::string SendComm(std::string command);
	std::string Request_Handle_TCP(std::string ip, std::string packet_type, std::string timeout, std::string start_angle);
	std::string Release_Handle(std::string ip);
	std::string Start_Scanoutput(std::string ip);
	std::string Stop_Scanoutput(std::string ip);
	std::string Set_Parameter(std::string ip, std::string parameter);
	std::string Get_Parameter_Info(std::string ip);
	std::string set_scanoutput_config(std::string ip,std::string parameter);
	std::string Feed_Watchdog(std::string ip);
	std::string Get_Parameter_List(std::string ip);
	std::string set_scan_direction(std::string ip,std::string parameter="ccw");
	std::string Get_scanoutput_config(std::string ip);
	void Clear_Handle();

	std::string SendComm_test(std::string command);
public:
	CHttpClient m_httpclient_;
	DataConvert m_DataConvert_;
	S16 Int16_Sucess_;
	//S16 Int16_ErrorCode;
	std::string Handle_;
	std::string Port_;


};

#endif /* SENDCOMMAND_H_ */
