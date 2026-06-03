#include <vector>
#include <thread>
#include <iostream>
#include <semaphore>

const int n = 3;
int count = n;

auto bar1 = std::counting_semaphore<n>(0);
auto bar2 = std::counting_semaphore<n>(0);
auto mutex = std::counting_semaphore<1>(1);

void barrier()
{
    mutex.acquire();
    count = count - 1;

    if (count == 0)
        bar1.release(n);
    mutex.release();

    bar1.acquire();

    // critical section

    mutex.acquire();
    count = count + 1;

    if (count == n)
        bar2.release(n);

    mutex.release();

    bar2.acquire();
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