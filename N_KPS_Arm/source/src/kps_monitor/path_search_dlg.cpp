
#include <QDebug>

#include "ip_list_dlg.h"

#include "project/project_manage.h"
#include "project/dijkstra.h"
#include "project/path_search.h"
#include "project/task_rpc_client.h"

#include "path_search_dlg.h"

char pro[] = {'/' , '-' , '\\' , '\|' ,'*'};

path_search_dlg::path_search_dlg( QWidget *parent)
{

	qcmb_start_node_ = 0;
	qcomp_start_node_ = 0;
	qstrlist_start_node_ = 0;
	qedit_start_node_ = 0;

	qcmb_end_node_ = 0;
	qcomp_end_node_ = 0;
	qstrlist_end_node_ = 0;
	qedit_end_node_ = 0;

	qcmb_start_angle_ = 0;
	qcomp_start_angle_ = 0;
	qstrlist_start_angle_ = 0;
	qedit_start_angle_ = 0;

	qcmb_end_angle_ = 0;
	qcomp_end_angle_ = 0;
	qstrlist_end_angle_ = 0;
	qedit_end_angle_ = 0;

	txt_Result_ = 0;
	txt_path_ = 0;

	btn_exchange_ = 0;
	btn_search_ = 0;
	btn_show_ = 0;
	btn_close_ = 0;

	btn_mvlist_ = 0;
	btn_mvdetail_ = 0;
	btn_erase_path_ = 0;
	btn_load_path_ = 0;
	btn_save_path_ = 0;

	btn_run_path_ = 0;
	btn_run_loop_ = 0;


	b_run_ = false;
	timer_ = new QTimer(this);
	timer_->setInterval(1000);
	connect(timer_, SIGNAL(timeout()), this, SLOT(updateTimerEvent()));
	index_ = 0;
	i_run_path_id_ = -1;

	p_task_rpc_client_ = 0;
	it_run_ = l_run_path_.end();
}

path_search_dlg::~path_search_dlg()
{

}
bool path_search_dlg::event(QEvent *e)
{
	if (e->type() == QEvent::WindowActivate) {
		// window was activated
		std::cout<<"path_search_dlg activated,refresh node list!"<<std::endl;
		init_node_list();
	}
	return QWidget::event(e);
}
void path_search_dlg::init_timer()
{
	if (!b_run_){
		it_run_ = l_run_path_.begin();
		timer_->start();
	}else{
		timer_->stop();
		btn_run_loop_->setText(tr("run_loop"));
	}
	b_run_ = !b_run_;
	
}

void path_search_dlg::updateTimerEvent()
{
	
	int i_size = sizeof(pro);

	index_ = ++index_ % i_size ;
	std::stringstream ss;
	ss<<"(Run: "<<pro[index_]<<" )";

	btn_run_loop_->setText(QString::fromStdString(ss.str()));

	//no path run
	if (i_run_path_id_ == -1){
		//end of path,stop timer

		if ( it_run_ == l_run_path_.end()){
			b_run_ = false;
			timer_->stop();
			btn_run_loop_->setText(tr("run_loop"));
			return ;
		}

		//do new path
		if (!p_task_rpc_client_){

			p_task_rpc_client_ = new task_rpc_client();

			int agvid = 0 ;
			std::string str_ip = get_dev_ip();
			if (str_ip == "127.0.0.1"){
				bool ok = true;
				agvid =  QInputDialog::getInt(0 ,tr("agvid"),tr("agvid:"), 0 , 0 , 100, 1, &ok);
			}
			p_task_rpc_client_->init(str_ip,RPC_TASK_SER_PORT + agvid);

		}
		std::vector<SPathData> seg_path = *it_run_;
		i_run_path_id_ = p_task_rpc_client_->create_fix_path(seg_path);
		if (i_run_path_id_ < 0 ){
			timer_->stop();
			btn_run_loop_->setText(tr("run_loop"));
			return ;
		}
		it_run_++;
	}else{
		std::vector<task_feadback> ftb;
		p_task_rpc_client_->get_feadback(i_run_path_id_,ftb);
		if (ftb.size() > 0){
			if ( ftb[0].get_status() == STASK_STA::TASK_DONE ){
				std::cout<<"run path over!!!"<<std::endl;
				i_run_path_id_ = -1;
			}else if ( ftb[0].get_status() == STASK_STA::TASK_ERR){
				std::cout<<"run path err!!!"<<std::endl;
				i_run_path_id_ = -1;
			}
		}
		SLEEP(200);
	}

	

}





