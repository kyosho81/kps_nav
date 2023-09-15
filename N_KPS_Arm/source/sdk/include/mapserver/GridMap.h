#ifndef _GRID_MAP_KYOSHO_20150630_
#define _GRID_MAP_KYOSHO_20150630_

#include <string>
#include <vector>
#include <map>
#include <boost/function.hpp>

#include "RobotStruct.h"
#include "map_def.h"
#include  "MapDBase.h"
#include "mapserver/filter_template.h"


#define GRID_IDX( c , x , y ) ( (c) * (y) + (x))
//#include "interprocess/shared_pool.hpp"

class MapAnchor
{
public:
	MapAnchor();
	~MapAnchor();

	void SetAnchor(F32 origin_x,F32 origin_y,S64 origin_g_x,S64 origin_g_y);

	F32 origin_x_;		
	F32 origin_y_;

	U32 origin_g_x_;		
	U32 origin_g_y_;	

protected:
private:

		
};

class GridMap
{
public:
	GridMap();
	GridMap(std::string name);
	~GridMap();

	bool Init(map_data_base::M_TYPE type,std::string name,std::string data_para,std::string layer,F32 origin_x,F32 origin_y,S64 origin_g_x,S64 origin_g_y,F32 resolution,U32 g_width,U32 g_height );
	void set_map_border(F32 min_x, F32 min_y, F32 max_x,F32 max_y);
	inline void set_border_value(F32 wx, F32 wy){
		max_x_ = cComm::Max(wx,max_x_);
		max_y_ = cComm::Max(wy,max_y_);

		min_x_ = cComm::Min(wx,min_x_);
		min_y_ = cComm::Min(wy,min_y_);
	};
	inline void set_border_value(U32 gx, U32 gy){
		F32 wx = 0;
		F32 wy = 0;
		grid2world(gx,gy,wx,wy);
		set_border_value(wx,wy);
	};
	void get_map_border(F32 &min_x, F32 &min_y, F32 &max_x,F32 &max_y);

	void lock();
	void unlock();
	U8* Get_data();
	U32 Get_data(U8* &map_data);

	bool set_data(U8* in,U32 &len);
	bool set_data_ptr(U8* in,U32 &dsize);


	U32 Get_grid_width();
	void Set_grid_width(U32 gw);
	U32 Get_grid_height();
	void Set_grid_height(U32 gh);

	F32 Get_width();
	void Set_width(F32 width);
	F32 Get_height();
	void Set_height(F32 height);
	

	std::string Get_name();
	void Set_name(std::string name);

	void bind_parser( boost::function<void(GridMap* map,std::string layer,U8* data,U32 len)> fnc);
	void begin_parser(U8 hz);
	void end_parser();

	std::string layer_;
	
	inline U32 g2i(const U32 &gx,const U32 &gy){
		return GRID_IDX( grid_width_, gx , gy );
	};
private:
	
	void th_run();
	U8 run_hz_;
	boost::thread* parser_th_;
	boost::function<void(GridMap* map,std::string layer,U8* data,U32 len)> fnc_;

public://inline
	inline bool check_valid(const U32 &gx,const U32 &gy){
		if((gx >= grid_width_) || ( gy >= grid_height_)){
			//std::cout<<"set grid data out of range x:"<<gx<<" y:"<<gy<<std::endl;
			return false;
		}
		return true;
	};
	inline bool check_valid(const F32 &wx,const F32 &wy){
		if(( wx < map_anchor_.origin_x_ ) || (wx > (map_anchor_.origin_x_ + width_))){
			return false;
		}
		if(( wy < map_anchor_.origin_y_ ) || (wy > (map_anchor_.origin_y_ + height_))){
			return false;
		}
		return true;
	};
	inline bool world2grid(const F32 &wx,const F32 &wy,U32 &gx,U32 &gy){

		if(!check_valid(wx,wy)){
			return false;
		}

		double xOffsetWorld = wx - map_anchor_.origin_x_;
		double yOffsetWorld = wy - map_anchor_.origin_y_;

		if (xOffsetWorld >= 0)
			xOffsetWorld += resolution_ / 2.0;
		else
			xOffsetWorld -= resolution_ / 2.0;

		if (yOffsetWorld >= 0)
			yOffsetWorld += resolution_ / 2.0;
		else
			yOffsetWorld -= resolution_ / 2.0;

		gx = xOffsetWorld / resolution_;
		gy = yOffsetWorld / resolution_;

		gx += map_anchor_.origin_g_x_;
		gy += map_anchor_.origin_g_y_;

		return true;
	};
	inline void grid2world(const U32 &gx,const U32 &gy,F32 &wx,F32 &wy){
		U32 xGridOffset = gx - map_anchor_.origin_g_x_;
		U32 yGridOffset = gy - map_anchor_.origin_g_y_;

		wx =  map_anchor_.origin_x_ + xGridOffset * resolution_;
		wy =  map_anchor_.origin_y_ + yGridOffset * resolution_;
	};

	
	inline bool setgrid(const F32 &fx,const F32 &fy,S8 value){
		U32 gx = 0;
		U32 gy = 0;

		if(!world2grid(fx,fy,gx,gy)){
			return false;
		}

		//std::cout<<"fx:"<<fx<<" fy:"<<fy<<" xoffsetworld:"<<xoffsetworld<<" yoffsetworld:"<<yoffsetworld<<std::endl;
		return setgrid( (U32)gx,(U32)gy,value );
	};

