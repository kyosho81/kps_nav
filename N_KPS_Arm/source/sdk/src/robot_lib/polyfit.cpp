#include "math.h"
#include <boost/thread.hpp>
#include "Comm.h"

#include "robot/polyfit.h"

polyfit::polyfit()
{

}

polyfit::~polyfit()
{

}

Eigen::VectorXd polyfit::fit(Eigen::VectorXd xvals, Eigen::VectorXd yvals, int order) {
	assert(xvals.size() == yvals.size());
	assert(order >= 1 && order <= xvals.size() - 1);
	Eigen::MatrixXd A(xvals.size(), order + 1);
	for (int i = 0; i < xvals.size(); i++) {
		A(i, 0) = 1.0;
	}
	for (int j = 0; j < xvals.size(); j++) {
		for (int i = 0; i < order; i++) {
			A(j, i + 1) = A(j, i) * xvals(j);
		}
	}
	//std::cout<<A<<std::endl;

	auto Q = A.householderQr();
	auto result = Q.solve(yvals);

	//std::cout<<result<<std::endl;

	return result;
}
std::vector<F64> polyfit::fit(std::vector<F64> xvals, std::vector<F64> yvals, int order) {
	std::vector<F64> vres;

	assert(xvals.size() == yvals.size());
	assert(order >= 1 && order <= xvals.size() - 1);
	Eigen::MatrixXd A(xvals.size(), order + 1);
	for (int i = 0; i < xvals.size(); i++) {
		A(i, 0) = 1.0;
	}
	for (int j = 0; j < xvals.size(); j++) {
		for (int i = 0; i < order; i++) {
			A(j, i + 1) = A(j, i) * xvals[j];
		}
	}
	//std::cout<<A<<std::endl;
	Eigen::VectorXd y(yvals.size(),1);
	std::vector<F64>::iterator it = yvals.begin();
	int index = 0;
	for ( ; it !=  yvals.end() ; ++it ){
		y(index++,0) = *it;
	}
	auto Q = A.householderQr();
	auto result = Q.solve(y);
	Eigen::VectorXd r = result;
	//std::cout<<result<<std::endl;
	for( int i = 0 ; i < (order + 1) ; ++i ){
		vres.push_back(r[i]) ;
	}
	return vres;
}
double polyfit::polyval(Eigen::VectorXd coeffs, double x) {
	F64 result = 0.0;
	for (int i = 0; i < coeffs.size(); i++) {
		result += coeffs[i]*pow(x, i);
	}
	return result;
}

F64 polyfit::polyval(std::vector<F64> coeffs, F64 x)
{
	double result = 0.0;
	for (int i = 0; i < coeffs.size(); i++) {
		F64 f = coeffs[i]*pow(x, i);
		result += f;
	}
	return result;
}
