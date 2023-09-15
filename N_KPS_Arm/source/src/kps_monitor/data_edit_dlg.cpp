
#include <QDebug>
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"

#include "scene/map_view.h"
#include "scene/map_scene.h"

#include "robot/Geometry.h"
#include "Comm/Comm.h"

#include "msg_pump/msg_pump.hpp"
#include "laser_filter/laser_filter.h"
#include "laser_filter/laser_filter_ex.h"

#include "property/qtpropertymanager.h"
#include "property/qtvariantproperty.h"
#include "property/qttreepropertybrowser.h"
#include "property/qteditorfactory.h"

#include "device/device_pool.h"
#include "scene/robot_item.h"
#include "plot/Plot_Lib.h"
#include "reflected_pillar/reflected_pillar.h"
#include "project/project_manage.h"
#include "Comm/configs.h"
#include "scene/item_define.h"



#include "data_edit_dlg.h"

data_edit_dlg::data_edit_dlg( QWidget *parent)
{
	parent_ = parent;

	map_sc_ = 0;

	b_run_task_ = true;
}

data_edit_dlg::~data_edit_dlg()
{


	SDelete(variantManager_);
	SDelete(enumManager_);
	SDelete(boolManager_);

	SDelete(variantFactory_);
	SDelete(comboBoxFactory_);
	SDelete(checkBoxFactory_);

	SDelete(variantEditor_);

}


void data_edit_dlg::init(map_scene* map_sc){

	map_sc_ = map_sc;
	timer_ = 0;


	variantManager_ = 0;
	enumManager_ = 0;
	boolManager_ = 0;

	variantFactory_ = 0;
	comboBoxFactory_ = 0;
	checkBoxFactory_ = 0;

	variantEditor_ = 0;



	QGridLayout* grid = new QGridLayout();

	//grid->addWidget(create_para_wiget(),0,0);

	btn_save_ = new QPushButton(tr("save"));
	btn_refresh_ = new QPushButton(tr("Refresh"));
	btn_add_ = new QPushButton(tr("Add"));
	btn_del_ = new QPushButton(tr("Del"));
	
	connect(btn_refresh_, SIGNAL(clicked(bool)), parent_, SLOT(ChooseRefresh(bool)));
//	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseRunTask(bool)));
//	connect(btn_save_, SIGNAL(clicked(bool)), parent_, SLOT(ChooseSave(bool)) );

	connect(btn_add_, SIGNAL(clicked(bool)), this, SLOT(ChooseAdd(bool)));
	connect(btn_del_, SIGNAL(clicked(bool)), this, SLOT(ChooseDel(bool)));
	//grid->addWidget(btn_upload_,13,0);
	
	btn_add_->setEnabled(false);
	btn_del_->setEnabled(false);


	grid->addWidget(btn_refresh_,13,3);
	grid->addWidget(btn_save_,13,4);
	grid->addWidget(btn_add_,14,3);
	grid->addWidget(btn_del_,14,4);

	//grid->setColumnMinimumWidth(0,300);

	QVBoxLayout* v1 = new QVBoxLayout();
	v1->addWidget(create_para_wiget());
	
	QLabel *lab_nun = new QLabel(tr(""));
	v1->addWidget(lab_nun);

	v1->addLayout(grid);

// 	QHBoxLayout* h1 = new QHBoxLayout();
// 	
// 	h1->addWidget(map_view_);
// 	h1->addLayout(v1);

	setLayout(v1);


}