	inline bool setgrid(const U32 &gx,const U32 &gy,S8 value){
		
		//std::cout<<"gx:"<<gx<<" gy:"<<gx<<std::endl;
		if((gx >= grid_width_) || ( gy >= grid_height_)){
			//std::cout<<"set grid data out of range x:"<<gx<<" y:"<<gy<<std::endl;
			return false;
		}
		if(map_data_){
			U32 index = GRID_IDX(grid_width_,gx,gy);
			map_data_[index] = value;

			if ( ( value >0) && (value <= MAP_OCCUPY_MAX))
			{
				SGridXY xy;
				xy.x_ = gx;
				xy.y_ = gy;
				xy.value_ = value;

				occupy_point_[index] = xy;
			}
			
		}
		return true;
	};
	//set grid value free
	inline bool setgrid_vf(const U32 &gx,const U32 &gy,S8 value){

		//std::cout<<"gx:"<<gx<<" gy:"<<gx<<std::endl;
		if((gx >= grid_width_) || ( gy >= grid_height_)){
			//std::cout<<"set grid data out of range x:"<<gx<<" y:"<<gy<<std::endl;
			return false;
		}
		if(map_data_){
			U32 index = GRID_IDX(grid_width_,gx,gy);
			map_data_[index] = value;

			SGridXY xy;
			xy.x_ = gx;
			xy.y_ = gy;
			xy.value_ = value;

			occupy_point_[index] = xy;

		}
		return true;
	};
// 	inline bool setgridp(const U32 &gx,const U32 &gy,U16 protential){
// 
// 		//std::cout<<"gx:"<<gx<<" gy:"<<gx<<std::endl;
// 		if((gx >= grid_width_) || ( gy >= grid_height_)){
// 			//std::cout<<"set grid data out of range x:"<<gx<<" y:"<<gy<<std::endl;
// 			return false;
// 		}
// 		if(map_data_){
// 			U32 index = GRID_IDX(grid_width_,gx,gy);
// 	
// 			if ( protential > 0)
// 			{
// 				SGridXY xy;
// 				xy.x_ = gx;
// 				xy.y_ = gy;
// 				xy.protential = protential;
// 
// 				occupy_point_[index] = xy;
// 			}
// 
// 		}
// 		return true;
// 	};
	inline bool getgrid(const F32 &fx,const F32 &fy,S8 &value){
		U32 gx = 0;
		U32 gy = 0;

		if(world2grid(fx,fy,gx,gy)){
			return getgrid(gx,gy,value);
		}
		value = MAP_OUT;
		return false;
	
	}

