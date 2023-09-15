
#include <QDebug>
#include "robot/RobotStruct.h"
#include "interface/xml_rpc_client.h"

#include "scene/map_view.h"
#include "scene/map_scene.h"

#include "robot/Geometry.h"
#include "Comm/Comm.h"
#include "interface/rpc_config_client.h"

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

#include "para_dlg.h"

para_dlg::para_dlg( QWidget *parent):
th_show_laser_(1)
{

	//get_config();

// 	plot_ = new Plot();
// 	iinten_ = plot_->AddPlot("intensities",100);
// 	plot_->show();
}

para_dlg::~para_dlg()
{
	SDelete(map_scene_);
	SDelete(map_view_);

	SDelete(variantManager_);
	SDelete(enumManager_);
	SDelete(boolManager_);

	SDelete(variantFactory_);
	SDelete(comboBoxFactory_);
	SDelete(checkBoxFactory_);

	SDelete(variantEditor_);

}
void para_dlg::bind_lab_event( qt_eve::mouse_event::Slot_Lab event_slot )
{
	map_scene_->bind_lab_event(event_slot);
}
void para_dlg::init(){

	timer_ = 0;
	map_scene_ = 0;
	map_view_ = 0;

	variantManager_ = 0;
	enumManager_ = 0;
	boolManager_ = 0;

	variantFactory_ = 0;
	comboBoxFactory_ = 0;
	checkBoxFactory_ = 0;

	variantEditor_ = 0;

	b_connection_ = false;


	map_scene_ = new map_scene();
	map_view_ = new map_view();
	map_view_->setScene(map_scene_);
	
	

// 	create_x_y_axle();
// 	create_laser_y();
// 
// 	map_view_->zoom(25);
// 	map_view_->centerOn(0,0);

	QGridLayout* grid = new QGridLayout();

	//grid->addWidget(create_para_wiget(),0,0);

	btn_upload_ = new QPushButton(tr("upload"));
	btn_download_ = new QPushButton(tr("download"));

	btn_import_ = new QPushButton(tr("import"));
	btn_export_ = new QPushButton(tr("export"));

	btn_save_ = new QPushButton(tr("save"));
	btn_exit_ = new QPushButton(tr("exit"));

	connect(btn_upload_, SIGNAL(clicked(bool)), this, SLOT(ChooseUpload(bool)));
	connect(btn_download_, SIGNAL(clicked(bool)), this, SLOT(ChooseDownload(bool)));

	connect(btn_import_, SIGNAL(clicked(bool)), this, SLOT(ChooseImport(bool)));
	connect(btn_export_, SIGNAL(clicked(bool)), this, SLOT(ChooseExport(bool)));

	connect(btn_save_, SIGNAL(clicked(bool)), this, SLOT(ChooseSave(bool)));
	connect(btn_exit_, SIGNAL(clicked(bool)), this, SLOT(ChooseExit(bool)));

	//grid->addWidget(btn_upload_,13,0);
	grid->addWidget(btn_download_,13,0);

	grid->addWidget(btn_import_,13,1);
	grid->addWidget(btn_export_,13,2);

	grid->addWidget(btn_save_,13,3);
	grid->addWidget(btn_exit_,13,4);


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

	
//   	boost::function<bool( const SLaser& laser )> fnc_laser;
//   	fnc_laser = boost::bind(&para_dlg::s_update_laser,this,_1);
//   	msg_pump::sub_msg(PUB_AMCL_LASER,fnc_laser);
// 
// 	boost::function<bool( const SLaser_Ex& laser )> fnc_laser_ex;
// 	fnc_laser_ex = boost::bind(&para_dlg::s_update_laser_ex,this,_1);
// 	msg_pump::sub_msg(PUB_LASER_EX,fnc_laser_ex);

}

