
#include <iostream>
#include <fstream>
#include <vector>

#include <Eigen/Dense>

#include "robot/Geometry.h"
#include "Comm/Rand.hpp"

using namespace Eigen;

using namespace std;

int main()
{
	//cout << "Start Program" << endl;
// 	ifstream fread("data.txt");
// 
// 	if (fread.fail())
// 	{
// 		cout << "Data File does not exit." << endl;
// 		return 0;
// 	}

	double x = 0;
	double y = 0;
	vector<double> xs;
	vector<double> ys;

// 	while (!fread.eof())
// 	{
// 		fread >> x >> y;
// 		xs.push_back(x);
// 		ys.push_back(y);
// 	}

	Line ln = Line::makeLineFromPositionAndAngle(VecPosition(0,1),30);

	MyRand rn;
	for (int i = 0 ; i < 20 ; ++i)
	{
		Line ln2 = Line::makeLineFromPositionAndAngle(VecPosition(i,0),90);
		VecPosition v;
		ln.getIntersection(ln2,v);
		xs.push_back(v.getX());
		y = rn.randND(0,0.01);
		y += v.getY();
		ys.push_back( y );
		std::cout<<"x:"<<v.getX()<<" y:"<<v.getY()<<std::endl;
	}

	int len = xs.size();
	//cout << len << endl;
	Eigen::MatrixXd A(len, 2);
	Eigen::MatrixXd B(len, 1);
	for (int i = 0; i < len; i++)
	{
		A(i, 0) = xs[i];
		A(i, 1) = 1;

		B(i, 0) = ys[i];
	}
	cout << "Matrix A" << endl;
	cout << A << endl;

	cout << "Matrix B" << endl;
	cout << B << endl;

	Eigen::MatrixXd f(2, 1);
	f = (A.transpose()*A).inverse()*A.transpose()*B;
	cout << "Matrix f" << endl;
	cout << f << endl;
}
