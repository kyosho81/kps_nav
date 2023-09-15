#include <cassert>
#include <iostream>

#include "Comm/Comm.h"

#include "Comm/file.h"

file::file()
{

}

file::~file()
{

}

int file::open_file(const std::string &file_path)
{
	if( !cComm::FileExist(file_path) ){
		return -1;
	}

	if (fis_.is_open())
	{
		std::cout<<"force close old file!"<<std::endl;
		fis_.close();
	}

	fis_.open(file_path.c_str(),std::ios::in | std::ios::binary);

	std::cout<<"open file:"<<file_path<<std::endl;

	if (fis_.is_open())
	{
		fis_.seekg(0,std::ios::end);
		int itotal_len = fis_.tellg();
// 		fis_.ignore(std::numeric_limits<std::streamsize>::max());
// 		std::streamsize itotal_len = fis_.gcount();
// 		fis_.clear();
		fis_.seekg(0,std::ios::beg);
		return itotal_len;
	}
	return -2;
}

int file::read_file(char* data , int &len , const int r_len)
{
	len = 0;
	memset(data,0,r_len);

	if (!fis_.is_open())
	{
		return -2;
	}
	if (fis_.eof())
	{
		fis_.close();
		return 0;
	}
	
	fis_.read(data,r_len);
	len = fis_.gcount();
	return len;
}

void file::close_file()
{
	if (fis_.is_open())
	{
		fis_.close();
	}
}

int file::open_wfile(const std::string &file_path)
{
	//if( cComm::FileExist(file_path) ){
	//	std::cout<<"file existed! "<<file_path<<std::endl;
	//	return -1;
	//}

	if (fos_.is_open())
	{
		std::cout<<"force close old file!"<<std::endl;
		fos_.close();
	}

	if (!fos_.is_open())
	{
		fos_.open(file_path.c_str(),std::ios::out | std::ios::trunc | std::ios::binary);
		std::cout<<"open file:"<<file_path<<std::endl;
	}

	if (fos_.is_open())
	{
		std::cout<<"open file to write!"<<std::endl;
		return 0;
	}else{
		std::cout<<"open file to write Err!"<<std::endl;
		return -2;
	}
}

int file::write_file(char* data , const int &ilen)
{
	if (!fos_.is_open())
	{
		return -1;
	}
	fos_.write(data,ilen);
	return 0;
}

void file::close_wfile()
{
	if (fos_.is_open())
	{
		fos_.close();
	}

}
