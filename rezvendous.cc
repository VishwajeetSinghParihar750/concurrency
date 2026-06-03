
#include <thread>
#include <iostream>
#include <semaphore>

auto bArrived = std::counting_semaphore<1>(0);
auto aArrived = std::counting_semaphore<1>(0);

void threadA()
{

    std::cout << "a1 \n";

    aArrived.release();
    bArrived.acquire();

    std::cout << "a2 \n";
}

void threadB()
{
    std::cout << "b1\n";

    bArrived.release();
    aArrived.acquire();

    std::cout << "b2\n";
}

int main()
{

    auto a = std::thread(threadA);
    auto b = std::thread(threadB);

    a.join();
    b.join();
}