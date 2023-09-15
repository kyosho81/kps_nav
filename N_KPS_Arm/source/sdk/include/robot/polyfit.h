#ifndef _POLYFIT_WANGHONGTAO_2020_07_21_
#define _POLYFIT_WANGHONGTAO_2020_07_21_

#include <map>

#include "MyDefine.h"
#include <boost/thread.hpp>

#include "TimerDiff.h"
#include "RobotStruct.h"
#include "buffer_con.hpp"

#include <Eigen/Dense>

class polyfit
{
public:
	polyfit();
	~polyfit();


	static double polyval(Eigen::VectorXd coeffs, double x);
	static F64 polyval(std::vector<F64> coeffs, F64 x);
	static Eigen::VectorXd fit(Eigen::VectorXd xvals, Eigen::VectorXd yvals, int order);
	static std::vector<F64> fit(std::vector<F64> xvals, std::vector<F64> yvals, int order);

protected:

private:

};


#endif//_POLYFIT_WANGHONGTAO_2020_07_21_