bool data_edit_dlg::add_para( const std::string &group_name,  SSMetaData &para){

	if( para.mt_type_ == META_TYPE::META_BOOL){

		S32 i_data = 0;
		para.get_data(i_data);
		add_bool( group_name ,para.str_para_name_ ,i_data,para.get_read_only());

	}else if (para.mt_type_ == META_TYPE::META_I ){

		S32 i_data = 0;
		S32 i_max = 0;
		S32 i_min = 0;
		para.get_data(i_data);
		para.get_max(i_max);
		para.get_min(i_min);
		add_para_int( group_name ,para.str_para_name_ ,i_data,i_min,i_max,para.get_read_only());

	}else if (para.mt_type_ == META_TYPE::META_F ){

		double d_data = 0;
		double d_max = 1e10;
		double d_min = -1e10;
		para.get_data(d_data);
		para.get_max(d_max);
		para.get_min(d_min);
		add_para_double( group_name,para.str_para_name_ ,d_data,d_min,d_max,para.get_read_only());

	}else if (para.mt_type_ == META_TYPE::META_STR ){
		std::string str;
		para.get_data(str);
		add_para_string(group_name,para.str_para_name_,str,para.get_read_only());
	}else if (para.mt_type_ == META_TYPE::META_ENUM ){
		S32 i_data = 0;
		para.get_data(i_data);
		add_cmb_enum(group_name,para.str_para_name_ ,i_data,para.get_list(),para.get_read_only());
	}else if (para.mt_type_ == META_TYPE::META_COLOR ){
		std::string str;
		para.get_data(str);
		add_color(group_name,para.str_para_name_ ,str , para.get_read_only());
	}else if (para.mt_type_ ==  META_TYPE::META_MT_SEL ){
		std::string str;
		para.get_data(str);
		add_group(group_name,para.str_para_name_,str,Singleton_Group_Data::get_mutable_instance().v_group_,para.get_read_only());
	}else if (para.mt_type_ ==  META_TYPE::META_COMB ){
		S32 i_data = 0;
		std::string str;
		para.get_data(str);
		std::vector<std::string> cmb_list = para.get_list();
		

		//match data by string
		int i_index = -1;
		auto it = cmb_list.begin();
		for ( ; it != cmb_list.end() ; ++it ){
			
			if ( str == *it ){
				i_index = i_data;
				break;
			}
			i_data++;
		}
		//match by index
		if (i_index == -1){
			i_data = 0;
			auto it = cmb_list.begin();
			for ( ; it != cmb_list.end() ; ++it ){
				int i_sel = 0;
				if( cComm::ConvertToNum(i_sel,str)){
					if (i_data == i_sel){
						i_index = i_data; 
						break;
					}
				}
				i_data++;
			}
		}
		
		add_cmb_enum(group_name,para.str_para_name_ ,i_index,para.get_list(),para.get_read_only());
	}
	else{
		return false;
	}

	
	return true;

}
QWidget* data_edit_dlg::create_para_wiget(){

	variantManager_ = new QtVariantPropertyManager();
	enumManager_ = new QtEnumPropertyManager();
	boolManager_ = new QtBoolPropertyManager();

	variantFactory_ = new QtVariantEditorFactory();
	comboBoxFactory_ = new QtEnumEditorFactory();
	checkBoxFactory_ = new QtCheckBoxFactory();

	variantEditor_ = new QtTreePropertyBrowser();
	
	variantEditor_->setFactoryForManager(variantManager_, variantFactory_);
	variantEditor_->setFactoryForManager(enumManager_, comboBoxFactory_);
	variantEditor_->setFactoryForManager(boolManager_, checkBoxFactory_);
// 	variantEditor->addProperty(laser_para_group);
// 	variantEditor->addProperty(calib_group);

//	create_group_pro(variantEditor_);

	variantEditor_->setPropertiesWithoutValueMarked(true);
	variantEditor_->setRootIsDecorated(false);
	
	
// 	connect(variantManager_, SIGNAL(valueChanged(QtProperty *, QVariant)),
// 		this, SLOT(valueChanged(QtProperty *, QVariant)));

	//disconnect( variantManager_,SIGNAL(valueChanged(QtProperty *, QVariant)), 0 ,0);

	return (QWidget*)variantEditor_;
}

