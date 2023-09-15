#if 0
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
#include "pca.h"
#include "bmd5.hpp"
// #include "interprocess/mu_shared_range.hpp"
// #include "interprocess/shared_range.hpp"
#include "interprocess/shared_pool.hpp"

using namespace Eigen;

void shutdown(int sig)
{
	std::cout<<"ctrl c shut down"<<std::endl;
	//brun = false;
	shared_pool::destructor();
	SLEEP(500);

	exit(0);

	return;
}

void init_shared_pool(char *argv[]){

	shared_pool::init(argv);
	std::cout<<"shared test init call back"<<std::endl;
}

int main(int argc, char* argv[]){
	
	CMD5 md5(10240);
	const clock_t start = clock();
	const char *p = "abc";
	if (argv[1][0] == '-' && argv[1][1] == 's')
		md5.MD5String(argv[2]);
	else if (argv[1][0] == '-' && argv[1][1] == 'f')
		md5.MD5File(argv[2]);
	else
		md5.MD5Binary(p, 3);
	const double ms = 1000.0 * (clock() - start) / CLOCKS_PER_SEC;
	std::cout << md5.MD5Hex().c_str() << std::endl;
	std::cout << ms << " ms/n";
	return 0;


	std::list<SPos> data;
	SPos pos;
	memset(&pos,0,sizeof(SPos));

	for ( int i = 0 ; i < 10 ; ++i){
		pos.x_ = i;
		data.push_back(pos);
	}
	std::vector<SVec> vec;
	SVec mean = Singleton_PCA::get_mutable_instance().pca2d(vec,data);
	std::vector<Sxy> rangle_list = Singleton_PCA::get_mutable_instance().get_range();

	SPos mid_pos;
	if ( vec.size() > 0 )
	{
		mid_pos.th_ = VecPosition(vec[0].x_,vec[0].y_).getDirection();
		mid_pos.th_ = -Deg2Rad(mid_pos.th_);
	}
	mid_pos.x_ = mean.x_;
	mid_pos.y_ = mean.y_;

}
int main2(int argc, char* argv[]){

#if 0
	//MatrixXf m(10, 3);
	//Matrix3f cov_matrix;

	for(int i=0 ; i<3 ; ++i){
		for (int j = 0; j < 3; ++j)
		{           
			VectorXf v1 = m.col(i);
			VectorXf v2 = m.col(j);
			float mean_1 = v1.mean();
			float mean_2 = v2.mean();           
			for (int k = 0; k < v1.size(); ++k)
			{
				v1[k] -= mean_1;
				v2[k] -= mean_2;
			}           
			float sum = v1.dot(v2);
			sum /= 9;
			cov_matrix(i, j) = cov_matrix(j, i) = sum;
		}       
	}
	// 
	EigenSolver<Matrix3f> es(cov_matrix);
	Vector3f D = es.pseudoEigenvalueMatrix().diagonal();//
	Matrix3f V = es.pseudoEigenvectors();    // 
	std::cout<<"D:"<<D<<std::endl;
	std::cout<<"V:"<<V<<std::endl;

	// 
	std::vector<std::pair<int, float>> eigen_value_index;
	for (int i = 0; i < 3; ++i)
		eigen_value_index.push_back(std::make_pair(i,D[i]));
	auto f = [](std::pair<int, float> &a, std::pair<int, float>&b)->bool {return a.second > b.second;  };
	sort(eigen_value_index.begin(), eigen_value_index.end(), f);              

	Matrix3f tranform_matrix;
	for (int i = 0; i < 3; ++i)
	{
		int idx = eigen_value_index[i].first;
		tranform_matrix.col(i) = V.col(idx);
	}   


	auto res = m*V;
#else
	std::vector<SVec> vec;
	std::list<SPos> data;
	SPos p;
	p.x_ = 1.2f; p.y_ =2.5f; 
	data.push_back(p);
	p.x_ = -3.6f; p.y_ =9.2f;
	data.push_back(p);
	p.x_ = 4.3f; p.y_ =1.3f;
	data.push_back(p);
	p.x_ = 4.3f; p.y_ =1.3f;
	data.push_back(p);
	p.x_ = 4.3f; p.y_ =1.3f;
	data.push_back(p);
	p.x_ = 4.3f; p.y_ =1.3f;
	data.push_back(p);
	p.x_ = 4.3f; p.y_ =1.3f;
	data.push_back(p);
	

	Singleton_PCA::get_mutable_instance().pca2d(vec,data);
// 	MatrixXf m(3,4);
// 	m<<1.2f, 2.5f ,5.6, -2.5,
// 	  -3.6f, 9.2f ,0.5, 7.2,
// 	   4.3f, 1.3f ,9.4 ,-3.4;
	 
 	MatrixXf m(7,2);
 	m<<1.2f, 2.5f ,
 		-3.6f, 9.2f ,
 		4.3f, 1.3f ,
		4.3f, 1.3f ,
		4.3f, 1.3f ,
		4.3f, 1.3f ,
		4.3f, 1.3f ;

	 int rows = m.rows() ;
	 int cols = m.cols() ;

	fprintf(stderr, "source matrix:\n");
	std::cout << m << std::endl;

	fprintf(stdout, "\nEigen implement:\n");

	Eigen::MatrixXf meanVec = m.colwise().mean();
	std::cout << "print mean: " << std::endl << meanVec << std::endl;
#if 0
	Eigen::MatrixXf tmp(rows, cols);
	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < cols; ++x) {
			tmp(y, x) = m(y, x) - meanVec(0, x);
		}
	}