bool para_dlg::add_para(config_it* c_para){

	m_name_type[c_para->get_name()] = c_para->get_type();

	if (c_para->get_type() == typeid(double).name()){
		double d_data = 0;
		double d_max = 0;
		double d_min = 0;
		c_para->get_value(d_data);
		c_para->get_max(d_max);
		c_para->get_min(d_min);
		return add_para_double(c_para->get_seg(),c_para->get_name(),d_data,d_min,d_max);
	}else if (c_para->get_type() == typeid(float).name()){
		float f_data = 0;
		float f_max = 0;
		float f_min = 0;
		c_para->get_value(f_data);
		c_para->get_max(f_max);
		c_para->get_min(f_min);
		return add_para_double(c_para->get_seg(),c_para->get_name(),f_data,f_min,f_max);
	}else if (c_para->get_type() == typeid(int).name()){
		int i_data = 0;
		int i_max = 0;
		int i_min = 0;
		c_para->get_value(i_data);
		c_para->get_max(i_max);
		c_para->get_min(i_min);
		return add_para_int(c_para->get_seg(),c_para->get_name(),i_data,i_min,i_max);
	}else if (c_para->get_type() == "string" ){
		std::string str_data;
		c_para->get_value(str_data);
		return add_para_string(c_para->get_seg(),c_para->get_name(),str_data);
	}else{
		std::cout<<"err para type!"<<c_para->get_type()<<std::endl;
		assert(false);
	}
	return false;
}
QWidget* para_dlg::create_para_wiget(){

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

	load_para();
	create_group_pro(variantEditor_);

	variantEditor_->setPropertiesWithoutValueMarked(true);
	variantEditor_->setRootIsDecorated(false);
	
	
	connect(variantManager_, SIGNAL(valueChanged(QtProperty *, QVariant)),
		this, SLOT(valueChanged(QtProperty *, QVariant)));

	return (QWidget*)variantEditor_;
}
void para_dlg::valueChanged(QtProperty *property, const QVariant &value)
{	
	std::string str_name = property->propertyName().toStdString();
	std::string str_code;
	RPC_CONFIG_CLIENT.get_whole_config( str_code, str_name);
	config_it cfg("default");
	if(!cfg.decode(str_code)){
		std::cout<<"decode error new cfg don't contain para name:"<<str_name<<std::endl;
		return;
	}

	if ( cfg.get_type() =="string"){
		cfg.set_value(value.toString().toStdString());
	}else if (cfg.get_type() == typeid(int).name()){
		cfg.set_value(value.toInt());
	}else if (cfg.get_type() == typeid(float).name()){
		cfg.set_value(value.toFloat());
	}else if (cfg.get_type() == typeid(double).name()){
		cfg.set_value(value.toDouble());
	}else{
		assert(false);
		std::cout<<"para_dlg::valueChanged value type err!"<<std::endl;
	}

	m_update[str_name] = cfg.code();

	std::cout<<"set para name:"<<property->propertyName().toStdString()<<" value:"<<value.toString().toStdString()<<std::endl;
// 	if (property->propertyName()== QLatin1String("calib line")) {
// 		item_line_->setLine(value.toDouble(),-2,value.toDouble(),2);
// 	} 
}
void para_dlg::init_timer()
{
	if (!timer_)
	{
		timer_ = new QTimer(this);
		timer_->setInterval(1000);
		connect(timer_, SIGNAL(timeout()), this, SLOT(update_sensor()));

		timer_->start();
	}
	
}

void para_dlg::stop_timer()
{
	if(timer_){
		timer_->stop();
		delete timer_;
	}

}

bool para_dlg::s_update_laser(const SLaser& laser)
{

	return true;
}

void para_dlg::create_x_y_axle()
{
	QGraphicsItem* qi = 0;
	QPen pen;
	pen.setColor(Qt::black);
	qi =map_scene_->addLine(-10,0,10,0,pen);
	qi->setZValue(0);
	qi =map_scene_->addLine(0,-10,0,10,pen);
	qi->setZValue(0);
	
	SPos arrow;
	arrow.x_ = 10;
	arrow.y_ = 0;
	arrow.th_ = 0;
	QPolygonF p3;
	get_triangle(p3,arrow);
	qi = map_scene_->addPolygon(p3,pen);
	qi->setZValue(0);

	arrow.x_ = 0;
	arrow.y_ = 10;
	arrow.th_ = M_PI/2;
	QPolygonF p31;
	get_triangle(p31,arrow);
	qi = map_scene_->addPolygon(p31,pen);
	qi->setZValue(0);
}

void para_dlg::create_laser_y()
{
	QPen pen;
	pen.setColor(Qt::blue);
	item_line_ = map_scene_->addLine(3,-2,3,2,pen);
	item_line_->setZValue(0);
}
void para_dlg::get_triangle( QPolygonF &p3, const SPos &pos){
	QPointF p;

	VecPosition phead(0.8,0,POLAR);
	phead.rotate(Rad2Deg(pos.th_));
	phead += VecPosition(pos.x_,pos.y_);
	p.setX(phead.getX());
	p.setY(phead.getY());
	p3<<p;

	VecPosition pleft(0.2,90,POLAR);
	pleft.rotate(Rad2Deg(pos.th_));
	pleft += VecPosition(pos.x_,pos.y_);
	p.setX(pleft.getX());
	p.setY(pleft.getY());
	p3<<p;

	VecPosition pright(0.2,-90,POLAR);
	pright.rotate(Rad2Deg(pos.th_));
	pright += VecPosition(pos.x_,pos.y_);
	p.setX(pright.getX());
	p.setY(pright.getY());
	p3<<p;

}

