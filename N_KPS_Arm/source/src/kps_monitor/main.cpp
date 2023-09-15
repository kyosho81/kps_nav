#include <QTranslator>
#ifndef Q_MOC_RUN 
#include "Comm/dump_w32.hpp"
#endif
#include "Comm/Comm.h"
#include "device/device_pool.h"
// #include "device/device_base.h"
// #include "device/device_lms1xx.h"
// #include "sensor/sick/lms111.h"
//#include "device/device_data_server.h"
#include "msg_pump/msg_pump.hpp"
#include "interpro_shared/sh_pool.hpp"

#include "kps_main_win.h"


int main(int argc, char *argv[])
{
#ifdef _WIN32
	SetUnhandledExceptionFilter(ExceptionFilter);
#endif
	QApplication a(argc, argv);


	QTranslator translator_zh_CN;
	bool b_load_ok = translator_zh_CN.load(".//language//kps_monitor_zh_CN.qm");
	if (b_load_ok){
		a.installTranslator(&translator_zh_CN);
	}else{
		std::cout<<"load language file error!!! .//language//kps_monitor_zh_CN.qm no found!!"<<std::endl;
	}
	
	//
	bool b_init_core = true;
	bool b_agvs = false;
	if(argc > 1){
		std::string para = argv[1];
		
		if (para == "agvs"){
			b_agvs = true;
			b_init_core = true;
		}else if (para == "shared"){
			b_agvs = false;
			b_init_core = false;
		}else if (para == "sim"){
			b_agvs = true;
			b_init_core = false;
		}else{
			b_agvs = false;
			b_init_core = true;
		}
	}

	kps_main_win* m_main = new kps_main_win(b_init_core,b_agvs);
	//m_main->showMaximized();
	m_main->setMinimumWidth(800);
	m_main->setMinimumHeight(650);
	m_main->show();

	return a.exec();

}