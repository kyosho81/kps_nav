#ifndef _REFLECTED_PILLAR_G2O_KYOSHO_20191120_
#define _REFLECTED_PILLAR_G2O_KYOSHO_20191120_

#include <map>
#include <string>
#include <list>

#include <boost/serialization/singleton.hpp>
#include "robot/Geometry.h"
#include "MyDefine.h"
#include "RobotStruct.h"




#include "g2o/core/sparse_optimizer.h"
#include "g2o/core/block_solver.h"
#include "g2o/core/optimization_algorithm_gauss_newton.h"
#include "g2o/solvers/csparse/linear_solver_csparse.h"

#include "g2o_slam/se2.h"
#include "g2o_slam/g2o_tutorial_slam2d_api.h"
#include "g2o_slam/types_tutorial_slam2d.h"

#include "protobuf_msg/protobuf_bag_ex.h"
#include "reflected_pillar/reflected_pillar.h"

class reflected_pillar_g2o
{
public:

	reflected_pillar_g2o();
	~reflected_pillar_g2o();

	void init(const F32 &dx,const F32 &dy);
	
	SLaser_Ex_Ref g2o_mapping(std::vector<SPUB_BAG_EX*> &v_bag_ex,std::map<protobuf_reflector*,SPUB_BAG_EX*> &m_bag_ex_bind_over, std::string path_name );
	

//g2o
private:
	//add robot pos
	int add_robot_pos(const int &i_bag_id,const SOdomSpeed &odom);
	//add pos edge
	int add_pos_edge(const int &i_bag_from,const int &i_bag_to);
	//add reflector pos
	int add_ref_pos(const int &i_ref_uid,const SVec &vp);
	//add ref to robot edge
	int add_ref_pos_edge(const int &i_bag_id,const int &i_ref_id,const SVec &vp);

	bool save_ref_map(std::string str_path);

	g2o::tutorial::SE2 laserOffsetTransf_;
	Eigen::Matrix3d information_;
	Eigen::Matrix2d landmark_information_;

	typedef g2o::BlockSolver< g2o::BlockSolverTraits<-1, -1> >  SlamBlockSolver;
	typedef g2o::LinearSolverCSparse< SlamBlockSolver::PoseMatrixType> SlamLinearSolver;

	SlamLinearSolver* p_linearSolver_;
	SlamBlockSolver* p_blockSolver_;
	g2o::OptimizationAlgorithmGaussNewton* p_solver_;
	g2o::SparseOptimizer* p_optimizer_;
	g2o::tutorial::ParameterSE2Offset* p_sensorOffset_;
//para
private:
	F32 laser_dx_;
	F32 laser_dy_;

	static const int MAX_POS_ID = 100000;
};

#endif//_REFLECTED_PILLAR_G2O_KYOSHO_20191120_
