#ifndef _SHAPE_LIST_DLG_WANGHONGTAO_2018_03_06_
#define _SHAPE_LIST_DLG_WANGHONGTAO_2018_03_06_

#include <QtGui>
#include <QDialog>
#include <QtGui/QComboBox>

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include "boost/unordered/unordered_map.hpp"
#include "robot/RobotStruct.h"
#endif

class QComboBox;
class QCompleter;
class QStringListModel;
class QtVariantProperty;

class shape_dlg : public QDialog
{
	Q_OBJECT

public:
	shape_dlg(QWidget *parent = 0);
	~shape_dlg();

	void bind_show( boost::function<void(std::string ,const std::vector<Sxy>)> fnc);
	
	void set_shape_list(std::vector<std::pair<std::string, QtVariantProperty *>> v_shape_pro);
	void get_sel_shape(QtVariantProperty* p_item);

protected:

private:
	std::vector<Sxy> split_para(std::string str_shape);

	//std::vector<std::string> cv_file_list_;
	std::string str_name_;
	QtVariantProperty* p_item_;

	std::vector<std::pair<std::string, QtVariantProperty *>> v_shape_pro_;
	boost::function<void(std::string ,const std::vector<Sxy>)> fnc_show_;
	
	QPushButton* btn_Refresh_;	//refresh show
	QPushButton* btn_Collision_;	    //save cfg
	QPushButton* btn_Close_;	//close


	QComboBox* qcom_shape_;
	QCompleter* qcompleter_;
	QStringListModel* qstringlistmodel_;
	QStringList indicator_;

	QListWidget* list_widget_;

	QLineEdit* qedit_para_;

	private slots:

		void ChooseRefresh(bool flag );
		void ChooseCollision( bool flag );
		void ChooseClose(bool flag );
	
		void onCombChanged(const QString &qs);
};
#endif//_SHAPE_LIST_DLG_WANGHONGTAO_2018_03_06_