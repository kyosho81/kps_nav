#include <cstdlib>
#include "math.h"
//#include "Geometry.h"
//#include <boost/bind.hpp>
#include "mapserver/MapServer.h"
#include "mapserver/GridMap.h"
#include "bag/cloest_filter.h"

#include "robot/Astar.h"

Node::Node( U32 in_x,U32 in_y,S8 in_value )
{
	x = in_x;
	y = in_y;
	value = in_value ;

	g = 0;
	h = 0;
	f = 0;

	p_parent = NULL;
	p_next = NULL;


	node_ref_list.clear();
}

Node::Node( const Node* node )
{
	assert(node !=  NULL);
	if (node != NULL)
	{
		x = node->x;
		y = node->y;
		value = node->value ;

		g = 0;
		h = 0;
		f = 0;

		p_parent = NULL;
		p_next = NULL;


		node_ref_list = node->node_ref_list;
	}

}

Node::~Node()
{

}

void Node::AddRefNode( Node* p_node )
{
	if (!p_node)
	{
		return;
	}
	node_ref_list.push_back(p_node);
}




AStar::AStar()
{
	xWidth = 0;
	yHeight = 0;

	xStart = 0;
	yStart = 0;

	xEnd = 0;
	yEnd = 0;

	point_width = 10;

	open_list = 0;
	clost_list = 0;
	node_best = 0;

	global_map_ = 0;
	laser_map_ = 0;

	retval_ = -1;
	rearch_step_ = 0;

	rxy[0].x = -1;
	rxy[0].y = -1;

	rxy[1].x = -1;
	rxy[1].y = 0;

	rxy[2].x = -1;
	rxy[2].y = 1;

	rxy[3].x = 0;
	rxy[3].y = 1;

	rxy[4].x = 1;
	rxy[4].y = 1;

	rxy[5].x = 1;
	rxy[5].y = 0;

	rxy[6].x = -1;
	rxy[6].y = -1;

	rxy[7].x = 1;
	rxy[7].y = -1;
}

AStar::~AStar()
{

	Clear();
}

void AStar::GetWidthHeight( U32 &x,U32 &y )
{
	x = xWidth;
	y = yHeight;
}

void AStar::Clear()
{
	for(U32 index = 0; index <NodeAll.size();++index)
	{

		assert(NodeAll[index] != NULL);
		delete NodeAll[index];
	}
	NodeAll.clear();
	
}

void AStar::Init_map()
{
	
// 	GridMap* gmap;
// 	gmap_ = gmap;
// 	if(!gmap_)
// 		return;
// 
// 	xWidth = gmap_->Get_grid_width();
// 	yHeight = gmap_->Get_grid_height();
	global_map_ = MAP_SERVER.GetGridMap(SHARED_GLOBAL_INF_MAP);
	laser_map_ = MAP_SERVER.GetGridMap(SHARED_LASER_INF_MAP);

	if( !global_map_ || !laser_map_){
		std::cout<<"err map load"<<std::endl;
		return;
	}

 	xWidth = global_map_->Get_grid_width();
 	yHeight = global_map_->Get_grid_height();
}


void AStar::ClearNodes()
{
	Node* temp = NULL;

	if (open_list) {
		while (open_list) {
			temp = open_list->p_next;

			delete open_list;

			open_list = temp;
		}
	}

	if (clost_list) {
		while (clost_list) {
			temp = clost_list->p_next;

			delete clost_list;

			clost_list = temp;
		}
	}
}

// bool AStar::SetStart( U32 gx,U32 gy )
// {
// 	if(( gx <= xWidth) && (gy <= yHeight))
// 	{
// 		ClearNodes();
// 
// 		xStart = gx;
// 		yStart = gy;
// 		assert(gx*gy<NodeAll.size());
// 		Node* node_start = NodeAll[gx+xWidth*gy]; 
// 
// 		//todo
// 		Node* node_tmp = new Node(node_start);
// 		AddToOpen(node_tmp);
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// }
bool AStar::SetStart( F32 x,F32 y )
{
	Node* node = GetNode(x,y);
	if( !node ){
		return false;
	}

	ClearNodes();

	xStart = node->x;
	yStart = node->y;

	AddRefNode(node);
	Node* node_tmp = new Node(node);
	
	AddToOpen(node_tmp);

	return true;



	
}
bool AStar::SetEnd( F32 x,F32 y ){
	
	Node* node = GetNode(x,y);
	
	if(!node){
		return false;
	}

	SetEnd(node->x,node->y);

	return true;
}
bool AStar::SetEnd( U32 gx,U32 gy )
{
	if(( gx <= xWidth) && (gy <= yHeight))
	{
		xEnd = gx;
		yEnd = gy;
		
		long dx = xEnd - xStart;
		long dy = yEnd - yStart;
		rearch_step_ = abs( dx) + abs(dy);
		rearch_step_ *= 100;

		return true;
	}
	else
	{
		return false;
	}
}

