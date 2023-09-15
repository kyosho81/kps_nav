#ifndef _SEG_PATH_AGAINST_WANGHONGTAO_20220303_
#define _SEG_PATH_AGAINST_WANGHONGTAO_20220303_

#include <string>
#include <vector>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>

#include "buffer_con.hpp"

#include "RobotStruct.h"
#include "Comm/pattern_thread.h"


class superior
{
public:
	int i_from_id_;
	int i_to_id_;
	int i_index_;
	int i_agv_id_;
	int i_path_size_;
};


class seg_path_against
{
public:
	seg_path_against();
	~seg_path_against();

	void init( std::string str_file, bool b_save = false);

	
	void insert_seg_path( int i_agv_id , std::vector<SPathData> &seg_path);
	void insert_seg_path_occupy( int i_agv_id , std::vector<SPathData> &seg_path );

	void check_against_path();
	void print_pause();
	int get_pause(std::vector<std::pair<int,int>> &v_pause_list);
	int check_priority( int i_agv_id_1, int i_agv_id_2 );

	bool check_run_free( int i_agv_id );

protected:
private:
	typedef std::pair<std::multimap<int,superior>::iterator, std::multimap<int,superior>::iterator> P_IT;
	typedef std::multimap<int,superior>::iterator M_IT;

	std::multimap<int,superior>::iterator insert_edge( int i_path_size, int i_index, int i_agv_id, int i_from ,int i_to);
	std::multimap<int,superior> path_against( int i_agv_id, int i_from ,int i_to );

	M_IT get_edge( int i_agv_id, int i_from ,int i_to );
	
	//edge container
	std::multimap<int,superior> m_seg_from_to_;

	//agv id
	//edge list iterator
	std::map<int,std::vector<M_IT>> m_agv_seg_list_;

	//pause list
	void set_pause(int i_subordinate, int i_superior);
	bool pause(int i_subordinate);

	std::map<int,std::map<int,int>> m_pause_list_;


	typedef std::pair<std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> PRT_IT;
	typedef std::multimap<int,int>::iterator MRT_IT;

	std::vector<MRT_IT> get_pause_relation(int i_subordinate);
	MRT_IT get_pause_relation(int i_subordinate, int i_superior);
	bool set_pause_relation(int i_subordinate, int i_superior);
	std::multimap<int,int> mt_pause_relation_;
	//test file
private:
	bool b_save_;
	bool load_file(std::string str_file);
	void save_file( std::string str_file , int i_agv_id , SPathData &seg_data );
	

	std::ofstream off_;
	std::string str_test_file_;

private:
	//all against
	void create_all_path_against();
	void check_all_path_against();
	std::map<int,int> m_pause_each_;

	void remove_path_free();
	void first_seg_priorityup();
	void remove_pause_agv();

	void mt_against_do();

	void clear_all_path_against();
	std::map<int,std::multimap<int,superior> >& get_against_by_id(int i_agv_id);
	void del_it_m_id_index_against(int i_agv_id,  M_IT it_erase );
	
	// agv id : seg path index : against path
	std::map<int ,std::map<int,std::multimap<int,superior> >> m_id_index_against_;

	// for check_run_free 
	std::map<int , std::vector<SPathData>> m_all_run_path_;
};


#endif//_SEG_PATH_AGAINST_WANGHONGTAO_20220303_
