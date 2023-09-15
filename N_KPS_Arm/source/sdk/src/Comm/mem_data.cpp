#include <cassert>
#include <iostream>

#include "Comm/Comm.h"

#include "Comm/mem_data.h"

mem_data::mem_data()
{
	data_ = 0;
	i_total_size_ = 0;
	i_index_ = 0;
}

mem_data::~mem_data()
{
	if (data_){
		delete[] data_;
		data_ = 0;
	}

	i_total_size_ = 0;
	i_index_ = 0;
}


bool mem_data::read_data(char* data , int &ilen , const int r_len)
{
	if ( (i_index_ + r_len) < i_total_size_){
		
		ilen = r_len;

		memcpy(data, data_ + i_index_ , ilen);
		
		i_index_ += ilen;
		return true;

	}else{
		ilen = i_total_size_ - i_index_ - 1;
		
		memcpy(data,data_ + i_index_ ,ilen);
		i_index_ += ilen;

		return false;
	}
}

bool mem_data::write_data(char* data , const int &ilen)
{
	if (data_){
		delete[] data_;
		data_ = 0;
	}

	data_ = new char[ilen];
	if (!data_){
		return false;
	}
	memset(data_,0,ilen);
	memcpy(data_,data,ilen);

	i_total_size_ = ilen;
	i_index_ = 0;

	return true;
}
