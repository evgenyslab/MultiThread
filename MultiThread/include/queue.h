//
// Created by Evgeny Nuger on 15/01/18.
//

#pragma once
#ifndef FRAMEWORKS_QUEUE_H
#define FRAMEWORKS_QUEUE_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>

/// blah 1
/// blah
namespace queue{
  enum FLAGS {
    QUEUE_FIXEDSIZE       = 0b0000'0001,
    QUEUE_FRONTLOAD       = 0b0000'0010,
    QUEUE_DESTRUCTIVE     = 0b0000'0100,
    QUEUE_NEWDATAADDED    = 0b0000'0001,
  };

  template <class T>
  class queue{
  private:
      std::vector<T> q;
      unsigned char options;
      unsigned char status;
      unsigned long addCounter;

  public:

    // constructor
    queue():options(0),status(0),addCounter(0){};

    explicit queue(unsigned int s, unsigned char opt):options(opt),status(0),addCounter(0){
      q.resize(s);
    };

    //destructor
    ~queue()= default;

    // configure (use with default constructor):
    void configure(unsigned char opt, unsigned int s = -1){
      // set options:
      options |= opt;
      // fix size if s>0:
      if (s>0){
        q.resize(s);
        options |= QUEUE_FIXEDSIZE;
      }

    };

    // add object to queue:
    void add(T tobj){
      auto opt = options & ~QUEUE_DESTRUCTIVE; // remove desctructive flag
      switch(opt){ // switch by options for fixed size or frontload
        case (QUEUE_FIXEDSIZE | !QUEUE_FRONTLOAD):{
          // end load case, shift up by 1, then add to end
          this->shift();
          q.back() = tobj;
          break;
        }
        case (QUEUE_FIXEDSIZE | QUEUE_FRONTLOAD):{
          // front load case, shift down by 1, then add to front
          this->shift(-1);
          q.front() = tobj;
          break;
        }
        default:{
          q.emplace_back(tobj); // default case, no options
          break;
        }
      }
      // set status flag to indicate new data was added to the queue:
      status |= QUEUE_NEWDATAADDED;
      // increment add counter
      addCounter++;
    }

    // get size of queue:
    unsigned long size(){
      return q.size();
    }

    // clear object queue
    void clear(){
      q.clear();
    }

    // generic shifter
    // default shift is one up.
    void shift(int n = 1){
      // n < 0 shifts down,
      // n > 0 shifts up
      // First, make copy of queue.
      std::vector<T> old = q;
        if(options & QUEUE_DESTRUCTIVE){
          for(unsigned long i=0; i<q.size();i++){
            // check if new pose is outside of queue:
            unsigned long newPose = (i+n);
            if ((newPose < 0) | (newPose >= q.size())){
              // add empty T object to current pose:
              q[i] = T();
            }else{
              q[i] = old[(i+n)%q.size()];
            }
          }
        }
        else{
          // non destructive
          for(unsigned long i=0; i<q.size();i++){
            q[i] = old[(i+n)%q.size()];
          }
        }
    }

    // return item at ith position of queue
    T& operator[](unsigned int i){
      if (i<q.size()) {
        return std::ref(q[i]);
      }
      else{
        throw std::runtime_error("Attempted to access out of bounds item in Queue.");;
      }
    }

    // bool check to see if new data is available:
    unsigned long available(){
      return (addCounter>0? (addCounter>q.size()? q.size(): addCounter) : 0);
    }

    // Return method with RESETTING THE NEW DATA ADDED flag
    T& get(unsigned int i){
      if (i<q.size()) {
        status |= ~QUEUE_NEWDATAADDED; // reset data get flag.
        addCounter = 0; //reset add counter
        return std::ref(q[i]);
      }
      else{
        throw std::runtime_error("Attempted to access out of bounds item in Queue.");
      }
    }


  };

}

#endif //FRAMEWORKS_QUEUE_H
