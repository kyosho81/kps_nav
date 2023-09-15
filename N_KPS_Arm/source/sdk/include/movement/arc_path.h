
#ifndef _ARC_PATH_KYOSHO_2019_07_08_H_
#define _ARC_PATH_KYOSHO_2019_07_08_H_

#include <vector>
#include <RobotStruct.h>

class arc_path
{
public:
	arc_path();
	~arc_path();

public:

	bool ArcPathPnts(std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> input_points,
		             const F32 &R, const F32& dl );
	bool ArcPathPnts(std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> input_points,
		             const F32 &R, const F32& dl ,
					 const F32 &straight_v ,const F32 &arc_v);
	bool LinePathPnts( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> input_points,
			          const F32 &R, const F32& dl );
	//for new algorithm
	bool exLinePathPnts( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> input_points,
			          const F32& dl);
	void fill_speed( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> line_points,std::vector<SOdomSpeed> arc_points,const F32 &straight_v ,const F32 &arc_v);

private:
	bool CreateArcData(std::vector<SOdomSpeed> &out_points,SOdomSpeed& aO,SOdomSpeed& cO,const SOdomSpeed& A,const SOdomSpeed& B,const SOdomSpeed& C);
	
	F32 R_;
	F32 dl_;
	F32 slow_dis_;
	F32 acc_dis_;
	F32 dec_dis_;

	bool CreateLineData(std::vector<SOdomSpeed> &out_points,const SOdomSpeed& A,const SOdomSpeed& B);

	bool preProcessLine(std::vector<SOdomSpeed> &input_points);
	bool check_inline(const SOdomSpeed &A,const SOdomSpeed &B,const SOdomSpeed &C);

	void fill_speed_ln( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> line_points,F32 cur_vx, const F32 &last_vx ,const F32 &slow_vx);
	void fill_speed_arc( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> arc_points,const F32 &cur_vx);
	void fill_speed_ln_dec( std::vector<SOdomSpeed> &out_points,F32 last_path_len,const F32 &last_vx,const F32 &arc_v);
	void fill_speed_ln_acc( std::vector<SOdomSpeed> &out_points,std::vector<SOdomSpeed> line_points,F32 cur_vx,const F32 &slow_vx);
	F32 v_min_;
	F32 v_accelerate_;
	
	S32 path_count_;
	F32 inline_angle_deg_;
};




#endif // _ARC_PATH_KYOSHO_2019_07_08_H_