Node* AStar::CheckList( Node* node, Node* node_tmp )
{
	while (node) {
		if ((node->x == node_tmp->x) && (node->y ==node_tmp->y))return node;

		node = node->p_next;
	}

	return NULL;
}

void AStar::AddToOpen( Node* p_node )
{

	Node* node = open_list;
	Node* prev = NULL;

	if (!open_list) {
		open_list = p_node;
		open_list->p_next = NULL;

		return;
	}

	while(node) {
		if (p_node->f > node->f) {
			prev = node;
			node = node->p_next;
		} else {
			if (prev) {
				prev->p_next = p_node;
				p_node->p_next = node;

			} else {
				Node* temp = open_list;

				open_list = p_node;
				open_list->p_next = temp;

			}

			return;
		}
	}

	prev->p_next = p_node;

}

bool AStar::GeneratePath()
{
	retval_ = 0;

	while (retval_ == 0) {
		retval_ = SerachStep();

		if(!rearch_step_--){
			retval_ = -1;
			std::cout<<"time out!quit!!!!"<<rearch_step_<<std::endl;
			break;
		}
	}

	if (retval_ == -1 || !node_best) {
		node_best = NULL;
		return false;
	}

	return true;
}
void AStar::stop(){
	retval_ = -1;
}
void AStar::GetPath(std::vector<S16xy> &path)
{
	path.clear();


	Node* node = node_best;
	while (node)
	{

		//gmap_->setgrid(node->x,node->y,-99);
		S16xy gxy;
		gxy.x_ = node->x;
		gxy.y_ = node->y;

		path.push_back(gxy);
		node = node->p_parent;

	}
	std::cout<<"search node size:"<<NodeAll.size()<<std::endl;
	std::cout<<"path count:"<<path.size()<<std::endl;
}
void AStar::GetPath(std::list<SGridXY> &path){
	path.clear();

	std::list<SPos> wpath;

	Node* node = node_best;

	SGridXY sxy;
	while (node)
	{

		//gmap_->setgrid(node->x,node->y,-99);
		sxy.x_ = node->x;
		sxy.y_ = node->y;
		path.push_front(sxy);
		node = node->p_parent;

	}

	
	std::cout<<"search node size:"<<NodeAll.size()<<std::endl;
	std::cout<<"path count:"<<path.size()<<std::endl;
}
void AStar::GetSmoothPath(std::list<SGridXY> &path){
	path.clear();

	std::list<SPos> wpath;

	Node* node = node_best;

	while (node)
	{

		//gmap_->setgrid(node->x,node->y,-99);
		SPos pos;
		pos.th_;
		global_map_->grid2world(node->x,node->y,pos.x_,pos.y_);
		wpath.push_front(pos);

		node = node->p_parent;

	}

	cloest_filter filter;
	filter.bind_check( boost::bind(&AStar::check_available,this,_1,_2) );
	filter.make_cloest(wpath);

	SGridXY sxy;
	U32 gx = 0;
	U32 gy = 0;

	std::list<SPos>::iterator it = wpath.begin();
	for (;it != wpath.end() ; ++it)
	{
		
		global_map_->world2grid( it->x_,it->y_,gx,gy );
		sxy.x_ = gx;
		sxy.y_ = gy;
		path.push_back(sxy);
	}

	std::cout<<"search node size:"<<NodeAll.size()<<std::endl;
	std::cout<<"path count:"<<path.size()<<std::endl;
}
int AStar::SerachStep()
{

	
	if (!(node_best = GetBest()))
		return -1;

	
	if ((node_best->x == xEnd) && (node_best->y == yEnd)) 
		return 1;
	
	CreateChildren(node_best);

	return 0;
}

