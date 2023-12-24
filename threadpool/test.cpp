
#include <iostream>
#include "threadpool.h"

void test()
{
    ThreadPool pool;
    pool.start(2);

    std::thread td1([&pool]
                    {
        for (int i =0; i< 10; i++){
            auto id = std::this_thread::get_id();
            pool.addTask([id]{
                std::cout<<"Thread ID of thread 1 in sync queue: "<<id<<std::endl;
            });
        } });

    std::thread td2([&pool]
                    {
        for (int i=0; i< 10; i++){
            auto id = std::this_thread::get_id();
            pool.addTask([id]{
                std::cout<<"Thread ID of thread 2 in sync queue: "<<id<<std::endl;
            });
        } });

    std::this_thread::sleep_for(std::chrono::seconds(2));
    getchar();
    pool.stop();
    td1.join();
    td2.join();
}

int main()
{
    test();

    return 0;
}
