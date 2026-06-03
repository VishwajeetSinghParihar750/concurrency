
#include <thread>
#include <iostream>
#include <semaphore>

auto mutex = std::counting_semaphore<1>(1);
int count = 0;

void common()
{

    for (auto i = 0; i < 10000; i++)
    {

        mutex.acquire();
        count = count + 1;
        mutex.release();
    }
}

int main()
{

    auto a = std::thread(common);
    auto b = std::thread(common);

    a.join();
    b.join();

    std::cout << count << std::endl;
}