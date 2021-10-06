/*Пять безмолвных философов сидят вокруг круглого стола, перед каждым философом стоит тарелка спагетти. Вилки лежат на столе между каждой парой ближайших философов.
 
 Каждый философ может либо есть, либо размышлять. Приём пищи не ограничен количеством оставшихся спагетти — подразумевается бесконечный запас. Тем не менее, философ может есть только тогда, когда держит две вилки — взятую справа и слева (альтернативная формулировка проблемы подразумевает миски с рисом и палочки для еды вместо тарелок со спагетти и вилок).

 Каждый философ может взять ближайшую вилку (если она доступна) или положить — если он уже держит её. Взятие каждой вилки и возвращение её на стол являются раздельными действиями, которые должны выполняться одно за другим.

 Вопрос задачи заключается в том, чтобы разработать модель поведения (параллельный алгоритм), при котором ни один из философов не будет голодать, то есть будет вечно чередовать приём пищи и размышления.*/

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <semaphore>
#include <chrono>
//#include <iostream>
//#include <iostream>

using namespace std;

int numOfPhilosopher = 0;

#define N 5
#define LEFTFORK (numOfPhilosopher-1)%N
#define RIGHTFORK (numOfPhilosopher+1)%N
#define THINKING 1
#define EATING 1
#define HUNGRY 0

int status[N];
mutex mtx;
binary_semaphore sem[N];


class PHILOSOPHER {
public:
    void process() {
        while(1) {
            Thinking();
            TakeFork();
            Eating();
            PutFork();
        }
    };
    void Eating();
    void Thinking();
    void CheckForkIsFree(){
        if (status[numOfPhilosopher] == HUNGRY && status[LEFTFORK] != EATING && status[RIGHTFORK] != EATING) {
            status[numOfPhilosopher] = EATING;
            sem[numOfPhilosopher].max();
        }
           
    };
    void TakeFork() {
        mtx.lock();
        status[numOfPhilosopher] = HUNGRY;
        //test(I)
        mtx.unlock();
        sem[numOfPhilosopher].max();
    };
    void PutFork() {
        mtx.lock();
        status[numOfPhilosopher] = THINKING;
        //test(left) ;test(right)
        mtx.unlock();
    };
};
using namespace std;
int main() {
    PHILOSOPHER philosopher;
    PHILOSOPHER arrOfPhilosophers[N];
//    int status[N];
//    mutex mut;
//    binary_semaphore sem[N];
    return 0;
}
