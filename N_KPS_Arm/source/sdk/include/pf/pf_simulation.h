#ifndef _PF_SIMULATION_WANGHONGTAO_20151021_
#define _PF_SIMULATION_WANGHONGTAO_20151021_


#include <string>
#include <boost/thread.hpp>

#include "RobotStruct.h"
#include "buffer_con.hpp"
#include "Rand.hpp"
#include "merge_tf.h"


#define SIM_LASER 541
#define MIN_PATICLES 64
#define MAX_PATICLES 1024

class GridMap;

typedef struct _SimLaser
{
	F32 x_;
	F32 y_;

}SimLaser;


typedef struct _SimparticleAW
{
	F32 x_;
	F32 y_;
	F32 th_;
	F32 aw_;

}SimparticleAW;


class pf_simulation{

public:
	pf_simulation();
	~pf_simulation();

	void init(bool b_laser_cab,bool b_gn_amcl);
	void set_pf_constraint( bool b_pf_constraint, F32 f_pf_disperse_dis, F32 f_pf_disperse_angle );
	void update_init_pos();
	void update_motion_modle();
	bool update_resapmle( SPos center_pos );

	void init_particle();
	void init_pos(const SInit_Pos &pos);
	bool s_init_pos(const SInit_Pos &pos);
	void init_amcl_map(GridMap* shared_map);
	GridMap* get_amcl_map();
	void clear_import_data();

	//call back when interprocess_laser (50hz)
	//void update_laser(const SLaser& laser);
	bool s_update_laser( const SLaser& laser );
	bool s_update_laser_ex_cab( const SLaserXYEx& laser_ex_cab );
	void set_base_laser(F32 x, F32 y ,F32 th);
	
	//call back when interprocess_chassis (20hz)
	void update_odom(const SOdomSpeed& new_odom);

	void set_min_rand(const F32 &crxy,const F32 &crth);
	void set_motion_rand(const F32 &crmod,const F32 &crmth,const F32&crot);
	

	void get_particle(SparticlePub &pub);
	

	void destructor();


	void load_test_data();
	void test_update_laser();

	SAMCL_ENTROPY ae_;
	SPos res_pos_;
	SLaserXYEx laser_;

	bool clone(GridMap* out_map);

private:
//laser
	void set_laser_tf(const SLaser& laser);
	void set_laser();


	CSBuffer<SLaserXYEx,1> new_laser_ex_cab_;

	
 	SimLaser_tf laser_tf_[SIM_LASER];
	
	bool no_laser_tf_;
	SPos base_laser_;


//particle
	
	U32 checksize(U32 newsize);
	void clean_particles();
	void get_weight();
	void sort();
	bool cal_pos(std::vector<SimparticleAW> &sort_p,std::vector<F32> &sum_drop);
	
	void cal_entropy( const SPos &res_pos, std::vector<SimparticleAW> &samples);
	U32 check_health_resize();
	void resample(const std::vector<SimparticleAW> &sort_p,std::vector<F32> &sum_drop, SPos center_pos);
	MyRand rd_;
	SimparticleAW* particle_;

	U32 psize_;
	F32 top_per_;
	inline U32 get_map_weight(const F32& x,const F32& y);
	bool new_init_pos_;
	boost::mutex mu_init_;
	SInit_Pos init_pos_;

//publish
	SparticlePub pub_;

//map
	GridMap* amcl_map_;
	

//odom
	boost::mutex mu_odom_;
	bool get_diff();


	SOdomSpeed last_odom_;
	SOdomSpeed new_odom_;
	SPos diff_odom_;
	bool first_odom_;

	F32 delta_trans_;
	F32 delta_the_;
	
//odom random
	MyRand rxy_;
	MyRand rth_;

	F32 crxy_;
	F32 crth_;

//odom motion random
	MyRand rmod_;
	MyRand rmth_;
	MyRand rrot_;

// 	TimeRand rmod_;
// 	TimeRand rmth_;
// 	TimeRand rrot_;

	F32 crmod_;
	F32 crmth_;
	F32 crot_;
	
	SPos create_motion_diff(SPos diff_odom);
	SPos create_motion_diff(SPos diff_odom,boost::random::mt19937 &gen);
	SPos create_rand_diff(SPos diff_odom);
	bool check_particle(const F32 &gx,const F32 &gy);



	F32 max_x_;
	F32 min_x_;

	F32 max_y_;
	F32 min_y_;

	F32 max_th_;
	F32 min_th_;
	

	bool b_laser_cab_;
	bool b_gn_amcl_;

	bool b_pf_constraint_;
	F32  f_pf_disperse_dis_;
	F32  f_pf_disperse_angle_;
};

#endif//_PF_SIMULATION_WANGHONGTAO_20151021_

