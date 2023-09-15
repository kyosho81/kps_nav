
#include <fstream>
#include <string>
#include <stdio.h>
#include <map>
#include <cctype>

#if defined(_WINDOWS)
#include <windows.h>
#else
#include <unistd.h>
#endif


#include "boost/filesystem/path.hpp"  
#include "boost/filesystem/operations.hpp"  
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include <boost/filesystem.hpp>

#include "Comm.h"
#include "Comm/version.h"
#include "robot/Geometry.h"

using namespace boost;
using namespace boost::xpressive;
using namespace boost::filesystem;
using namespace std;


/**************************************************************************************************
 * class cComm
****************************************************************************************************/
U8 cComm::bit_value_[8];
KPS_VERSION cComm::ver_;

cComm::cComm(void)
{
	cComm::load();
}


cComm::~cComm(void)
{
}


bool cComm::load()
{
	bit_value_[0] = 1;
	bit_value_[1] = 2;
	bit_value_[2] = 4;
	bit_value_[3] = 8;
	bit_value_[4] = 16;
	bit_value_[5] = 32;
	bit_value_[6] = 64;
	bit_value_[7] = 128;

	memset(&ver_,0,sizeof(KPS_VERSION));
	ver_.v_main_ = VERSION_MAIN;
	ver_.v_sub_1_ = VERSION_SUB_1;
	ver_.v_sub_2_ = VERSION_SUB_2;
	ver_.temp_ = 0;

	return true;
}


std::string cComm::trim(std::string &str)
{
  std::string::size_type pos = str.find_first_not_of(32);
  if (pos != std::string::npos)
  {
      str = str.substr(pos);
  }else{
	  str = "";
	  return str;
  }

  std::string::size_type pos2 = str.find_last_not_of(32);
  if (pos2 != std::string::npos)
  {
       str = str.substr(0,pos2 + 1);
  }

  return str;
}
std::string cComm::trim_n(std::string &str)
{
  std::string::size_type pos = str.find_first_not_of(0x0a);
  if (pos == std::string::npos)
  {
      return str;
  }

  std::string::size_type pos2 = str.find_last_not_of(0x0a);
  if (pos2 != std::string::npos)
  {
      return str.substr(pos, pos2 - pos + 1);
  }

  return str.substr(pos);
}
std::string cComm::trim_cr(std::string &str)
{
	std::string::size_type pos = str.find_first_not_of(0x0d);
	if (pos == std::string::npos)
	{
		return str;
	}

	std::string::size_type pos2 = str.find_last_not_of(0x0d);
	if (pos2 != std::string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}

	return str.substr(pos);
}
S32 cComm::SplitString(const std::string    &input,
				       const std::string    &delimiter,
				       vector<std::string>  &results)
{
	S32 iPos   = 0;
	S32 newPos = -1;
	S32 sizeS2 = (S32)delimiter.size();
	S32 isize  = (S32)input.size();
	results.clear();

	if( ( 0 == isize) || ( 0 == sizeS2) )
	{
		return 0;
	}

	vector<S32> positions;
	S32         numFound = 0;
	while ((newPos = input.find (delimiter, iPos)) != string::npos )
	{
		positions.push_back(newPos);
		iPos = newPos + sizeS2;
		numFound++;
	}

	if( numFound == 0 )
	{
		if (input.size()>0)
		{
			results.push_back(input);
		}
		return 1;
	}

	if (positions.back() != isize)
	{
		positions.push_back(isize);
	}

	int     offset = 0;
	std::string  s("");
	for( S32 i=0; i < (S32)positions.size(); ++i )
	{
		s = input.substr( offset, positions[i]- offset ); 

		offset = positions[i] + sizeS2;

 		if (s.length()>0 && !all(s,is_space()))
 		{
 			results.push_back(s);
 		}
	}
	return numFound;
}
int cComm::PatternCount(const std::string       &str,
							   const std::string       &pattern)

{
	int count = 0 ;
	std::size_t pos = 0;

	while(pos != string::npos)
	{
		pos = str.find(pattern, pos);
		if(pos != string::npos)
		{
			++count;                        // 如果在str中找到一个pattern，number就加1
			pos += (pattern.size() );    // 在str中指向下一个匹配起始点
		}
	}
	return count;
}

void cComm::StringUpper(std::string &strDes)
{
	std::transform(strDes.begin(),strDes.end(),strDes.begin(),::toupper);  //ת��д
}


