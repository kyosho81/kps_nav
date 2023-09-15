#define MAIN0 0
#define MAIN1 0
#define MAIN2 0
#define MAIN3 1

#include "Comm/Comm.h"

#if MAIN0

/*! \file
* \brief threadpool tutorial.
*
* This file contains a tutorial for the threadpool library. 
*
* Copyright (c) 2005-2007 Philipp Henkel
*
* Distributed under the Boost Software License, Version 1.0. (See
* accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*
* http://threadpool.sourceforge.net
*
*/

//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include "threadpool/threadpool.hpp"

using namespace std;
using namespace boost::threadpool;

//
// Helpers
boost::mutex m_io_monitor;

void print(string text)
{
  boost::mutex::scoped_lock lock(m_io_monitor);
  cout << text;
}

template<typename T>
string to_string(T const & value)
{
  ostringstream ost;
  ost << value;
  ost.flush();
  return ost.str();
}



//
// An example task functions
void task_1()
{
  print("  task_1()\n");
  throw 5;
}

void task_2()
{
  print("  task_2()\n");
  throw 5;
}

void task_3()
{
  print("  task_3()\n");
}

void task_with_parameter(int value)
{
  print("  task_with_parameter(" + to_string(value) + ")\n");
}

int loops = 0;
bool looped_task()
{
  print("  looped_task()\n");
  return ++loops < 5; 
}


int task_int_23()
{
  print("  task_int_23()\n");
  return 23;
}

int task_int_1()
{
  print("  task_int_1()\n");
  return 1;
}


class CTest
{
  pool m_pool;
public:
  CTest()
    : m_pool(pool(1000))
  {
  }
};


//
// A demonstration of the thread_pool class
int main (int , char * const []) 
{
  print("\nWelcome to the threadpool tutorial!\n");

  print("\n**************************************\n");
  print("Section 1: Quick Start\n");
  
  //void func()
  {	
    print("  Create a new thread pool\n");
    pool tp(2); // tp is handle to the pool

    // Add tasks
    tp.schedule(&task_1);
    tp.schedule(&task_2);
    tp.schedule(&task_3);
    tp.schedule(boost::bind(task_with_parameter, 4));

    // The pool handle tp is allocated on stack and will 
    // be destructed if it gets out of scope. Before the 
    // pool is destroyed it waits for its tasks. 
    // That means the current thread of execution is 
    // blocked at the end of the function 
    // (until all tasks are processed).
    // while (&tp){int i = 3; ++i;}
  }	 

  { // Section Futures
    print("\n**************************************\n");
    print("Section 1: Futures\n");
    
  //typedef thread_pool<task_func, fifo_scheduler, static_size, empty_controller, wait_for_all_tasks> test_pool;

    pool tp;

//    tp.resize(0);
    tp.pending();
//    tp.clear();
    boost::xtime t;
    tp.wait(t);
    bool test = tp.empty();
    if(test) 
    {
      test = false;
    }

    tp.size_controller().resize(2);

    //test_pool::size_controller_type controller = tp.size_controller();
//    controller.resize(5);

    schedule(tp, &task_int_1);
    future<int> res = schedule(tp, &task_int_23);
    future<int> res2 = schedule(tp, &task_int_1);

    res.wait();
    int value = res.get() + res2.get();

    res.cancel();
    res.is_cancelled();
value ++;

//thread_pool<boost::function0<int>, fifo_scheduler> test2332;

//TODO runnable comile test
  }



  {	// Section 2
    print("\n**************************************\n");
    print("Section 2: Controlling scheduling\n");

    // Create a lifo_pool: last task in, first task out
    lifo_pool tp(0);

    print("  Add tasks (using the pool's schedule function)\n");	
    schedule(tp, &task_1);
    schedule(tp, &task_2);
    schedule(tp, &task_3);

    // tp.wait();  This would be a deadlock as there are no threads which process the tasks.

    print("  Add some threads ...\n");	
    tp.size_controller().resize(5);

    print("  Wait until all tasks are finished ...\n");
    tp.wait();
    print("  Tasks finished!\n");	
  }	



  {	// Section 3:
    print("\n**************************************\n");
    print("Section 3: Prioritized Tasks\n");

    prio_pool tp(0);


    print("  Add prioritized tasks ...\n");	
    schedule(tp, prio_task_func(1, &task_1));
    schedule(tp, prio_task_func(10,&task_2));
    schedule(tp, prio_task_func(5,&task_3));

    // Tasks are ordered according to their priority: task_2, task_4, task_3, task_1

    print("  Thread added\n");	
    tp.size_controller().resize(10);

    print("  Wait until all tasks are finished ...\n");
    tp.wait();
    print("  Tasks finished!\n");	
  }		


/* */
  {	// Section 5:
    print("\n**************************************\n");
    print("Section 5: Advanced thread pool instantiation\n");
    // Create the pool directly
/*
TODO
boost::shared_ptr<fifo_pool> tp = fifo_pool::create_pool(5);			

    print("  Add tasks ...\n");
    tp->schedule(&task_1);
    tp->schedule(&task_2);
    tp->schedule(&task_3);
    tp->schedule(looped_task_func(&looped_task, 1500));

    print("  Wait until all tasks are finished ...\n");
    tp->wait();
*/
  
    print("  Tasks finished!\n");
  			
  }			


  print("\n**************************************\n");
  print("Tutorial finished!\n");



  {	// Section Compile Tests
    print("\n**************************************\n");
    print("Section Compile Tests\n");


    fifo_pool tp;
    tp.size_controller().resize(0);
    tp.empty(); 
  }

  return 0;
}
#endif //MAIN0