Node* AStar::GetBest()
{
	if (!open_list) return NULL;

	Node* temp = open_list, *temp2 = clost_list;
	open_list = temp->p_next;

	clost_list = temp;
	clost_list->p_next = temp2;

	return temp;
}

void AStar::CreateChildren( Node* p_node )
{
	Node::vNode::iterator it = p_node->node_ref_list.begin();
	for (;it != p_node->node_ref_list.end();++it)
	{
		LinkChild(p_node,*it);
	}
}
void AStar::setValue(U32 gx,U32 gy,U32 f){
	Node* node = 0;

	U32 index = gx+xWidth*gy;

	mNode::iterator it = NodeAll.find(index);

	if ( it != NodeAll.end() )
	{
		node = it->second;
		node->f = f;
	}
}
void AStar::LinkChild( Node* node, Node* temp )
{

	if(!Reachable(node,temp)) 
		return ;

	U32 g = node->g + CostFunction(node, temp);

	Node* check = NULL;


	if (check = CheckList(open_list, temp)) {


		// A better route found, so update
		// the node and variables accordingly.
		if (g < check->g) {
			check->p_parent = node;
			check->g = g;
			check->f = g + check->h;

			//setValue(check->x,check->y,check->f);
		}
		
	} else if (check = CheckList(clost_list, temp)) { 


		if (g < check->g) {
			check->p_parent = node;
			check->g = g;
			check->f = g + check->h;

			//setValue(check->x,check->y,check->f);
		}
		
	} else {
		//todo 
		AddRefNode(temp);
		Node* newnode = new Node(temp);

		newnode->p_parent = node;
		newnode->g = g;
 		F32 dx = newnode->x;
 		dx = dx - xEnd;
 		F32 dy = newnode->y;
 		dy = dy - yEnd;
		newnode->h = sqrt(dx*dx + dy*dy);
		newnode->f = newnode->g + newnode->h;
		
		//setValue(newnode->x,newnode->y,newnode->f);

		AddToOpen(newnode);

	}
}
S8 AStar::Get_grid_value(const U32& gx,const U32& gy){
	S8 value = MAP_SERVER.getCost(gx,gy,WORLD_LAYER,SHARED_LASER_INF_MAP);
	Node* node = GetNode(gx,gy);
	if((node) && ( node->value > value))
	{
		value = node->value;
	}
	return value;
}
bool AStar::Reachable( Node* node, Node* temp )
{

  	S8 value = MAP_SERVER.getCost(temp->x,temp->y,WORLD_LAYER,SHARED_LASER_INF_MAP);
  	if (value > 0)
  	{
 		return false;
 	}else if (value < 0){
 		if(MAP_OUT != value){
 			return false; 
 		}
 	}
	if((temp->value > 70) || (temp->value < 0)){
 		return false;
 	}
	return true;

}

U32 AStar::CostFunction( Node* node, Node* temp )
{
	S32 dx = (S32)(node->x) - temp->x;
	S32 dy = (S32)(node->y) - temp->y;
	S32 lValue = abs(dx) + abs(dy);
	
// 	S16 nxy = GetNodeValue(node->x,node->y);
// 	nxy = GetNodeValue(temp->x,temp->y) - nxy;
// 	
// 	if (nxy < 0)
// 	{
// 		nxy = 0;
// 	}else if(nxy > 0){
// 		
// 		nxy = 10;
// 	}
// 	
	
	if (lValue > 1)
	{
		return 2;
	}
	else{
		return 1;
	}

}

 Node* AStar::GetNode( F32 x,F32 y )
 {
 	U32 gx = 0;
 	U32 gy = 0;
 
 
 	if (!global_map_->world2grid(x,y,gx,gy))
 	{
 		return 0;
 	}
 	
 	return GetNode(gx,gy);
 
 }

Node* AStar::GetNode( U32 gx,U32 gy )
{
	Node* node = 0;

	U32 index = gx+xWidth*gy;

	mNode::iterator it = NodeAll.find(index);

	if ( it != NodeAll.end() )
	{
		node = it->second;

	}else{



		S8 value = 0;
		if (global_map_->getgrid((U32)gx,(U32)gy,value))
		{
			if (value < 0)
			{
				std::cout<<"get map unknown! gx:"<<gx<<" gy:"<<gy<<" value:"<<int(value)<<std::endl;
				
				return 0;
			}
			
			node = new Node(gx,gy,value);
			NodeAll[index] = node;
		}
	}
	return node;

}

