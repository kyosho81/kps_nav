
#include <QDebug>
#include <QHeaderView>

#include "interface/xml_rpc_client.h"
#include "dev_data_model.h"

#include "dev_monitor_dlg.h"

#define STR_DEVICE_ERR  "DS Err"
#define STR_DEVICE_INIT "DS Init"
#define STR_DEVICE_IDLE "DS Idle"
#define STR_DEVICE_RUN  "DS Run"
#define STR_DEVICE_2ERR "DS toRun"

#define STR_BAG_IDLE "Bag Idle"
#define STR_BAG_LOGGING "Bag Logging"
#define STR_BAG_PLAYBACK "Bag PlayBack"
#define STR_BAG_PLAYBACK_WAIT "Bag PlayBack Wait"
#define STR_BAG_IDLE_LOGGING "Bag Idle Logging"
#define STR_BAG_IDLE_PLAYBACK "Bag Idle PlayBack"
#define STR_BAG_LOGGING_IDLE "Bag Logging Idle"
#define STR_BAG_PLAYBACK_IDLE "Bag PlayBack Idle"
#define STR_BAG_UPLOAD "Bag Upload"
#define STR_BAG_ERR "Bag Error"


#define STR_MAP_IDLE "Mapping Idle"
#define STR_MAP_RUN_MAPPING "Mapping Run Mapping"
#define STR_MAP_BAG_MAPPING "Mapping Bag Mapping"
#define STR_MAP_IDLE_RUN_MAPPING "Mapping Idle Run Mapping"
#define STR_MAP_IDLE_BAG_MAPPING "Mapping Idle Bag Mapping"
#define STR_MAP_RUN_MAPPING_IDLE "Mapping Run Mapping Idle"
#define STR_MAP_BAG_MAPPING_IDLE "Mapping Bag Mapping Idle"
#define STR_MAP_SAVE_MAP "Mapping Save Map"
#define STR_MAP_SHOW_MAP "Mapping Show Map"
#define STR_LC_IDLE "LC IDLE"
#define STR_LC_LOAD "LC LOAD"
#define STR_LC_INIT "LC INIT"
#define STR_LC_RUN  "LC RUN"
#define STR_LC_ERR  "LC ERR"

#define STR_ERR_CODE_NONE			"."
#define STR_ERR_CODE_INIT			"Init Error"
#define STR_ERR_CODE_COMMUNICATE	"Commnicate Error"
#define STR_ERR_CODE_HZ				"Health Error(Hz)"
#define STR_ERR_INIT_POS			"Set map and init pos"
#define STR_ERR_REFLECTOR_IN        "Reflector Scan Err!"
#define STR_ERR_REFLECTOR_NO_MATCH  "Reflector No match!"
#define STR_ERR_REFLECTOR_LS        "Reflector Least square Err!"
#define STR_ERR_REFLECTOR_MT_MATCH  "Reflector Multi match Err!"
#define STR_ERR_REFLECTOR_ZERO      "Reflector No found!"
#define STR_ERR_LC_FRAME_INIT_ERR   "LC frame load Err!"
#define STR_ERR_LC_FRAME_RN_ERR     "LC run Err!"
#define STR_ERR_MV_LOCATION_ERR     "MV location Err!"
#define STR_ERR_MV_SEG_PATH_ERR     "MV seg path Err!"
#define STR_ERR_MV_OUTOFF_TARGET_ERR  "MV out of target Err!"
#define STR_ERR_MV_MV_OUTOFF_LINE_ERR "MV out of line Err!"
#define STR_ERR_UNKNOWN             "UNKNOWN ERROR!>>"

#define STR_LOG_IDLE "LOG IDLE"
#define STR_LOG_RUN  "LOG RUN"
#define STR_LOG_PKG  "LOG PKG"

Dev_monitor_dlg::Dev_monitor_dlg( QWidget *parent)
	: QTableView(parent)
{
	//	model_ = new dev_data_models(this);

	// 	model_ = new QStandardItemModel(this);
	// 	model_->setItem(0, 0, new QStandardItem("1")); 
	// 	model_->setItem(0, 1, new QStandardItem("2"));
	// 	model_->setItem(0, 2, new QStandardItem("3"));
	//	this->setModel(model_);

	this->setAlternatingRowColors(true);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

	/*this->setMinimumWidth((int)1200);*/
	this->setObjectName("dev_monitor");
	QHeaderView* hHeader = this->horizontalHeader();
	hHeader->setObjectName("hHeader");

	QHeaderView* vHeader = this->verticalHeader();
	vHeader->setObjectName("vHeader");
	vHeader->setFixedWidth(35);
	this->horizontalHeader()->setStretchLastSection(true);


	model_ = new dev_data_model(this);
	this->setModel(model_);   //绑定数据模型

	//set table header
	QStringList headers;
	headers << tr("Dev ID")<<tr("Dev_name")<<tr("Dev_status")<<tr("Error_code")<<tr("Cycle_ms")<<tr("Run_ms");
	model_->setHorizontalHeader(headers);

	//this->setColumnWidth(0, 80);

	this->setSortingEnabled(true);
}