bool path_search_dlg::eventFilter(QObject * watched , QEvent * event)
{



//	if (QEvent::MouseButtonPress == event->type()){
	if (QEvent::FocusIn == event->type()){
		if (watched == qcmb_start_node_){
			//init_node_list();
			qedit_start_node_->selectAll();
		}else if (watched == qcmb_end_node_){
			qedit_end_node_->selectAll();
		}else if (watched == qcmb_start_angle_){
			qedit_start_angle_->selectAll();
		}else if (watched == qcmb_end_angle_){
			qedit_end_angle_->selectAll();
		}
	}
	return QDialog::eventFilter(watched,event);
}

void path_search_dlg::init()
{
	QGridLayout* grid = new QGridLayout();

	
	init_start_node();
	init_end_node();
	init_start_angle();
	init_end_angle();

	init_node_list();

	txt_Result_ = new QTextEdit();
	txt_path_= new QListWidget();

	QLabel *lab_node_start = new QLabel(tr("Node start:"));
	QLabel *lab_node_end = new QLabel(tr("Node end:"));

	QLabel *lab_start_angle = new QLabel(tr("start angle:"));
	QLabel *lab_end_angle = new QLabel(tr("end angle:"));

	QLabel *lab_speed = new QLabel(tr("speed:"));
	QLabel *lab_ori = new QLabel(tr("ori:"));
	qedit_speed_ = new QLineEdit();
	qedit_ori_ = new QLineEdit();
	qedit_ori_->setText("0");
	qedit_speed_->setText("0.2");

	btn_exchange_ = new QPushButton(tr("exchange"));
	btn_search_ = new QPushButton(tr("search"));
	btn_show_ = new QPushButton(tr("show"));
	btn_close_ = new QPushButton(tr("close"));

	btn_mvlist_ = new QPushButton(tr(">>"));
	btn_mvdetail_ = new QPushButton(tr("<<"));
	btn_erase_path_ = new QPushButton(tr("erase"));
	btn_load_path_ = new QPushButton(tr("load"));
	btn_save_path_ = new QPushButton(tr("save"));

	btn_run_path_ = new QPushButton(tr("run_path"));
	btn_run_loop_ = new QPushButton(tr("run_loop"));

	connect(btn_exchange_, SIGNAL(clicked(bool)), this, SLOT(ChooseExchange(bool)));
	connect(btn_search_, SIGNAL(clicked(bool)), this, SLOT(ChooseSearch(bool)));
	connect(btn_show_, SIGNAL(clicked(bool)), this, SLOT(ChooseShow(bool)));
	connect(btn_close_, SIGNAL(clicked(bool)), this, SLOT(ChooseClose(bool)));


	connect(btn_mvlist_, SIGNAL(clicked(bool)), this, SLOT(ChooseMvlist(bool)));
	connect(btn_mvdetail_, SIGNAL(clicked(bool)), this, SLOT(ChooseMvdetail(bool)));
	connect(btn_erase_path_, SIGNAL(clicked(bool)), this, SLOT(ChooseErase(bool)));
	connect(btn_load_path_, SIGNAL(clicked(bool)), this, SLOT(ChooseLoad(bool)));
	connect(btn_save_path_, SIGNAL(clicked(bool)), this, SLOT(ChooseSave(bool)));

	connect(btn_run_path_, SIGNAL(clicked(bool)), this, SLOT(ChooseRunPath(bool)));
	connect(btn_run_loop_, SIGNAL(clicked(bool)), this, SLOT(ChooseRunLoop(bool)));
	
	grid->addWidget(lab_node_start,0,0,1,3);
	grid->addWidget(qcmb_start_node_,1,0,1,3);

	grid->addWidget(lab_start_angle,0,3,1,3);
	grid->addWidget(qcmb_start_angle_,1,3,1,3);

	grid->addWidget(lab_node_end,2,0,1,3);
	grid->addWidget(qcmb_end_node_,3,0,1,3);

	grid->addWidget(lab_end_angle,2,3,1,3);
	grid->addWidget(qcmb_end_angle_,3,3,1,3);

	grid->addWidget(btn_exchange_,2,7,1,1);

	grid->addWidget(lab_ori,4,0,1,3);
	grid->addWidget(qedit_ori_,5,0,1,3);

	grid->addWidget(lab_speed,4,3,1,3);
	grid->addWidget(qedit_speed_,5,3,1,3);


	grid->addWidget(txt_Result_,6,0,10,6);
	grid->addWidget(btn_mvlist_,8,7,1,1);
	//grid->addWidget(btn_mvdetail_,9,7,1,1);
	QLabel *lab_path_list = new QLabel(tr("path list:"));
	grid->addWidget(lab_path_list,5,8,1,1);
	grid->addWidget(txt_path_,6,8,10,7);

	grid->addWidget(btn_search_,16,0);
	grid->addWidget(btn_show_,16,2);
	grid->addWidget(btn_run_path_,16,4);
	grid->addWidget(btn_close_,16,5);

	grid->addWidget(btn_erase_path_,16,8);
	grid->addWidget(btn_load_path_,16,9);
	grid->addWidget(btn_save_path_,16,10);
	grid->addWidget(btn_run_loop_,16,11);
	

	setLayout(grid);

	
}

