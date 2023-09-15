#ifndef _PUB_VIEW_DATA_WANGHONGTAO_2020_09_24_
#define _PUB_VIEW_DATA_WANGHONGTAO_2020_09_24_



#include "protobuf_msg/view_data.pb.h"
#include "Comm/TimerDiff.h"

#include "interpro_shared/pipe_shared_pool.hpp"

#define PUB_PIPE_VIEW_DATA "pub_pipe_view_data"

class pub_view_data
{
public:
	pub_view_data();
	~pub_view_data();


	static void init(std::string str_nm){
		str_pro_nm_ = str_nm;
		str_pro_nm_ = cComm::Get_FileName(str_pro_nm_);

	};

	static void init(char *argv[]){
		str_pro_nm_ = argv[0];
		str_pro_nm_ = cComm::Get_FileName(str_pro_nm_);

	};

	static std::string sub_view_pipe(boost::function<bool (std::string name,U8* data,U32 len)> fnc ){

		return pipe_shared_pool::sub_pipe(PUB_PIPE_VIEW_DATA,fnc);
	};

	static bool pub( std::string str_nm ,  SVec point , bool b_merge = true ){
		

		KPS::s_view_data view_data;
		KPS::mp_lab* p_lab = view_data.mutable_lab();
		p_lab->set_lab(str_nm);
		p_lab->set_id(0);
		p_lab->set_x(.0);
		p_lab->set_y(.0);
		p_lab->set_show(1);

		str_nm = get_pub_name(str_nm);
		view_data.set_name(str_nm);
		
		if (b_merge){
			view_data.set_insert_type(KPS::s_view_data::Insert_Type::s_view_data_Insert_Type_MERGE);
		}else{
			view_data.set_insert_type(KPS::s_view_data::Insert_Type::s_view_data_Insert_Type_NEW);
		}
		
		
		KPS::s_point * pp = view_data.add_point();
		pp->set_x(point.x_);
		pp->set_y(point.y_);
		view_data.set_shape_type(KPS::s_view_data::Shape_Type::s_view_data_Shape_Type_CIRCLE );


		int ilen = view_data.ByteSize();
		U8* data = new U8[ilen];
		view_data.SerializeToArray(data,ilen);

		return pub_pipe(str_nm,data,ilen);

	};

	static bool pub( std::string str_nm , const SPos &pos , bool b_merge = true ){

		KPS::s_view_data view_data;

		KPS::mp_lab* p_lab = view_data.mutable_lab();
		p_lab->set_lab(str_nm);
		p_lab->set_id(0);
		p_lab->set_x(.0);
		p_lab->set_y(.0);
		p_lab->set_show(1);

		str_nm = get_pub_name(str_nm);
		view_data.set_name(str_nm);

		if (b_merge){
			view_data.set_insert_type(KPS::s_view_data::Insert_Type::s_view_data_Insert_Type_MERGE);
		}else{
			view_data.set_insert_type(KPS::s_view_data::Insert_Type::s_view_data_Insert_Type_NEW);
		}

		KPS::s_pos * pp = view_data.add_pos();
		pp->set_x(pos.x_);
		pp->set_y(pos.y_);
		pp->set_th(pos.th_);
		view_data.set_shape_type(KPS::s_view_data::Shape_Type::s_view_data_Shape_Type_TRIANGLE );

		int ilen = view_data.ByteSize();
		U8* data = new U8[ilen];
		view_data.SerializeToArray(data,ilen);

		return pub_pipe(str_nm,data,ilen);

	};
	static bool pub( std::string str_nm , U8* cp_data, int ilen ){
		//str_nm = get_pub_name(str_nm);
		return pub_pipe(str_nm,cp_data,ilen);
	}

private:

	static std::string get_pub_name( std::string str_nm ){
		str_nm = str_pro_nm_ + "_" + str_nm;
		return str_nm;
	};
	static bool pub_pipe( std::string str_nm , U8* data , const int &ilen ){

		std::stringstream ss;
		ss<<cTimerDiff::total_ms()<<" "<<str_nm;
		
		if(!pipe_shared_pool::push_back( PUB_PIPE_VIEW_DATA, ss.str() , data,ilen )){
			std::cout<<"pub_view_data pub  err!"<<std::endl;
			delete[] data;
			data = 0;
			return false;
		}
		delete[] data;
		data = 0;
		return true;
	};

	static std::string str_pro_nm_;
};
#endif//_PUB_VIEW_DATA_WANGHONGTAO_2020_09_24_
