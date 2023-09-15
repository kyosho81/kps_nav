#include "Comm/Comm.h"

#include "ip_list_dlg.h"


ip_list_dlg::ip_list_dlg( QWidget *parent /*= 0*/ )
{
	btn_Ok_ = new QPushButton(tr("Ok"));
	btn_Cancel_ = new QPushButton(tr("Cancel"));

	sel_file_nm_ = "";
	str_ip_para_ = ".//cfg//ip.txt";
	
	QLineEdit* m_edit = new(std::nothrow) QLineEdit(this);

	qcom_ip_ = new(std::nothrow) QComboBox(this);

	qcompleter_ = new(std::nothrow) QCompleter();

	QStringList indicator;
	load_ip_para();
	auto it = l_ip_.begin();
	for ( ; it != l_ip_.end() ; ++it ){
		//indicator << QString("127.0.0.1") << QString("192.168.1.99") << QString("106.12.90.152")<< QString("192.168.2.165");
		indicator << QString::fromStdString(*it);
	}
	
	if (l_ip_.size() == 0){
		indicator << QString("127.0.0.1") << QString("192.168.1.99") << QString("106.12.90.152")<< QString("192.168.2.165");
	}
	qstringlistmodel_ = new QStringListModel();

	qstringlistmodel_->setStringList(indicator);//仅显示indicator里面的

	qcompleter_->setModel(qstringlistmodel_);

	qcompleter_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	//qcompleter_->setFilterMode(Qt::MatchRecursive);//匹配规则：包含则匹配

	//m_completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

	//m_edit->setCompleter(m_completer);

	qcom_ip_->clear();

	qcom_ip_->addItems(indicator);

	qcom_ip_->setEditable(true);  //设置可编辑

	qcom_ip_->setCompleter(qcompleter_); //模糊匹

	m_edit->setToolTip("ip add:");

	qcom_ip_->setLineEdit(m_edit);   //与编辑m_edit绑定
	qcom_ip_->setGeometry(11,12,200,22);
	m_edit->selectAll();

	QVBoxLayout* v_layout = new QVBoxLayout();
	QLabel *label = new QLabel(tr("select ip:")); 
	v_layout->addWidget(label);
	v_layout->addWidget(qcom_ip_);

	QHBoxLayout* h_layout = new QHBoxLayout();
	h_layout->addWidget(btn_Ok_);
	h_layout->addWidget(btn_Cancel_);
	v_layout->addLayout(h_layout);

	setLayout(v_layout);

	connect(btn_Ok_, SIGNAL(clicked(bool)), this, SLOT(ChooseOk(bool)));
	connect(btn_Cancel_, SIGNAL(clicked(bool)), this, SLOT(ChooseCancel(bool)));

	connect(qcom_ip_,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCurrentStringChanged(QString)));

	sel_file_type_ = "";

}

void ip_list_dlg::onCurrentStringChanged( QString )
{
	
}

ip_list_dlg::~ip_list_dlg()
{

}
// 
// bool ip_list_dlg::eventFilter(QObject * watched , QEvent * event)
// {
//  
//  	//	if (QEvent::MouseButtonPress == event->type()){
//  	if (QEvent::FocusIn == event->type()){
//  		if (watched == qcom_ip_){
//  			//init_node_list();
//  			str_last_ip_ = qcom_ip_->currentText().toStdString();
//  		}
// 	}else if (QEvent::FocusOut == event->type()){
// 		std::string str_new_ip_ = qcom_ip_->currentText().toStdString();
// 		if (str_last_ip_ != str_new_ip_){
// 			
// 			auto it_last = l_ip_.begin();
// 			for (; it_last !=l_ip_.end(); ++it_last){
// 				if (*it_last == str_last_ip_){
// 					break;
// 				}
// 			}
// 
// 			auto it_new = l_ip_.begin();
// 			for (; it_new !=l_ip_.end(); ++it_new){
// 				if (*it_new == str_new_ip_){
// 					break;
// 				}
// 			}
// 
// 			if ( (it_last != l_ip_.end()) && (it_new != l_ip_.end())){
// 				std::string tmp = *it_last;
// 				*it_last = *it_new ;
// 				*it_new = tmp;
// 			}
// 		}
// 	}
//  	return QDialog::eventFilter(watched,event);
// }
void ip_list_dlg::ChooseOk( bool flag )
{
	QString str;
	str = qcom_ip_->currentText();
	if (cComm::Check_ip(str.toStdString())){
		
		int i_msize = m_ip_cnt_.size();
		m_ip_cnt_[str.toStdString()] ;
		//new ip add
		if (i_msize != m_ip_cnt_.size()){
			l_ip_.push_front(str.toStdString());
			save_ip_para();
		}else{
			swap_ip();
			save_ip_para();
		}
		
	}
	sel_file_nm_ = str.toStdString();

	accept();
	close();
}

void ip_list_dlg::ChooseCancel( bool flag )
{
	accept();
	close();
}

void ip_list_dlg::get_sel_file( std::string &file_nm )
{
	file_nm = sel_file_nm_;
}

void ip_list_dlg::set_file_type( std::string file_type )
{
	sel_file_type_ = file_type;
}

bool ip_list_dlg::load_ip_para()
{
	std::ifstream iff(str_ip_para_.c_str(), std::ios::in |std::ios::binary);

	if (!iff.is_open())
	{
		std::cout<<">>>>>>>>>>>>>>>>>>>>load_ip_para file err!"<<str_ip_para_<<std::endl;
		return false;
	}

	m_ip_cnt_.clear();
	l_ip_.clear();


	std::string str_ln;

	while ( std::getline(iff, str_ln) ){
		if (!cComm::Check_ip(str_ln)){
			continue;
		}
		
		m_ip_cnt_[str_ln];
		l_ip_.push_back(str_ln);
	}

	return true;
}

bool ip_list_dlg::save_ip_para()
{
	std::ofstream off(str_ip_para_.c_str(), std::ios::trunc | std::ios::binary);
	if (!off.is_open())
	{
		std::cout<<">>>>>>>>>>>>>>>>>>>>save_ip_para file err!"<<str_ip_para_<<std::endl;
		return false;
	}
	int icount = 0; 
	auto it = l_ip_.begin();
	for ( ; it != l_ip_.end() ; ++it ){
		
		off<<*it<<std::endl;
	}
	off.close();

	return true;
}

bool ip_list_dlg::swap_ip()
{
	std::string str_new_ip_ = qcom_ip_->currentText().toStdString();
	
	auto it_new = l_ip_.begin();
	for (; it_new !=l_ip_.end(); ++it_new){
		if (*it_new == str_new_ip_){
			break;
		}
	}

	if(it_new != l_ip_.end()){
		l_ip_.erase(it_new);
		l_ip_.push_front(str_new_ip_);
	}

// 	if (str_last_ip_ != str_new_ip_){
// 
// 		auto it_last = l_ip_.begin();
// 		for (; it_last !=l_ip_.end(); ++it_last){
// 			if (*it_last == str_last_ip_){
// 				break;
// 			}
// 		}
// 
// 		auto it_new = l_ip_.begin();
// 		for (; it_new !=l_ip_.end(); ++it_new){
// 			if (*it_new == str_new_ip_){
// 				break;
// 			}
// 		}
// 
// 		if ( (it_last != l_ip_.end()) && (it_new != l_ip_.end())){
// 			std::string tmp = *it_last;
// 			*it_last = *it_new ;
// 			*it_new = tmp;
// 		}else 
// 	}
// 	str_last_ip_ = str_new_ip_;
	return true;
}
