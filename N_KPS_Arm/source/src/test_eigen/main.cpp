#include <iostream>
#include <Eigen/Dense>

#include "g2o_slam/se2.h"
#include "robot/Geometry.h"

double polyeval(Eigen::VectorXd coeffs, double x) {
	double result = 0.0;
	for (int i = 0; i < coeffs.size(); i++) {result += coeffs[i]*pow(x, i);}
	return result;
}

Eigen::VectorXd polyfit(Eigen::VectorXd xvals, Eigen::VectorXd yvals, int order) {
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
	std::cout<<A<<std::endl;

	auto Q = A.householderQr();
	auto result = Q.solve(yvals);

	//std::cout<<result<<std::endl;

	return result;
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
void m_base2world(float lx,float ly,float la,float wx,float wy,float wa,float &nx,float &ny,float &na){

	Eigen::Vector3f vl;
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
void test_eigen_tf(){
	double o1x = 1;
	double o1y = -3;
	double o1a = 1.75;
	
	double o2x = 2;
	double o2y = .05;
	double o2a = -1.57;

	g2o::tutorial::SE2 odom1(o1x,o1y,o1a);
	g2o::tutorial::SE2 odom2(o2x,o2y,o2a);

	g2o::tutorial::SE2 o2_in_o1 = odom1.inverse()*odom2;
	Eigen::Vector3d v3 = o2_in_o1.toVector();
	std::cout<<v3<<std::endl;

	std::cout<<(odom1*o2_in_o1).toVector()<<std::endl;

	float nx,ny,na;
	m_world2base(o1x,o1y,o1a,o2x,o2y,o2a,nx,ny,na);
	//World2Local(o1x,o1y,o1a,o2x,o2y,o2a,o1x,o1y,o1a);
	std::cout<<nx<<" "<<ny<<" "<<na<<std::endl;

}
void test_ch3(){
// 	Eigen::Quaterniond q1(0.35, 0.2, 0.3, 0.1);         //定义四元数q1,在这里是旋转矩阵的四元数表达
// 	Eigen::Quaterniond q2(-0.5, 0.4, -0.1, 0.2);        //定义四元数q2
// 	Eigen::Vector3d t1(0.3, 0.1, 0.1);                  //定义平移向量t1
// 	Eigen::Vector3d t2(-0.1, 0.5, 0.3);                 //定义平移向量t2
// 	Eigen::Vector3d p1(0.5, 0, 0.2);                    //定义世界坐标系下p点在第一个相机坐标系下的坐标位p1
// 
// 	Eigen::Quaterniond q1_one = q1.normalized();
// 	Eigen::Quaterniond q2_two = q2.normalized();        //对四元数q1,q2进行归一化
// 	Eigen::Matrix3d R1 = q1_one.toRotationMatrix();     //将四元数转换为旋转矩阵表示
// 	Eigen::Matrix3d R2 = q2_two.toRotationMatrix();
// 	Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity();     //定义一个4*4的变换矩阵
// 	T1.rotate ( R1 );                                         //将旋转矩阵加到变换矩阵中
// 	T1.pretranslate(Eigen::Vector3d (0.3, 0.1, 0.1));         //将平移向量加到变换矩阵中
// 	Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
// 	T2.rotate ( R2 );
// 	T2.pretranslate(Eigen::Vector3d (-0.1, 0.5, 0.3));
// 	Eigen::Vector3d p3 = T2.inverse()*T1*p1;
// 	Eigen::Vector3d p2 = T2*T1.inverse()*p1; //p1=T1*Pw(Pw为点p在世界坐标系下坐标)，p2=T2*Pw,则p2 = T2*T1.inverse()*p1
// 	std::cout << "p2 = " << p2 <<std::endl;
// 	std::cout << "p3 = " << p3 <<std::endl;


	Eigen::Quaterniond q1(0.55, 0.3, 0.2, 0.2);         //定义四元数q1,在这里是旋转矩阵的四元数表达
	Eigen::Quaterniond q2(-0.1, 0.3, -0.7, 0.2);        //定义四元数q2
	Eigen::Vector3d t1(0.7, 1.1, 0.2);                  //定义平移向量t1
	Eigen::Vector3d t2(-0.1, 0.4, 0.8);                 //定义平移向量t2
	Eigen::Vector3d p1(0.5, -0.1, 0.2);                    //定义世界坐标系下p点在第一个相机坐标系下的坐标位p1

	Eigen::Quaterniond q1_one = q1.normalized();
	Eigen::Quaterniond q2_two = q2.normalized();        //对四元数q1,q2进行归一化
	Eigen::Matrix3d R1 = q1_one.toRotationMatrix();     //将四元数转换为旋转矩阵表示
	Eigen::Matrix3d R2 = q2_two.toRotationMatrix();
	Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity();     //定义一个4*4的变换矩阵
	T1.rotate ( R1 );                                         //将旋转矩阵加到变换矩阵中
	T1.pretranslate(t1);                                      //将平移向量加到变换矩阵中
	Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
	T2.rotate ( R2 );
	T2.pretranslate(t2);
	Eigen::Vector3d p3 = T2.inverse()*T1*p1;
	Eigen::Vector3d p2 = T2*T1.inverse()*p1; //p1=T1*Pw(Pw为点p在世界坐标系下坐标)，p2=T2*Pw,则p2 = T2*T1.inverse()*p1
	std::cout << "p2 = " << p2 <<std::endl;
	std::cout << "p3 = " << p3 <<std::endl;

}
int main(){
	test_ch3();
	test_eigen_tf();
	return 0;
	int i= 6;
	Eigen::VectorXd xvals(i);
	Eigen::VectorXd yvals(i);
	xvals << 9.261977, -2.06803, -19.6663, -36.868, -51.6263, -66.3482;
	yvals << 5.17,     -2.25,    -15.306,  -29.46,  -42.85,   -57.6116;
	auto coeffs= polyfit(xvals,yvals,2);

	std::cout<<"a:"<<coeffs[2]<<" b:"<<coeffs[1]<<" c:"<<coeffs[0]<<std::endl;
	std::cout<<"x:"<<-coeffs[1]/ (coeffs[2]*2)<<std::endl;
	std::cout<< "Y(16)=" << polyeval(coeffs,16) << std::endl;
	return 0;
}