void data_edit_dlg::time_event()
{
	if ( PRODUCER_ITEM == str_type_ ){
		//update_producer(id_,str_group_name,str_name,value.toString().toStdString());

		std::stringstream ss;
		ss<<str_type_<<TYPE_DELIMITER_ID<<str_id_;

		slot_show_data(QString::fromStdString(ss.str()));
	}
	stop_timer();
}

void data_edit_dlg::valueChanged(QtProperty *property, const QVariant &value)
{	

	std::string str_group_name = get_group_pro(property);
	std::string str_name = property->propertyName().toStdString();
	std::string str_data = value.toString().toStdString();
	


	QVariant qv = ((QtVariantProperty*)property)->attributeValue("enumNames");
	QStringList enumNames = qv.toStringList();
	if (enumNames.size() > 0){
		int cmb_index = 0;
		cComm::ConvertToNum(cmb_index,str_data);
		if ( cmb_index < enumNames.size()){
			str_data = enumNames.takeAt(cmb_index).toStdString();
		}
	}

	std::cout<<"group "<<str_group_name<<" set para name:"<<str_name<<" value:"<<str_data<<std::endl;

// 	SUpdatePara update;
// 	update.str_id_ = id_;
// 	update.str_group_ = str_group_name;
// 	update.str_name_ = str_name;
// 	update.str_data_ = value.toString().toStdString();
	
	bool b_refresh_data = false;
	int id = -1;
	cComm::ConvertToNum(id,str_id_);
	if ( NODE_ITEM == str_type_ ){
		b_refresh_data = update_node(id,str_group_name,str_name,str_data);
	}else if ( EDGE_ITEM == str_type_ ){
		b_refresh_data = update_edge(id,str_group_name,str_name,str_data);
	}else if ( REFLECTOR_ITEM == str_type_ ){
		b_refresh_data = update_reflector(id,str_group_name,str_name,str_data);
	}else if ( PRODUCER_ITEM == str_type_ ){
		b_refresh_data = update_producer(id,str_group_name,str_name,str_data);
	}else if ( CONSUMER_ITEM == str_type_ ){
		b_refresh_data = update_consumer(id,str_group_name,str_name,str_data);
	}else if ( PROCESSER_ITEM == str_type_ ){
		b_refresh_data = update_processr(id,str_group_name,str_name,str_data);
	}else if ( STORAGE_ITEM == str_type_ ){
		b_refresh_data = update_storage(id,str_group_name,str_name,str_data);
	}else if ( CHARGE_ITEM == str_type_ ){
		b_refresh_data = update_charge(id,str_group_name,str_name,str_data);
	}else if ( RECT_ITEM == str_type_ ){
		std::stringstream ss;
		ss<<str_type_<<TYPE_DELIMITER_ID<<str_id_;
		b_refresh_data = update_rect(ss.str(),str_group_name,str_name,str_data);
	}else if ( RANGE_ITEM == str_type_ ){
		std::stringstream ss;
		ss<<str_type_<<TYPE_DELIMITER_ID<<str_id_;
		b_refresh_data = update_range(ss.str(),str_group_name,str_name,str_data);
	}else if ( QRCODE_ITEM == str_type_ ){
		std::stringstream ss;
		ss<<str_type_<<TYPE_DELIMITER_ID<<str_id_;
		b_refresh_data = update_qrcode(id,str_group_name,str_name,str_data);
	}

	if (b_refresh_data){
		std::stringstream ss;
		ss<<str_type_<<TYPE_DELIMITER_ID<<str_id_;
		slot_show_data(QString::fromStdString(ss.str()));
	}
	//init_timer();
}
bool data_edit_dlg::split_id_data(std::string &str_type , std::string &str_id, std::string str_sig)
{
	str_type = "";
	str_id = "-1";

	std::vector<std::string> v_res;
	cComm::SplitString(str_sig,TYPE_DELIMITER_ID,v_res);
	
	if ( v_res.size() == 2 ){
		str_type = v_res[0];
		str_id = v_res[1];

		return true;
	}
	return false;
}


