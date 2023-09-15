#ifndef _MY_TF_KYOSHO_20150906_
#define _MY_TF_KYOSHO_20150906_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"



class my_tf
{
public:
	my_tf();
	~my_tf();

	void getLaserInBaselink( F32& x, F32& y ,F32 dx, F32 dy,F32 th );
	void getBaselinkInLaser( F32& x, F32& y ,F32 dx, F32 dy,F32 th );

	void tf_l2b( F32* out_x, F32* out_y ,F32* in_x ,F32 dx, F32 dy,F32* th ,U32 size );
	void tf_b2c( F32* out_x, F32* out_y ,F32* in_x, F32* in_y ,F32 th ,U32 size );
	void tf_l2c( F32* out_x, F32* out_y ,const F32* in_x ,const F32 dx, F32 dy,const F32* th ,const F32& rotation,U32 size );
	void tf_b2w( F32* out_x, F32* out_y ,F32* in_x, F32* in_y ,F32* dx, F32* dy,F32* sin_th,F32* cos_th ,U32 size );
	//void setLaserInBaselink(F32 x ,F32 y ,F32 th);

	//void getDLaserInBaselink(F32 &x, F32 &y,F32 amcl_rotation);
	//void getDLaserInBaseOdom(F32 &x,F32 &y,F32 ox,F32 oy,F32 oth);
	//
	//void getBaselinkInLaser( VecPosition &npos );
	////set laser angle by begin angle and resolution
	//void setLaserPara(const SLaser &lpara);
	//void getLaserXY(SLaserXY &laserxy,const SLaser &lpara,F32 amcl_rotation);
	void setLaserInBaseLink(const SLaser &laser,const F32& x,const F32& y,const F32& th);
	void tf_l2lm( SLaserXY& des,const SLaser& src,const F32& odom_rotation );
	void tf_l2lm( SLaserXY& des,const SLaser& src,const F32& odom_rotation , const F32 &roi);
	void tf_l2lm( SLaserXY& des,const SLaser& src,const SPos& robot_pos , const F32 &roi);

private://para


	

protected:
private:

 	SPos laser_pos_;	//base_laer in base link
 
 	F32 angle_list_[LASER_COUNT];
 
 	F32 cos_laser_[LASER_COUNT];
 	F32 sin_laser_[LASER_COUNT];
};

class layer_tf
{
public:
	layer_tf();
	~layer_tf();

	std::string parent_;	//where layer_diff_'s original 
	std::string child_;    //

	S64 diff_x_;
	S64 diff_y_;

};

class map_tf_server
{

public:

	map_tf_server();
	~map_tf_server();

	bool create_tf(std::string parent,std::string child,S64 diff_x,S64 diff_y);

	void get_tf(std::string parent,std::string child,S64 &diff_x,S64 &diff_y);


private:
	
	typedef std::map<std::string,layer_tf> LayerMap;
	LayerMap layer_list_;


};



#endif//_MY_TF_KYOSHO_20150906_
