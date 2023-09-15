#include "Comm/Comm.h"
#include "property/qtvariantproperty.h"

#include "shape_dlg.h"


shape_dlg::shape_dlg( QWidget *parent /*= 0*/ )
{
	qedit_para_ = new QLineEdit();

	btn_Refresh_ = new QPushButton(tr("Refresh"));
	btn_Collision_ = new QPushButton(tr("Collision"));
	btn_Close_ = new QPushButton(tr("Close"));

	str_name_ = "";
	p_item_ = 0;
	
	QLineEdit* m_edit = new(std::nothrow) QLineEdit(this);

	qcom_shape_ = new(std::nothrow) QComboBox(this);

	qcompleter_ = new(std::nothrow) QCompleter();


	indicator_ << QString("dev_robot_shape") ;

	qstringlistmodel_ = new QStringListModel();

	qstringlistmodel_->setStringList(indicator_);//仅显示indicator里面的

	qcompleter_->setModel(qstringlistmodel_);

	qcompleter_->setCaseSensitivity(Qt::CaseInsensitive);//大小写不敏感

	//qcompleter_->setFilterMode(Qt::MatchRecursive);//匹配规则：包含则匹配

	//m_completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

	//m_edit->setCompleter(m_completer);

	qcom_shape_->clear();

	qcom_shape_->addItems(indicator_);

	qcom_shape_->setEditable(true);  //设置可编辑

	qcom_shape_->setCompleter(qcompleter_); //模糊匹

	m_edit->setToolTip("shape edit:");

	qcom_shape_->setLineEdit(m_edit);   //与编辑m_edit绑定
	qcom_shape_->setGeometry(11,12,300,22);
	m_edit->selectAll();

	
	QLabel *label = new QLabel(tr("select shape:")); 
	
	/////////////////////////
	QLabel *lab_shape = new QLabel(tr("shape:")); 
	qedit_para_ = new QLineEdit();
	qedit_para_->setGeometry(11,12,800,22);
	
	/////////////////////
	

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(label,0,0,1,1);
	grid->addWidget(qcom_shape_,0,1,1,5);
	grid->addWidget(lab_shape,1,0,1,1);
	grid->addWidget(qedit_para_,1,1,1,5);

	grid->addWidget(btn_Refresh_,2,0,1,1);
	grid->addWidget(btn_Collision_,2,1,1,1);
	grid->addWidget(btn_Close_,2,5,1,1);


	setLayout(grid);

	connect(btn_Refresh_, SIGNAL(clicked(bool)), this, SLOT(ChooseRefresh(bool)));
	connect(btn_Collision_, SIGNAL(clicked(bool)), this, SLOT(ChooseCollision(bool)));
	connect(btn_Close_, SIGNAL(clicked(bool)), this, SLOT(ChooseClose(bool)));
	
	//connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentIndexChanged(int)));
	connect(qcom_shape_,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCombChanged(QString)));

}

shape_dlg::~shape_dlg()
{

}

void shape_dlg::bind_show(boost::function<void(std::string ,const std::vector<Sxy>)> fnc)
{
	fnc_show_ = fnc;
}
std::vector<Sxy> shape_dlg::split_para(std::string str_shape)
{
	std::vector<Sxy> shape;

	std::vector<std::string> vres;
	cComm::SplitString(str_shape,";",vres);
	std::vector<std::string>::iterator it = vres.begin();
	for ( ; it !=  vres.end() ; ++it)
	{
		std::string str = *it;
		std::vector<std::string> vpos;
		cComm::SplitString(str,",",vpos);

		if (vpos.size() > 1)
		{
			Sxy xy;
			cComm::ConvertToNum(xy.x_,vpos[0]);
			cComm::ConvertToNum(xy.y_,vpos[1]);
			shape.push_back(xy);
		}
	}

	return shape;
}
void shape_dlg::ChooseRefresh( bool flag )
{
	QString str;
	str = qcom_shape_->currentText();
	str_name_ = str.toStdString();

	bool b_found = false;
	std::vector<std::pair<std::string, QtVariantProperty *>>::iterator it = v_shape_pro_.begin();
	for ( ; it != v_shape_pro_.end(); ++it ){
		if (str_name_ == it->first){
			b_found = true;
			break;
		}
	}
	if (b_found){

		p_item_ = it->second;

		QString qs = qedit_para_->text();
		p_item_->setValue(qs);
		std::string str_shape = p_item_->value().toString().toStdString();
		std::vector<Sxy> v_shape = split_para(str_shape);

		if ( fnc_show_){
			fnc_show_(str_name_,v_shape);
		}

	}
}
void shape_dlg::ChooseCollision( bool flag )
{

}

void shape_dlg::ChooseClose( bool flag )
{
	accept();
	close();
}

void shape_dlg::onCombChanged(const QString &qs)
{
	std::string str_name_ = qs.toStdString();

	bool b_found = false;
	std::vector<std::pair<std::string, QtVariantProperty *>>::iterator it = v_shape_pro_.begin();
	for ( ; it != v_shape_pro_.end() ; ++it ){
		if (str_name_ == it->first ){
			b_found = true;
			break;
		}
	}
	if ( b_found ){
		p_item_ = it->second;

		std::string str_shape = p_item_->value().toString().toStdString();
		qedit_para_->setText(QString::fromStdString(str_shape));
		//std::vector<Sxy> v_shape = split_para(str_shape);
	}
}

void shape_dlg::set_shape_list( std::vector<std::pair<std::string, QtVariantProperty *>> v_shape_pro )
{
	indicator_.clear();
	v_shape_pro_ = v_shape_pro;

	std::vector<std::pair<std::string, QtVariantProperty *>>::iterator it = v_shape_pro_.begin();
	for ( ; it != v_shape_pro_.end() ; ++it)
	{
		indicator_ << QString::fromStdString(it->first);
	}

	qstringlistmodel_->setStringList(indicator_);
	qcompleter_->setModel(qstringlistmodel_);

	qcom_shape_->clear();
	qcom_shape_->addItems(indicator_);

}

void shape_dlg::get_sel_shape( QtVariantProperty* p_item )
{
	p_item = p_item_;
}


