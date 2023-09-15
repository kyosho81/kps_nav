#ifndef QWT_PLOT_20120604_
#define QWT_PLOT_20120604_


#include <qwt_plot.h>
#include <qrect.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_magnifier.h>
#include <qwt_picker_machine.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_plot_rescaler.h>

#ifndef Q_MOC_RUN
#include <boost/thread.hpp>
#endif

#include <string>
#include <map>

class MainWindow;

class PlotData{

public:
	PlotData():
	  data_x_(NULL),
		  data_y_(NULL),
		  data_x_out_(NULL),
		  data_y_out_(NULL),
		  data_deep_(0),
		  current_index_(-1),
		  index_count_(0),
		  name_(""),
		  range_y_max_(10),
		  range_y_min_(-10)

	  {
		  id_ = GetID();
	  };

	  ~PlotData();

	  void Init(long data_deep);

	  long GetPlotData();

	  void InsertData(const double &x,const double &y,bool bReSetRange = true);

	  void SetRange_MaX(const double &value){
		  boost::mutex::scoped_lock lock(mutex_range_);
		  if (value > range_x_max_)
		  {
			  range_x_max_ = value;
		  }
		  // 		}else if(value < range_x_min_){
		  // 			range_x_min_ = value;
		  // 		}
	  };
	  void SetRange_Min(const double &value){
		  boost::mutex::scoped_lock lock(mutex_range_);
		  range_x_min_ = value;

	  }
	  void GetRange_X(double &v_min,double &v_max){
		  boost::mutex::scoped_lock lock(mutex_range_);
		  v_min = range_x_min_;
		  v_max = range_x_max_;
	  };


	  void SetRange_Y(const double &value){
		  boost::mutex::scoped_lock lock(mutex_range_);
		  if (value > range_y_max_)
		  {
			  range_y_max_ = value;
		  }else if(value < range_y_min_){
			  range_y_min_ = value;
		  }
	  };

	  void GetRange_Y(double &v_min,double &v_max){
		  boost::mutex::scoped_lock lock(mutex_range_);
		  v_min = range_y_min_;
		  v_max = range_y_max_;
	  };


	  double* data_x_out_;
	  double* data_y_out_;

	  int id_;
	  std::string name_;

	  long data_deep_;
	  long index_count_;	//数据有过已经循环记录
private:

	static int id_all_;
	static int GetID(){
		++id_all_;
		return id_all_;
	};
	void DelData();

	boost::mutex mutex_;
	boost::mutex mutex_range_;

	double* data_x_;
	double* data_y_;


	double range_y_max_;
	double range_y_min_;

	double range_x_max_;
	double range_x_min_;

	long current_index_;

};
class Zoomer: public QwtPlotZoomer
{
public:
	Zoomer(int xAxis, int yAxis, QWidget *canvas):
	  QwtPlotZoomer(xAxis, yAxis, canvas)
	  {
		  setTrackerMode(QwtPicker::AlwaysOff);
		  setRubberBand(QwtPicker::NoRubberBand);

		  // RightButton: zoom out by 1
		  // Ctrl+RightButton: zoom out to full size

		  setMousePattern(QwtEventPattern::MouseSelect2,
			  Qt::RightButton, Qt::ControlModifier);
		  setMousePattern(QwtEventPattern::MouseSelect3,
			  Qt::RightButton);
	  };
};
class Plot;
class Picker : public QwtPlotPicker{
public:
	Picker(int xAxis, int yAxis,RubberBand rubberBand, DisplayMode trackerMode,QWidget *canv)
		:QwtPlotPicker(xAxis,yAxis,rubberBand,trackerMode,canv){
			setStateMachine(new QwtPickerDragPointMachine());
			setRubberBandPen(QColor(Qt::green));
			setRubberBand(QwtPicker::CrossRubberBand);
			setTrackerPen(QColor(Qt::black));
			//show_pick = true;
	};
	~Picker(){};
private:

};

class Plot : public QwtPlot
{
	Q_OBJECT

public:

	Plot(QWidget *parent = NULL);
	~Plot(){
		std::map<int,PlotData*>::iterator it = m_plot_data_.begin();
		for (;it != m_plot_data_.end();++it)
		{
			delete it->second;
			it->second = NULL;
		}

		std::map<int,QwtPlotCurve*>::iterator it2 = m_plot_qt_.begin();
		for (;it2 != m_plot_qt_.end();++it2)
		{
			delete it2->second;
			it2->second = NULL;
		}
	};
	void SetMainWnd(MainWindow* wnd){
		wnd_ = wnd;
	};
	int AddPlot(std::string str_name,long l_data_deep);
	void AddPlotData(int id,const double &x,const double &y);
	void DelPlot(int id);
	void DelAll();
private:
	MainWindow* wnd_;

	void timerEvent(QTimerEvent *);
	void panned_slot(int, int);

	std::map<int,PlotData*> m_plot_data_;
	std::map<int,QwtPlotCurve*> m_plot_qt_;

	bool key_press_;
	QwtPlotRescaler * plot_rescaler;
	//	void	mousePressEvent ( QMouseEvent * event );
	//	void	mouseReleaseEvent ( QMouseEvent * event );
	void	keyPressEvent ( QKeyEvent * event );
public:
	Zoomer* d_zoomer;
	Picker* d_picker;
};

#endif //QWT_PLOT_20120604_