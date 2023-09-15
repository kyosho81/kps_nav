#ifndef _CONDITION_BUFFER_KYOSHO_20150909_
#define _CONDITION_BUFFER_KYOSHO_20150909_

#include <boost/thread.hpp>
#include <boost/circular_buffer.hpp> 
#include <list>
#include <iostream>

//a list buffer ,if full or empty will waiting
//usually used for comsumer productor model
template<typename T>
class LBuffer
{
private:
    boost::mutex mu;
    boost::condition_variable_any cond_put;
    boost::condition_variable_any cond_get;

	std::list<T> buffer_list;
public:
	explicit LBuffer(size_t buffer_size) : full_size(buffer_size)
    {};
	
    size_t put(T in)
    {
		size_t icount = 0;
		{
			boost::mutex::scoped_lock lock(mu);

			 while (buffer_list.size() >= full_size)
			 {
     			std::cout << "full waiting..." << std::endl;
				 cond_put.wait(lock); //
			 }
// 			if (buffer_list.full())
// 			{
// 				std::cout << "circular_buffer full:"<<buffer_list.size()<<std::endl;
// 			}
			
			buffer_list.push_back(in);
			icount = buffer_list.size();
		}
		//std::cout<<"buffer size:"<<buffer_list.size()<<std::endl;
        cond_get.notify_one();
		return icount;
    };
    void get(T &out)
    {
		{
			boost::mutex::scoped_lock lock(mu);

			while (buffer_list.empty())
			{
				//std::cout << "empty waiting..." << std::endl;
				cond_get.wait(lock);
			}
			out = buffer_list.front();
			buffer_list.pop_front();

		}
        cond_put.notify_one();
    };

	size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_list.size();
	}
private:
	int full_size ;
};
//multimap put get with condition
template<typename I,typename T>
class MtBuffer
{
private:
	boost::mutex mu;
	boost::condition_variable_any cond_put;
	boost::condition_variable_any cond_get;

	std::multimap<I,T> buffer_map;
public:
	explicit MtBuffer(size_t buffer_size) : full_size_(buffer_size)
	{};

	size_t put(I index, T in,bool b_force_put = false)
	{
		size_t icount = 0;
		{
			boost::mutex::scoped_lock lock(mu);

			while (buffer_map.size() >= full_size_)
			{
				if (b_force_put){
					break;
				}
				
				//std::cout << "full waiting..." << std::endl;
				cond_put.wait(lock); //
			}

			buffer_map.insert(std::make_pair(index,in));
			icount = buffer_map.size();
		}
		//std::cout<<"buffer size:"<<buffer_list.size()<<std::endl;
		cond_get.notify_one();
		return icount;
	};

	bool get(I &index,T &out,bool b_force_wait = true)
	{
		{
			boost::mutex::scoped_lock lock(mu);

			while (buffer_map.size() < 1)
			{
				if (b_force_wait){
					//std::cout << "empty waiting..." << std::endl;
					cond_get.wait(lock);
				}else{
					return false;
				}
				
				
			}

			typename std::multimap<I,T>::iterator it = buffer_map.begin();
			if (it != buffer_map.end()){
				index = it->first;
				out = it->second;
				buffer_map.erase(it);
			}


		}
		cond_put.notify_one();
		return true;
	};

	size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_map.size();
	}
private:
	int full_size_ ;
};

// a ring buffer put over head , if empty get will waiting 
template<typename T>
class CBuffer
{
private:
	boost::mutex mu;
	boost::condition_variable_any cond_get;

