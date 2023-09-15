#ifndef _2D_LASER_LOOP_CLOSURE_KYOSHO_20190217_
#define _2D_LASER_LOOP_CLOSURE_KYOSHO_20190217_

#include <map>
#include <string>

#include <boost/serialization/singleton.hpp>
#include "flirt/utils/HistogramDistances.h"
#include "flirt/feature/point.h"

#include "robot/RobotStruct.h"

class LogSensorStream;
class CarmenLogWriter;
class CarmenLogReader;

class LaserReading;

class CurvatureDetector;
class NormalBlobDetector;
class NormalEdgeDetector;
class RangeDetector;
class Detector;

class InterestPoint;

class BetaGridGenerator;
class ShapeContextGenerator;
class DescriptorGenerator;

class RansacFeatureSetMatcher;

class SimpleMinMaxPeakFinder;
class AbstractReading;

class scan_map_conver;
class pos_filter;
class GridMap;

#include "DBoW3/DBoW3.h"
//class DBoW3::Vocabulary;
//class DBoW3::Database;

typedef struct _SMatch_res
{
	LaserReading* lreadReference_;
	OrientedPoint2D trans_;
	std::vector< std::pair<InterestPoint*, InterestPoint* > > correspondences_;
}SMatch_res;


class laser2d_loop_closure
{
public:

	laser2d_loop_closure();
	~laser2d_loop_closure();

	
	void init(const bool &b_dbow3);
	
	int load(std::string str_file ,  const bool &b_dbow3 = false);
	void init_filter( GridMap* p_map = 0 );
	void reset();

	LaserReading* Laser2LaserRead(const SLaser &laser);

	int match( std::vector<SMatch_res> &v_res, LaserReading* lreadReference);
	F32 filter_pos(SPos &final_pos ,std::vector<STriangle> &v_probability_pos,const std::vector<SMatch_res> &v_res);

	bool seek(const unsigned int &position);
	bool end() const;
	AbstractReading* next();
	AbstractReading* current();

	bool init_over();

protected:
	//flirt
private:
	
	int load_log(std::string str_file);
	int load_maproto(std::string str_file);
	int load_maprotoex(std::string str_file);
	int load_frame(std::string str_file);

	void detect_describe();

	int ori_match( std::vector<SMatch_res> &v_res, LaserReading* lreadReference);
	int dbow3_match( std::vector<SMatch_res> &v_res, LaserReading* lreadReference);
	int i_min_match_cnt_;
	double max_d_;
	double min_d_;
	
	LogSensorStream* m_sensorReference_;

	SimpleMinMaxPeakFinder* m_peakMinMax_;
	SimpleMinMaxPeakFinder* m_peakMNE_;
	CurvatureDetector* m_detectorCurvature_;
	NormalBlobDetector* m_detectorNormalBlob;
	NormalEdgeDetector* m_detectorNormalEdge;
	RangeDetector* m_detectorRange;
	Detector* m_detector_;

	std::vector< std::vector<InterestPoint *> > m_pointsReference_;

	BetaGridGenerator* m_betaGenerator_;
	ShapeContextGenerator* m_shapeGenerator;
	DescriptorGenerator* m_descriptor_;
	HistogramDistance<double>* m_dist_;

	RansacFeatureSetMatcher* m_ransac_;

	double angErrorTh_;
	double linErrorTh_;

	

	unsigned int corresp[8];

	unsigned int m_localSkip_;

	int i_total_size_;

	//dbow3
	bool b_dbow3_;
	int i_dbow_range_diff_;
	DBoW3::Vocabulary* m_vocab_;
	DBoW3::Database* m_db_;

	//scan_map_conver
	bool conver_readref2scan( SPUB_BAG &pub_bag ,const LaserReading* const lreadReference);
	void create_scan_map();
	scan_map_conver* scan_map_conver_;
	void save_map(std::string str_file);
	void save_map( GridMap* &p_map );
	
	GridMap* g_mem_map_;

	pos_filter* pos_filter_;

	//process bar
	SProcess_Bar pro_bar_;
	void pub_process_bar( const int &current_step, const int &max_step );
};

//typedef boost::serialization::singleton<project_manage> Singleton_Project_Manage;

#endif//_2D_LASER_LOOP_CLOSURE_KYOSHO_20190217_
