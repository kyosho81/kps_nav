#ifndef _SLICE_SEGMENT_20210309_H
#define _SLICE_SEGMENT_20210309_H


#include "robot/RobotStruct.h"
#include "robot/Geometry.h"

typedef struct _SSegment
{
	VecPosition p1_;
	VecPosition p2_;

}SSegment;

class segment_inline{
public:
	segment_inline(){};
	~segment_inline(){};
	int put(const SSegment &seg);
private:
	std::vector<SSegment> from_to_list_;
};


#endif // _SLICE_SEGMENT_20210309_H