std::string cComm::ByteToHexString( U8* pData,
		                       S32 iLen )
{
	std::string strTmp;

	char chTmp[8];
	for(S32 i = 0; i<iLen ;++i)
	{
		sprintf(chTmp, "%02X ", pData[i]);
		strTmp += chTmp;
	}
	return strTmp;
}


S32 cComm::HexStringToByte( U8     **pChar,
		                    S32     &iLen,
		                    std::string   strHex )
{
	std::vector<std::string> v_str;
	SplitString(strHex," ",v_str);

	std::vector<std::string>::iterator it = v_str.begin();
	
	if (v_str.size() <=0)
	{
		return 0;
	}

	*pChar = new U8[v_str.size()];
	memset(*pChar,0,v_str.size());

	S32 index(0);
	for (;it != v_str.end();++it)
	{
		if ((*it).length() > 2 ||(index >= v_str.size()))
		{
			continue;
		}
		else if ( (*it).length() == 1)
		{
			S8 ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(*pChar)[index] = ch[0] - 48;//�ַ�0��ASCIIֵΪ48   
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(*pChar)[index] =ch[0] -'a' + 10;
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(*pChar)[index] = ch[0]-'A'+10; 
			}
		}
		else if ((*it).length() == 2)
		{
			S8 ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(*pChar)[index] = ch[0] - 48;//�ַ�0��ASCIIֵΪ48
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(*pChar)[index] = ch[0] -'a' + 10;
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(*pChar)[index] = ch[0]-'A'+10; 
			}

			ch[0] = 0 ;
			memcpy(ch,(*it).c_str()+1,1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0] - 48);//�ַ�0��ASCIIֵΪ48   
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0] -'a' + 10);
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(*pChar)[index] = (*pChar)[index]*16 + (ch[0]-'A'+10); 
			}
		}

		index++;
	}
	iLen = v_str.size();
	return iLen;
}

S32 cComm::HexStringToByte( U8* pChar,
	S32     &iLen,
	std::string   strHex )
{
	memset(pChar,0,iLen);

	std::vector<std::string> v_str;
	SplitString(strHex," ",v_str);

	std::vector<std::string>::iterator it = v_str.begin();

	if (v_str.size() <=0)
	{
		return 0;
	}
	if ( v_str.size() > iLen )
	{
		return -1;
	}

	

	S32 index(0);
	for (;it != v_str.end();++it)
	{
		if ((*it).length() > 2 ||(index >= v_str.size()))
		{
			continue;
		}
		else if ( (*it).length() == 1)
		{
			S8 ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(pChar)[index] = ch[0] - 48;  
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(pChar)[index] =ch[0] -'a' + 10;
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(pChar)[index] = ch[0]-'A'+10; 
			}
		}
		else if ((*it).length() == 2)
		{
			S8 ch[1] = {0};
			memcpy(ch,(*it).c_str(),1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(pChar)[index] = ch[0] - 48;
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(pChar)[index] = ch[0] -'a' + 10;
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(pChar)[index] = ch[0]-'A'+10; 
			}

			ch[0] = 0 ;
			memcpy(ch,(*it).c_str()+1,1);
			if ((ch[0] >='0') && (ch[0] <='9'))
			{
				(pChar)[index] = (pChar)[index]*16 + (ch[0] - 48);  
			}
			else if ((ch[0]>='a') && (ch[0]<='f'))
			{
				(pChar)[index] = (pChar)[index]*16 + (ch[0] -'a' + 10);
			}
			else if ((ch[0]>='A') && (ch[0]<='F'))
			{
				(pChar)[index] = (pChar)[index]*16 + (ch[0]-'A'+10); 
			}
		}

		index++;
	}
	iLen = v_str.size();
	return iLen;
}
void cComm::Find_files(const std::string        &strdir,
		               const std::string        &filename,
		               std::vector<std::string> &v)
{
	path dir(strdir);
	typedef recursive_directory_iterator rd_iterator;
	static xpressive::sregex_compiler rc;
	if(!rc[filename].regex_id())
	{
		std::string str = replace_all_copy(replace_all_copy(filename,".","\\."),"*",".*");
		rc[filename] = rc.compile(str);
	}
	typedef vector<path> result_type;
	if (!exists(dir) || !is_directory(dir))
	{
		return;
	}
	rd_iterator end;
	for (rd_iterator pos(dir);pos != end;++pos)
	{
		if (!is_directory(*pos) && regex_match(pos->path().filename().string(),rc[filename]))
		{
			std::string str_path = pos->path().string();
			cComm::replace_str(str_path,"\\","//");
			v.push_back(str_path);
		}
	}
}


