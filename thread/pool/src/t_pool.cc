//
// (c) 2024 S-Patriarch
//
#include "../include/t_pool.hh"
//------------------------------------------------------------------------------
void ThreadPool::start()
   // запуск пула - инициализирует внутренние потоки
   // в этом методе взводится флаг _work в true, после чего создается 
   // четыре потока
   // в качестве функции входа передается метод t_func
   // все потоки складываются в _threads
{
   _work = true;
   for (unsigned int i=0; i!=4; i++)
      _threads.push_back(std::thread(&ThreadPool::t_func,this));
}
//------------------------------------------------------------------------------
void ThreadPool::stop()
   // остановка пула - устанавливает флаг для завершения работы потоков
   // в этом методе снимается флаг _work (делаем его false)
   // затем вызывается оповещение для всех потоков, чтобы они могли выйти из
   // режима ожидания и завершиться, если очередь задач пуста
   // после этих действий дожидаемся завершения  всех потоков
{
   _work = false;
   _event_holder.notify_all();
   for (auto& t : _threads)
      t.join();
}
//------------------------------------------------------------------------------
void ThreadPool::push_task(FuncType f,int id,int arg)
   // проброс задач - метод, который добавляет новый std::function в
   // очередь задач
   // первый параметр данного метода является указателем на функцию
   // благодаря ему можно передать в этот метод любую функцию, соответствующую
   // эталону FuncType, который определяется в заголовочном файле
{
   std::lock_guard<std::mutex> l(_locker);
   std::function<void()> new_task([=]() {f(id,arg);});
   _task_queue.push(new_task);
   _event_holder.notify_one(); // оповещаем случайный поток о новой задаче
}
//------------------------------------------------------------------------------
void ThreadPool::t_func()
   // метод, который является функцией выполнения для потоков
   // организован бесконечный цикл, который находится в режиме ожидания, пока
   // не придет оповещение
   // как только поступает новая задача на выполнение, поток просыпается,
   // забирает ее оттуда и выполняет задачу, вызвав task_to_do()
   // task_to_do - это тот самый функтор, который добавляется в очередь в
   // методе push_task()
{
   for (;;) {
      // обработка очередной задачи
      std::function<void()> task_to_do;
      {
         std::unique_lock<std::mutex> l(_locker);
         if (_task_queue.empty() && !_work)
            // очередь пуста и взведен флаг - выходим
            return;
         if (_task_queue.empty())
            // очередь пуста - ждем события
            _event_holder.wait(l,[&]() {return !_task_queue.empty() || !_work;});
         if (!_task_queue.empty()) {
            // нужно снова проверить на пустоту, ведь могли проснуться по !_work
            task_to_do = _task_queue.front();
            _task_queue.pop();
         }
      }
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