void path_search_dlg::init_node_list()
{
	protobuf_node* p_node = 0;
	p_node = PRO_MANAGE.get_next_node("",-1);
	indicator_.clear();

	while(p_node){
		std::string str = cComm::ConvertToString(p_node->get_id());
		indicator_ << QString::fromStdString(str);
		p_node = PRO_MANAGE.get_next_node("",p_node->get_id());

	}
	qstrlist_start_node_->setStringList(indicator_);
	qcomp_start_node_->setModel(qstrlist_start_node_);
	qcomp_end_node_->setModel(qstrlist_start_node_);

	qcmb_start_node_->clear();
	qcmb_end_node_->clear();
	qcmb_start_node_->addItems(indicator_);
	qcmb_end_node_->addItems(indicator_);
	
}

void path_search_dlg::init_start_node()
{

	qedit_start_node_ = new(std::nothrow) QLineEdit(this);

	qcmb_start_node_ = new(std::nothrow) QComboBox(this);

	qcomp_start_node_ = new(std::nothrow) QCompleter();

	

	//indicator << QString("node_1") << QString("node_2") << QString("node_3");

	qstrlist_start_node_ = new QStringListModel();

	qstrlist_start_node_->setStringList(indicator_);//仅显示indicator里面的

	qcomp_start_node_->setModel(qstrlist_start_node_);

	qcomp_start_node_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_start_node_->clear();

	qcmb_start_node_->addItems(indicator_);

	qcmb_start_node_->setEditable(true);  //设置可编辑

	qcmb_start_node_->setCompleter(qcomp_start_node_); //模糊匹

	qedit_start_node_->setToolTip("select node:");

	qcmb_start_node_->setLineEdit(qedit_start_node_);   //与编辑m_edit绑定
	qcmb_start_node_->setGeometry(11,12,200,22);
	qedit_start_node_->selectAll();
	qcmb_start_node_->installEventFilter(this);
	//qedit_start_node_->setMouseTracking(true);
}

void path_search_dlg::init_end_node()
{

	qedit_end_node_ = new(std::nothrow) QLineEdit(this);

	qcmb_end_node_ = new(std::nothrow) QComboBox(this);

	qcomp_end_node_ = new(std::nothrow) QCompleter();

	QStringList indicator;

	indicator << tr("node_1") << tr("node_2") << tr("node_3");

	qstrlist_end_node_ = new QStringListModel();

	qstrlist_end_node_->setStringList(indicator_);//仅显示indicator里面的

	qcomp_end_node_->setModel(qstrlist_end_node_);

	qcomp_end_node_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_end_node_->clear();

	qcmb_end_node_->addItems(indicator_);

	qcmb_end_node_->setEditable(true);  //设置可编辑

	qcmb_end_node_->setCompleter(qcomp_end_node_); //模糊匹

	qedit_end_node_->setToolTip(tr("select node:"));

	qcmb_end_node_->setLineEdit(qedit_end_node_);   //与编辑m_edit绑定
	qcmb_end_node_->setGeometry(11,12,200,22);
	qedit_end_node_->selectAll();
	qedit_end_node_->installEventFilter(this);
	qcmb_end_node_->setMouseTracking(true);
}


