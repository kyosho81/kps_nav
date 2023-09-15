#include <iostream>
#include <assert.h>

//octomap
#include "octomap/octomap.h"
using namespace std;
using namespace octomath;

void test_bbx(octomap::OcTree *tree);

int main( int argc, char** argv )
{
	if (argc != 2)
	{
		cout<<"Usage: pcd2octomap <input_file> <output_file>"<<endl;
		return -1;
	}

	string output_file = argv[1];


	cout<<"point cloud loaded, piont size = "<<endl;

	//声明octomap变量
	cout<<"copy data into octomap..."<<endl;
	// 创建八叉树对象，参数为分辨率，这里设成了0.05
	octomap::OcTree tree( 0.05 );

	for ( int i = 0 ; i < 10 ; ++i){
	
		// 将点云里的点插入到octomap中
		tree.updateNode( octomap::point3d((float)i*0.1,(float)i*0.2,(float)i*0.3), true );
	}

	// 更新octomap
	tree.updateInnerOccupancy();

	test_bbx(&tree);

	// 存储octomap
	tree.writeBinary( output_file );
	cout<<"done."<<endl;

	return 0;
}
void test_bbx(octomap::OcTree *tree){

	octomap::OcTreeKey bbxMinKey, bbxMaxKey;
// 	double temp_x,temp_y,temp_z;
// 	tree->getMetricMin(temp_x,temp_y,temp_z);
// 	octomap::point3d bbxMin = octomap::point3d(float(temp_x), float(temp_y), float(temp_z));
// 
// 	tree->getMetricMax(temp_x,temp_y,temp_z);
// 	octomap::point3d bbxMax = octomap::point3d(float(temp_x), float(temp_y), float(temp_z));
// 
// 	tree->coordToKeyChecked(bbxMin, bbxMinKey);
// 	tree->coordToKeyChecked(bbxMax, bbxMaxKey);
// 
// 	octomap::OcTree::leaf_bbx_iterator it_bbx = tree->begin_leafs_bbx(bbxMinKey,bbxMaxKey);
// 	it_bbx == tree->begin_leafs_bbx(bbxMinKey,bbxMaxKey);
// 	octomap::OcTree::leaf_bbx_iterator end_bbx = tree->end_leafs_bbx();
// 	end_bbx == tree->end_leafs_bbx();

	octomap::point3d bbxMin(-1.0, -1.0, - 1.0);
	octomap::point3d bbxMax(3.0, 2.0, 1.);

	tree->coordToKeyChecked(bbxMin, bbxMinKey);
	tree->coordToKeyChecked(bbxMax, bbxMaxKey);

	typedef octomap::unordered_ns::unordered_map<octomap::OcTreeKey, double, octomap::OcTreeKey::KeyHash> KeyVolumeMap;

	KeyVolumeMap bbxVoxels;

	size_t count = 0;
	for(octomap::OcTree::leaf_bbx_iterator it = tree->begin_leafs_bbx(bbxMinKey,bbxMaxKey), end=tree->end_leafs_bbx();
		it!= end; ++it)
	{
		count++;
		octomap::OcTreeKey currentKey = it.getKey();
		// leaf is actually a leaf:
		assert(!tree->nodeHasChildren(&(*it)));

		// leaf exists in tree:
		//OcTreeNode* node = tree->search(currentKey);
		//assert(node);
		//EXPECT_EQ(node, &(*it));
		// all leafs are actually in the bbx:
		for (unsigned i = 0; i < 3; ++i){
			//      if (!(currentKey[i] >= bbxMinKey[i] && currentKey[i] <= bbxMaxKey[i])){
			//        std::cout << "Key failed: " << i << " " << currentKey[i] << " "<< bbxMinKey[i] << " "<< bbxMaxKey[i]
			//             << "size: "<< it.getSize()<< std::endl;
			//      }
			assert(currentKey[i] >= bbxMinKey[i] && currentKey[i] <= bbxMaxKey[i]);
			
		}

		octomap::point3d b = tree->keyToCoord(currentKey);
		std::cout<<"b:"<<b<<std::endl;

		bbxVoxels.insert(std::pair<octomap::OcTreeKey,double>(currentKey, it.getSize()));
	}
}