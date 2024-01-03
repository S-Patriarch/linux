/*
   (c) 2024 S-Patriarch
   Пример защиты вывода информации в терминал при многопоточном режиме.
*/
#include <iostream>
#include <thread>
#include <mutex>
//------------------------------------------------------------------------------
// Мьютекс вывода в терминал.
std::mutex mtx_lock_cout;
//------------------------------------------------------------------------------
// Функция потока.
//
void lock_output(const std::string& str_)
{
   std::lock_guard<std::mutex> raii{mtx_lock_cout};
   std::cout
      <<str_
      <<'\n';
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
   std::cout
      <<"Количество ядер у процессора: "
      <<std::thread::hardware_concurrency()
      <<'\n';
   std::cout
      <<"Поток 0 : id "
      <<std::this_thread::get_id()
      <<'\n';
     
   std::thread t1(lock_output, "Строка потока 1");
   std::thread t2(lock_output, "Строка потока 2");
   std::thread t3(lock_output, "Строка потока 3");

   t1.join();
   t2.join();
   t3.join();

   return 0;
}

