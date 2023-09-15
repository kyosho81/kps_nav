#include "math.h"
#include <boost/thread.hpp>
#include "Comm.h"

#include "robot/angle_calibration.h"

angle_calibration::angle_calibration()
{

}

angle_calibration::~angle_calibration()
{

}

void angle_calibration::init()
{
	ad_zero_ = 9855;
	ad_max_= 0;
	ad_min_= 0;

	k1_= -1530.43;
	k2_= 1490.96;

}

void angle_calibration::setZero( const S32 &ad_value )
{
	ad_zero_ = ad_value;
}

void angle_calibration::setAngleMax( const S32 &ad_value )
{
	ad_max_ = ad_value;
	cal_k();
}

void angle_calibration::setAngleMin( const S32 &ad_value )
{
	ad_min_ = ad_value;
	cal_k();
}

F32 angle_calibration::getAngle( const S32 &ad_value )
{
	F32 angle = 0;

	if ( ( fabs( k1_ ) < 1.0e-4  ) || ( fabs( k2_ ) < 1.0e-4 ))
	{
		return 0;
	}

	if( ad_value == 0){
		std::cout<<"error ad_value:"<<ad_value<<std::endl;
		return 0;
	}
	if ( ad_value > ad_zero_  )
	{
		angle = ( ad_value - ad_zero_) / k1_;
	}
	else
	{
		angle = ( ad_zero_ - ad_value) / k2_;
	}


	return angle;
}



void angle_calibration::cal_k()
{
	
	k1_ = ad_min_ - ad_zero_ ;
	k1_ /= -M_PI/2;

	k2_ = ad_zero_ - ad_max_ ;
	k2_ /= M_PI/2;

}

void angle_calibration::setK( const F32 &k1,const F32 &k2 )
{
	k1_ = k1;
	k2_ = k2;
}

F32 angle_calibration::getK1()
{
	return k1_;
}

F32 angle_calibration::getK2()
{
	return k2_;
}

S32 angle_calibration::getZero()
{
	return ad_zero_;
}

angle_manage::angle_manage()
{

}

angle_manage::~angle_manage()
{
	destroy_angle_inc();
}

F32 angle_manage::getAngle( const S32 &id,const S32 &ad_value )
{
	F32 angle = 0;
	angle_calibration* ac = getAngle_instance(id);
	if (ac)
	{
		angle = ac->getAngle(ad_value);
	}
	return angle;
}

void angle_manage::setZero( const S32 &id,const S32 &ad_value )
{
	angle_calibration* ac = getAngle_instance(id);
	if (ac)
	{
		ac->setZero(ad_value);
	}
}

void angle_manage::setAngleMax( const S32 &id,const S32 &ad_value )
{
	angle_calibration* ac = getAngle_instance(id);
	if (ac)
	{
		ac->setAngleMax(ad_value);
	}
}

void angle_manage::setAngleMin( const S32 &id,const S32 &ad_value )
{
	angle_calibration* ac = getAngle_instance(id);
	if (ac)
	{
		ac->setAngleMin(ad_value);
	}
}

angle_calibration* angle_manage::getAngle_instance( const S32 &id )
{
	std::map<U32, angle_calibration* >::iterator it = angle_list_.find(id);
	angle_calibration* ac = 0 ;
	if (it == angle_list_.end() )
	{
		ac = new angle_calibration();
		angle_list_[id] = ac;
	}else{
		ac = it->second;
	}
	return ac;
}

void angle_manage::destroy_angle_inc()
{
	std::map<U32, angle_calibration* >::iterator it = angle_list_.begin();
	angle_calibration* ac = 0;
	for ( ; it != angle_list_.end() ; ++it)
	{
		ac = it->second;
		delete ac;
	}
	angle_list_.clear();
}

void angle_manage::setK( const S32 &id,const F32 &k1,const F32 &k2 )
{
	angle_calibration* ac = getAngle_instance(id);
	if (ac)
	{
		ac->setK(k1,k2);
	}

}
void angle_manage::loadAngle(){

	std::ifstream file("angle_para.txt",std::ios::in | std::ios::binary);
	S32 id = 0;
	F32 k1 = 0;
	F32 k2 = 0;
	S32 zero_angle = 0;

	if (file.is_open())
	{

		file>>id;
		file>>zero_angle;
		file>>k1;
		file>>k2;

		getAngle_instance(0)->setZero(zero_angle);
		getAngle_instance(0)->setK(k1,k2);

	}
	

}
void angle_manage::saveAngle()
{

	std::ofstream file("angle_para.txt",std::ios::out | std::ios::binary);

	std::map<U32, angle_calibration* >::iterator it = angle_list_.begin();
	angle_calibration* ac = 0;
	for ( ; it != angle_list_.end() ; ++it)
	{
		ac = it->second;
		file<<it->first<<" "<<ac->getZero()<<" "<<ac->getK1()<<" "<<ac->getK2()<<std::endl;
	}
	file.flush();
	file.close();
}
