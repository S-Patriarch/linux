//
// (c) 2024 S-Patriarch
//
#include "../include/t_pool.hh"
//------------------------------------------------------------------------------
void ThreadPool::start()
{
   for (int i=0; i!=_thread_count; i++)
      _threads.emplace_back(&ThreadPool::t_func,this,i);
}
//------------------------------------------------------------------------------
void ThreadPool::stop()
{
   for (int i=0; i!=_thread_count; i++) {
      // кладем задачу-пустышку в каждую очередь
      // для завершения потока
      std::function<void()> empty_task;
      _thread_queues[i].push(empty_task);
   }
   for (auto& t : _threads)
      t.join();
}
//------------------------------------------------------------------------------
void ThreadPool::push_task(FuncType f,int id,int arg)
{
   // вычисляем индекс очереди, куда положим задачу
   int queue_to_push = _index++%_thread_count;
   // формируем функтор
   std::function<void()> task = [=]() {f(id,arg);};
   // кладем в очередь
   _thread_queues[queue_to_push].push(task);
}
//------------------------------------------------------------------------------
void ThreadPool::t_func(int qindex)
{
   for (;;) {
      // обработка очередной задачи
      std::function<void()> task_to_do;
      bool res;
      int i {0};
      for (; i!=_thread_count; i++) {
         // попытка быстро забрать задачу из любой очереди,
         // начиная со своей
         res = _thread_queues[(qindex+i)%_thread_count].fast_pop(task_to_do);
         if (res) break;
      }
      if (!res) {
         // вызываем блокирующее получение очереди
         _thread_queues[qindex].pop(task_to_do);
      }
      else if (!task_to_do) {
         // чтобы не допустить зависания потока
         // кладем обратно задачу-пустышку
         _thread_queues[(qindex+i)%_thread_count].push(task_to_do);
      }
      if (!task_to_do) return;
      task_to_do(); // выполняем задачу, вызвав функтор
   }
}
//------------------------------------------------------------------------------
RequestHandler::RequestHandler() 
   // запускает пул
{_tpool.start();}
//------------------------------------------------------------------------------
RequestHandler::~RequestHandler() 
   // останавливает пул
{_tpool.stop();}
//------------------------------------------------------------------------------
void RequestHandler::push_request(FuncType f,int id,int arg)
   // бросает функцию-задачу в пул
{_tpool.push_task(f,id,arg);}