	inline bool getgrid(const U32 &gx,const U32 &gy,S8 &value){
		
		value = MAP_ERR;

		if ((gx >= grid_width_) || (gy >= grid_height_))
		{
			value = MAP_OUT;
			return false;
		}
		U32 index = GRID_IDX(grid_width_,gx,gy);
		//if (index < get_dsize())
		{
			//S8* data = (S8*)map_data_ ;
			if (map_data_)
			{
				value = *((S8*)map_data_ + index);
				return true;
			}
		}

		return false;
	};
// 	inline bool getgtidp(const U32 &gx,const U32 &gy,U16 &value){
// 
// 		value = 0;
// 
// 		if ((gx >= grid_width_) || (gy >= grid_height_))
// 		{
// 			return false;
// 		}
// 		U32 index = GRID_IDX(grid_width_,gx,gy);
// 		//if (index < get_dsize())
// 		std::map<U32,SGridXY>::iterator it = occupy_point_.find(index);
// 		if (it != occupy_point_.end() )
// 		{
// 			SGridXY xy = it->second;
// 			if(xy.protential > 0){
// 				value = xy.protential;
// 			}
// 			
// 		}
// 
// 		return false;
// 	};
// 	inline bool getgtid_ex(const U32 &gx,const U32 &gy,S8 &value){
// 
// 		value = MAP_ERR;
// 
// 		if ((gx >= grid_width_) || (gy >= grid_height_))
// 		{
// 			return false;
// 		}
// 		U32 index = GRID_IDX(grid_width_,gx,gy);
// 
// 		std::map<U32,SGridXY>::iterator it = dynamic_occupy_.find(index);
// 		if(it != dynamic_occupy_.end()){
// 			std::cout<<"dynamic_occupy point x:"<<it->second.x_<<" y:"<<it->second.y_<<" value:"<<int(it->second.value_)<<std::endl;
// 			return false;
// 		}
// 		//if (index < get_dsize())
// 		{
// 			//S8* data = (S8*)map_data_ ;
// 			if (map_data_)
// 			{
// 				value = *((S8*)map_data_ + index);
// 				return true;
// 			}
// 		}
// 
// 		return false;
// 	};
	inline bool get_dynamic_occupy( S8& value , const F32& fx,const F32& fy){
		U32 gx = 0;
		U32 gy = 0;
		
		if(!world2grid(fx,fy,gx,gy)){
			return false;
		}
		U32 index = GRID_IDX(grid_width_,gx,gy);
		std::map<U32, SGridXY>::iterator it = dynamic_occupy_.find(index);
		if (it != dynamic_occupy_.end())
		{
			value = it->second.value_;
			return true;
		}else{
			value = 0;
			return false;
		}
		
	};
	inline bool put_dynamic_occupy(const F32& fx,const F32& fy,const S8& value)
	{
		U32 gx = 0;
		U32 gy = 0;

		if(!world2grid(fx,fy,gx,gy)){
			return false;
		}

		U32 index = GRID_IDX(grid_width_,gx,gy);

		if(value > 0){

			SGridXY xy;
			xy.x_ = gx;
			xy.y_ = gy;
			xy.value_ = value;

			dynamic_occupy_[index] = xy;
		}

	};
	inline bool del_dynamic_occupy(const U32 &gx,const U32 &gy,const U8& dec){
		U32 index = g2i(gx,gy);
		F32 fx,fy;
		auto it = dynamic_occupy_.find(index);
		if (it != dynamic_occupy_.end()){
			SGridXY &xy(it->second);
			S8 sv = xy.value_ - dec;
			//grid2world(xy.x_,xy.y_,fx,fy);
			//std::cout<<"xy.value_:"<<int(xy.value_)<<" dec:"<<int(dec)<<" sv:"<<int(sv)<<std::endl;
			if ( sv <= 0)
			{
				//std::cout<<"erase it:"<<dynamic_occupy_.size()<<std::endl;

				//std::cout<<" erase it:"<<fx<<" "<<fy<<std::endl;
				dynamic_occupy_.erase(it++);

			}else{
				//std::cout<<" save it:"<<fx<<" "<<fy<<std::endl;
				xy.value_ -= dec;
				it++;
			}
			return true;
		}
		return false;
	};
	int clear_dynamic_occupy(const U8& dec);

	int insert_dy_grid(const U32 &insert_index, const F32 &fx, const F32 &fy, S8 value_k);
	int earse_dy_grid(const U32 &insert_index);
	void set_dy_template(filter2D_template f2d);
	bool get_dy_grid( S8& value , const F32& fx,const F32& fy);
	void clear_dy_grid();

public:

	void clear();
	void fill(S8 value);

	void transfer();
	void expand(long g_width,long g_height,bool mid = true);
	void shrink();
	void check_occupy();
	int check_unknow();
	void check_border();

	U32 get_dsize();

	std::map<U32,SGridXY> occupy_point_;
	std::map<U32,SGridXY> dynamic_occupy_;
	std::map<U32,SGridXY> known_point_;
	

	MapAnchor map_anchor_;
	F32 Get_resolution();
private:

	bool SetMapData(unsigned char* data ,U32 dsize);

	std::string map_name_;		
	
			

	public:
	F32 width_;				
	F32 height_;				
	F32 resolution_;         
	
	//unsigned char* map_data_;	//grid map data
	
	U32 grid_width_;			//grid map width
	U32 grid_height_;			//grid map height
	private:
	U8* map_data_;				//map data point
	map_data_base* base_daba_;
	bool init_data(map_data_base::M_TYPE type,std::string data_para);
	
	/////////////dynamic_inf_data for path inflation/////////
private:
	filter2D_template f2d_;
	int data_index_;
	std::map< U32, SGridXY> m_dynamic_inf_data_;
	//map x_y_index value
	//every cell have multi value
	std::map< U32, std::list< std::map< U32, SGridXY>::iterator > > m_dynamic_map_index_it_;
	
	//index which is insert,
	//iterator from dynamic_inflation_
	//used for delete
	std::map< U32, std::list< std::map< U32, SGridXY>::iterator > > m_dynamic_ins_index_it_;


	// map available range
private:
	F32 min_x_;
	F32 min_y_;
	F32 max_x_;
	F32 max_y_;
};

#endif//_GRID_MAP_KYOSHO_20150630_
