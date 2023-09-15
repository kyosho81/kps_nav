#ifndef _TF_2D_SERVER_KYOSHO_20210704_
#define _TF_2D_SERVER_KYOSHO_20210704_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"


class tf_2d
{
public:
	tf_2d(){};
	~tf_2d(){};

	std::string parent_;	//where layer_diff_'s original 
	std::string child_;    //

	SPos pos_;	//clild in parent tf like : base_laer in base link

};



class tf_2d_server
{
public:

	tf_2d_server();
	~tf_2d_server();

	void set_base_laser_in_base_link(const F32& x,  const F32& y , const F32& th);
	void tf_base_laser_to_base_link(VecPosition& p);
	void tf_base_laser_to_base_link(SPos& pos);
	void tf_base_link_to_base_laser(VecPosition& p);

	bool tf_laser_to_odom(SPos& p);
	bool tf_odom_to_laser(SPos& p);

protected:
private:
	typedef std::map<std::string,tf_2d> M_tf_2d;
	M_tf_2d tf_2d_list_;
	
	bool get_tf( std::string parent,std::string child,SPos& pos );
	bool create_tf(std::string parent,std::string child,const SPos& pos);
};

typedef boost::serialization::singleton<tf_2d_server> Singleton_TF;

#define TF_SERVER Singleton_TF::get_mutable_instance()



#endif//_TF_2D_SERVER_KYOSHO_20210704_
