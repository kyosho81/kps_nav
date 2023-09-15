#ifndef _FILE_LIST_DLG_WANGHONGTAO_2018_03_06_
#define _FILE_LIST_DLG_WANGHONGTAO_2018_03_06_

#include <QtGui>
#include <QDialog>
#include <QtGui/QComboBox>


class file_list_dlg : public QDialog
{
	Q_OBJECT

public:
	file_list_dlg(QWidget *parent = 0);
	~file_list_dlg();

	void set_file_list(const std::vector<std::string> cv_file_list);
	void set_map_list(const std::vector<std::string> cv_file_list);
	void get_sel_file(std::string &file_nm);
	void set_file_type(std::string file_type);

protected:

private:

	//std::vector<std::string> cv_file_list_;
	std::string sel_file_nm_;
	std::string sel_file_type_;

	QPushButton* btn_Ok_;	//test_model
	QPushButton* btn_Cancel_;	//enable


	QComboBox* comb_file_;
	QListWidget* list_widget_;

	private slots:

		void ChooseOk( bool flag );
		void ChooseCancel(bool flag );
	
		
};
#endif//_FILE_LIST_DLG_WANGHONGTAO_2018_03_06_