void para_dlg::update_sensor()
{
	//Singleton_XML_Client::get_mutable_instance().get_laser()
}
void para_dlg::get_config(){

}

void para_dlg::ChooseUpload( bool flag )
{
	std::cout<<"ChooseUpload"<<std::endl;
	
}
void para_dlg::ChooseDownload( bool flag )
{
	

	QMessageBox *tips = new QMessageBox(QMessageBox::Question,"download para to robot"," Yes>>set new value to robot! No>> cancel \n (warning para don't save)",QMessageBox::Yes | QMessageBox::No,0);
	if (tips->exec() == QMessageBox::Yes){
		QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
		
		std::map< std::string, std::string >::iterator it = m_update.begin();
		for (; it != m_update.end() ; ++it ){
			
			RPC_CONFIG_CLIENT.set_whole_config(it->first,it->second);
		}
	}

	std::cout<<"ChooseDownload"<<std::endl;

	QApplication::restoreOverrideCursor();
}

void para_dlg::ChooseImport( bool flag )
{

	std::string file_name = ".//cfg//";
	QString dir = QFileDialog::getOpenFileName(NULL,tr("Import cfg"),
		file_name.c_str(),
		"cfg (*.bak)");
	file_name = dir.toStdString();
	if ( cComm::FileExist(file_name))
	{
		std::ifstream iff;
		iff.open(file_name.c_str(),std::ios::in | std::ios::binary);

		if (!iff.is_open())
		{
			return ;
		}
		std::string str;
		std::vector<std::string> v_res;
		std::string str_name;
		std::string str_value;
		
		clear_para();
		m_update.clear();

		QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

		while( std::getline(iff,str) ){
			config_it cfg("default");
			cfg.decode(str);
			add_para(&cfg);
			m_update[cfg.get_name()] = str;
		}
		create_group_pro(variantEditor_);
	}
	std::cout<<"ChooseImport"<<std::endl;
	QApplication::restoreOverrideCursor();
}
void para_dlg::ChooseExport( bool flag )
{
	bool ok = true;
	std::stringstream ss;
	ss<<".//cfg//"<<cTimerDiff::get_file_now()<<".bak";
	QString qstr_cfg_name = QString::fromStdString(ss.str());
	qstr_cfg_name = QInputDialog::getText(this, tr("Save cfg?"),
		tr("cfg name:"), QLineEdit::Normal,
		qstr_cfg_name, &ok);

	std::string str_file = qstr_cfg_name.toStdString();

	if (ok && !qstr_cfg_name.isEmpty()){

		std::ofstream off;
		off.open(str_file.c_str(),std::ios::out | std::ios::trunc | std::ios::binary);

		if (!off.is_open())
		{
			QMessageBox::warning(0, tr("Error"), "File open err!");
			return ;
		}
		
		QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));

		std::vector<std::string> vres;
		RPC_CONFIG_CLIENT.get_config_list(vres);
		std::vector<std::string>::iterator it = vres.begin();
		for ( ; it != vres.end(); ++it)
		{
			std::string str;
			RPC_CONFIG_CLIENT.get_whole_config(str,*it);
			off<<str;
		}
		off.flush();
		off.close();

		QMessageBox::information(0, tr("Over"), "Export cfg file over!");

		std::cout<<"action:ChooseExport name:"<<qstr_cfg_name.toStdString()<<std::endl;
	}else{
		std::cout<<"action: cancel ChooseExport"<<std::endl;
	}

	std::cout<<"ChooseExport"<<std::endl;

	QApplication::restoreOverrideCursor();
}

