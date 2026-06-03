#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <semaphore>

const int readersCount = 1000;
const int writersCount = 10;
int readers = 0;
const int maxReaders = 100000;

auto q = std::queue<int>();

auto writerMutex = std::counting_semaphore<1>(1);
auto noReaderLeft = std::counting_semaphore<1>(1);
auto readerMutex = std::counting_semaphore<1>(1);

void reader()
{
    writerMutex.acquire();
    readerMutex.acquire();

    if (readers == 0)
        noReaderLeft.acquire();

    readers++;

    readerMutex.release();
    writerMutex.release();

    // critical

    readerMutex.acquire();
    readers--;
    if (readers == 0)
        noReaderLeft.release();

    readerMutex.release();
}
void writer()
{
    writerMutex.acquire();

    noReaderLeft.acquire();
    noReaderLeft.release();

    // critical

    writerMutex.release();
}

int main()
{

    std::vector<std::thread> vec;

    for (auto i = 0; i < readersCount; i++)
        vec.emplace_back(std::thread(reader));
    for (auto i = 0; i < writersCount; i++)
        vec.emplace_back(std::thread(writer));

    for (auto &&t : vec)
        t.join();
}