std::string cComm::GetRunPath()
{
	return boost::filesystem::initial_path<boost::filesystem::path>().string();
}


bool cComm::FileExist(std::string strPath)
{
	return boost::filesystem::exists(strPath);
}


std::string cComm::Get_FileName(std::string strPath)
{
	const char *full_name = strPath.c_str();

	const char *mn_first = full_name;
	const char *mn_last  = full_name + strlen( full_name );
	if ( std::strrchr( full_name, '\\' ) != NULL )
	{
		mn_first = strrchr( full_name, '\\' ) + 1;
	}
	else if ( strrchr( full_name, '/' ) != NULL )
	{
		mn_first = strrchr( full_name, '/' ) + 1;
	}
	if ( strrchr( full_name, '.' ) != NULL )
	{
		mn_last = strrchr( full_name, '.' );
	}
	if ( mn_last < mn_first )
	{
		mn_last = full_name + strlen( full_name );
	}

	strPath.assign( mn_first, mn_last );

	return strPath;
}


std::string cComm::Get_FileType( std::string strPath )
{
	std::vector<std::string> v_path;
	SplitString(strPath,".",v_path);
	if ((v_path.size()>1))
	{
		return v_path[v_path.size() -1];
	}
	return strPath;
}


std::string cComm::Get_FilePath( std::string strPath )
{
	S32 iPos   = 0;
	S32 newPos = -1;
	S32 sizeS2 = 1;

	while ((newPos = strPath.find ("/", iPos)) > -1)
	{
		iPos = newPos + sizeS2;
	}

	if (iPos == -1)
	{
		return "";
		//iPos = strPath.size();
	}
	std::string path = strPath.substr(0,iPos);

	return path;
}


U32 cComm::GetBit(const U8 &data,
		          const U8 &pos )
{
	return data & bit_value_[pos];
}


void cComm::sleep(float time)
{
#if defined(_WINDOWS)
	Sleep(time);
#else
	usleep(time*1000);
#endif
}
U16 cComm::CRC16(U8 *p,U32 len){

	if ( (!p) || ( len < 1 ) )
	{
		return 0;
	}

	U8 i;
	int j;

	U16 uiCRC = 0xffff;

	for(j=0;j<len;j++)
	{
		uiCRC ^= (*p);
		p++;
		for( i=8; i != 0; i--)
		{
			if( uiCRC & 1 ){
				uiCRC >>= 1;
				uiCRC ^= 0xa001;
			}
			else{
				uiCRC>>=1;
			}
		}
	}
	return(uiCRC);
}

bool cComm::Check_CRC16( U8 *p,U32 len )
{
	if ( (!p) || ( len < 2 ) )
	{
		return false;
	}

	U16 crc = cComm::CRC16( p, len - 2);

	if(  (p[len - 2] != (crc & 0x00ff)>>0 ) || ( p[len - 1] != (crc & 0xff00)>>8 )){
		return false;
	}
	
	return true;

}


U8 cComm::XOR(U8 *p,U32 ilen)
{
	if ( (!p) || ( ilen < 1 ) )
	{
		return 0;
	}

	U8 u_xor = 0;
	for ( int i = 0 ; i < ilen; ++i ){
		u_xor ^= p[i];
	}
	return u_xor;
}

bool cComm::Check_XOR(U8 *p,U32 ilen)
{
	if ( (!p) || ( ilen < 2 ) )
	{
		return false;
	}

	U8 u_xor = XOR( p, ilen - 1);

	if ( p[ilen -1] == u_xor){
		return true;
	}
	return false;
}

bool cComm::Check_ip( std::string str_ip )
{
	boost::xpressive::cregex reg_ip = boost::xpressive::cregex::compile("(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[.](25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[1-9])");   
	return  regex_match(str_ip.c_str(), reg_ip); 
}