inline S8 AStar::GetNodeValue(U32 gx,U32 gy){
	Node* node = GetNode(gx,gy);
	if (node)
	{
		return node->value;
	}
	std::cout<<"out of map grid"<<std::endl;
	return 0;
}

void AStar::AddRefNode( Node* p_node )
{
	if (p_node->node_ref_list.size() > 0)
	{
		return;
	}
	Node* node_ref = 0;
	////left down
	//Node* node_ref = GetNode(p_node->x -1, p_node->y -1);
	//p_node->AddRefNode(node_ref);

	////left mid
	//node_ref = GetNode(p_node->x -1, p_node->y);
	//p_node->AddRefNode(node_ref);

	////left top
	//node_ref = GetNode(p_node->x -1, p_node->y + 1);
	//p_node->AddRefNode(node_ref);

	////min top
	//node_ref = GetNode(p_node->x , p_node->y + 1);
	//p_node->AddRefNode(node_ref);

	////right top
	//node_ref = GetNode(p_node->x + 1, p_node->y + 1);
	//p_node->AddRefNode(node_ref);

	////right mid
	//node_ref = GetNode(p_node->x + 1, p_node->y );
	//p_node->AddRefNode(node_ref);

	////right down
	//node_ref = GetNode(p_node->x + 1, p_node->y -1);
	//p_node->AddRefNode(node_ref);

	////mid down
	//node_ref = GetNode(p_node->x, p_node->y -1);
	//p_node->AddRefNode(node_ref);
	
	//right down

	int ri = rd_.randInt(1,8);
	
	
	int index = 0;
	for (int i = 0 ; i < 8 ; ++i)
	{
		//rand direction 
		if (ri % 2 == 1)
		{
			//front
			index = ( 8 + ri + i) % 8;
		}else{
			//back
			index = ( 8 + ri - i) % 8;
		}

		
		node_ref = GetNode(p_node->x + rxy[index].x, p_node->y + rxy[index].y);
		p_node->AddRefNode(node_ref);
	}
// 	node_ref = GetNode(p_node->x + 1, p_node->y -1);
// 	p_node->AddRefNode(node_ref);
// 
// 	//right mid
// 	node_ref = GetNode(p_node->x + 1, p_node->y );
// 	p_node->AddRefNode(node_ref);
// 
// 	//right top
// 	node_ref = GetNode(p_node->x + 1, p_node->y + 1);
// 	p_node->AddRefNode(node_ref);
// 
// 	//min top
// 	node_ref = GetNode(p_node->x , p_node->y + 1);
// 	p_node->AddRefNode(node_ref);
// 	
// 	//left top
// 	node_ref = GetNode(p_node->x -1, p_node->y + 1);
// 	p_node->AddRefNode(node_ref);
// 
// 	//left mid
// 	node_ref = GetNode(p_node->x -1, p_node->y);
// 	p_node->AddRefNode(node_ref);
// 
// 
// 	//left down
// 	node_ref = GetNode(p_node->x -1, p_node->y -1);
// 	p_node->AddRefNode(node_ref);
// 
// 	//mid down
// 	node_ref = GetNode(p_node->x, p_node->y -1);
// 	p_node->AddRefNode(node_ref);

}

// void AStar::get_protential(GridMap* map){
// 	if (!map)
// 	{
// 		return;
// 	}
// 	mNode::iterator it = NodeAll.begin();
// 	for ( ; it != NodeAll.end(); ++it)
// 	{
// 		Node* node = it->second;
// 		map->setgridp(node->x,node->y,node->f);
// 	}
// 	std::ofstream fo("protential.txt");
// 	for (int y = 4000; y < 4200 ; ++y)
// 	{
// 		for (int x = 4050; x < 12000 ; ++x)
// 		{
// 			U16 value = 0;
// 			map->getgtidp(x,y,value);
// 
// 			fo<<value<<" ";
// 		}
// 		fo<<std::endl;
// 	}
// 	fo.flush();
// 	fo.close();
// }
bool AStar::check_available(F32 x,F32 y){
	U32 gx = 0 ;
	U32 gy = 0 ;
	global_map_->world2grid(x,y,gx,gy);
	S8 value = Get_grid_value(gx,gy);
	if (value > 70)
	{
		return false;
	}
	return true;
}
//void AStar::filter(){
//
//}
