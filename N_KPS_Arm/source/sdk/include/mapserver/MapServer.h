#ifndef _MAP_SERVER_KYOSHO_20150630_
#define _MAP_SERVER_KYOSHO_20150630_

#include <string>
#include <vector>
#include <map>
//#include <boost/pool/detail/singleton.hpp>
#include <boost/serialization/singleton.hpp>

#include "map_def.h"


#include "mapserver/filter_template.h"
#include "robot/process_bar.h"

#include "GridMap.h"

#include "gmapping/scanmatcher/scanmatcher.h"


class diff_pair
{
public:
	diff_pair(){};
	~diff_pair(){};

	std::string parent_;
	std::string child_;

	U32 diff_x_;
	U32 diff_y_;
};

class Map_Server
{
public:
	
	Map_Server();
	~Map_Server();

	GridMap* LoadPgmMap(std::string name , map_data_base::M_TYPE type,std::string para);
	GridMap* LoadPgmMap( std::string name , GridMap* p_map );
	GridMap* LoadPgmMapM( std::string name , GridMap* p_map );
	GridMap* LoadInfMap(std::string name , map_data_base::M_TYPE type,std::string para);
	bool LoadScanMap( std::string name , GridMap* p_map );
	bool LoadScanExMap( std::string name , GridMap* p_map , F32 rotation = 0);

    //GridMap* GetGridMap();
    GridMap* GetGridMap(std::string name);
	GridMap* CreateGridMap( std::string name , map_data_base::M_TYPE type,std::string para,std::string layer,F32 origin_x,F32 origin_y,F32 resolution,U32 g_width,U32 g_height,S64 origin_g_x = 0,S64 origin_g_y = 0);

	GridMap* MergeMap(std::string des,std::string src);

	void RemoveGridMap(GridMap* &gm);

	bool inflation(float sigma,std::string in_name,std::string out_name);
	bool fast_inflation(float sigma,std::string name);
	bool fast_inflation(filter2D_template f2d,std::string name);
	bool dynamic_inflation(filter2D_template f2d,std::string name);
	bool notching( float sigma,std::string name );
	bool clone(std::string in_name,std::string out_name);

	void save_map( std::string name ,std::string path );
	void save_yaml(std::string name ,std::string path);

	void set_map_diff(std::string parent,std::string child,const F32 &px,const F32 &py);
	
	S8 getCost(const U32 &gx,const U32 &gy,std::string layer,std::string target_map);
	bool layer_tf(U32 &gx,U32 &gy,std::string layer_from,std::string layer_to);

	void do_map_diff();

	void bind_amcl_do(boost::function< void(const SPos &amcl_pos)> fnc);
	void bind_pub_bar(boost::function<void(SProcess_Bar &pro_bar)> fnc);
	
	void update_amcl( const SPos &amcl_pos );
	void update_goal( const SPos &goal_pos );

protected:
private:

	
	bool call_back_amcl(const SPos &amcl_pos);
	
	boost::function< void(const SPos &amcl_pos)> call_fnc_;
	boost::mutex amcl_mutex_;

	void grid_diff(std::string parent,std::string child,const F32 &cx,const F32 &cy,U32 &diff_x,U32 &diff_y);

	bool yaml_parse(std::string name,F32 &origin_x,F32 &origin_y,F32 &resolution);
	

	std::map<std::string,GridMap*> grid_map_list_;
	U8 map_value(U8 in);
	U8 value_pgm(U8 out);
	std::map<std::string,diff_pair> map_diff_list_;

	//process_bar
private:
	process_bar pro_bar_;
	boost::function<void(SProcess_Bar &pro_bar)> fnc_pub_pro_;
	void pub_process(const std::string &str_nm,const int &icurrent,const int &imax);
	void save(GridMap* p_map,const GMapping::ScanMatcherMap& smap);
private:
	F32 xmin_;
	F32 xmax_;
	F32 ymin_;
	F32 ymax_;
	F32 delta_;
	F32 occ_thresh_;

	
};

//typedef boost::details::pool::singleton_default<Map_Server> Singleton_MapServer;
typedef boost::serialization::singleton<Map_Server> Singleton_MapServer;

#define MAP_SERVER Singleton_MapServer::get_mutable_instance()

#define CREATE_MEM_GMAP(name) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::MEM,"",WORLD_LAYER,GLOBAL_ORI_X,GLOBAL_ORI_Y,MAP_RESOLUTION,GLOBAL_MAP_WIDTH,GLOBAL_MAP_HEIGHT)
#define CREATE_SHARED_GMAP(name) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::SHARED,"",WORLD_LAYER,GLOBAL_ORI_X,GLOBAL_ORI_Y,MAP_RESOLUTION,GLOBAL_MAP_WIDTH,GLOBAL_MAP_HEIGHT)
#define CREATE_MMAP_GMAP(name,add) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::MMAP,(add),WORLD_LAYER,GLOBAL_ORI_X,GLOBAL_ORI_Y,MAP_RESOLUTION,GLOBAL_MAP_WIDTH,GLOBAL_MAP_HEIGHT)

#define CREATE_MEM_LMAP(name) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::MEM,"",ODOM_LAYER,LOCAL_ORI_X,LOCAL_ORI_Y,MAP_RESOLUTION,LOCAL_MAP_WIDTH,LOCAL_MAP_HEIGHT)
#define CREATE_SHARED_LMAP(name) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::SHARED,"",ODOM_LAYER,LOCAL_ORI_X,LOCAL_ORI_Y,MAP_RESOLUTION,LOCAL_MAP_WIDTH,LOCAL_MAP_HEIGHT)
#define CREATE_MMAP_LMAP(name,add) Singleton_MapServer::get_mutable_instance().CreateGridMap((name),map_data_base::MMAP,(add),ODOM_LAYER,LOCAL_ORI_X,LOCAL_ORI_Y,MAP_RESOLUTION,LOCAL_MAP_WIDTH,LOCAL_MAP_HEIGHT)

#endif//_MAP_SERVER_KYOSHO_20150630_