	boost::circular_buffer<T> buffer_list;
	
public:
	explicit CBuffer(size_t buffer_size) : buffer_list(buffer_size)
	{};
	size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_list.size();
	};
	void put(T in)
	{
		
		{
			boost::mutex::scoped_lock lock(mu);
			if (buffer_list.full())
			{
				//std::cout << "full !! over head ..." << std::endl;
			}
			
			buffer_list.push_back(in);
			
		}
		//std::cout<<"buffer size:"<<buffer_list.size()<<std::endl;
		cond_get.notify_one();

	};
	void get(T &out)
	{
		{
			boost::mutex::scoped_lock lock(mu);

			while (buffer_list.empty())
			{
				//std::cout << "empty waiting..." << std::endl;
				cond_get.wait(lock);
			}
			out = buffer_list.front();
			buffer_list.pop_front();

		}
	
	};
	void clear(){
		boost::mutex::scoped_lock lock(mu);
		buffer_list.clear();
	};
private:
	//int full_size ;
};
// a predefine size(SIZE) ring buffer  : put over head , if empty get will waiting
template<typename T,int SIZE>
class CSBuffer
{
private:
	boost::mutex mu;
	boost::condition_variable_any cond_get;

	boost::circular_buffer<T> buffer_list;

public:
	explicit CSBuffer() : buffer_list(SIZE)
	{};
	size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_list.size();
	};
	void put(T in)
	{

		{
			boost::mutex::scoped_lock lock(mu);
			if (buffer_list.full())
			{
				//buffer_list.pop_front();
				//std::cout << "full !! over head ..." << std::endl;
			}

			buffer_list.push_back(in);

		}
		//std::cout<<"buffer size:"<<buffer_list.size()<<std::endl;
		cond_get.notify_one();

	};
	void get(T &out)
	{
		{
			boost::mutex::scoped_lock lock(mu);

			while (buffer_list.empty())
			{
				//std::cout << "empty waiting..." << std::endl;
				cond_get.wait(lock);
			}
			out = buffer_list.front();
			buffer_list.pop_front();

		}

	};
	void clear()
	{
		boost::mutex::scoped_lock lock(mu);
		while(!buffer_list.empty()){
			buffer_list.pop_front();
		}
	};

};

// a ring buffer put get no wait
template<typename T>
class SBuffer{

public:
	explicit SBuffer(size_t buffer_size) : buffer_list(buffer_size){};
	
	std::size_t size(){
		boost::mutex::scoped_lock lock(mu);
		return buffer_list.size();
	};

	void clear(){
		boost::mutex::scoped_lock lock(mu);
		buffer_list.clear();
	};
	bool put(T in){
		boost::mutex::scoped_lock lock(mu);
		if (buffer_list.full())
		{
			buffer_list.push_back(in);
			return false;
		}else{
			buffer_list.push_back(in);
			return true;
		}
		
	};
	bool get(T &out){
		boost::mutex::scoped_lock lock(mu);
		if (buffer_list.empty())
		{
			return false;
		}
		out = buffer_list.front();
		buffer_list.pop_front();
		return true;
	};
private:
	boost::mutex mu;

	boost::circular_buffer<T> buffer_list;
};
// no use boost:a ring buffer put over head , if empty get will waiting 
#define BUFFER_SIZE 10
template<typename T>
class OCBuffer{

public:
	OCBuffer():head_(0),rear_(0),deap_(0){

	};
	~OCBuffer(){

	};
	
	bool empty(){
		if (deap_ == 0)
		{
			return true;
		}else{
			return false;
		}

	};
	bool full(){
		if (deap_ == BUFFER_SIZE)
		{
			return true;
		}else{
			return false;
		}

	};

	void push_back(const T &in){
		{
			boost::mutex::scoped_lock lock(mu);
			if (full())
			{
				std::cout<<"is full ignore:"<<msg_list_[head_]<<std::endl;
				head_ = (++head_) % BUFFER_SIZE;
				deap_--;
			}

			msg_list_[rear_] = in;
			rear_ = (++rear_) % BUFFER_SIZE;
			deap_++;
		}
		cond_get.notify_one();
		assert(deap_ < (BUFFER_SIZE+1));
	};
	void pop_front(T &in){
		boost::mutex::scoped_lock lock(mu);

		while (empty())
		{
			//std::cout << "empty waiting..." << std::endl;
			cond_get.wait(lock);
		}

		in = msg_list_[head_];
		std::cout<<"pop index:"<<head_<<" value:"<<msg_list_[head_]<<std::endl;

		head_ = (++head_) % BUFFER_SIZE;
		deap_--;

	};

private:
	T msg_list_[BUFFER_SIZE];
	int head_;
	int rear_;
	int deap_;
	boost::mutex mu;
	boost::condition_variable_any cond_get;
};
//no mutex no boost :a ring buffer put over head , if empty get will waiting 
template<typename T,int BSIZE>
class CrList{

public:
	CrList():head_(0),rear_(0),deap_(0){
		memset(msg_list_,0,sizeof(T)* BSIZE);
	};

