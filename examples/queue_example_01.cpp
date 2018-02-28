//
// Created by Evgeny Nuger on 16/01/18.
//

#include <iostream>
#include <queue.h>

class myClass{
public:
  int j;
  myClass():j(0){};
  explicit myClass(int k):j(k){
  };
};

int main(int argc, char** argv){

  myClass obja(1), objb(2), objc(3), objd(4);
  queue::queue<myClass> q(5,queue::QUEUE_FIXEDSIZE | !queue::QUEUE_FRONTLOAD | queue::QUEUE_DESTRUCTIVE);

  std::cout << "is there new data in q? : " << q.available() << "\n";
  q.add(obja);
  std::cout << "is there new data in q? : " << q.available() << "\n";
  q.add(objb);
  std::cout << "is there new data in q? : " << q.available() << "\n";
  q.add(objc);
  q.get(0);
  std::cout << "is there new data in q? : " << q.available() << "\n";
  q.add(objd);
  std::cout << "is there new data in q? : " << q.available() << "\n";

  q.shift(3);

  q.add(q[0]);

  q[0] = myClass(7);

  auto k = q[0];
}