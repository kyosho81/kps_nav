#include <Eigen/Dense>

#include "Comm/Comm.h"

#include "k_means.h"


k_means::k_means()
{

}
k_means::~k_means(){

}

void k_means::add_data(const float &fx, const float &fy, const float &fa)
{
	point pt;
	pt.x = fx;
	pt.y = fy;
	pt.th = fa;
	pt.cluster = 0;

	v_dataset_.push_back(pt);
}

void k_means::clear()
{
	v_dataset_.clear();
	m_cluster_.clear();
}

bool k_means::cluster(const int &k)
{
	if ( k < 1)
	{
		return false;
	}
	cal_data(v_dataset_,k);
	return true;
}

float k_means::squareDistance(point a,point b){
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

void k_means::cal_data(std::vector<point> &dataset,const int &k){
	std::vector<point> centroid;
	int n=1;
	int len = dataset.size();
	srand((int)time(0));
	//random select centroids
	while(n<=k){
		int cen = (float)rand()/(RAND_MAX+1)*len;
		point cp(dataset[cen].x,dataset[cen].y,dataset[cen].th,n);
		centroid.push_back(cp);
		n++;
	}
	for(int i=0;i<k;i++){
		std::cout<<"x:"<<centroid[i].x<<"\ty:"<<centroid[i].y<<"\tc:"<<centroid[i].cluster<<std::endl;
	}
	//cluster
	int time = 100;
	int oSSE = INT_MAX;
	int nSSE = 0;
	while(abs(oSSE-nSSE)>=1){
		//	while(time){
		oSSE = nSSE;
		nSSE = 0;
		//update cluster for all the points
		for(int i=0;i<len;i++){
			n=1;
			float shortest = INT_MAX;
			int cur = dataset[i].cluster;
			while(n<=k){
				float temp=squareDistance(dataset[i],centroid[n-1]);			
				if(temp<shortest){
					shortest = temp;
					cur = n;
				}
				n++;
			}
			dataset[i].cluster = cur;
		}
		//update cluster centroids
		int *cs = new int[k];
		for(int i=0;i<k;i++) cs[i] = 0;
		for(int i=0;i<k;i++){
			centroid[i] = point(0,0,0,i+1);
		}
		for(int i=0;i<len;i++){
			centroid[dataset[i].cluster-1].x += dataset[i].x;
			centroid[dataset[i].cluster-1].y += dataset[i].y;
			cs[dataset[i].cluster-1]++;
		}
		for(int i=0;i<k;i++){
			centroid[i].x /= cs[i];
			centroid[i].y /= cs[i];
		}
		std::cout<<"time:"<<time<<std::endl;
		for(int i=0;i<k;i++){
			std::cout<<"x:"<<centroid[i].x<<"\ty:"<<centroid[i].y<<"\tc:"<<centroid[i].cluster<<std::endl;
		}	
		//SSE
		for(int i=0;i<len;i++){
			nSSE += squareDistance(centroid[dataset[i].cluster-1],dataset[i]);
		}
		//		time--;
	}

	
	m_cluster_.clear();
	std::vector<point>::iterator it = dataset.begin();
	for ( ; it != dataset.end() ; ++it )
	{
		m_cluster_[it->cluster].push_back(it);
	}
// 	std::fstream clustering;
// 	clustering.open("clustering.txt",std::ios::out);
// 	for(int i=0;i<len;i++){
// 		clustering<<dataset[i].x<<","<<dataset[i].y<<","<<dataset[i].cluster<<"\n";
// 	}
// 	clustering.close();
	
	//	cout<<endl;
	//	for(int i=0;i<centroid.size();i++){
	//		cout<<"x:"<<centroid[i].x<<"\ty:"<<centroid[i].y<<"\tc:"<<centroid[i].cluster<<endl;
	//	}
}
const std::map<int, std::vector<std::vector<point>::iterator>>& k_means::get_data(){
	return m_cluster_;
}
// int k_means::get_data(  std::vector<std::vector<point>::iterator> max_cluster )
// {
// 	int max_cluster_size = -1;
// 	
// 	std::map<int, std::vector<std::vector<point>::iterator>>::iterator it_max = m_cluster_.end();
// 	std::map<int, std::vector<std::vector<point>::iterator>>::iterator it =  m_cluster_.begin();
// 	
// 	for ( ; it !=  m_cluster_.end(); ++it )
// 	{
// 		int isize = it->second.size();
// 		if( isize > max_cluster_size){
// 			it_max = it;
// 			max_cluster_size = isize;
// 		}
// 	}
// 	if ( it_max != m_cluster_.end())
// 	{
// 		max_cluster = it_max->second;
// 	}
// 	return max_cluster.size();
// }
