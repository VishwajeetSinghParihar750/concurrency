#include <vector>
#include <thread>
#include <iostream>
#include <semaphore>

const int n = 3;
int count = n;

auto followerArrived = std::counting_semaphore<1>(0);
auto leaderArrived = std::counting_semaphore<1>(0);
auto mutex = std::counting_semaphore<1>(1);
auto mutex2 = std::counting_semaphore<1>(1);

void follower()
{

    mutex.acquire();

    followerArrived.release();
    leaderArrived.acquire();

    // dance

    mutex.release();
}
void leader()
{
    mutex2.acquire();

    leaderArrived.release();
    followerArrived.acquire();

    // dance

    mutex2.release();
}

int main()
{

    std::vector<std::thread> vec;

    for (auto i = 0; i < count; i++)
        vec.emplace_back(std::thread(follower));
    for (auto i = 0; i < count; i++)
        vec.emplace_back(std::thread(leader));

    for (auto &&t : vec)
        t.join();

    std::cout << count << std::endl;
}