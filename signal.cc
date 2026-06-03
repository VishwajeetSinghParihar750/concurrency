#include <thread>
#include <iostream>
#include <semaphore>

auto countingSem = std::counting_semaphore<1>(0);

void threadA()
{
    std::cout << "a must run first \n";
    countingSem.release();
}

void threadB()
{

    countingSem.acquire();
    std::cout << "b must run later \n";
}

int main()
{

    auto a = std::thread(threadA);
    auto b = std::thread(threadB);

    a.join();
    b.join();
}