void path_search_dlg::init_start_angle()
{
	qedit_start_angle_ = new(std::nothrow) QLineEdit(this);

	qcmb_start_angle_ = new(std::nothrow) QComboBox(this);

	qcomp_start_angle_ = new(std::nothrow) QCompleter();

	QStringList indicator;

	indicator << QString("") << QString("0") << QString("90") << QString("-90")<< QString("180");

	qstrlist_start_angle_ = new QStringListModel();

	qstrlist_start_angle_->setStringList(indicator);//仅显示indicator里面的

	qcomp_start_angle_->setModel(qstrlist_start_angle_);

	qcomp_start_angle_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_start_angle_->clear();

	qcmb_start_angle_->addItems(indicator);

	qcmb_start_angle_->setEditable(true);  //设置可编辑

	qcmb_start_angle_->setCompleter(qcomp_start_angle_); //模糊匹

	qedit_start_angle_->setToolTip(tr("select node:"));

	qcmb_start_angle_->setLineEdit(qedit_start_angle_);   //与编辑m_edit绑定
	qcmb_start_angle_->setGeometry(11,12,200,22);
	qedit_start_angle_->selectAll();
	qedit_start_angle_->installEventFilter(this);
	qcmb_start_angle_->setMouseTracking(true);
}

void path_search_dlg::init_end_angle()
{
	qedit_end_angle_ = new(std::nothrow) QLineEdit(this);

	qcmb_end_angle_ = new(std::nothrow) QComboBox(this);

	qcomp_end_angle_ = new(std::nothrow) QCompleter();

	QStringList indicator;

	indicator << QString("") << QString("0") << QString("90") << QString("-90")<< QString("180");

	qstrlist_end_angle_ = new QStringListModel();

	qstrlist_end_angle_->setStringList(indicator);//仅显示indicator里面的

	qcomp_end_angle_->setModel(qstrlist_end_angle_);

	qcomp_end_angle_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	qcmb_end_angle_->clear();

	qcmb_end_angle_->addItems(indicator);

	qcmb_end_angle_->setEditable(true);  //设置可编辑

	qcmb_end_angle_->setCompleter(qcomp_end_angle_); //模糊匹

	qedit_end_angle_->setToolTip(tr("select node:"));

	qcmb_end_angle_->setLineEdit(qedit_end_angle_);   //与编辑m_edit绑定
	qcmb_end_angle_->setGeometry(11,12,200,22);
	qedit_end_angle_->selectAll();
	qcmb_end_angle_->installEventFilter(this);
	//qedit_end_angle_->setMouseTracking(true);
}
void path_search_dlg::ChooseExchange(bool flag){
	QString qs;
	qs = qcmb_end_node_->currentText();
	qedit_end_node_->setText(qcmb_start_node_->currentText());
	qedit_start_node_->setText(qs);

	qs = qcmb_end_angle_->currentText();
	qedit_end_angle_->setText(qcmb_start_angle_->currentText());
	qedit_start_angle_->setText(qs);
}

