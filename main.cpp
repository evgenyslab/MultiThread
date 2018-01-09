#include <iostream>
#include <vector>
#include <thread>


class worker{
public:
    void operator()(int);
};

class worker_a : public worker{
public:
    worker_a(){

    };
    ~worker_a()=default;
    void operator()(int j)const{
        std::cout << "worker_a\n";
    };
};

class worker_b : public worker{
public:
    worker_b(){

    };
    ~worker_b()=default;
    void operator()(int j)const{
        std::cout << "worker_b\n";
    };
};

class test{
    test(){

    };
public:
    void operator()(int j)const{
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
        t.emplace_back(std::thread(std::ref(in),0));
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

    worker_a a,c;
    worker_b b;
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