	CrList(const T &t):head_(0),rear_(0),deap_(0){

		head_ = t.head_;
		rear_ = t.rear_;
		deap_ = t.deap_;
		memcpy(msg_list_,t.get_data_p(),sizeof(T)* BSIZE);
	};

	~CrList(){

	};


	bool empty(){
		if (deap_ == 0)
		{
			return true;
		}else{
			return false;
		}

	};
	bool full(){
		if (deap_ == BSIZE)
		{
			return true;
		}else{
			return false;
		}

	};

	bool push_back(const T &in , const bool &force_push = false){
		{

			if (full())
			{
				if(force_push){
					//std::cout<<" CBuffer is full ignore:"<<msg_list_[head_]<<std::endl;
					head_ = (++head_) % BSIZE;
	
					msg_list_[rear_] = in;
					rear_ = (++rear_) % BSIZE;


				}
				
				return false;
			}

			msg_list_[rear_] = in;
			rear_ = (++rear_) % BSIZE;
			deap_++;
		}

		assert(deap_ < (BSIZE+1));

		return true;
	};
	bool pop_front(T &in){

		if (empty())
		{
			return false;
		}

		in = msg_list_[head_];
		//std::cout<<"pop index:"<<head_<<" value:"<<msg_list_[head_]<<std::endl;

		head_ = (++head_) % BSIZE;
		deap_--;

		return true;
	};
	bool pop_back(T &in){

		if (empty())
		{
			return false;
		}
		rear_ = (--rear_ + BSIZE) % BSIZE;
		in = msg_list_[rear_];
		//std::cout<<"pop index:"<<head_<<" value:"<<msg_list_[head_]<<std::endl;

		deap_--;

		return true;
	};
	void clear(){
		head_ = 0;
		rear_ = 0;
		deap_ = 0;

		memset( &msg_list_, 0 , sizeof(T)*BSIZE );
	};

	void* get_data_p(){
		return (void*)msg_list_;
	};
private:

	T msg_list_[BSIZE];
	int head_;
	int rear_;
	int deap_;

};

template<typename T,int SIZE>
class filter{


private:

	T g_average[SIZE];
	int average_index;
	bool b_full_;
public:
	filter():average_index(0){
		memset(g_average,0,sizeof(T)*SIZE);
		b_full_ = false;
	};
	~filter(){};
	void clear(){
		average_index;
		memset(g_average,0,sizeof(T)*SIZE);
		b_full_ = false;
	};
	T Average(T data){
		int index;
		double tmp = 0;
		g_average[average_index] = data;

		if ( (average_index + 1) == SIZE)
		{
			b_full_ = true;
		}

		int max_index = SIZE;
		if (!b_full_)
		{
			max_index = average_index+1;
		}

		for (index = 0; index < max_index; ++index)
		{
			tmp += g_average[index];
		}
		tmp /= max_index;

		average_index++;
		average_index %= SIZE;

		return tmp;
	};
};

template<typename T>
class THSafe{

public:

	THSafe(){};
	~THSafe(){};

	THSafe(const T& in){
		boost::mutex::scoped_lock lock(mu_);
		t_ = in;
	};

	void operator = ( const T &in ){
		boost::mutex::scoped_lock lock(mu_);
		t_ = in;
	};

	T operator () (void){
		boost::mutex::scoped_lock lock(mu_);
		T out = t_;
		return out;
	};

private:

	T t_;
	boost::mutex mu_;
};

template<typename T,int SIZE>
class UData_buffer{
public:

	UData_buffer(){

		clear_data();

	};
	~UData_buffer(){
		index_tail_ = 0;

	};
	bool put( const T* t,int ilen ){
		if ( (index_tail_ + ilen ) < SIZE )
		{
			
			memcpy((char*)(data_ + size()),(char*)t,sizeof(T)*ilen);
			index_tail_ += ilen;
			
			return true;
		}
		else{
			return false;
		}
	};

	bool put(const T &t){
		if ( (index_tail_ + 1) < SIZE )
		{
			index_tail_++;
			data_[index_tail_] = t;
			return true;
		}
		else{
			return false;
		}
	};
	bool get( T &t){
		if ( index_tail_  >= 0)
		{
			t = data_[index_tail_--];
			return true;
		}else{
			return false;
		}

	};
	bool get( T* p_data, int ilen){
		
		if ( (size() - ilen) >= 0)
		{
			memcpy((char*)p_data,(char*)data_,sizeof(T)*ilen);
			index_tail_ -= ilen;
			memcpy(data_, data_ + sizeof(T)*ilen, sizeof(T)*size()  );
			
			return true;
		}else{
			return false;
		}

	};
	bool get_all(T* p_data,int &len){
		len =  size();
		if ( len )
		{
			memcpy((char*)p_data,(char*)data_,sizeof(T)*len);
			memset((char*)data_, 0,sizeof(T)*SIZE);
			index_tail_ = -1;
			return true;
		}else{
			return false;
		}

	}
	std::size_t size(){
		return index_tail_ + 1;
	};

	void clear_data(){
		memset((char*)data_, 0,sizeof(T)*SIZE);
		index_tail_ = -1;
	};
private:
	T data_[SIZE];
	int index_tail_;
};
// LBuffer<int> data_list_(10);
// void thread_consumer(){
// 	int i = 0;
// 
// 	while(1){
// 		if (i%5 == 0)
// 		{	
// 			for (int ic = 0; ic < 10 ; ++ic)
// 			{
// 				int si = data_list_.put(i);
// 				std::cout<<"th1 buf size:"<<si<<std::endl;
// 			}
// 
// 		}else{
// 			int si = data_list_.put(i);
// 			std::cout<<"th1 buf size:"<<si<<std::endl;
// 		}
// 		SLEEP(500);
// 		++i;
// 
// 	}
// }
// void thread_producter(){
// 	while(1){
// 		int i = 0;
// 		data_list_.get(i);
// 		std::cout<<"get:"<<i<<std::endl;
// 	}
// }
// int main(int argc, char* argv[]){
// 	boost::thread th1(boost::bind(thread_consumer));
// 	boost::thread th2(boost::bind(thread_producter));
// 
// 	while(1){
// 		for (int ic = 0; ic < 10 ; ++ic)
// 		{
// 			int si = data_list_.put(-99);
// 			std::cout<<"buf size:"<<si<<std::endl;
// 		}
// 		SLEEP(1000);
// 	}
// CBuffer<int> data_list_(10);
// void thread_consumer(){
// 	int i = 0;
// 
// 	while(1){
// 
// 		data_list_.put(i);
// 		std::cout<<"put:"<<i<<std::endl;
// 		SLEEP(100);
// 		++i;
// 
// 	}
// }
// void thread_producter(){
// 	while(1){
// 		int i = 0;
// 		data_list_.get(i);
// 		std::cout<<"     get:"<<i<<std::endl;
// 		SLEEP(200);
// 	}
// }
// int main(int argc, char* argv[]){
// 	boost::thread th1(boost::bind(thread_consumer));
// 	boost::thread th2(boost::bind(thread_producter));
// 
// 	while(1){
// 
// 		SLEEP(1000);
// 	}
// }

#endif//_CONDITION_BUFFER_KYOSHO_20150909_