void data_edit_dlg::slot_show_data(QString str)
{
	disconnect( variantManager_,SIGNAL(valueChanged(QtProperty *, QVariant)), 0 ,0);

	clear_group();
	variantEditor_->clear();
	btn_add_->setEnabled(false);
	btn_del_->setEnabled(false);

	if(split_id_data( str_type_, str_id_ , str.toStdString())){
		int id = -1;
		cComm::ConvertToNum(id,str_id_);
		if ( NODE_ITEM == str_type_) {
			show_node(id);
			map_sc_->sel_item(NODE_ITEM,str_id_);
		}else if ( EDGE_ITEM == str_type_){
			show_edge(id);
			map_sc_->sel_item(EDGE_ITEM,str_id_);
		}else if ( LAB_ITEM == str_type_){

		}else if ( REFLECTOR_ITEM == str_type_){
			show_reflector(id);
		}else if( CARGO_TYPE_ITEM == str_type_){
			show_cargo_type(id);
			btn_add_->setEnabled(true);
			btn_del_->setEnabled(true);

		}else if( PALLET_TYPE_ITEM == str_type_){
			show_pallet_type(id);
			btn_add_->setEnabled(true);
			btn_del_->setEnabled(true);

		}else if ( PRODUCER_ITEM == str_type_){
			show_producer(id);
			map_sc_->sel_item(PRODUCER_ITEM,str_id_);
		}else if ( CONSUMER_ITEM == str_type_){
			show_consumer(id);
			map_sc_->sel_item(CONSUMER_ITEM,str_id_);
		}else if ( PROCESSER_ITEM == str_type_){
			show_processer(id);
			map_sc_->sel_item(PROCESSER_ITEM,str_id_);
		}else if ( STORAGE_ITEM == str_type_){
			show_storage(id);
			map_sc_->sel_item(STORAGE_ITEM,str_id_);
		}else if ( CHARGE_ITEM == str_type_){
			show_charge(id);
			map_sc_->sel_item(CHARGE_ITEM,str_id_);
		}else if ( RECT_ITEM == str_type_){
			show_rect(str.toStdString());
			//map_sc_->sel_item(RECT_ITEM,str.toStdString());
		}else if ( RANGE_ITEM == str_type_){
			show_range(str.toStdString());
			//map_sc_->sel_item(RANGE_ITEM,str.toStdString());
		}else if ( QRCODE_ITEM == str_type_){
			show_qrcode(id);
			//map_sc_->sel_item(RANGE_ITEM,str.toStdString());
		}
		
	}else{
		if ( CARGO_TYPE_ITEM == str.toStdString()){
			str_type_ = CARGO_TYPE_ITEM;
			btn_add_->setEnabled(true);
			btn_del_->setEnabled(true);
		}else if ( PALLET_TYPE_ITEM == str.toStdString()){
			str_type_ = PALLET_TYPE_ITEM;
			btn_add_->setEnabled(true);
			btn_del_->setEnabled(true);
		}

	}
	
	create_group_pro(variantEditor_);

	connect(variantManager_, SIGNAL(valueChanged(QtProperty *, QVariant)),
		this, SLOT(valueChanged(QtProperty *, QVariant)));
}

void data_edit_dlg::init_timer()
{
	if (!timer_)
	{
		timer_ = new QTimer(this);
		timer_->setInterval(1000);
		connect(timer_, SIGNAL(timeout()), this, SLOT(time_event()));

		timer_->start();
	}
	
}

void data_edit_dlg::stop_timer()
{
	if(timer_){
		timer_->stop();
		delete timer_;
		timer_ = 0;
	}

}

