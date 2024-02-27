//
// (c) 2024 S-Patriarch
//
#ifndef T_POOL_HH
#define T_POOL_HH

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

// тип указатель на функцию, которая является эталоном для функций задач
typedef void (*FuncType)(int,int);
//------------------------------------------------------------------------------
class ThreadPool {
   // класс, хронящий ветор потоков
   // гвоздь программы - это вектор _threads, который содержит массив потоков
   // далее по важности - это очередь _task_queue, которая представляет из себя
   // последовательность объектов std::function<void()>, тех самых задач,
   // которые будут выполнены в потоке
private:
   std::vector<std::thread>          _threads;      // коллекция потоков
   std::queue<std::function<void()>> _task_queue;   // очередь задач
   std::mutex                        _locker;       // поддержка синхронизации очереди
   std::condition_variable           _event_holder; // для синхронизации потоков
   volatile bool                     _work;         // флаг для остановки потоков
public:
   void start();                     // запуск пула потоков
   void stop();                      // остановка пула потоков
   void push_task(FuncType,int,int); // проброс задач в пул потоков
   void t_func();                    // функция входа для потока
};
//------------------------------------------------------------------------------
class RequestHandler {
   // класс, принимающий запрос и пробрасывающий его на обработку в пул потоков
   // можно было бы не делать такую обертку над пулом потоков, создавая
   // ThreadPool напрямую и вызывая у него pusk_task() для проброса
   // функций-задач на выполнение
   // но обячно программы строят таким образом, что есть какой-то 
   // класс-посредник, который принимает запросы по сети и формирует задачу на
   // выполнение, пробрасывая ее в свой внутренний пул
   // именно в этом классе хранится пул потоков
private:
   ThreadPool _tpool; // пул потоков
public:
   RequestHandler();
   ~RequestHandler();
   void push_request(FuncType,int,int); // отправка запроса на выполнение
};
#endif // T_POOL_HH
