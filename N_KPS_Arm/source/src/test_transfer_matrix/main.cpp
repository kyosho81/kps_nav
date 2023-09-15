
#include <iostream>
#include <fstream>
#include <vector>

#include <Eigen/Dense>

#include "robot/Geometry.h"
#include "Comm/Rand.hpp"

using namespace Eigen;

using namespace std;

void m_base2world(float lx,float ly,float la,float wx,float wy,float wa,float &nx,float &ny,float &na){
	
	Vector3f vl;
	vl(0) = lx;
	vl(1) = ly;
	vl(2) = 1;

	Eigen::Matrix3f WB;
	WB(0,0) = cos(wa);
	WB(0,1) = -sin(wa);
	WB(1,0) = sin(wa);
	WB(1,1) = cos(wa);
	WB(2,0) = 0;
	WB(2,1) = 0;

	WB(0,2) = wx;
	WB(1,2) = wy;
	WB(2,2) = 1;

	//WB * vl;
	vl = WB * vl;

	nx = vl(0);
	ny = vl(1);
	na = wa + la;
}
//ox oy oa is new origin pos
void m_world2base(float ox,float oy,float oa,float rx,float ry,float ra,float &lx,float &ly,float &la){
	Eigen::Matrix3f WO;
	WO(0,0) = cos(oa);
	WO(0,1) = -sin(oa);
	WO(1,0) = sin(oa);
	WO(1,1) = cos(oa);
	WO(2,0) = 0;
	WO(2,1) = 0;

	WO(0,2) = ox;
	WO(1,2) = oy;
	WO(2,2) = 1;

	Eigen::Matrix3f WR;
	WR(0,0) = cos(ra);
	WR(0,1) = -sin(ra);
	WR(1,0) = sin(ra);
	WR(1,1) = cos(ra);
	WR(2,0) = 0;
	WR(2,1) = 0;

	WR(0,2) = rx;
	WR(1,2) = ry;
	WR(2,2) = 1;

	WO = WO.inverse() * WR;
	//std::cout<<WO<<std::endl;
	lx = WO(0,2);
	ly = WO(1,2);
	la = atan2(WO(1,0),WO(0,0));
}
void add_data(Eigen::MatrixXd &A,Eigen::MatrixXd &b,float ux,float uy,float uth,float usx,float usy,float usth){
	int irows = A.rows();
	A(irows,0) = ux;
	A(irows,1) = uy;
	A(irows,2) = uth;
	A(irows,3) = 0;
	A(irows,4) = 0;
	A(irows,5) = 0;
	A(irows,6) = 0;
	A(irows,7) = 0;
	A(irows,8) = 0;

	A(irows+1,0) = 0;
	A(irows+1,1) = 0;
	A(irows+1,2) = 0;
	A(irows+1,3) = ux;
	A(irows+1,4) = uy;
	A(irows+1,5) = uth;
	A(irows+1,6) = 0;
	A(irows+1,7) = 0;
	A(irows+1,8) = 0;

	A(irows+2,0) = 0;
	A(irows+2,1) = 0;
	A(irows+2,2) = 0;
	A(irows+2,3) = 0;
	A(irows+2,4) = 0;
	A(irows+2,5) = 0;
	A(irows+2,6) = ux;
	A(irows+2,7) = uy;
	A(irows+2,8) = uth;

	assert(irows == b.rows());
	b(irows,0) = usx;
	b(irows+1,0) = usy;
	b(irows+2,0) = usth;


}
int main()
{
	float nx,ny,na;
	m_base2world(1,0,Deg2Rad(0),0,1,Deg2Rad(45),nx,ny,na);

	m_world2base(0,0,Deg2Rad(45),0,2,Deg2Rad(0),nx,ny,na);
// 	Eigen::MatrixXd f(2, 1);
// 	f = (A.transpose()*A).inverse()*A.transpose()*B;
// 	cout << "Matrix f" << endl;
// 	cout << f << endl;
}