void path_search_dlg::ChooseSearch(bool flag)
{
	QString qs;
	qs = qcmb_start_node_->currentText();
	std::string str_start_node = qs.toStdString();
	str_start_node = cComm::trim(str_start_node);

	qs = qcmb_end_node_->currentText();
	std::string str_end_node = qs.toStdString();
	str_end_node = cComm::trim(str_end_node);

	qs = qcmb_start_angle_->currentText();
	std::string str_start_angle = qs.toStdString();
	str_start_angle = cComm::trim(str_start_angle);

	qs = qcmb_end_angle_->currentText();
	std::string str_end_angle = qs.toStdString();
	str_end_angle = cComm::trim(str_end_angle);

	float f_start_angle = 0;
	float f_end_angle = 0;
	int i_start_node = -1;
	int i_end_node = -1;
	ori_ = ORI_FORWARD;
	l_path_.clear();
	cComm::ConvertToNum(i_start_node,str_start_node);
	cComm::ConvertToNum(i_end_node,str_end_node);


	//angle search
	if (str_start_angle.length()  ){
		if (str_end_angle.length() ){

			cComm::ConvertToNum(f_start_angle,str_start_angle);
			cComm::ConvertToNum(f_end_angle,str_end_angle);

			PATH_SEARCH.search(i_start_node , i_end_node, f_start_angle, f_end_angle);
			ori_ = (ORIENTAION)PATH_SEARCH.get_path_ori(l_path_);
		}else{
			cComm::ConvertToNum(f_start_angle,str_start_angle);

			PATH_SEARCH.search(i_start_node , i_end_node, f_start_angle);

			ori_ = (ORIENTAION)PATH_SEARCH.get_path_ori(l_path_);
		}
		


	}else{
		
		
		PATH_SEARCH.search(i_start_node , i_end_node);
		
		ori_ = (ORIENTAION)PATH_SEARCH.get_path_ori(l_path_);
		
	}


	std::stringstream ss;

	if (ori_ == ORI_FORWARD){
		ss<<"forward"<<" "<<std::endl;
	}else if (ori_ == ORI_BACKWARD){
		ss<<"backward"<<" "<<std::endl;
	}else if (ori_ == ORI_LEFTSHIFT){
		ss<<"leftshift"<<" "<<std::endl;
	}else if (ori_ == ORI_RIGHTSHIFT){
		ss<<"rightshift"<<" "<<std::endl;
	}

	auto it = l_path_.begin();
	for ( ; it != l_path_.end() ; ++it ){
		ss<<*it<<" "<<std::endl;
	}
	txt_Result_->clear();
	txt_Result_->append(QString::fromStdString(ss.str()));
}

void path_search_dlg::ChooseShow(bool flag)
{

}

void path_search_dlg::ChooseClose(bool flag)
{
	accept();
	close();
}
void path_search_dlg::show_path_loop(){

	txt_path_->clear();

	auto it = l_run_path_.begin();
	for ( ; it != l_run_path_.end() ; ++it ){
		std::vector<SPathData> &path = *it;

		std::stringstream ss;
		auto it2 = path.begin();
		for ( ; it2 != path.end() ; ++it2 ){
			SPathData &pdata = *it2;
			ss<<"nf:"<<pdata.node_from_<<" nt:"<<pdata.node_to_<<" speed:"<<pdata.speed_<<" ori:"<<Rad2Deg(pdata.orientation_)<<" ";
		}
		//txt_mult_path_->append(QString::fromStdString(ss.str()));
		txt_path_->addItem(QString::fromStdString(ss.str()));
	}
}
void path_search_dlg::ChooseMvlist(bool flag)
{
	std::vector<SPathData> seg_path;
	if( 0 == get_run_path(seg_path)){
		return;
	}

	l_run_path_.push_back(seg_path);
	show_path_loop();
}

void path_search_dlg::ChooseMvdetail(bool flag)
{
	
}

void path_search_dlg::ChooseErase(bool flag)
{
	int i_row = txt_path_->currentRow();
	std::list<std::vector<SPathData>>::iterator it = l_run_path_.begin();
	int i_cur_row = 0;
	for ( ; it != l_run_path_.end() ; ++it ){
		if (i_row == i_cur_row){
			l_run_path_.erase(it);
			break;
		}
	}
	show_path_loop();
}

void path_search_dlg::ChooseLoad(bool flag)
{

}

void path_search_dlg::ChooseSave(bool flag)
{

}

