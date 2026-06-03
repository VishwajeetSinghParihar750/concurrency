#include <vector>
#include <thread>
#include <iostream>
#include <semaphore>

const int n = 3;
int count = n;

auto bar1 = std::counting_semaphore<n>(0);
auto bar2 = std::counting_semaphore<n>(1);
auto mutex = std::counting_semaphore<1>(1);

void barrier()
{
    mutex.acquire();
    count = count - 1;

    if (count == 0)
    {
        bar2.acquire();
        bar1.release();
    }
    mutex.release();

    bar1.acquire();
    bar1.release();

    // critical section

    mutex.acquire();
    count = count + 1;
    if (count == n)
    {
        bar1.acquire();
        bar2.release();
    }

    mutex.release();

    bar2.acquire();
    bar2.release();
}

int main()
{

    std::vector<std::thread> vec;

    for (auto i = 0; i < count; i++)
        vec.emplace_back(std::thread(barrier));

    for (auto &&t : vec)
        t.join();

    std::cout << count << std::endl;
}