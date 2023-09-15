#ifndef _GEO_POINT2D_H_
#define _GEO_POINT2D_H_

#include <iostream>

/**
 * Primitive 2D point class used as input for the LineParamEstimator.
 *
 * Author: Ziv Yaniv (zivy@cs.huji.ac.il)
 */
namespace ransac{

class Point2D {
public:
	Point2D(double px, double py) : x(px), y(py),usable(false) {}
	double x;
	double y;
	bool usable;
};

inline std::ostream &operator<<(std::ostream &output,const Point2D &pnt)
{
	output<<pnt.x<<' '<<pnt.y;
	return(output);
}
};
#endif //_GEO_POINT2D_H_