#else

	Eigen::RowVectorXf meanVecRow(Eigen::RowVectorXf::Map(meanVec.data(),m.cols()));
	std::cout<<"meanVecRow:"<<meanVecRow<<std::endl;
	Eigen::MatrixXf zeroMeanMat = m;
	zeroMeanMat.rowwise()-=meanVecRow;

#endif
	std::cout << "zeroMeanMat: " << std::endl << zeroMeanMat << std::endl;

	//Eigen::MatrixXf covar = (zeroMeanMat.adjoint() * zeroMeanMat) /*/ float(nsamples - 1)*/;
	float nsamples = m.rows();
	if(m.rows() > 1){
		nsamples -= 1;
	}

	Eigen::MatrixXf covMat = ( zeroMeanMat.adjoint()*zeroMeanMat) / nsamples ;
	std::cout << "print covariance matrix: " << std::endl << covMat << std::endl;

	// 	
	EigenSolver<Matrix2f> es(covMat);
	Vector2f D = es.pseudoEigenvalueMatrix().diagonal();// 
	Matrix2f V = es.pseudoEigenvectors();    //
	std::cout<<"D:"<<D<<std::endl;
	std::cout<<"V:"<<V<<std::endl;

	// 
	std::vector<std::pair<int, float>> eigen_value_index;
	for (int i = 0; i < 2; ++i)
		eigen_value_index.push_back(std::make_pair(i,D[i]));
	//auto f = [](std::pair<int, float> &a, std::pair<int, float>&b)->bool {return a.second > b.second;  };
	//sort(eigen_value_index.begin(), eigen_value_index.end(), f);               

	
	Matrix2f tranform_matrix;
	for (int i = 0; i < 2; ++i)
	{
		int idx = eigen_value_index[i].first;
		tranform_matrix.col(i) = V.col(idx);
	}   
	std::cout<<"tranform_matrix:"<<tranform_matrix<<std::endl;


	auto res = m*V;

#endif
	system("pause");
	return 0;
}
#else
#include <iostream>

#include <boost/interprocess/allocators/node_allocator.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/offset_ptr.hpp>

#include <boost/container/string.hpp>
#include <boost/lexical_cast.hpp>

namespace bipc = ::boost::interprocess;
typedef bipc::managed_mapped_file managed_mapped_file_t;
typedef bipc::managed_mapped_file::segment_manager mapped_segment_manager_t;

typedef bipc::node_allocator<float, mapped_segment_manager_t> vec_allocator_t;
typedef bipc::vector<float, vec_allocator_t> vector_t;

struct Msg
{
	Msg(const vec_allocator_t &vec_alloc) : score(vec_alloc){}

	uint32_t id;
	uint32_t age;
	vector_t score;
};

typedef std::pair<const uint32_t, Msg> pair_t;
typedef bipc::node_allocator<pair_t, mapped_segment_manager_t> allocator_t;
typedef std::less<uint32_t> less_t;

typedef bipc::map<uint32_t, Msg, less_t, allocator_t> msg_map_t;
typedef msg_map_t::iterator map_iter_t;

int main()
{
	managed_mapped_file_t obj_mapped_file(bipc::open_or_create, \
		"./msg_map_vector_construct.mmap", 1600*1024*1024);
	msg_map_t *p_msg_map = obj_mapped_file.find_or_construct<msg_map_t>("msg_map")(\
		less_t(), obj_mapped_file.get_segment_manager());
	if(NULL == p_msg_map)
	{
		std::cerr<<"construct msg_map failed"<<std::endl;
		return -1;
	}

	vec_allocator_t obj_alloc(obj_mapped_file.get_segment_manager());

	for(int i = 0; i < 10; ++i)
	{ 
		map_iter_t itr = p_msg_map->find(i);
		if(itr == p_msg_map->end())
		{
			std::cout<<"not find:"<<i<<" insert:"<<i<<std::endl;

			Msg msg(obj_alloc);
			msg.id = i;
			msg.age = 100 +i;
			msg.score.push_back(i);
			msg.score.push_back(i + 1);

			p_msg_map->insert(std::pair<uint32_t, Msg>(i, msg));
		}
		else
		{
			std::cout<<"find:"<<i<<" data:"<<itr->second.age;
			std::cout<<" score:";
			for(int j = 0; j < itr->second.score.size(); ++j)
				std::cout<<itr->second.score[j]<<" ";
			std::cout<<std::endl;
		}
	}

	return 0;
}

#endif