// 
// void data_edit_dlg::ChooseSave( bool flag )
// {
// 	QMessageBox *tips = new QMessageBox(QMessageBox::Question,"save to project"," Yes>>save now ! No>> cancel \n",QMessageBox::Yes | QMessageBox::No,0);
// 	if (tips->exec() == QMessageBox::Yes){
// 		QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
// 	
// 	}
// 
// 	std::cout<<"ChooseSave"<<std::endl;
// 
// 	QApplication::restoreOverrideCursor();
// }
// void data_edit_dlg::ChooseExit( bool flag )
// {
// 	hide();
// }


QtProperty* data_edit_dlg::get_group(const std::string &group_name)
{
	//normal data type, no create group
	if ( group_name.length() == 0){
		return 0;
	}
	std::map< std::string,QtProperty*>::iterator it = m_group_name.find(group_name);
	if ( it != m_group_name.end() ){
		return it->second;
	}

	QString qs =  QLatin1String(group_name.c_str());
	QtProperty *group_property = variantManager_->addProperty(QtVariantPropertyManager::groupTypeId(),qs);
	group_property->setPropertyId(qs);

	m_group_name[group_name] = group_property;

	return group_property;
}

bool data_edit_dlg::add_para_string(const std::string &group_name,const std::string &para_name,const std::string &para_value,bool b_read_only = true)
{
	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::String, QString::fromStdString(para_name));

	QString qs = QString::fromStdString(para_value);
	item_str->setValue(qs);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		add_pro_group(item_str,group_name);

	}else{
		variantEditor_->addProperty(item_str);

	}
	return false;
}


bool data_edit_dlg::add_para_int(const std::string &group_name,const std::string &para_name,const int &i_data,const int &i_min,const int &i_max, bool b_read_only = true )
{

	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::Int, QString::fromStdString(para_name));
	item_str->setValue(i_data);
	if (b_read_only){
		item_str->setAttribute(QLatin1String("minimum"), i_data);
		item_str->setAttribute(QLatin1String("maximum"), i_data);
	}else{
		item_str->setAttribute(QLatin1String("minimum"), i_min);
		item_str->setAttribute(QLatin1String("maximum"), i_max);
	}
	
	item_str->setAttribute(QLatin1String("singleStep"), 1);
	item_str->setAttribute(QLatin1String("readOnly"), b_read_only);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		add_pro_group(item_str,group_name);
	}else{
		variantEditor_->addProperty(item_str);
	}
	return true;
}

bool data_edit_dlg::add_para_double(const std::string &group_name,const std::string &para_name,const double &d_data,const double &d_min,const double &d_max, bool b_read_only = true)
{
	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::Double, QString::fromStdString(para_name));
	item_str->setValue(d_data);
	item_str->setAttribute(QLatin1String("singleStep"), 0.001);
	item_str->setAttribute(QLatin1String("decimals"), 4);
	if (b_read_only){
		item_str->setAttribute(QLatin1String("minimum"), d_data);
		item_str->setAttribute(QLatin1String("maximum"), d_data);
	}else{
		item_str->setAttribute(QLatin1String("minimum"), d_min);
		item_str->setAttribute(QLatin1String("maximum"), d_max);
	}

	item_str->setAttribute(QLatin1String("readOnly"), b_read_only);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		add_pro_group(item_str,group_name);
	}else{
		variantEditor_->addProperty(item_str);
	}
	return true;
}
bool data_edit_dlg::add_cmb_enum( const std::string &group_name,const std::string &para_name,const int &e_data,std::vector<std::string> v_cmb, bool b_read_only = true )
{
	QtVariantProperty* item_enum = variantManager_->addProperty(QtVariantPropertyManager::enumTypeId(), QString::fromStdString(para_name));

	QStringList enumNames;
	auto it = v_cmb.begin();
	for ( ; it != v_cmb.end() ; ++it ){
		enumNames<<QString::fromStdString(*it) ;
	}
	
	item_enum->setAttribute(QLatin1String("enumNames"), enumNames);
	item_enum->setValue(e_data);

	item_enum->setAttribute(QLatin1String("readOnly"), b_read_only);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_enum);
		add_pro_group(item_enum,group_name);
	}else{
		variantEditor_->addProperty(item_enum);
	}
	return true;
}

