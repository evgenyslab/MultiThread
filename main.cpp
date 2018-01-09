#include <iostream>
#include <vector>
#include <thread>


class worker{
public:
    void operator()();
};

class worker_a : public worker{
public:
    worker_a(){

    };
    ~worker_a()=default;
    void operator()()const{
        std::cout << "worker_a finished\n";
    };
};

class worker_b : public worker{
public:
    worker_b(){

    };
    ~worker_b()=default;
    void operator()()const{
        std::cout << "worker_b finished\n";
    };
};

class worker_c {
public:
  worker_c(){

  };
  ~worker_c()=default;
  void operator()()const{
    std::cout << "worker_c finished\n";
  };
};

class test{

public:
  test(){

  };
    void operator()()const{
        std::cout << "bleh\n";
    };

};

/* threaPool
 *
 * */
class threadPool{
public:
    std::vector<std::thread> t;
    template<class T>
    void add(T & in){
        t.emplace_back(std::thread(std::ref(in)));
        // may want to add max thread count and join, reset
    }

    void join(){
        for (auto& th : t) th.join();
        t.clear();
    }

};

void run(int i){
    std::cout << "Run!\n";
}


int main() {
    std::cout << "Hello, Thread!" << std::endl;

    test tobj;
    std::thread t(std::ref(tobj));
  t.join();

    worker_a a;
    worker_b b;
  worker_c c;
    threadPool p;

    p.add(a);
    p.add(b);
    p.join();

    p.add(a);
    p.add(b);
    p.add(c);
    p.add(b);
    p.add(c);
    p.add(a);
    p.add(b);
    p.join();

    return 0;
}