void para_dlg::ChooseSave( bool flag )
{
	QMessageBox *tips = new QMessageBox(QMessageBox::Question,"save para on robot"," Yes>>save now ! No>> cancel \n",QMessageBox::Yes | QMessageBox::No,0);
	if (tips->exec() == QMessageBox::Yes){
		QApplication::setOverrideCursor(QCursor(Qt::BusyCursor));
	
		RPC_CONFIG_CLIENT.save();
	}

	std::cout<<"ChooseSave"<<std::endl;

	QApplication::restoreOverrideCursor();
}
void para_dlg::ChooseExit( bool flag )
{
	close();
	std::cout<<"ChooseExit"<<std::endl;
}
robot_item* para_dlg::get_robot_item()
{
	std::vector<QGraphicsItem*> v_item;
	QGraphicsItem* qi = map_scene_->get_item(v_item,"robot");
	
	robot_item*  p_robot_item = static_cast<robot_item*>(qi);

	if (!p_robot_item)
	{
		p_robot_item = new robot_item();
		//SLaser_para laser_para = Singleton_remote_para::get_mutable_instance().get_laser_para();
	
		map_scene_->add_item( "robot" , (QGraphicsItem*)p_robot_item);
	}
	p_robot_item->setZValue(10);
	return p_robot_item;
}

bool para_dlg::s_update_laser_ex( const SLaser_Ex& laser_ex )
{
	

	return true;
}
bool para_dlg::show_laser_ex_seg( const SLaser_Ex& laser_ex )
{
	
	//exit(0);
	return true;
}

QtProperty* para_dlg::get_group(const std::string &group_name)
{
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

bool para_dlg::add_para_string(const std::string &group_name,const std::string &para_name,const std::string &para_value)
{
	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::String, QString::fromStdString(para_name));

	QString qs = QString::fromStdString(para_value);
	item_str->setValue(qs);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		return add_para_map(para_name,item_str);
	}
	return false;
}

bool para_dlg::add_para_map(const std::string &para_name,QtProperty* pro)
{
	std::map< std::string,QtProperty*>::iterator it = m_name_value.find(para_name);
	if ( it != m_name_value.end()){
		return false;
	}

	m_name_value[para_name] = pro;

	return true;
}

bool para_dlg::add_para_int(const std::string &group_name,const std::string &para_name,const int &i_data,const int &i_min,const int &i_max)
{

	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::Int, QString::fromStdString(para_name));
	item_str->setValue(i_data);
	item_str->setAttribute(QLatin1String("minimum"), i_min);
	item_str->setAttribute(QLatin1String("maximum"), i_max);
	item_str->setAttribute(QLatin1String("singleStep"), 1);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		return add_para_map(para_name,item_str);
	}
	return false;
}

bool para_dlg::add_para_double(const std::string &group_name,const std::string &para_name,const double &d_data,const double &d_min,const double &d_max)
{
	QtVariantProperty* item_str = variantManager_->addProperty(QVariant::Double, QString::fromStdString(para_name));
	item_str->setValue(d_data);
	item_str->setAttribute(QLatin1String("singleStep"), 0.1);
	item_str->setAttribute(QLatin1String("decimals"), 4);
	item_str->setAttribute(QLatin1String("minimum"), d_min);
	item_str->setAttribute(QLatin1String("maximum"), d_max);

	QtProperty* grop = get_group(group_name);
	if (grop){
		grop->addSubProperty(item_str);
		return add_para_map(para_name,item_str);
	}
	return false;
}

int para_dlg::create_group_pro(QtTreePropertyBrowser *variantEditor)
{
	std::map< std::string,QtProperty*>::iterator it = m_group_name.begin();
	for ( ; it != m_group_name.end() ; ++it ){
		variantEditor->addProperty( it->second );
	}
	return m_group_name.size();

}

bool para_dlg::load_para()
{
	std::vector<std::string> vres;
	RPC_CONFIG_CLIENT.get_config_list(vres);
	std::vector<std::string>::iterator it = vres.begin();
	for ( ; it != vres.end(); ++it)
	{
		std::string str;
		if(RPC_CONFIG_CLIENT.get_whole_config(str,*it)){
			config_it c_it("def");
			if( c_it.decode(str) ){
				add_para(&c_it);
			}
		}else{
			
			std::cout<<"get_whole_config data err:"<<str<<std::endl;
			continue;
		}

		
	}
	return true;
}

std::string para_dlg::get_type(const std::string str_name)
{
	std::map< std::string,std::string>::iterator it = m_name_type.begin();
	if ( it != m_name_type.end() ){
		return it->second;
	}
	return "";
}

void para_dlg::clear_para()
{
	m_name_type.clear();
	m_group_name.clear();
	m_name_value.clear();

	variantManager_->clear();
	enumManager_->clear();
	boolManager_->clear();

}
