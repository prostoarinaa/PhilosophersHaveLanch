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
#include <thread>

using namespace std;
//vector<int> Prioritet = {5,5,5,5,5,5};

#define N 5
int numOfPhilosopher = 0;
int status[N];


//int status[N];
mutex mtx, mtx1, mtx2;
 counting_semaphore sem;
//vector<counting_semaphore<5>> vecOfSem[5];

class PHILOSOPHER {
    
public:
    int numOfPhil = 0;
    PHILOSOPHER (const int& numOfPhilo) {
       // process();
        numOfPhil = numOfPhilo;
    };
    void process() {
        while(1) {
            
            Thinking();
            mtx2.lock();
            TakeFork();
            Eating();
            PutFork();
           // Prioritet[numOfPhil]--;
            this_thread::sleep_for(chrono::milliseconds(10));
            mtx2.unlock();
        }
    };

    void Eating() {
        mtx1.lock();
        cout << "Philosopher N " << numOfPhil << " " << "is eating"<< endl;
        mtx1.unlock();
    };
    void Thinking() {
        mtx1.lock();
        cout << "Philosopher N " << numOfPhil << " " << "is thinking"<< endl;
        mtx1.unlock();
    };
    void CheckForkIsFree(int numOfPhil){
        if (status[numOfPhil] == 0 && status[(numOfPhil-1)%N] != 1 && status[(numOfPhil+1)%N] != 1) {
            status[numOfPhil] = 1;
            
       // mtx2.lock();
            sem.release();
        }
           
    };
    void TakeFork() {
        mtx.lock();
        status[numOfPhil] = 0;
        CheckForkIsFree(numOfPhil);
        mtx.unlock();
       // mtx2.unlock()   ;
    };
    void PutFork() {
        mtx.lock();
        status[numOfPhil] = 0;
        CheckForkIsFree((numOfPhil-1)%N) ;
        CheckForkIsFree((numOfPhil+1)%N);
        mtx.unlock();
        sem.acquire();
    };
};

int main() {
    thread::id id;
    
    vector <PHILOSOPHER> vecOfPhilosophers = {};
    for (int i =0;i<5;i++){
        numOfPhilosopher = i;
        vecOfPhilosophers.push_back(PHILOSOPHER(numOfPhilosopher));
    }
    for (int i =0;i<5;i++){
       // numOfPhilosopher = i;
        cout << vecOfPhilosophers[i].numOfPhil<< endl;
       // vecOfPhilosophers[i].process();
    }
        thread thread_array[5];
    thread_array[0] = thread([&](){
        vecOfPhilosophers[0].process();
    });
    thread_array[1] = thread([&](){
        vecOfPhilosophers[1].process();
    });
    thread_array[2] = thread([&](){
        vecOfPhilosophers[2].process();
    });
    thread_array[3] = thread([&](){
        vecOfPhilosophers[3].process();
    });
    thread_array[4] = thread([&](){
        vecOfPhilosophers[4].process();
    });

        for (int i = 0; i < 5; i++) {
                   thread_array[i].join();
        }

    return 0;
}