void path_search_dlg::ChooseRunPath(bool flag)
{

	
	std::vector<SPathData> seg_path;
	if( 0 == get_run_path(seg_path)){
		return;
	}

	if (!p_task_rpc_client_){

		p_task_rpc_client_ = new task_rpc_client();

		std::string str_ip = get_dev_ip();

		p_task_rpc_client_->init(str_ip,RPC_TASK_SER_PORT);

	}

	int i_task_id = p_task_rpc_client_->create_fix_path(seg_path);
}

void path_search_dlg::ChooseRunLoop(bool flag)
{
	init_timer();
}

int path_search_dlg::get_run_path(std::vector<SPathData> &seg_path)
{
	seg_path.clear();

	if (l_path_.size() == 0 ){
		QMessageBox::warning(0, tr("Error"), tr("Please, Search path first!"));
		return 0;
	}

	QString qs = qedit_speed_->text();
	std::string str_speed = qs.toStdString();
	str_speed = cComm::trim(str_speed);

	F32 f_speed = 0;

	//cComm::ConvertToNum(f_speed,str_speed);
	//cComm::RangeIt(f_speed,F32(-0.8),F32(0.8));


	SPathData p_data;


	std::list<int>::iterator it = l_path_.begin();
	int i_start_node = -1;
	int i_end_node = -1;
	for (  ; it != l_path_.end() ; ++it ){

		memset(&p_data,0,sizeof(SPathData));
		if (it == l_path_.begin()){
			i_start_node = *it;
			continue;
		}

		SPos p;
		protobuf_node* p_node = 0;
		p_node = PRO_MANAGE.get_node(CURRENT_PRO,i_start_node);
		if (!p_node){
			seg_path.clear();
			return 0;
		}
		p_node->get_pos(p);

		p_data.tn_from_.x_ = p.x_;
		p_data.tn_from_.y_ = p.y_;
		p_data.tn_from_.th_ = p.th_;
		p_data.node_from_ = p_node->get_id();
		p_data.speed_from_ = f_speed;

		i_end_node = *it;
		p_node = PRO_MANAGE.get_node(CURRENT_PRO,i_end_node);
		i_start_node = i_end_node;

		if (!p_node){
			seg_path.clear();
			return 0;
		}
		p_node->get_pos(p);

		p_data.tn_to_.x_ = p.x_;
		p_data.tn_to_.y_ = p.y_;
		p_data.tn_to_.th_ = p.th_;
		p_data.node_to_ = p_node->get_id();

		if (ORI_FORWARD == ori_){
			p_data.orientation_ = 0;
			p_data.speed_ = f_speed;
		}else if (ORI_BACKWARD == ori_){
			p_data.orientation_ = 0;
			p_data.speed_ = -f_speed;
		}else if (ORI_LEFTSHIFT == ori_){
			p_data.orientation_ = Deg2Rad(90);
			p_data.speed_ = f_speed;
		}else if (ORI_RIGHTSHIFT == ori_){
			p_data.orientation_ = -Deg2Rad(90);
			p_data.speed_ = f_speed;
		}


		protobuf_edge* p_edge = PRO_MANAGE.get_edge(CURRENT_PRO,p_data.node_from_,p_data.node_to_);
		if (p_edge){
			if (ORI_FORWARD == ori_){
				p_data.speed_ = p_edge->forward_speed();
			}else if (ORI_BACKWARD == ori_){
				p_data.speed_ = -p_edge->backward_speed();
			}else if (ORI_LEFTSHIFT == ori_){
				p_data.speed_ = p_edge->leftshift_speed();
			}else if (ORI_RIGHTSHIFT == ori_){
				p_data.speed_ = p_edge->rightshift_speed();
			}
		}
		f_speed = p_data.speed_;

		p_data.complete_pre_ = 0;

		seg_path.push_back(p_data);
	}
	return seg_path.size();
}

std::string path_search_dlg::get_dev_ip()
{
	bool ok = true;
	std::string str_para_ip = "127.0.0.1";

	ip_list_dlg *pDlg = new ip_list_dlg(); 
	pDlg->setModal(true); 
	//pDlg->set_map_list(v_map_list);
	pDlg->exec();

	pDlg->get_sel_file(str_para_ip);

	SDelete(pDlg);
	if (!cComm::Check_ip(str_para_ip)){
		return "";
	}
	return str_para_ip;
}

