//
// Created by Evgeny Nuger on 15/01/18.
//

#pragma once

#ifndef FRAMEWORKS_WORKER_H
#define FRAMEWORKS_WORKER_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>

namespace worker{

  // Data partitioning for multithread pools
  // Data must in a vector, for k threads
  // output is a vector of size k with vectors of data
  template<class T>
  static void partition(std::vector<T> & data, std::vector<std::vector<T>> & partitions, unsigned long k=1){
    // ensure input number of data is greater or equal to the number of partitions
    assert(data.size() >= k);
    // get number of input data pieces:
    auto n = data.size();
    // resize the output number of partitions:
    partitions.resize(k);
    // get peices per partition:
    auto ppk = n/k;
    // position iterator of data vector:
    auto start = data.begin();
    // populate partitions
    for(auto i=0; i<k;i++){
      std::vector<T> temp(start,(i==k-1? data.end(): start + ppk));
      partitions[i].swap(temp);
      start = start+ppk;
    }

  }

  class threadpool{
  private:
    std::vector<std::thread> t;

  public:

    template<class T>
    void add(T & workable){
      t.emplace_back(std::thread(std::ref(workable)));
      // may want to add max thread count and join, reset
    }



    void join(){
      for (auto& th : t) th.join();
      t.clear();
    }

  };

  /// This is a serial implementation of a worker queue
  /// it will simply run the functor operation on the workable class.
  class serial{
  public:
    template<class T>
    void add(T & workable){
      workable();
    }
  };

  /// Template interface for work processes that MUST overload () functor
  /// The purpose of this template interface is to ensure all child worker functions have a set of minimum implementations.
  class work{
  protected:
    std::string process_name;
    unsigned long process_ID;


  public:


    virtual ~work()=default;
    // overload:
    virtual void operator()()=0;

    // NOTE, to create virtual function that must be defined by derived class:
//     virtual void blah()=0;
//     BUT, the derived class must use the same arguments!

    std::string getInfo(){
      return process_name;
    }

  };

}


#endif //FRAMEWORKS_WORKER_H
