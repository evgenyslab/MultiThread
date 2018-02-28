//
// Created by Evgeny Nuger on 16/01/18.
//

#include <iostream>
#include <queue.h>
#include <worker.h>
void add(int j){
  j++;
}

class worker_b: public worker::work {
public:

  worker_b(){
    process_name = "worker_a";
  };

  ~worker_b()=default;

  // do work:
  void operator()() override{
    for(int i=0; i< 1e9; i++){
      add(i);
    };
    std::cout << "worker_b finished\n";
  };
};

class basic_work{
public:
   basic_work()=default;
  ~basic_work()=default;

  void operator()(){
    for(int i=0;i<1e3;i++){};
  }
};


class worker_c: public worker::work {
public:

  worker_c(){
    process_name = "worker_a";
  };

  ~worker_c()=default;

  // do work:
  void operator()() override{
    // do threaded work here...
    worker::threadpool local_pool;
    basic_work a;
    basic_work b;
    local_pool.add(a);
    local_pool.add(b);

    std::cout << "worker_c finished\n";
  };
};

int main(int argc, char** argv){
  std::cout << "Example of multi-Threading Function\n";

  // make worker object:
  worker::threadpool pool;

  worker_b process_a_1;
  worker_b process_a_2;
  worker_b process_a_3;
  worker_b process_a_4;


  pool.add(process_a_1);
  pool.add(process_a_2);
  pool.add(process_a_3);
  pool.add(process_a_4);

  pool.join();



  return 0;
}