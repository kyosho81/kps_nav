#ifndef _ASTAR_KYOSHO_20110802_
#define _ASTAR_KYOSHO_20110802_


#include <map>
#include <assert.h>
#include <iostream>
#include <fstream>


#include "MyDefine.h"
#include "RobotStruct.h"
#include "Rand.hpp"

class GridMap;

typedef struct _SRandXY
{
	S8 x;
	S8 y;
}SRandXY;



class Node
{
public:
	Node(U32 in_x,U32 in_y,S8 in_value);
 	Node(const Node* node);
	~Node();


	inline void AddRefNode(Node* p_node);


	Node* p_parent;
	Node* p_next;


	U32 x;       
	U32 y;		  
	S8 value;    

	U32 g;       
	U32 h;		  
	U32 f;		   //g+h

	

	typedef std::vector<Node*> vNode;
	vNode node_ref_list;     


};


class AStar
{
	typedef std::map<U32,Node*> mNode;


public:
	AStar();
	~AStar();

	void GetWidthHeight(U32 &x,U32 &y);
	void Clear();

	//void InitReference();
	//void Init(U32 x,U32 y);

	//void Init(unsigned char* data,U32 x,U32 y);
	void Init_map();

	void ClearNodes() ;

	//bool SetStart(U32 gx,U32 gy);
	bool SetStart(F32 x,F32 y);
	bool SetEnd(U32 gx,U32 gy);
	bool SetEnd(F32 x,F32 y);
	Node* GetNode(F32 x,F32 y);
	Node* GetNode(U32 gx,U32 gy);
	S8 GetNodeValue(U32 gx,U32 gy);
	Node* CreateNode(U32 gx,U32 gy,S8 value);
	
	Node* CheckList(Node* node, Node* node_tmp); 
	
	void AddToOpen(Node* p_node);

	bool GeneratePath();
	void stop();
	void GetPath(std::vector<S16xy> &path);
	void GetPath(std::list<SGridXY> &path);
	void GetSmoothPath(std::list<SGridXY> &path);

	int SerachStep();
	Node* GetBest();

	void AddRefNode(Node* p_node);
	void CreateChildren(Node* p_node);
	
	void setValue(U32 gx,U32 gy,U32 f);
	void LinkChild(Node* node, Node* temp);

	bool Reachable(Node* node, Node* temp);
	U32 CostFunction(Node* node, Node* temp);

	//void get_protential(GridMap* map);

	S8 Get_grid_value(const U32& gx,const U32& gy);
	bool check_available(F32 x,F32 y);
private:

	MyRand rd_;
	SRandXY rxy[8];

	mNode NodeAll;

	U32 xWidth;
	U32 yHeight;

	U32 xStart;
	U32 yStart;

	U32 xEnd;
	U32 yEnd;

	U32  point_width;
	
	Node* open_list;
	Node* clost_list;
	Node* node_best;

	int retval_;
	long rearch_step_;

private:
	GridMap* global_map_;
	GridMap* laser_map_;
};


#endif //_ASTAR_KYOSHO_20110802_