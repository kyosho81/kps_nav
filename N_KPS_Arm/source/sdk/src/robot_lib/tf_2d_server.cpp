#include <string.h>
#include "Geometry.h"
#include "math.h"
#include "tf_2d_server.h"



tf_2d_server::tf_2d_server()
{

}

tf_2d_server::~tf_2d_server()
{

}

bool tf_2d_server::create_tf( std::string parent,std::string child,const SPos& pos )
{
	M_tf_2d::iterator it = tf_2d_list_.find(child);
	if (it != tf_2d_list_.end())
	{
		tf_2d &tf(it->second);
		if (tf.parent_ == parent)
		{
			tf.pos_ = pos;
		}
		else{
			std::cout<<" tf 2d err: only can have one parent"<<std::endl;
			return false;
		}
	}else{

		tf_2d tf;
		tf.child_ = child;
		tf.parent_ = parent;
		tf.pos_ = pos;

		tf_2d_list_[child] = tf;
	}


	return true;
}

bool tf_2d_server::get_tf( std::string parent,std::string child,SPos& pos )
{
	pos.x_ = 0;
	pos.y_ = 0;
	pos.th_ = 0;
	tf_2d_server::M_tf_2d::iterator it = tf_2d_list_.find(child);

	if(it != tf_2d_list_.end()){
		tf_2d &tf(it->second);
		if(tf.parent_ ==  parent){
			pos = tf.pos_;
			return true;
		}
	}
	return false;
}

void tf_2d_server::set_base_laser_in_base_link( const F32& x,  const F32& y , const F32& th)
{
	SPos pos;
	pos.x_ = x;
	pos.y_ = y;
	pos.th_ = th;
	create_tf(BASE_LINK,BASE_LASER,pos);
}

void tf_2d_server::tf_base_laser_to_base_link( VecPosition& p)
{
	SPos tf_pos;
	get_tf(BASE_LINK,BASE_LASER,tf_pos);

	
	p.rotate(Rad2Deg(tf_pos.th_));
	
	VecPosition ptf(tf_pos.x_,tf_pos.y_);
	p += ptf;


}

void tf_2d_server::tf_base_laser_to_base_link(SPos& pos)
{
	SPos tf_pos;
	get_tf(BASE_LINK,BASE_LASER,tf_pos);

	double wx = 0;
	double wy = 0;
	double wa = 0;
	Local2World(pos.x_, pos.y_, pos.th_ ,tf_pos.x_, tf_pos.y_ , tf_pos.th_ , wx , wy ,wa );
	pos.x_ = wx;
	pos.y_ = wy;
	pos.th_ = wa;

}

// p is laser in world coordinate 
// return robot pos int world coordinate
bool tf_2d_server::tf_laser_to_odom(SPos& p)
{
	SPos tf_pos;
	if(get_tf(BASE_LINK,BASE_LASER,tf_pos)){
		double nx = 0;
		double ny = 0;
		double na = 0;
		World2Local(tf_pos.x_,tf_pos.y_,tf_pos.th_,0,0,0,nx,ny,na);
		Local2World(nx,ny,na,p.x_,p.y_,p.th_,nx,ny,na);
		p.x_ = nx;
		p.y_ = ny;
		p.th_ = na;
		return true;
	}
	return false;
	
}

void tf_2d_server::tf_base_link_to_base_laser( VecPosition& p )
{
	SPos tf_pos;
	get_tf(BASE_LINK,BASE_LASER,tf_pos);

	VecPosition ptf(tf_pos.x_,tf_pos.y_);

	p -= ptf;
	p.rotate( -Rad2Deg(tf_pos.th_));


}
// p is robot in world coordinate 
// return laser pos int world coordinate
bool tf_2d_server::tf_odom_to_laser(SPos& p)
{
	SPos tf_pos;
	if( get_tf(BASE_LINK,BASE_LASER,tf_pos) ){
		double nx = 0;
		double ny = 0;
		double na = 0;
		Local2World(tf_pos.x_,tf_pos.y_,tf_pos.th_,p.x_,p.y_,p.th_,nx,ny,na);
		p.x_ = nx;
		p.y_ = ny;
		p.th_ = na;
		return true;
	}
	return false;

}

