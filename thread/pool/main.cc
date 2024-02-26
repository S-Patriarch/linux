//
// (c) 2024 S-Patriarch
//
#include "include/t_pool.hh"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
//------------------------------------------------------------------------------
void task_func(int id, int delay)
{
   // имитируем время выполнения задачи
   std::this_thread::sleep_for(std::chrono::seconds{delay});
   // выводим информацию о завершении
   std::cout << "task " << id 
             << " made by thread_id " << std::this_thread::get_id() 
             << '\n';
}
////////////////////////////////////////////////////////////////////////////////
int main()
   // создаем объект класса RequestHandler
   // затем пробрасываем в него 20 запросов
   // в качестве задачи передается функция task_func, которая полностью
   // соответствует эталону FuncType
{
   RequestHandler rh;
   std::srand(std::time(0));
   for (unsigned int i=1; i!=21; i++) 
      rh.push_request(task_func,i,1+std::rand()%3);
   return 0;
}
