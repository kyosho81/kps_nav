
// #include <stdio.h>
// #include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <Eigen/Dense>

#include "Comm.h"
#include "robot/k_means.h"
#include "Rand.hpp"
// #include "interprocess/mu_shared_range.hpp"
// #include "interprocess/shared_range.hpp"


int main(int argc, char* argv[]){
	MyRand rd;

	k_means km;
	std::vector<point> vp;
	for (int i = 0 ; i < 300 ; ++i)
	{
		point p;
		F32 c = (i / 100)*10 + 1;
		p.x = rd.randFloat(-1.0,1.0) + c;
		p.y = rd.randFloat(-1.0,1.0) + c;
		p.cluster = 0;
		km.add_data(p.x,p.y,p.th);
		vp.push_back(p);
	}
	
	km.cluster(3);

	std::map<int, std::vector<std::vector<point>::iterator>> max_cluster;
	max_cluster = km.get_data();

	return 0;
}
