#include <Eigen/Dense>

#include "Comm/Comm.h"

#include "pca.h"

using namespace Eigen;

pca::pca()
{

}

pca::~pca()
{

}
std::vector<Sxy> pca::get_range(){
	return block_range_;
}
SVec pca::pca2d( std::vector<SVec> &vec,const std::list<SPos> &data )
{
	SVec mean;
	mean.x_ = 0;
	mean.y_ = 0;

	vec.clear();
	block_range_.clear();

	F32 min_x = 1e10;
	F32 min_y = 1e10;
	F32 max_x = -1e10;
	F32 max_y = -1e10;

	int rows = data.size() ;
	int cols = 2 ;

	MatrixXf m( rows , cols);
	int i_ros = 0;
	std::list<SPos>::const_iterator cit = data.begin();
	for ( ; cit != data.end() ; ++cit )
	{
		const SPos &pos( *cit );
		m( i_ros , 0 ) = pos.x_;
		m( i_ros++ , 1 ) = pos.y_;
		min_x = cComm::Min( min_x, pos.x_);
		min_y = cComm::Min( min_y, pos.y_);
		max_x = cComm::Max( max_x, pos.x_);
		max_y = cComm::Max( max_y, pos.y_);
	}
	Sxy xy;
	xy.x_ = min_x;
	xy.y_ = min_y;
	block_range_.push_back(xy);
	xy.x_ = max_x;
	xy.y_ = min_y;
	block_range_.push_back(xy);
	xy.x_ = max_x;
	xy.y_ = max_y;
	block_range_.push_back(xy);
	xy.x_ = min_x;
	xy.y_ = max_y;
	block_range_.push_back(xy);
	xy.x_ = min_x;
	xy.y_ = min_y;
	block_range_.push_back(xy);
	//std::cout<<" data matrix:"<<m<<std::endl;

	Eigen::MatrixXf meanVec = m.colwise().mean();
	std::cout << "meanVec: " << std::endl << meanVec << std::endl;
	mean.x_ = meanVec(0,0);
	mean.y_ = meanVec(0,1);

	Eigen::RowVectorXf meanVecRow(Eigen::RowVectorXf::Map(meanVec.data(),m.cols()));

	Eigen::MatrixXf zeroMeanMat = m;
	zeroMeanMat.rowwise()-=meanVecRow;

	//std::cout << "zeroMeanMat: " << std::endl << zeroMeanMat << std::endl;
	
	
	float nsamples = m.rows();
	if(m.rows() > 1){
		nsamples -= 1;
	}

	Eigen::MatrixXf covMat = ( zeroMeanMat.adjoint()*zeroMeanMat) / nsamples ;
	//std::cout << "print covariance matrix: " << std::endl << covMat << std::endl;

	EigenSolver<Matrix2f> es(covMat);
	Vector2f D = es.pseudoEigenvalueMatrix().diagonal();
	Matrix2f V = es.pseudoEigenvectors();
	//std::cout<<"V:"<<V<<std::endl;

	std::vector<std::pair<int, float>> eigen_value_index;
	for (int i = 0; i < 2; ++i)
		eigen_value_index.push_back(std::make_pair(i,D[i]));
	auto f = [](std::pair<int, float> a, std::pair<int, float>b)->bool {return a.second > b.second;  };
	sort(eigen_value_index.begin(), eigen_value_index.end(), f);


	Matrix2f tranform_matrix;
	for (int i = 0; i < 2; ++i)
	{
		int idx = eigen_value_index[i].first;
		tranform_matrix.col(i) = V.col(idx);

	}   
	
	SVec v;
	v.x_ = V(0,0);
	v.y_ = V(1,0);
	vec.push_back(v);
	v.x_ = V(0,1);
	v.y_ = V(1,1);
	vec.push_back(v);


	return mean;
	//
	//auto res = m*V;
}
