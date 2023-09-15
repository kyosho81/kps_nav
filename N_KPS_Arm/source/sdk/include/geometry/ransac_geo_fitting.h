#ifndef _RANSAC_GEOMETRY_FITTING_KYOSHO_20210703_H_
#define _RANSAC_GEOMETRY_FITTING_KYOSHO_20210703_H_

#include <iostream>
#include "robot/RobotStruct.h"
#include "geometry/Point2D.h"

class ransac_geometry_fitting{
public:
	ransac_geometry_fitting();
	~ransac_geometry_fitting();

	static bool fit_line( SLine2P &line_pa ,std::vector<ransac::Point2D> &pointData, float delta = 0.03);
	static bool fit_circle( SCircle &circle_pa ,std::vector<ransac::Point2D> &pointData, float radius , float delta = 0.03);

};
#define FIT_LINE( ln , data ) ransac_geometry_fitting::fit_line(ln , data )
#define FIT_LINE2( ln , data , delta ) ransac_geometry_fitting::fit_line(ln , data , delta)

#define FIT_CIRCLE( cir , data , radius ) ransac_geometry_fitting::fit_circle( cir , data , radius )
#define FIT_CIRCLE2( cir , data , radius , delta ) ransac_geometry_fitting::fit_circle( cir , data , radius ,delta)

#endif //_RANSAC_GEOMETRY_FITTING_KYOSHO_20210703_H_