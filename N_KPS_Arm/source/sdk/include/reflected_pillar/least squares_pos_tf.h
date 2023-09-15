#ifndef _LEASE_SQUARES_POS_TRANSFER_KYOSHO_20191120_
#define _LEASE_SQUARES_POS_TRANSFER_KYOSHO_20191120_

#include <iostream>
#include <map>

#include <Eigen/Jacobi>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Householder>

#include "RobotStruct.h"

class least_squares_pos_tf
{
public:

	least_squares_pos_tf();
	~least_squares_pos_tf();

	bool Solve( SPos &pos, std::vector<std::pair<SVec,SVec>> &v_pp_pairs);

protected:

private:

	Eigen::MatrixXd A;
	Eigen::VectorXd  b;

};



#endif//_LEASE_SQUARES_POS_TRANSFER_KYOSHO_20191120_
