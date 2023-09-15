#ifndef _MID_FILTER_WANGHONGTAO_20200329_
#define _MID_FILTER_WANGHONGTAO_20200329_

#include <string>
#include <map>
#include <boost/thread.hpp>

#include "Comm/buffer_con.hpp"

class GridMap;

template<typename T>
class mid_filter
{
public:
	mid_filter(){};
	~mid_filter(){};



	T filter_data(int filter_wind, const T &data){

		assert(filter_wind > 0);
		
		l_filter_.push_back(data);

		if (l_filter_.size() > filter_wind){

			l_filter_.pop_front();
		}
		if (filter_wind > l_filter_.size() ){
			return data;
		}


		std::map<T,int> res;

		typename std::list<T>::iterator it = l_filter_.begin();
		for ( ; it != l_filter_.end(); ++it ){
			res[*it] = 0;
			//std::cout<<" f:"<<*it;
		}
		//std::cout<<std::endl;


		typename std::map<T,int>::iterator it2 = res.begin();
		for (int i = 0 ; it2 != res.end() ; ++i ){
			if( i >= (filter_wind / 2 )){
				break;
			}else{
				typename std::map<T,int>::iterator it3 = it2;
				if ( ++it3 != res.end()){
					it2 = it3;
				}

			}
		}

		return it2->first;

	};

	void clear(){
		l_filter_.clear();
	};

protected:
private:
	std::list<T> l_filter_;
};


#endif//_MID_FILTER_WANGHONGTAO_20200329_
