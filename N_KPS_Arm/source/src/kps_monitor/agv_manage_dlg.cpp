
#include <QDebug>

#include "scene/map_scene.h"
#include "dispatching/agv_manage.h"
#include "agv_manage_table.h"
#include "dispatching/traffic_control.h"
#include "scene/map_scene.h"
#include "scene/agv_item.h"


#include "agv_manage_dlg.h"


agv_manage_dlg::agv_manage_dlg( QWidget *parent)
{
	table_ = 0;

	btn_search_ = 0;
	btn_lock_ = 0;
	btn_set_init_ = 0;

	btn_sim_fast_ = 0;
	btn_sim_low_ = 0;

	i_speed_ = 1;
	i_heart_beat_= 0;

	timer_ = 0;
}

agv_manage_dlg::~agv_manage_dlg()
{

}

void agv_manage_dlg::init_timer()
{

	if (!timer_){
		timer_ = new QTimer(this);
		timer_->setInterval(100);
		connect(timer_, SIGNAL(timeout()), this, SLOT(updateTimerEvent()));
		timer_->start();
	}else{
		timer_->stop();
		SDelete(timer_);
	}

}

void agv_manage_dlg::updateTimerEvent()
{

	//all agv data collect to maplist;
	AGV_MANAGE.do_agv_sm(i_heart_beat_++,i_speed_);

	std::map<int,SAGV_Info> m_agv_status;
	AGV_MANAGE.get_agv_status(m_agv_status);
	
	std::map<int,SRobot_Inf> m_agv_info;
	AGV_MANAGE.get_agv_info(m_agv_info);

	std::map<int,std::list<SPathData>> m_run_path;
	AGV_MANAGE.get_agv_run_path(m_run_path);

	std::map<int,std::vector<SVec>> m_robot_shape;
	AGV_MANAGE.get_agv_shape(m_robot_shape);

	std::map<int,std::pair<int,int>> m_lock_pause;
	AGV_MANAGE.get_agv_lock_pause(m_lock_pause);

	std::map<int,SAct_Fork> m_ex_data;
	AGV_MANAGE.get_agv_ex_data(m_ex_data);

	TRAFFIC_CONTROL.set_data(m_agv_status,m_agv_info,m_run_path,m_robot_shape);

	TRAFFIC_CONTROL.do_traffic_control();

	update_agv_item(TRAFFIC_CONTROL.get_agv_raw_show() );

	table_->show_agv_list(m_agv_status, m_agv_info, m_lock_pause, m_ex_data);
	
}

void agv_manage_dlg::init( map_scene* map_scene )
{
	QGridLayout* grid = new QGridLayout();

	table_ = new agv_manage_table();
	
	btn_search_ = new QPushButton(tr("search"));
	btn_lock_ = new QPushButton(tr("lock"));
	btn_set_init_ = new QPushButton(tr("set_init"));
	btn_set_offline_ = new QPushButton(tr("set_offline"));


	btn_sim_fast_ = new QPushButton(tr("SimFast"));
	btn_sim_low_ = new QPushButton(tr("SimSlow"));

	QLabel* lab_sim_speed_ = new QLabel(tr("sim speed:")); 
	qedit_speed_ = new QLineEdit();

	connect(btn_search_, SIGNAL(clicked(bool)), this, SLOT(ChooseSearch(bool)));
	connect(btn_lock_, SIGNAL(clicked(bool)), this, SLOT(ChooseLock(bool)));
	connect(btn_set_init_, SIGNAL(clicked(bool)), this, SLOT(ChooseSetInit(bool)));
	connect(btn_set_offline_, SIGNAL(clicked(bool)), this, SLOT(ChooseSetOffline(bool)));

	connect(btn_sim_fast_, SIGNAL(clicked(bool)), this, SLOT(ChooseSimFast(bool)));
	connect(btn_sim_low_, SIGNAL(clicked(bool)), this, SLOT(ChooseSimSlow(bool)));


	grid->addWidget(table_,0,0,1,11);
	grid->addWidget(btn_search_,1,0);
	grid->addWidget(btn_lock_,1,1);
	grid->addWidget(btn_set_init_,1,2);
	grid->addWidget(btn_set_offline_,1,3);

	grid->addWidget(lab_sim_speed_,1,7);
	grid->addWidget(qedit_speed_,1,8);
	
	grid->addWidget(btn_sim_fast_,1,9);
	grid->addWidget(btn_sim_low_,1,10);
	
	qedit_speed_->setEnabled(false);
	QIntValidator *pIntValidator = new QIntValidator(this);
	pIntValidator->setRange(1, 10);
	qedit_speed_->setValidator(pIntValidator);
	qedit_speed_->setText(QString("%1").arg(i_speed_));
	
	setLayout(grid);

	map_scene_ = map_scene;

	init_timer();
}