int cComm::String2Char(U8* &p_data,int &ilen,std::string str)
{
	if (p_data){
		delete[] p_data;
		p_data = 0;
	}
	str = trim(str);
	ilen = str.length();
	if (ilen > 0)
	{
		p_data = new U8[ilen];
		if (p_data)
		{
			memcpy(p_data,str.c_str(),str.length());
		}else{
			ilen = 0;
		}
		
	}
	return ilen;

}
int cComm::String2Charlist(S8* p_data,int ilen,std::string str)
{
	memset(p_data,0,ilen);

	str = trim(str);
	int islen = str.length();

	if( islen > ilen){
		islen = ilen ;
	}
	ilen = islen;

	if (ilen > 0)
	{
		memcpy(p_data,str.c_str(),ilen);

	}
	return ilen;

}
int cComm::Char2String(std::string &str,U8* p_data)
{
	std::string s((char*)p_data);
	str = s;
	return s.length();
}
std::string& cComm::replace_str(std::string& str, const std::string& to_replaced, const std::string& newchars){

	for(std::string::size_type pos(0); pos != std::string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced,pos);
		if(pos != std::string::npos)
			str.replace(pos,to_replaced.length(),newchars);
		else
			break;
	}
	return   str;
}

int cComm::Get_FileSize(std::string strPath)
{
	int i_size = 0;
	boost::filesystem::path p1(strPath);
	try
	{
		i_size = boost::filesystem::file_size(p1); //
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		cout << e.path1() << endl;
		cout << e.what() << endl;
	}
	return i_size;
}


bool cComm::Create_File(const std::string &strPath)
{
	return boost::filesystem::create_directories(strPath); 
}

KPS_VERSION cComm::getVersion()
{
	load();
	return ver_;
}

std::string cComm::getSVersion()
{
	std::stringstream ss;
	ss<<"main v:"<<ver_.v_main_<<"."<<ver_.v_sub_1_<<"."<<ver_.v_sub_2_;
	return ss.str();
}

SPos cComm::World2Local(SPos ori_pos,SPos ref_pos)
{
	SPos loc_pos;
	//ref_pos is current pos
	//ori_pos is local pos for new origin pos
	//loc_pos is current pos int new origin pos
	VecPosition vo(ori_pos.x_,ori_pos.y_);
	//
	VecPosition vr(ref_pos.x_,ref_pos.y_);
	//
	VecPosition vl = vr -vo;
	vl.rotate(-Rad2Deg(ori_pos.th_));
	loc_pos.x_ = vl.getX();
	loc_pos.y_ = vl.getY();
	loc_pos.th_ = VecPosition::normalizeAngleRad(ref_pos.th_ - ori_pos.th_);

	return loc_pos;
}

SPos cComm::Local2World(SPos loc_pos,SPos world_pos)
{
	SPos res_pos;
	//
	VecPosition vl(loc_pos.x_,loc_pos.y_);
	vl.rotate(Rad2Deg(world_pos.th_));

	//
	VecPosition vw(world_pos.x_,world_pos.y_);
	vl+= vw;

	//
	res_pos.x_ = vl.getX();
	res_pos.y_ = vl.getY();
	res_pos.th_ =  VecPosition::normalizeAngleRad(loc_pos.th_ + world_pos.th_);

	return res_pos;
}
SPos cComm::odom2pos(const SOdomSpeed &odom){
	SPos pos;
	pos.x_ = odom.x_;
	pos.y_ = odom.y_;
	pos.th_ = odom.th_;
	return pos;
}
SPos cComm::cal_diff( SPos cur_pos, SPos ori_pos ){


	SPos pos_diff = World2Local( ori_pos , cur_pos);

	return pos_diff;
}

F32 cComm::dis_p2p(SPos pos_1, SPos pos_2)
{
	SPos pos_diff = World2Local( pos_1 , pos_2);

	F32 dis = VecPosition(pos_diff.x_,pos_diff.y_).getMagnitude();

	return dis;
}

bool cComm::Del_File(const std::string &strPath)
{
	try
	{
		boost::filesystem::path p1(strPath);
		boost::filesystem::remove(p1);
		return true;
	}
	catch(boost::bad_lexical_cast)
	{
		return false;
	}
}

bool cComm::Move_File(const std::string &str_src,const std::string str_des)
{
	try
	{
		boost::filesystem::path p1(str_src);
		boost::filesystem::path p2(str_des);
		boost::filesystem::rename(p1,p2);
		return true;
	}
	catch(boost::bad_lexical_cast)
	{
		return false;
	}

	
}