Dev_monitor_dlg::~Dev_monitor_dlg()
{

}

void Dev_monitor_dlg::init_timer()
{
	timer_ = new QTimer(this);
	timer_->setInterval(1000);
	connect(timer_, SIGNAL(timeout()), this, SLOT(updateProgressValue()));

	timer_->start();
}
std::string Dev_monitor_dlg::toStrDevStatus(const int &sta){

	switch ((eDEV_STATUS)sta)
	{
	case eDEV_STATUS::DEV_ERR:
		return STR_DEVICE_ERR;
		break;
	case eDEV_STATUS::DEV_INIT:
		return STR_DEVICE_INIT;
		break;
	case eDEV_STATUS::DEV_IDLE:
		return STR_DEVICE_IDLE;
		break;
	case eDEV_STATUS::DEV_RUN:
		return STR_DEVICE_RUN;
		break;
	case eDEV_STATUS::DEV_toERR:
		return STR_DEVICE_2ERR;
		break;

	case eBAG_STATUS::BAG_IDLE:
		return STR_BAG_IDLE;
		break;
	case eBAG_STATUS::BAG_LOGGING:
		return STR_BAG_LOGGING;
		break;
	case eBAG_STATUS::BAG_PLAYBACK:
		return STR_BAG_PLAYBACK;
		break;
	case eBAG_STATUS::BAG_PLAYBACK_WAIT:
		return STR_BAG_PLAYBACK_WAIT;
		break;
	case eBAG_STATUS::BAG_IDLE_LOGGING:
		return STR_BAG_IDLE_LOGGING;
		break;
	case eBAG_STATUS::BAG_IDLE_PLAYBACK:
		return STR_BAG_IDLE_PLAYBACK;
		break;
	case eBAG_STATUS::BAG_LOGGING_IDLE:
		return STR_BAG_LOGGING_IDLE;
		break;
	case eBAG_STATUS::BAG_PLAYBACK_IDLE:
		return STR_BAG_PLAYBACK_IDLE;
		break;
	case eBAG_STATUS::BAG_UPLOAD:
		return STR_BAG_UPLOAD;
		break;
	case eBAG_STATUS::BAG_ERR:
		return STR_BAG_ERR;
		break;

	case eMAP_STATUS::MAP_IDLE:
		return STR_MAP_IDLE;
		break;
	case eMAP_STATUS::MAP_RUN_MAPPING:
		return STR_MAP_RUN_MAPPING;
		break;
	case eMAP_STATUS::MAP_BAG_MAPPING:
		return STR_MAP_BAG_MAPPING;
		break;
	case eMAP_STATUS::MAP_IDLE_RUN_MAPPING:
		return STR_MAP_IDLE_RUN_MAPPING;
		break;
	case eMAP_STATUS::MAP_IDLE_BAG_MAPPING:
		return STR_MAP_IDLE_BAG_MAPPING;
		break;
	case eMAP_STATUS::MAP_RUN_MAPPING_IDLE:
		return STR_MAP_RUN_MAPPING_IDLE;
		break;
	case eMAP_STATUS::MAP_BAG_MAPPING_IDLE:
		return STR_MAP_BAG_MAPPING_IDLE;
		break;
	case eMAP_STATUS::MAP_SAVE_MAP:
		return STR_MAP_SAVE_MAP;
		break;
	case eMAP_STATUS::MAP_SHOW_MAP:
		return STR_MAP_SHOW_MAP;
		break;

	case LC_State::LC_IDLE:
		return STR_LC_IDLE;
		break;
	case LC_State::LC_LOAD:
		return STR_LC_LOAD;
		break;
	case LC_State::LC_INIT:
		return STR_LC_IDLE;
		break;
	case LC_State::LC_RUN:
		return STR_LC_RUN;
		break;
	case LC_State::LC_ERR:
		return STR_LC_ERR;
		break;

	case LOG_State::LOG_IDLE:
		return STR_LOG_IDLE;
		break;
	case LOG_State::LOG_RUN:
		return STR_LOG_RUN;
		break;
	case LOG_State::LOG_PKG:
		return STR_LOG_PKG;
		break;

	default:
		return "unknown";
		break;
	}
}
std::string Dev_monitor_dlg::err_codeToStr(const U16 &err_code){
	std::stringstream ss;
	
	if (err_code == 0){
		return STR_ERR_CODE_NONE;
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_NONE)  & err_code ){
		ss<<STR_ERR_CODE_NONE<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_INIT)  & err_code ){
		ss<<STR_ERR_CODE_INIT<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_COMMUNICATE)  & err_code ){
		ss<<STR_ERR_CODE_COMMUNICATE<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_HZ)  & err_code ){
		ss<<STR_ERR_CODE_HZ<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_INIT_POS)  & err_code ){
		ss<<STR_ERR_INIT_POS<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_REFLECTOR_IN)  & err_code ){
		ss<<STR_ERR_REFLECTOR_IN<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_REFLECTOR_NO_MATCH)  & err_code ){
		ss<<STR_ERR_REFLECTOR_NO_MATCH<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_REFLECTOR_LS)  & err_code ){
		ss<<STR_ERR_REFLECTOR_LS<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_REFLECTOR_MTI_FOUND)  & err_code ){
		ss<<STR_ERR_REFLECTOR_MT_MATCH<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_REFLECTOR_ZERO)  & err_code ){
		ss<<STR_ERR_REFLECTOR_ZERO<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_LC_FRAME_INIT_ERR)  & err_code ){
		ss<<STR_ERR_LC_FRAME_INIT_ERR<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_LC_FRAME_RN_ERR)  & err_code ){
		ss<<STR_ERR_LC_FRAME_RN_ERR<<" ";
	}
	
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_MV_LOCATION_ERR)  & err_code ){
		ss<<STR_ERR_MV_LOCATION_ERR<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_MV_SEG_PATH_ERR)  & err_code ){
		ss<<STR_ERR_MV_SEG_PATH_ERR<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_MV_OUTOFF_TARGET_ERR)  & err_code ){
		ss<<STR_ERR_MV_OUTOFF_TARGET_ERR<<" ";
	}
	if( ( 1<<eDEV_ERR_CODE::DEV_ERR_MV_OUTOFF_LINE_ERR)  & err_code ){
		ss<<STR_ERR_MV_MV_OUTOFF_LINE_ERR<<" ";
	}
	
	return ss.str();
}
std::string Dev_monitor_dlg::toStrDevErrCode(const SDevStatus  &sta)
{
	std::stringstream ss;

	if(sta.device_id_ < Comm_Dev_Id::ID_MAP_SERVER){
		return err_codeToStr(sta.err_code_);
	}else if( sta.device_id_ == Comm_Dev_Id::ID_MAP_SERVER ){
		if(sta.err_code_ > 0){
			std::stringstream ss;
			ss<<"regist scan size:"<<sta.err_code_;
			return ss.str();
		}else{
			return ".";
		}
		
	}else if( sta.device_id_ == Comm_Dev_Id::ID_LOOP_CLOSURE ){
		return err_codeToStr(sta.err_code_);

	}else if( sta.device_id_ == Comm_Dev_Id::ID_MOVE_MENT ){
		return err_codeToStr(sta.err_code_);

	}else{
		if(sta.err_code_ > 0){
			std::stringstream ss;
			ss<<STR_ERR_UNKNOWN<<sta.err_code_;
			return ss.str();
		}else{
			return ".";
		}
	}
	
}

