#ifndef _G2O_LOC_POS_GRAPH_H_
#define _G2O_LOC_POS_GRAPH_H_

#include "g2o/core/sparse_optimizer.h"

#include "g2o_slam/se2.h"
#include "g2o_slam/g2o_tutorial_slam2d_api.h"

#include <Eigen/StdVector>
#include "robot/RobotStruct.h"
#include "bag/bag.h"
#include "scanmatcher/psm_node.h"
#include "protobuf_msg/protobuf_bag.h"

#include "gmapping/gridfastslam/gridslamprocessor.h"
#include "gmapping/sensor/sensor_base/sensor.h"


namespace g2o {
	namespace slam2d {

		

		class g2o_loc{

		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
			g2o_loc();
			~g2o_loc();

			void init(SLaser_para laser_para);
			bool optimize(SPos &final_pos, std::vector<void*> data , SOdomSpeed odomspeed);
			bool optimize(std::vector<void*> data);

		private:
			void simulate();
			g2o::tutorial::SE2 laserOffsetTransf_;
			Eigen::Matrix3d information_;
			Eigen::Matrix2d landmark_information_;


			int add_robot_pos(g2o::SparseOptimizer &optimizer, int i_frame_id ,const SPos &pos, bool b_fixed = false);
			void add_pos_edge(g2o::SparseOptimizer &optimizer,const int &id_from,const int &id_to);
			void add_pos_edge(g2o::SparseOptimizer &optimizer,const int &id_from,const int &id_to,const SPos& estimate_pos);
			void add_observation_edge(g2o::SparseOptimizer &optimizer,const SBAG &bag_from,const SBAG &bag_to);
			//void add_laser_point(g2o::SparseOptimizer &optimizer,const SBAG &bag,const int &pos_id);

			int total_vector_id_;

			PSMNode psm_node_;

			SPos laser_diff2odom_diff(const SPos& laser_diff);
			SPos odom2laser(const SPos& odom_diff);
			SPos odom_diff2laser_diff(SPos odom_diff);

			//odom diff do one frame
// 			bool get_diff(const SOdomSpeed &new_odom_);
// 			F32 dr_;
// 			F32 dth_;
// 			bool first_odom_;
// 			SOdomSpeed last_odom_;
// 			SPos diff_odom_;

			protobuf_bag res_pro_bag_;

			//result bag
			bool add_res_bag(int id,const SBAG &bag);
			bool set_res_new_pos(int id,double ox,double oy,double oa);
			std::map<int,SBAG> res_bag_;
			int save_res(g2o::SparseOptimizer &optimizer);
			void save_map(const std::string &path_name,g2o::SparseOptimizer &optimizer);
			void save(std::string path,const GMapping::ScanMatcherMap &smap);


			int reset_res(std::map<int, void*> &m_pos_frame, g2o::SparseOptimizer &optimizer);

		private:
			
			SLaser_para laser_para_;
		};
	}
}

#endif//_G2O_LOC_POS_GRAPH_H_