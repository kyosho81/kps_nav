#include <iostream>
#include <cmath>
using namespace std; 

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

int main( int argc, char** argv )
{
	// ��Z��ת90�ȵ���ת����
	Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d(0,1,1)).toRotationMatrix();

	Sophus::SO3 SO3_R(R);               // Sophus::SO(3)����ֱ�Ӵ���ת������
	Sophus::SO3 SO3_v( 0, 0, M_PI/2 );  // ��ɴ���ת�������� x y z ����ת���ٶ�
	Eigen::Quaterniond q(R);            // ������Ԫ��
	Sophus::SO3 SO3_q( q );
	// ������﷽ʽ���ǵȼ۵�
	// ���SO(3)ʱ����so(3)��ʽ��� ��

	cout<<"SO(3) from matrix: "<<SO3_R<<endl;
	cout<<"SO(3) from vector: "<<SO3_v<<endl;
	cout<<"SO(3) from quaternion :"<<SO3_q<<endl;



	// ʹ�ö���ӳ�������������
	Eigen::Vector3d so3 = SO3_R.log();
	cout<<"so3 = "<<so3.transpose()<<endl;
	// hat Ϊ���������Գƾ���
	cout<<"so3 hat=\n"<<Sophus::SO3::hat(so3)<<endl;
	// ��Եģ�veeΪ���ԳƵ�����

	// �����Ŷ�ģ�͵ĸ���
	Eigen::Vector3d update_so3(1e-4, 0, 0); //���������Ϊ��ô��
	Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3)*SO3_R;
	cout<<"SO3 updated = "<<SO3_updated<<endl;

	/********************���ȵķָ���*****************************/
	cout<<"************���Ƿָ���*************"<<endl;
	// ��SE(3)������ͬС��
	Eigen::Vector3d t(1,0,0);           // ��X��ƽ��1
	Sophus::SE3 SE3_Rt(R, t);           // ��R,t����SE(3)
	Sophus::SE3 SE3_qt(q,t);            // ��q,t����SE(3)
	cout<<"SE3 from R,t= "<<endl<<SE3_Rt<<endl;
	cout<<"SE3 from q,t= "<<endl<<SE3_qt<<endl;
	// �����se(3) ��һ����ά���������������typedefһ��
	typedef Eigen::Matrix<double,6,1> Vector6d;
	Vector6d se3 = SE3_Rt.log();
	cout<<"se3 = "<<se3.transpose()<<endl;
	// �۲�������ᷢ����Sophus�У�se(3)��ƽ����ǰ����ת�ں�.
	// ͬ���ģ���hat��vee�������
	//hat �����������Գƾ���
	//vee �Ƿ��Գƾ�������
	cout<<"se3 hat = "<<endl<<Sophus::SE3::hat(se3)<<endl;
	cout<<"se3 hat vee = "<<Sophus::SE3::vee( Sophus::SE3::hat(se3) ).transpose()<<endl;//transpose������Ϊ���������һЩ

	// �����ʾһ�¸���
	Vector6d update_se3; //������
	update_se3.setZero();
	update_se3(0,0) = 1e-4;
	Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3)*SE3_Rt;
	cout<<"SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;

	return 0;
}
