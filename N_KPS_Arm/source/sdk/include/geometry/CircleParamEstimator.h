#ifndef _CIRCLE_PARAM_ESTIMATOR_H_
#define _CIRCLE_PARAM_ESTIMATOR_H_

#include "ParameterEsitmator.h"
#include "Point2D.h"


class CircleParamEstimator : public ParameterEsitmator<ransac::Point2D,double> {
public:
	CircleParamEstimator(double delta,double radius);

	/**
	 * Compute the Circle defined by the given data points.
	 * @param data A vector containing three 2D points.
	 * @param This vector is cleared and then filled with the computed parameters.
	 *        The parameters of the Circle passing through these points [center x,center y,radius]
	 *        
	 *        If the vector contains less than three points then the resulting parameters
	 *        vector is empty (size = 0).
	 */
	virtual void estimate(std::vector<ransac::Point2D *> &data, std::vector<double> &parameters);

	/**
	 * Compute a least squares estimate of the Circle*/

	virtual void leastSquaresEstimate(std::vector<ransac::Point2D *> &data, std::vector<double> &parameters);

	/**
	 * Return true if the distance between the Circle defined by the parameters and the
	 * given point is smaller than 'delta' (see constructor).
	 * @param parameters The line parameters [center x,center y,radius].
	 * @param data Check that the distance between this point and the Circle is smaller than 'delta'.
	 */
	virtual bool agree(std::vector<double> &parameters, ransac::Point2D &data);

	/**
	 * Test the class methods.
	 */
	static void debugTest(std::ostream &out);

private:
	double m_radius_;	//°ë¾¶Ô¼Êø
	double m_deltaAbsolute; //given line L and point P, if dist(L,P)^2 < m_delta^2 then the point is on the line
};

#endif //_CIRCLE_PARAM_ESTIMATOR_H_