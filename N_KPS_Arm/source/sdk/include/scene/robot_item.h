#ifndef _ROBOT_ITEM_KYOSHO_20180715_
#define _ROBOT_ITEM_KYOSHO_20180715_

#ifndef Q_MOC_RUN 
#include <boost/thread.hpp>
#include "robot/RobotStruct.h"
#include "Comm/buffer_con.hpp"
#endif

#include <QGraphicsItem>

#include "robot/RobotStruct.h"

class robot_item  : public QObject , public QGraphicsItem
{
	Q_OBJECT

public:
	robot_item(QGraphicsItem *parent = 0);
	~robot_item();


	void set_robot_shape(const std::vector<SVec> v_robot_shape);
	void set_shape(std::string str_nm, const std::vector<Sxy> v_shape);
	void set_amcl_pos(SPos amcl_pos);
	void set_amcl_pos_ref(SPos amcl_pos);
	void set_ref_pos(SPos ref_pos);
	void set_est_pos(const SPos &est_pos, const bool &b_show);
	void set_speed(const double &vx,const double &vy,const double &vw);
	void set_laser( const std::vector<SLaser_used> &laser_data);
	void set_laser( const SLaser &laser_data);
	void set_laser(const SLaserXY &laserxy);
	void set_laser( const SLaser_Ex &laser_data_ex);
	void set_laser( const SLaser_Ex2 &laser_data_ex2);
	void set_laser( const SLaserXYEx &laser_cab_ex);
	void set_laser_ex_ref( const SLaser_Ex_Ref &laser_ex_ref);
	void set_laser_seg( const SLaser &laser_data);

	void set_laser_para(const SLaser_para &laser_para);

	void set_chk_laser_range( const SCHK_LASER_RANGE &chk_laser_range );
	void set_range_show(  const std::vector<Range_type> &v_type );

	void set_reflect_feature( const std::vector<SVec> &reflect_feature);
	void set_scan_reflector( const SReflector &ref );

	void set_line(const std::vector<SLine2P> &ln);
	void set_sm_ori(SLine2P ln_pa);
	void set_steering( std::vector<SSteering> v_st );

protected:
private:
	

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	
private:

	void set_pos(const SPos &pos);

	QPainterPath painter_robot_shape_path_;
	QPainterPath painter_speed_;
	QPainterPath painter_line_;
	QPainterPath painter_steering_;

	QRectF bounding_rect_;

	//QPainterPath painter_shape_;
	std::map<std::string,QPolygonF> m_shape_;

private://laser data
	boost::mutex paint_mutex_;
	QPainterPath painter_laser_;
	QPainterPath painter_reflect_feature_;
	//laser para
	SLaser_para laser_para_;
	
	void show_intensies_laser(QPainter *painter);
	void show_seg_laser(QPainter *painter);
	SBuffer<SLaser> laser_seg_;
	void show_seg_laser_ex(QPainter *painter);
	SBuffer<SLaser_Ex> laser_intensities_;
	SBuffer<SLaser_Ex2> laser_intensities2_;

	void show_shape(QPainter *painter);

	boost::mutex paint_range_mutex_;
	std::map<Range_type,QPainterPath> m_painter_check_laser_;
	std::map<Range_type,int> m_show_type_;

	

private://mouse move estimate pos

	THSafe<bool> th_show_est_;
	F32 refect_pillar_dia_;

private://show amcl ref pos
	void draw_triangle(QPainter *painter , SPos pos);
	bool get_amcl_in_ref( SPos &loc_diff );

	CSBuffer<SPos,1> buf_amcl_pos_;
	CSBuffer<SPos,1> buf_ref_pos_;


private: //show steering
	F32 steering_radius_;
	F32 steering_x_;
	F32 steering_y_;
	F32 steering_w_ ;
	F32 steering_h_ ;

};

#endif//_ROBOT_ITEM_KYOSHO_20180715_