#if MAIN1
/*! \file
* \brief threadpool tutorial.
*
* This file contains a tutorial for the threadpool library. 
*
* Copyright (c) 2005-2006 Philipp Henkel
*
* Distributed under the Boost Software License, Version 1.0. (See
* accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*
* http://threadpool.sourceforge.net
*
*/




#include <iostream>
#include <sstream>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include "threadpool/threadpool.hpp"

using namespace std;
using namespace boost::threadpool;


//
// Helpers
boost::mutex m_io_monitor;

void print(string text)
{
	boost::mutex::scoped_lock lock(m_io_monitor);
	cout << text;
}

template<typename T>
string to_string(T const & value)
{
	ostringstream ost;
	ost << value;
	ost.flush();
	return ost.str();
}



//
// An example task functions
void task_1()
{
	print("  task_1()\n");
}

void task_2()
{
	print("  task_2()\n");
}

void task_3()
{
	print("  task_3()\n");
}

int task_4()
{
	print("  task_4()\n");
	return 4;
}

void task_with_parameter(int value)
{
	print("  task_with_parameter(" + to_string(value) + ")\n");
}

int loops = 0;
bool looped_task()
{
	print("  looped_task()\n");
	return ++loops < 5; 
}


int task_int()
{
	print("  task_int()\n");
	return 23;
}


void fifo_pool_test()
{
	pool tp;

	tp.schedule(&task_1);
	tp.schedule(boost::bind(task_with_parameter, 4));

	if(!tp.empty())
	{
		tp.clear();  // remove all tasks -> no output in this test
	}

	size_t active_threads   = tp.active();
	size_t pending_threads  = tp.pending();
	size_t total_threads    = tp.size();

	size_t dummy = active_threads + pending_threads + total_threads;
	dummy++;

	tp.size_controller().resize(5);
	tp.wait();
}

void lifo_pool_test()
{
	lifo_pool tp;
	tp.size_controller().resize(0);
	schedule(tp, &task_1);
	tp.size_controller().resize(10);
	tp.wait();
}

void prio_pool_test()
{
	prio_pool tp(2);
	schedule(tp, prio_task_func(1, &task_1));
	schedule(tp, prio_task_func(10,&task_2));
}


void future_test()
{
	fifo_pool tp(5);
	future<int> fut = schedule(tp, &task_4);
	int res = fut();
}


int main (int , char * const []) 
{
	fifo_pool_test();
	lifo_pool_test();
	prio_pool_test();
	future_test();
	return 0;
}
#endif //MAIN1

#if MAIN2
/*! \file
 * \brief Mergesort example.
 *
 * This example shows how to use the threadpool library. 
 *
 * Copyright (c) 2005-2006 Philipp Henkel
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * http://threadpool.sourceforge.net
 *
 */



#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "threadpool/threadpool.hpp"

using namespace std;
using namespace boost::threadpool;

//
// Helpers
boost::mutex m_io_monitor;

void print(string text)
{
  boost::mutex::scoped_lock lock(m_io_monitor);
  cout << text;
}

template<class T>
string to_string(const T& value)
{
  ostringstream ost;
  ost << value;
  ost.flush();
  return ost.str();
}

unsigned long get_ms_diff(boost::xtime& start, boost::xtime& end)
{
  boost::xtime::xtime_sec_t start_ms = start.sec * 1000	+ start.nsec/1000000; 
  boost::xtime::xtime_sec_t end_ms = end.sec * 1000	+ end.nsec/1000000; 
  return static_cast<unsigned long>(end_ms - start_ms);
}

class image
{
public:
  image() : m_content(0)	{}
  image(int content) : m_content(content)	{}

  image(const image& src)
  {
    m_content = src.m_content;
  }

