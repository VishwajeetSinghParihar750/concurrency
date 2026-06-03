#include <vector>
#include <thread>
#include <iostream>
#include <semaphore>

auto mutex = std::counting_semaphore<1>(1);
auto bar = std::counting_semaphore<3>(0);
int count = 3;

void barrier()
{

    mutex.acquire();
    count--;

    if (count == 0)
    {
        mutex.release();
    }
    else
    {
        mutex.release();
        bar.acquire();
    }

    bar.release();
}

void common()
{
    barrier();
    // ciritccal section
}

int main()
{

    std::vector<std::thread> vec;

    for (auto i = 0; i < count; i++)
        vec.emplace_back(std::thread(common));

    for (auto &&t : vec)
        t.join();

    std::cout << count << std::endl;
}