void Dev_monitor_dlg::updateProgressValue()
{
	std::vector<SPubDevStatus> v_dev_status;
	Singleton_XML_Client::get_mutable_instance().get_dev_status(v_dev_status);
	
	QVector<QStringList> data;

	// 	SPubDevStatus tmp;
	// 	std::string nm = "laser";
	// 	memset(tmp.name_,0,200);
	// 	memcpy(tmp.name_ , nm.c_str(), nm.length());
	// 	tmp.dev_status_.device_id_ = 0;
	// 	tmp.dev_status_.status_ = 0;
	// 	tmp.dev_status_.err_code_ = 0;
	// 	v_dev_status.push_back(tmp);

	std::vector<SPubDevStatus>::iterator it = v_dev_status.begin();
	for ( ; it != v_dev_status.end() ; ++it )
	{
		SPubDevStatus &dev(*it);
		QStringList rowset;
		rowset.push_back(QString::number(dev.dev_status_.device_id_));
		rowset.push_back(QString::fromStdString(dev.name_));	
		rowset.push_back(QString::fromStdString(toStrDevStatus(dev.dev_status_.status_)));
		rowset.push_back(QString::fromStdString(toStrDevErrCode(dev.dev_status_)));
		rowset.push_back(QString::number(dev.dev_status_.cycle_ms_));
		rowset.push_back(QString::number(dev.dev_status_.run_ms_));
		data.append(rowset);
	}
	//timer_->stop();

	model_->setData(data);
}