  bool operator<(const image& l) const
  {
    {	// simulate time needed for image comparison
      boost::xtime xt;
      boost::xtime_get(&xt, boost::TIME_UTC_);
      int duration = 1+(m_content % 4);
      xt.nsec += 250 * 1000 * duration;	
      boost::thread::sleep(xt); 
	    print(".");
    }	
    return m_content < l.m_content;
  }

protected:
  int m_content;	// represents image data in this example
};


template<class T>
class merge_job
{
public:
  merge_job(boost::shared_array<T> data, unsigned int position, unsigned int length) 
    : m_data(data)
    , m_position(position)
    , m_length(length) 
  {
    print("merge job created : " + to_string(m_position) +", "+ to_string(m_length) +"\n");
  }

  void run()
  {	
    print("merge job running :   " + to_string(m_position) +", "+ to_string(m_length) +"\n");

    T* begin = m_data.get();
    std::advance(begin, m_position);

    T* mid = m_data.get();
    std::advance(mid, m_position + m_length/2);

    T* end = m_data.get();
    std::advance(end, m_position + m_length);

    std::inplace_merge(begin, mid, end);

    print("\nmerge job finished:     "  + to_string(m_position) +", "+ to_string(m_length) +"\n");
  }

protected:
  boost::shared_array<T> m_data;
  unsigned int m_position;
  unsigned int m_length;
};




//
// A demonstration of the thread_pool class
int main (int argc, char * const argv[]) 
{
  print("MAIN: construct thread pool\n");

		

  boost::xtime start;
  boost::xtime_get(&start, boost::TIME_UTC_);

  int exponent = 7;
  int data_len = 1 << exponent;  // = pow(2, exponent) 

  print("MAIN: sort array with "+ to_string(data_len) + " elements.\n");

  boost::shared_array<image> data(new image[data_len]);

  // fill array with arbitrary values (not sorted ascendingly)
  for(int i = 0; i < data_len; i++)
  {
    data[i] = image((data_len - i - 1) % 23);
  }


  /***************************/
  /* Standard implementation */
  /***************************/

  pool tp;
  tp.size_controller().resize(5);	

// merge data array
  for(int step = 1; step <= exponent; step++)
  {
    print("\nMAIN: merge step "+ to_string(step)+"\n");

    // divide array into partitions
    int partition_size = 1 << step;
    for(int partition = 0; partition < data_len/partition_size; partition++)
    {
      // sort partition
      boost::shared_ptr<merge_job<image> > job(new merge_job<image>(data, partition*partition_size, partition_size));
      //tp->schedule(prio_task_func(5, boost::bind(&merge_job<image>::run, job)));
      schedule(tp, boost::bind(&merge_job<image>::run, job));
     // schedule(tp, job);
    }
    tp.wait();	// wait until all partitions are sorted
  } 

  boost::xtime end;
  boost::xtime_get(&end, boost::TIME_UTC_);				

  print("\nMAIN: duration " + to_string(get_ms_diff(start, end)) + " ms \n");

  print("\nMAIN: check if array is sorted... \n");

  // check if array is sorted ascendingly 
  bool ascending = true;
  for(int i = 0; i < data_len-1; i++)
  {
    if(data[i+1] < data[i])
    {
      ascending = false;
    }
  }

  if(ascending)
  {
    print("\nMAIN: array is sorted\n");
  }
  else
  {
    print("\nMAIN: array is NOT sorted!\n");
  }

  return 0;
}
#endif//MAIN2

#if MAIN3
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "threadpool/threadpool.hpp"

using namespace std;
using namespace boost::threadpool;


void task_1()
{
	cout << "task_1 start" << endl;
	cout << "thead_id(task_1): " << boost::this_thread::get_id() << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "1111111111111111111111111" << endl;
		SLEEP(1);
	}
}

void task_2()
{
	cout << "task_2 start" << endl;
	cout << "thead_id(task_2): " << boost::this_thread::get_id() << endl;
	for (int i = 0; i < 30; i++)
	{
		cout << "222222222222222222222222" << endl;
		SLEEP(1);
	}
}

void DoGetVersionNoForUpdate(int a)
{
	cout << "task_3 start" << endl;
	cout << "thead_id(task_3): " << boost::this_thread::get_id() << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << a*a << endl;
		SLEEP(1);
	}
}


int main(int argc, char *argv[])
{
	//设置允许开启的线程数
	pool tp(10);

	//加入线程调度，可以通过指针传参
	tp.schedule(&task_1);
	tp.schedule(&task_2);
	int i =10;
	tp.schedule(boost::bind(DoGetVersionNoForUpdate, i));

	//tp.wait();

	return (0);
}

#endif //MAIN3