bool data_edit_dlg::add_bool(const std::string &group_name,const std::string &para_name,const bool &i_data , bool b_read_only = true)
{
	QtVariantProperty *item_bool = variantManager_->addProperty(QVariant::Bool, QString::fromStdString(para_name));
	if (i_data > 0){
		item_bool->setValue(true);
	}else{
		item_bool->setValue(false);
	}
	item_bool->setAttribute(QLatin1String("readOnly"), b_read_only);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_bool);
		add_pro_group(item_bool,group_name);
	}else{
		variantEditor_->addProperty(item_bool);
	}
	return true;
}

bool data_edit_dlg::add_group(const std::string &group_name,const std::string &para_name, const std::string &para_value,std::vector<std::string> v_group, bool b_read_only)
{
	

	std::map<std::string, int> m_group;
	Singleton_Group_Data::get_mutable_instance().get_group_map(m_group,para_value,v_group);


	QtProperty* grop = get_group(group_name);
	if (grop){

		auto it = m_group.begin();
		for ( ; it != m_group.end() ; ++it ){

			QtVariantProperty *item_bool = variantManager_->addProperty(QVariant::Bool, QString::fromStdString(it->first));
			if ( it->second > 0){
				item_bool->setValue(true);
			}else{
				item_bool->setValue(false);
			}
			//item_bool->setAttribute(QLatin1String("readOnly"), b_read_only);
			grop->addSubProperty(item_bool);
			add_pro_group(item_bool,group_name);
		}
		
		return true;
	}else{
		return false;
	}

}

bool data_edit_dlg::add_color(const std::string &group_name,const std::string &para_name, const std::string &para_value, bool b_read_only)
{
	QColor color;
	color.setNamedColor(QString::fromStdString(para_value));
	QVariant qv = color;

	QtVariantProperty *item_color = variantManager_->addProperty(QVariant::Color, QString::fromStdString(para_name));
	item_color->setValue(qv);
	item_color->setAttribute(QLatin1String("readOnly"), b_read_only);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_color);
		add_pro_group(item_color,group_name);
	}else{
		variantEditor_->addProperty(item_color);
	}
	return true;
}

int data_edit_dlg::create_group_pro(QtTreePropertyBrowser *variantEditor)
{
	
	std::map< std::string,QtProperty*>::iterator it = m_group_name.begin();
	for ( ; it != m_group_name.end() ; ++it ){
		variantEditor->addProperty( it->second );
	}
	return m_group_name.size();

}



void data_edit_dlg::ChooseAdd(bool flag)
{
	if ( str_type_ == CARGO_TYPE_ITEM ){
		PRO_MANAGE.create_cargo_type(CURRENT_PRO);
	}else if ( str_type_ == PALLET_TYPE_ITEM ){
		PRO_MANAGE.create_pallet_type(CURRENT_PRO);
	}
	
}

void data_edit_dlg::ChooseDel(bool flag)
{
	int id = -1;
	cComm::ConvertToNum(id,str_id_);
	if ( str_type_ == CARGO_TYPE_ITEM ){
		
		PRO_MANAGE.remove_cargo_type(CURRENT_PRO,id);
	}else if ( str_type_ == CARGO_TYPE_ITEM ){
		PRO_MANAGE.remove_pallet_type(CURRENT_PRO,id);
	}
}

void data_edit_dlg::ChooseSave(bool flag)
{
// 	if ( b_run_task_ ){
// 		//(data_manage_dlg*)(parent_)->ChooseSave(true);
// 		btn_save_->setText(tr("BeginRunTask"));
// 	}else{
// 		//((data_manage_dlg*)parent_)->ChooseSave(true);
// 		btn_save_->setText(tr("StopRunTask"));
// 	}
// 	b_run_task_ = !b_run_task_;
}

