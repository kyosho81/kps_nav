#ifndef __MOTION_CONTROL_HEADER__
#define __MOTION_CONTROL_HEADER__

#include "robot/Geometry.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

template<typename T, int N>
class ObjectArray {
public:
	T data[N];
};

struct OrientPos {
	VecPosition pos;
	double angle;

	inline void std_out() {
		std::cout << "x= " << pos.getX() << " y= " << pos.getY() << " angle= "
				<< angle << std::endl;
	}

	OrientPos(double x = 0.0, double y = 0.0, double a = 0.0) :
		pos(x, y), angle(a) {

	}
};

struct TargetPos {
	VecPosition pos;
	double angle;
	double speed;

	TargetPos(double x = 0.0, double y = 0.0, double a = 0.0, double v = 0.0) :
		pos(x, y), angle(a), speed(v) {
	}
};

struct RobotPose2D {
	OrientPos pose_; //�洢x��y���Ƕ���ά״̬
	char map_name_[50];//�洢��ͼ��

	inline void set_pose(const OrientPos &p) {
		pose_ = p;
	}

	inline OrientPos pose() {
		return pose_;
	}

	inline void set_map_name(const std::string &s) {
#ifdef _WIN32
		strcpy_s(map_name_ , s.c_str());
#else
		strcpy(map_name_, s.c_str());
#endif
	}

	inline std::string map_name() {
		return std::string(map_name_);
	}
};

/*
 * ʸ����ʽ��ʾ������������ͼ�е�λ��
 */
class UPL {
public:
	UPL(int sid = -1, int eid = -1, double t = 0.0f, bool forwards = true,
			std::string map = "") :
		start_id_(sid), end_id_(eid), percent_(t), forward_(forwards)
	/*map_name_(map)*/{
		;
	}
	~UPL() {
		;
	}
	int start_id_;
	int end_id_;
	bool forward_; // ��ʱ���ã���start_id_ -> end_id_��ʾ����
	double percent_;
	//	std::string map_name_; // �Ժ���չ��
};

struct ControlParams {
	ControlParams() :
		max_vx_(-1.0), max_vy_(-1.0), max_w_(-1.0), max_av_(-1.0),
				max_aw_(-1.0) {
		;
	}
	ControlParams(double m_vx, double m_vy, double m_w, double m_av,
			double m_aw) :
		max_vx_(m_vx), max_vy_(m_vy), max_w_(m_w), max_av_(m_av), max_aw_(m_aw) {
		;
	}
	bool IsValid() {
		if (max_vx_ <= 0 || max_vy_ <= 0 || max_w_ <= 0 || max_av_ <= 0
				|| max_aw_ <= 0) {
			return false;
		} else
			return true;
	}
	std::string DebugString() {
		char buf[128];
		int j = sprintf(buf, "[v, w, va, wa] = %f, %f, %f, %f ", max_vx_,
				max_w_, max_av_, max_aw_);
		std::string s;
		if (j > 0)
			s.assign(buf);
		return s;
	}
	double max_vx_, max_vy_, max_w_; // С��/����0 ��ʹ�������ļ��е����ã�����ʹ�øò��������˶�����
	double max_av_, max_aw_; // ���ٶȿ��ƣ� ��λ m/s, rad/s , m/s^2, rad/s^2
};

struct OrientTarget {
#ifdef _WIN32
	static const int kNavigationType_AvoidObstacle = 1;
	static const int kNavigationType_AccurateTune = 2;
	static const int kNavigationType_Straight = 3;
	static const int kNavigationType_BiDirectionStraight = 4;
	static const int kNavigationType_BezierEdge = 5;

	static const int kEndConditionTypeDistOnly = 1; //��ֹ�����ж����Ͷ��壺���жϻ�����λ�ú�ĳ�̶�λ�õľ����Ƿ�С��һ��ֵ
	static const int kEndConditionTypeDistAndAngle = 2; //��ֹ�����ж����Ͷ��壺�����жϾ����Ƿ����㣬�����жϻ����˳����Ƿ���������
#else
	static const int kNavigationType_AvoidObstacle;
	static const int kNavigationType_AccurateTune;
	static const int kNavigationType_Straight;
	static const int kNavigationType_BiDirectionStraight;
	static const int kNavigationType_BezierEdge;

	static const int kEndConditionTypeDistOnly; //��ֹ�����ж����Ͷ��壺���жϻ�����λ�ú�ĳ�̶�λ�õľ����Ƿ�С��һ��ֵ
	static const int kEndConditionTypeDistAndAngle; //��ֹ�����ж����Ͷ��壺�����жϾ����Ƿ����㣬�����жϻ����˳����Ƿ���������
#endif

	OrientPos target_;
	UPL tar_; // kNavigationType_BezierEdgeʹ��������
	// 	double    max_vx_, max_vy_, max_w_;	// С��/����0 ��ʹ�������ļ��е����ã�����ʹ�øò��������˶�����
	// 	double    max_av_, max_aw_;	// ���ٶȿ��ƣ� ��λ m/s, rad/s , m/s^2, rad/s^2
	ControlParams con_params_; // 20130913 �ĳ�һ���ṹ�壬�Ժ���������ɾ��
	int navigation_type_;
	int end_condition_type_;
	double end_condition_dist_thres_;
	double end_condition_angle_thres_;
	bool b_consider_orientation_;
	bool b_precise_stop_; // 20130902 ����������Ƿ���þ�ȷ������Ʒ�ʽ
	// true - ��ȷ����
	// false - �ô�ͳ��ģʽ��Ĭ�ϣ�
};

#endif