void agv_manage_dlg::ChooseSearch(bool flag)
{
	AGV_MANAGE.search_online_agv();
}

void agv_manage_dlg::ChooseLock(bool flag)
{
	std::map<int, int> m_sel = table_->sel_agv_lock(); 

	if (m_sel.size() < 1){
		QMessageBox::warning(0, tr("Error"), "Select agv first!");
		return ;
	}

	bool b_lock = false;
	QMessageBox *tips = new QMessageBox(QMessageBox::Question,tr("AGV State"),tr("Yes,lock agv; No,unlock agv; Cancel"),QMessageBox::Yes | QMessageBox::No| QMessageBox::Cancel,0);
	int i_res = tips->exec();
	if ( i_res == QMessageBox::Yes){
		b_lock = true;
	}else if ( i_res == QMessageBox::No){
		b_lock = false;
	}else{
		return ;
	}

	auto it = m_sel.begin();
	for ( ; it != m_sel.end() ; ++it ){

		if (b_lock){
			AGV_MANAGE.set_agv_lock(it->first,1);
		}else{
			AGV_MANAGE.set_agv_lock(it->first,2);
		}
		
	}
}

void agv_manage_dlg::ChooseSetInit(bool flag)
{
	std::map<int, int> m_sel = table_->sel_agv_lock(); 

	if (m_sel.size() < 1){
		QMessageBox::warning(0, tr("Error"), tr("Select agv first!"));
		return ;
	}


	QMessageBox *tips = new QMessageBox(QMessageBox::Question,tr("AGV State"),tr("Yes, Set agv init ; Cancel"),QMessageBox::Yes |  QMessageBox::Cancel,0);
	int i_res = tips->exec();
	if ( i_res == QMessageBox::Yes){
		auto it = m_sel.begin();
		for ( ; it != m_sel.end() ; ++it ){

			AGV_MANAGE.set_agv_init(it->first);

		}
	}else{
		return ;
	}

	
}

void agv_manage_dlg::ChooseSetOffline(bool flag)
{
	std::map<int, int> m_sel = table_->sel_agv_lock(); 

	if (m_sel.size() < 1){
		QMessageBox::warning(0, tr("Error"), "Select agv first!");
		return ;
	}


	QMessageBox *tips = new QMessageBox(QMessageBox::Question,tr("AGV State"),tr("Yes, offline agv ; Cancel"),QMessageBox::Yes |  QMessageBox::Cancel,0);
	int i_res = tips->exec();
	if ( i_res == QMessageBox::Yes){
		auto it = m_sel.begin();
		for ( ; it != m_sel.end() ; ++it ){

			AGV_MANAGE.offline_agv(it->first);

		}
	}else{
		return ;
	}
}

void agv_manage_dlg::ChooseSimFast(bool flag)
{
	if (i_speed_ < 10){
		i_speed_++;
	}
	qedit_speed_->setText(QString("%1").arg(i_speed_));
}

void agv_manage_dlg::ChooseSimSlow(bool flag)
{
	if (i_speed_ > 0){
		i_speed_--;
	}
	qedit_speed_->setText(QString("%1").arg(i_speed_));
}


void agv_manage_dlg::remove_agv()
{
	m_agv_item_.clear();
}

bool agv_manage_dlg::get_agv_item( agv_item* &p_agv_item , const int &id )
{

	p_agv_item = 0;

	auto it = m_agv_item_.find(id);

	if ( it == m_agv_item_.end()) {

		p_agv_item = new agv_item();
		p_agv_item->i_id_ = id;
		map_scene_->add_item( AGV_ITEM , (QGraphicsItem*)p_agv_item);

		m_agv_item_[id] = p_agv_item;


	}else{
		p_agv_item = it->second;
	}
	return true;
}

void agv_manage_dlg::update_agv_item( std::map<int,agv_show_data> &show_data )
{

	std::map<int,int> m_online;

	auto it = show_data.begin();
	for ( ; it != show_data.end() ; ++it ){

		m_online[it->first] = 0;

		agv_item* p_agv_item = 0;
		if (get_agv_item(p_agv_item, it->first)){


			p_agv_item->set_robot_shape(it->second.v_shape_);
			p_agv_item->set_run_path(it->second.l_path_);
		}
		p_agv_item->set_amcl_pos(it->second.amcl_pos_);
	}

	check_agv_show(m_online);
}


bool agv_manage_dlg::check_agv_show( std::map<int,int> &m_online )
{
	auto it = m_agv_item_.begin();

	for ( ; it != m_agv_item_.end() ; ++it ) {
		if ( m_online.count( it->first )){
			it->second->show();
		}else{
			it->second->hide();
		}
	}
	return true;
}
