#include "Comm/Comm.h"

#include "file_list_dlg.h"


file_list_dlg::file_list_dlg( QWidget *parent /*= 0*/ )
{
	btn_Ok_ = new QPushButton(tr("Ok"));
	btn_Cancel_ = new QPushButton(tr("Cancel"));

	sel_file_nm_ = "";

	list_widget_ = new QListWidget();

	comb_file_ = new QComboBox();
	comb_file_->setMaxVisibleItems(6);
	comb_file_->setModel(list_widget_->model());
	comb_file_->setView(list_widget_);
	comb_file_->setEditable(true);

	QVBoxLayout* v_layout = new QVBoxLayout();
	QLabel *label = new QLabel(tr("select file:")); 
	v_layout->addWidget(label);
	v_layout->addWidget(comb_file_);

	QHBoxLayout* h_layout = new QHBoxLayout();
	h_layout->addWidget(btn_Ok_);
	h_layout->addWidget(btn_Cancel_);
	v_layout->addLayout(h_layout);

	setLayout(v_layout);

	connect(btn_Ok_, SIGNAL(clicked(bool)), this, SLOT(ChooseOk(bool)));
	connect(btn_Cancel_, SIGNAL(clicked(bool)), this, SLOT(ChooseCancel(bool)));

	sel_file_type_ = "";
}

file_list_dlg::~file_list_dlg()
{

}

void file_list_dlg::ChooseOk( bool flag )
{
	QString str;
	str = comb_file_->currentText();
	sel_file_nm_ = str.toStdString();

	accept();
	close();
}

void file_list_dlg::ChooseCancel( bool flag )
{
	accept();
	close();
}

void file_list_dlg::set_file_list( const std::vector<std::string> cv_file_list )
{
	std::vector<std::string>::const_iterator cit = cv_file_list.cbegin();
	for ( ; cit != cv_file_list.cend() ; ++cit)
	{
		std::string str = *cit;
		if ( sel_file_type_.length() > 0 )
		{
			if (sel_file_type_ == cComm::Get_FileType(str))
			{
				str = cComm::Get_FileName(str) + "." + cComm::Get_FileType(str);
				comb_file_->addItem(str.c_str());
			}
			
		}else{
			str = cComm::Get_FileName(str) + "." + cComm::Get_FileType(str);
			comb_file_->addItem(str.c_str());
		}
		
	}
	
}

void file_list_dlg::set_map_list( const std::vector<std::string> cv_file_list )
{
	std::vector<std::string>::const_iterator cit = cv_file_list.cbegin();
	for ( ; cit != cv_file_list.cend() ; ++cit)
	{
		std::string str = *cit;
		std::string str_type = cComm::Get_FileType(str);
		if(("pgm" == str_type) || ("maproto" == str_type)){
			str = cComm::Get_FileName(str) + "." + cComm::Get_FileType(str);
			comb_file_->addItem(str.c_str());
		}
		
	}

}
void file_list_dlg::get_sel_file( std::string &file_nm )
{
	file_nm = sel_file_nm_;
}

void file_list_dlg::set_file_type( std::string file_type )
{
	sel_file_type_ = file_type;
}
