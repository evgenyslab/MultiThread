//
// Created by Evgeny Nuger on 17/01/18.
//

/*
 * Example of using a data queue that stores workable classes, and then copies the queue indices into a threadpool.
 *
 * */

#include <iostream>
#include <queue.h>
#include <worker.h>

class worker_a: public worker::work {
private:
  std::string function_name;
  unsigned long function_ID;
public:

  worker_a(){
    process_name = "worker_a";
    function_name = "NULL";
    function_ID = 0;
  };
  // overload:
  explicit worker_a(std::string fname, unsigned long fid = 0):function_name(fname),function_ID(fid){
    process_name = "worker_a";
  };


  // do work:
  void operator()() override {
    for(int i=0; i< 1e3; i++){

    };
    std::cout << "worker_a: " << function_name << " " << function_ID << " finished\n";
  };


};

int main(int argc, char** argv){
  std::cout << "Example of multi-Threading Function\n";

  // make thread worker object:
  worker::threadpool pool;

  worker_a process_a_1("first",5);
  worker_a process_a_2("second",1);
  worker_a process_a_3("third",234);
  worker_a process_a_4("fourth",90);

  // create a workQueue:
  queue::queue<worker_a> q(5,queue::QUEUE_FIXEDSIZE | !queue::QUEUE_FRONTLOAD | queue::QUEUE_DESTRUCTIVE);

  q.add(process_a_1);
  q.add(process_a_2);
  q.add(process_a_3);
  q.add(process_a_4);

  // now, add queue indices to pool:
  pool.add(q[0]);
  pool.add(q[1]);
  pool.add(q[2]);
  pool.add(q[3]);

  pool.join();

  // now try serial queue:
  worker::serial serialWorkList;
  serialWorkList.add(q[0]);
  serialWorkList.add(q[1]);
  serialWorkList.add(q[2]);
  serialWorkList.add(q[3]);


  return 0;
}
