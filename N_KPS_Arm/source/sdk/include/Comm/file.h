#ifndef _WANGHONGTAO_FILE_2019_9_9_H_
#define _WANGHONGTAO_FILE_2019_9_9_H_

#include <string>
#include <fstream>

#define DOWN_LOAD_PACKAGE_SIZE 64000

class file
{
public:
	file();
	~file();

	int open_file(const std::string &file_path);
	int read_file( char* data , int &len , const int r_len);
	void close_file();

	int open_wfile(const std::string &file_path);
	int write_file(char* data , const int &ilen);
	void close_wfile();

protected:
private:

	std::ifstream fis_;
	std::ofstream fos_;
};

#endif//_WANGHONGTAO_FILE_2019_9_9_H_