void data_edit_dlg::show_node(int id)
{
	protobuf_node* p_node = PRO_MANAGE.get_node(CURRENT_PRO,id);
	
	if (!p_node){
		std::cout<<"show node err:"<<id<<std::endl;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_node->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
	
	
}

void data_edit_dlg::show_edge( int id )
{
	protobuf_edge* p_edge = PRO_MANAGE.get_edge(CURRENT_PRO,id);

	if (!p_edge){
		std::cout<<"show edge err:"<<id<<std::endl;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_edge->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_reflector(int id)
{
	protobuf_reflector*  p_reflector = PRO_MANAGE.get_reflector(CURRENT_PRO,id);

	if (!p_reflector){
		std::cout<<"show reflector err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_reflector->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_rect(std::string str_id)
{
	protobuf_rect* p_rect = PRO_MANAGE.get_rect(CURRENT_PRO,str_id);

	if (!p_rect){
		std::cout<<"show rect err:"<<str_id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_rect->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_range(std::string str_id)
{
	protobuf_range* p_range = PRO_MANAGE.get_range(CURRENT_PRO,str_id);

	if (!p_range){
		std::cout<<"show range err:"<<str_id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_range->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_cargo_type(int id)
{
	protobuf_cargo_type* p_cargo_type = PRO_MANAGE.get_cargo_type(CURRENT_PRO,id);

	if (!p_cargo_type){
		std::cout<<"show cargo type err:"<<id<<std::endl;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_cargo_type->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}

}

void data_edit_dlg::show_pallet_type(int id)
{
	protobuf_pallet_type* p_pallet_type = PRO_MANAGE.get_pallet_type(CURRENT_PRO,id);

	if (!p_pallet_type){
		std::cout<<"show pallet type err:"<<id<<std::endl;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_pallet_type->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_producer(int id)
{
	protobuf_producer* p_producer = PRO_MANAGE.get_producer(CURRENT_PRO,id);

	if (!p_producer){
		std::cout<<"show producer err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_producer->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_consumer(int id)
{
	protobuf_consumer* p_consumer = PRO_MANAGE.get_consumer(CURRENT_PRO,id);

	if (!p_consumer){
		std::cout<<"show consumer err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_consumer->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

bool data_edit_dlg::update_node( int id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_node* p_node = PRO_MANAGE.get_node(CURRENT_PRO,id);

	if (p_node){
		
		bool b_refresh = p_node->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update node err:"<<id<<std::endl;
	}
	return false;
}
bool data_edit_dlg::update_edge( int id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_edge* p_edge = PRO_MANAGE.get_edge(CURRENT_PRO,id);

	if (p_edge){

		bool b_refresh = p_edge->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update edge err:"<<id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_reflector(int id , std::string str_group, std::string str_name ,std::string str_data)
{
	protobuf_reflector*  p_reflector = PRO_MANAGE.get_reflector(CURRENT_PRO,id);

	if (p_reflector){
	

		bool b_refresh = p_reflector->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update reflector err:"<<id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_producer(int id , std::string str_group, std::string str_name ,std::string str_data)
{
	protobuf_producer* p_producer = PRO_MANAGE.get_producer(CURRENT_PRO,id);

	if (p_producer){
		
		bool b_refresh = p_producer->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update producer err:"<<id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_consumer(int id , std::string str_group, std::string str_name ,std::string str_data)
{
	protobuf_consumer* p_consumer = PRO_MANAGE.get_consumer(CURRENT_PRO,id);

	if (p_consumer){

		bool b_refresh = p_consumer->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update consumer err:"<<id<<std::endl;
	}
	return false;
}

void data_edit_dlg::clear_data()
{

	m_group_name.clear();

	m_property_group_.clear();


	variantManager_->clear();
	enumManager_->clear();
	boolManager_->clear();

}

void data_edit_dlg::clear_group()
{
	std::map< std::string,QtProperty*>::iterator it = m_group_name.begin();
	for ( ; it != m_group_name.end() ; ++it ){
		delete it->second;
	}
	m_group_name.clear();
}

void data_edit_dlg::add_pro_group( QtProperty* property, std::string str_group )
{
	m_property_group_[property] = str_group;
}


std::string data_edit_dlg::get_group_pro( QtProperty* property )
{
	auto it = m_property_group_.find(property);
	if ( it != m_property_group_.end() ){
		return it->second;
	}
	return "";
}

void data_edit_dlg::show_charge( int id )
{
	protobuf_station* p_charge = PRO_MANAGE.get_charge(CURRENT_PRO,id);

	if (!p_charge){
		std::cout<<"show charge err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_charge->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_qrcode(int id)
{
	protobuf_qrcode* p_qr_code = PRO_MANAGE.get_qrcode(CURRENT_PRO, id );
	if (!p_qr_code){
		std::cout<<"show qrcode err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_qr_code->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

bool data_edit_dlg::update_charge( int id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_station* p_charge = PRO_MANAGE.get_charge(CURRENT_PRO,id);

	if (p_charge){

		bool b_refresh = p_charge->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update charge err:"<<id<<std::endl;
	}
	return false;
}

void data_edit_dlg::show_processer( int id )
{
	protobuf_processer* p_processer = PRO_MANAGE.get_processer(CURRENT_PRO,id);

	if (!p_processer){
		std::cout<<"show processer err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_processer->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

void data_edit_dlg::show_storage( int id )
{
	protobuf_storage* p_storage = PRO_MANAGE.get_storage(CURRENT_PRO,id);

	if (!p_storage){
		std::cout<<"show storage err:"<<id<<std::endl;
		return;
	}
	std::vector< std::pair<std::string , std::vector< std::pair<std::string,SSMetaData>> >> m_data;

	p_storage->get_data( m_data  );

	auto it = m_data.begin();
	for ( ; it != m_data.end() ; ++it ){

		std::vector< std::pair<std::string,SSMetaData>>  &vdata = it->second;
		auto it2 = vdata.begin();
		for ( ; it2 != vdata.end(); ++it2 ){
			add_para(it->first,it2->second);
		}
	}
}

bool data_edit_dlg::update_processr( int id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_processer* p_processer = PRO_MANAGE.get_processer(CURRENT_PRO,id);

	if (p_processer){

		bool b_refresh = p_processer->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update processer err:"<<id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_storage( int id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_storage* p_storage = PRO_MANAGE.get_storage(CURRENT_PRO,id);

	if (p_storage){

		bool b_refresh = p_storage->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update storage err:"<<id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_rect( std::string str_id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_rect* p_rect = PRO_MANAGE.get_rect(CURRENT_PRO,str_id);

	if (p_rect){

		bool b_refresh = p_rect->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update rect err:"<<str_id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_range( std::string str_id , std::string str_group, std::string str_name ,std::string str_data )
{
	protobuf_range* p_range = PRO_MANAGE.get_range(CURRENT_PRO,str_id);

	if (p_range){

		bool b_refresh = p_range->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update range err:"<<str_id<<std::endl;
	}
	return false;
}

bool data_edit_dlg::update_qrcode(int id , std::string str_group, std::string str_name ,std::string str_data)
{
	protobuf_qrcode* p_qr_code = PRO_MANAGE.get_qrcode(CURRENT_PRO, id );
	if (p_qr_code){

		bool b_refresh = p_qr_code->update_data(str_group,str_name,str_data);
		map_sc_->update_item(str_type_,str_id_);
		return b_refresh;

	}else{
		std::cout<<"update qrcode err:"<<id<<std::endl;
	}
	return false;
}









