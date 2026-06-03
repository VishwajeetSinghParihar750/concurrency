#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <semaphore>

const int producers = 1;
const int consumers = 1;

auto q = std::queue<int>();

auto available = std::counting_semaphore<(long long)1e9>(0);
auto mutex = std::counting_semaphore<1>(1);

void consumer()
{
    while (true)
    {

        available.acquire();

        mutex.acquire();

        auto f = q.front();
        q.pop();
        std::cout << q.size() << " popped : " << f << "\n";

        mutex.release();
    }
}
void producer()
{

    while (true)
    {

        mutex.acquire();

        auto f = int(rand() * 2035);
        q.push(f);
        std::cout << q.size() << " pushed : " << f << "\n";

        mutex.release();

        available.release();
    }
}

int main()
{

    std::vector<std::thread> vec;

    for (auto i = 0; i < producers; i++)
        vec.emplace_back(std::thread(producer));
    for (auto i = 0; i < consumers; i++)
        vec.emplace_back(std::thread(consumer));

    for (auto &&t : vec)
        t.join();
}