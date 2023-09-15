#ifndef _AREA_20210309_H
#define _AREA_20210309_H


#include "robot/RobotStruct.h"


class border
{
public:
	border();
	~border();

	void set_border(F32 px, F32 py);
	std::vector<Sxy> get_border();

protected:
private:

	F32 min_x_;
	F32 min_y_;
	F32 max_x_;
	F32 max_y_;

};
class area
{
public:
	area(){};
	~area(){};

	void put_point(const SPos &pos);
	std::vector<Sxy> get_border();

	std::vector<std::pair<SPos,SPos> > outlet_;
	std::list<SPos>& get_block_point();
	

protected:
private:

	std::list<SPos> block_point_;
	border border_;
	
};

#endif // _AREA_20210309_H
