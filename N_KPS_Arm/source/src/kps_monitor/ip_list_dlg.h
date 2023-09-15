#ifndef _IP_LIST_DLG_WANGHONGTAO_2018_03_06_
#define _IP_LIST_DLG_WANGHONGTAO_2018_03_06_

#include <QtGui>
#include <QDialog>
#include <QtGui/QComboBox>

class QComboBox;
class QCompleter;
class QStringListModel;

class ip_list_dlg : public QDialog
{
	Q_OBJECT

public:
	ip_list_dlg(QWidget *parent = 0);
	~ip_list_dlg();


	void get_sel_file(std::string &file_nm);
	void set_file_type(std::string file_type);

protected:

private:
	bool load_ip_para();
	bool save_ip_para();
	bool swap_ip();

	std::string str_ip_para_;
	std::map<std::string,int> m_ip_cnt_;
	std::list<std::string> l_ip_;
	std::string str_last_ip_;

private:

	//std::vector<std::string> cv_file_list_;
	std::string sel_file_nm_;
	std::string sel_file_type_;

	QPushButton* btn_Ok_;	//test_model
	QPushButton* btn_Cancel_;	//enable


	QComboBox* qcom_ip_;
	QCompleter* qcompleter_;
	QStringListModel* qstringlistmodel_;

	QListWidget* list_widget_;

	private slots:

		void ChooseOk( bool flag );
		void ChooseCancel(bool flag );
		void onCurrentStringChanged(QString);

		//bool eventFilter(QObject * watched , QEvent * event);

		
};
#endif//_IP_LIST_DLG_WANGHONGTAO_2018_03_06_