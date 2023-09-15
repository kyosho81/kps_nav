#ifndef _KYOSHO_MEMDATA_2023_3_9_H_
#define _KYOSHO_MEMDATA_2023_3_9_H_

#include <string>
#include <fstream>

#define UP_LOAD_DATA_SIZE 64000000 //64m

class mem_data
{
public:
	mem_data();
	~mem_data();

	bool read_data( char* data , int &ilen , const int r_len);
	bool write_data(char* data , const int &ilen);

protected:
private:

	char* data_;
	int i_total_size_;
	int i_index_;

};

#endif//_KYOSHO_MEMDATA_2023_3_9_H_
