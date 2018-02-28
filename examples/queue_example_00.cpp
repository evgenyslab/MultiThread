//
// Created by Evgeny Nuger on 16/01/18.
//

#include <iostream>
#include <queue.h>


int main(int argc, char** argv){

  queue::queue<int> q(5,queue::QUEUE_FIXEDSIZE | !queue::QUEUE_FRONTLOAD | queue::QUEUE_DESTRUCTIVE);

  q.add(5);
  q.add(8);
  q.add(32);

  q.shift(3);

}