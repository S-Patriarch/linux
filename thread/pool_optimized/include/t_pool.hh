//
// (c) 2024 S-Patriarch
//
#ifndef T_POOL_HH
#define T_POOL_HH

#include <algorithm>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

// тип указатель на функцию, которая является эталоном для функций задач
typedef void (*FuncType)(int,int);
//------------------------------------------------------------------------------
template<class T>
class BlockedQueue {
   // класс, который является потокобезопасной очередью
private:
   std::mutex               _locker;     // поддержка синхронизации очереди
   std::queue<T>            _task_queue; // очередь задач
   std::condition_variable  _notifier;   // уведомитель
public:
   void push(T& item)
      // потокобезопасный push
   {
      std::lock_guard<std::mutex> l(_locker);
      _task_queue.push(item);
      // делаем оповещение, чтобы поток, вызвавший pop проснулся и
      // забрал из очереди задачу
      _notifier.notify_one();
   }
   void pop(T& item)
      // блокирующий метод получения элемента из очереди 
   {
      std::unique_lock<std::mutex> l(_locker);
      if ( _task_queue.empty())
         // ждем, пока вызовут push
         _notifier.wait(l,[this]() {return !_task_queue.empty();});
      item = _task_queue.front();
      _task_queue.pop();
   }
   bool fast_pop(T& item)
      // неблокирующий метод получения элемента из очереди
      // возвращает false, если очередь пуста
   {
      std::lock_guard<std::mutex> l(_locker);
      if (_task_queue.empty()) return false;
      // забираем элемент
      item = _task_queue.front();
      _task_queue.pop();
      return true;
   }
};
//------------------------------------------------------------------------------
class ThreadPool {
private:
   int _thread_count; // количество потоков
   std::vector<std::thread> _threads; // потоки
   // очереди задач для потоков
   std::vector<BlockedQueue<std::function<void()>>> _thread_queues;
   int _index;        // для равномерного распределения задач
public:
   ThreadPool() :
      _thread_count(std::thread::hardware_concurrency()!=0 ? 
      std::thread::hardware_concurrency() : 4),
      _thread_queues(_thread_count)
   {}
   void start();                     // запуск пула потоков
   void stop();                      // остановка пула потоков
   void push_task(FuncType,int,int); // проброс задач в пул потоков
   void t_func(int);                 // функция входа для потока
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
