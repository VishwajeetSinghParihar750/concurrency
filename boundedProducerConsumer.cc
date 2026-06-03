#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <semaphore>

const int producers = 1;
const int consumers = 1;

const long long maxLimit = 100;

auto q = std::queue<int>();

auto canPop = std::counting_semaphore<maxLimit>(0);
auto canPush = std::counting_semaphore<maxLimit>(maxLimit);

auto mutex = std::counting_semaphore<1>(1);

void consumer()
{
    while (true)
    {

        std::cout << "consumer 1" << std::endl;
        canPop.acquire();

        std::cout << "consumer 2" << std::endl;
        mutex.acquire();

        std::cout << "consumer 3" << std::endl;
        auto f = q.front();
        q.pop();
        std::cout << q.size() << " popped : " << f << std::endl;

        std::cout << "consumer 4" << std::endl;
        mutex.release();

        std::cout << "consumer 5" << std::endl;
        canPush.release();
        std::cout << "consumer 6" << std::endl;
    }
}
void producer()
{

    while (true)
    {

        std::cout << "producer 1" << std::endl;
        canPush.acquire();

        std::cout << "producer 2" << std::endl;
        mutex.acquire();

        std::cout << "producer 3" << std::endl;
        auto f = int(rand() % 2394092);
        q.push(f);
        std::cout << q.size() << " pushed : " << f << std::endl;
        std::cout << "producer 4" << std::endl;

        mutex.release();

        std::cout << "producer 5" << std::endl;
        canPop.release();
        std::cout << "producer 6" << std::endl;
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