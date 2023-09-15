#ifndef _COMM_KYOSHO_20110903_
#define _COMM_KYOSHO_20110903_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>



#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "Comm/MyDefine.h"


typedef union{
	U16 u16_crc_;
	U8 byte_[2];
}UNION_CRC16;

/**************************************************************************************************
 * class cComm
***************************************************************************************************/
class cComm
{
public:
	cComm(void);
	~cComm(void);

public:
	static void sleep(F32 time);

	static int SplitString(const std::string        &input,
			               const std::string        &delimiter,
			               std::vector<std::string> &results);

	static int PatternCount(const std::string       &str,
							const std::string       &pattern);

	static void StringUpper(std::string &strDes);

    static std::string trim(std::string &str);
    static std::string trim_n(std::string &str);
	static std::string trim_cr(std::string &str);

	static std::string ByteToHexString(U8   *pData,
			                      S32   iLen);

	static S32 HexStringToByte(U8      **pChar,
			                   S32      &iLen,
			                   std::string    strHex);
	static S32 HexStringToByte( U8*      pChar,
								S32      &iLen,
								std::string    strHex);

	static void Find_files(const std::string        &strdir,
			               const std::string        &filename,
			               std::vector<std::string> &v);

	static std::string GetRunPath();

	static bool FileExist(std::string strPath);

	static std::string Get_FileName(std::string strPath);

	static std::string Get_FileType(std::string strPath);

	static std::string Get_FilePath(std::string strPath);

	static int Get_FileSize(std::string strPath);

	static bool Create_File(const std::string &strPath);
	static bool Del_File(const std::string &strPath);
	static bool Move_File(const std::string &str_src,const std::string str_des);

	static bool load();

	static U32 GetBit(const U8 &data,
			          const U8 &pos );

	static U16 CRC16(U8 *p,U32 len);
	static bool Check_CRC16(U8 *p,U32 len);

	static U8 XOR(U8 *p,U32 len);
	static bool Check_XOR(U8 *p,U32 ilen);

	static bool Check_ip(std::string str_ip);

	static int String2Char(U8* &p_data,int &ilen,std::string str);
	static int String2Charlist(S8* p_data,int ilen,std::string str);
	static int Char2String(std::string &str,U8* p_data);

	static std::string& replace_str(std::string& str, const std::string& to_replaced, const std::string& newchars);


public:
	template<typename T>
	static bool RangeIt(T &res,
			            T  min,
			            T  max)
	{
		if (res < min)
		{
			res = min;
			return false;
		}
		if (res > max)
		{
			res = max;
			return false;
		}
		return true;
	};

	template<typename T>
	static bool SaveGetFromBuffer(T& res,char* buffer,T tmin,T tmax)
	{
		T t;
		memcpy(&t,buffer,sizeof(T));
		if (!RangeIt(t,tmin,tmax))
		{
			memset(&tmax,0,sizeof(T));
			return false;
		}else
		{
			res = t;
			return true;
		}
	};

	template<typename T>
	static bool SetBufferOfType(char* buffer,const T& source)
	{
		if (!buffer)
		{
			return false;
		}
		memset(buffer,0,sizeof(T));
		memcpy(buffer,&source,sizeof(T));
		return true;
	};

	template<typename T>
	static bool num_valid(const char* str)
	{
		try
		{
			boost::lexical_cast<T>(str);
			return true;
		}
		catch(boost::bad_lexical_cast)
		{
			return false;
		}
	};

	template<typename T>
	static std::string ConvertToString(T value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	};

	template<typename T>
	static bool ConvertToNum(T &res,const std::string &str)
	{
		try
		{
			res = boost::lexical_cast<T>(str.c_str());
			return true;
		}
		catch (boost::bad_lexical_cast& e)
		{
			//std::cout<<"conver err! str:"<<str<<" res:"<<res<<std::endl;
		}
		return false;
	};

	template<typename T>
	static T Max(T t1 ,T t2)
	{
		if (t1 > t2)
		{
			return t1;
		}
		else
		{
			return t2;
		}
	};

	template<typename T>
	static T Min(T t1 ,T t2){
		if (t1 < t2)
		{
			return t1;
		}
		else
		{
			return t2;
		}
	};
	template<typename T>
	static T Lcm(T t1, T t2)
	{
		return boost::math::lcm(t1,t2);
	};

public:
// 	static SPos World2Local(SPos ori_pos,SPos ref_pos);
// 	static SPos Local2World(SPos loc_pos,SPos world_pos);
// 	static SPos odom2pos(const SOdomSpeed &odom);
// 	static SPos cal_diff( SPos cur_pos, SPos ori_pos );
// 	static F32 dis_p2p(SPos pos_1, SPos pos_2);

private:
	static U8 bit_value_[8];

};






/**************************************************************************************************
 * Marocs
***************************************************************************************************/
#define SLEEP(time)      cComm::sleep(time)
#define SDelete( ptr )   do { if ( ptr ) { delete ( ptr ); ( ptr ) = 0; } } while(0)


#endif //_COMM_KYOSHO_20110903_
