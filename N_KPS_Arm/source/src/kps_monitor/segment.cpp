#include <iostream>

#include "Comm/Comm.h"
#include "Comm/TimerDiff.h"
#include "robot/vec2pos.hpp"

#include "segment.h"

int segment_inline::put(const SSegment &seg){
	from_to_list_.push_back(seg);
	return from_to_list_.size();
};