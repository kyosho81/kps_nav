#if 0
#include <stdlib.h>
#include "Comm/Rand.hpp"

#include "trans_dev.h"
#include "Comm.h"
#include <iostream>
#include <fstream>

//
#include "Comm/TimerDiff.h"
#include "trans_dev/can_base.h"
#include "trans_dev/canalyst2.h"
#include "trans_dev/can_tcp.h"
#include "trans_dev/can_socket.h"

int main(int argc, char *argv[])
{
	
#if 0
	std::string s1 = "1970-01-01 00:00:00.000000";
	boost::posix_time::ptime epoch(boost::posix_time::time_from_string(s1));
	//boost::posix_time::ptime epoch(boost::gregorian::date(1970, boost::gregorian::Jan, 1));
	boost::posix_time::ptime pt_now(
		boost::posix_time::microsec_clock::universal_time());

	std::cout<<"ut:"<<cTimerDiff::time_to_string(pt_now)<<std::endl;

	boost::posix_time::time_duration time_from_epoch =
		pt_now - epoch;
	long long dt = time_from_epoch.total_microseconds();

	 
// 	boost::posix_time::ptime pt = boost::posix_time::from_time_t(dt);
// 	std::string s2 = "1-01-01 00:00:00.000000";
// 	boost::posix_time::ptime epochdt(boost::posix_time::time_from_string(s2));
//	
//	long long dt2 = time_from_epoch2.total_microseconds();

	boost::posix_time::time_duration time_from_epoch2 = boost::posix_time::microseconds(dt);
	epoch += time_from_epoch2;
	std::cout<<"epo:"<<cTimerDiff::time_to_string(epoch)<<std::endl;;
	return 0;

#endif



	std::cout<<"ut:"<<cTimerDiff::get_now_ut()<<std::endl;
	std::string st;

	U64 ut = cTimerDiff::total_ms();
	cTimerDiff::lltime_to_string(st,ut);
	std::cout<<"llt 111:"<<st<<std::endl;
	SLEEP(1000);
	ut = cTimerDiff::total_ms();
	cTimerDiff::lltime_to_string(st,ut);
	std::cout<<"llt 222:"<<st<<std::endl;
}

#endif

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


int main() {
	// txt�������ļ�·��
	const string fileName = "./plot_test.TXT";

	// �����Ǽ������
	const int N = 2;

	// ��������vector
	vector<float> x, y;

	// ��ȡ�ļ�
	ifstream f(fileName);

	if (!f) {
		cout << "�����ļ���ʧ��" << endl;
		exit(EXIT_FAILURE);
	}

	float tempx, tempy;

	while (f >> tempx >> tempy) {
		x.push_back(tempx);
		y.push_back(tempy);
	}

	if (x.size() != y.size()) {
		cout << "�����ļ���������" << endl;
		exit(EXIT_FAILURE);
	}

	// ����A����
	Eigen::MatrixXd A(x.size(), N + 1);

	for (unsigned int i = 0; i < x.size(); ++i) {  // �������е�

		for (int n = N, dex = 0; n >= 1; --n, ++dex) {  // ����N��1��
			A(i, dex) = pow(x[i], n);
		}

		A(i, N) = 1;  //
	}

	// ����B����
	Eigen::MatrixXd B(y.size(), 1);

	for (unsigned int i = 0; i < y.size(); ++i) {
		B(i, 0) = y[i];
	}

	// ��������W
	Eigen::MatrixXd W;
	W = (A.transpose() * A).inverse() * A.transpose() * B;

	// ��ӡW���
	cout << W << endl;
}