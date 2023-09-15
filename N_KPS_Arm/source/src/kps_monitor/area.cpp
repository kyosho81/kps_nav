#include <iostream>

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "robot/vec2pos.hpp"

#include "area.h"


border::border()
{
	max_x_ = -1e10;
	max_y_ = -1e10;
	min_x_ = 1e10;
	min_y_ = 1e10;
}

border::~border()
{

}

void border::set_border( F32 px, F32 py )
{
	max_x_ = cComm::Max(px,max_x_);
	max_y_ = cComm::Max(py,max_y_);

	min_x_ = cComm::Min(px,min_x_);
	min_y_ = cComm::Min(py,min_y_);
}

std::vector<Sxy> border::get_border()
{
	std::vector<Sxy> map_border;
	Sxy xy;
	xy.x_ = min_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top left

	xy.x_ = max_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top right

	xy.x_ = max_x_;
	xy.y_ = min_y_;
	map_border.push_back(xy);// bottom right

	xy.x_ = min_x_;
	xy.y_ = min_y_;
	map_border.push_back(xy);// bottom left

	xy.x_ = min_x_;
	xy.y_ = max_y_;
	map_border.push_back(xy);// top left
	return map_border;
}

std::vector<Sxy> area::get_border()
{
	return border_.get_border();
}

void area::put_point( const SPos &pos )
{

	block_point_.push_back(pos);
	border_.set_border(pos.x_,pos.y_);
}

std::list<SPos>& area::get_block_point()
{
	return block_point_;
}


