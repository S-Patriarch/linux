//
// (c) 2024 S-Patriarch
//
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
//------------------------------------------------------------------------------
void thread_func(std::packaged_task<int()> &Pt)
{
  std::cout<<"in thread_func\n";
  // вызываем функцию, помещенную в упаковку
  Pt();
  // тут фьючерс перейдет в готовое состояние
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout<<"thread_func finished\n";
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
  // объявляем упаковку
  std::packaged_task<int()> Task{[]()
  {
    std::cout<<"packaged_task finished work\n";
    return 10;
  }};
  // получаем фьючерс
  std::future<int> F{Task.get_future()};
  // запускаем поток, передав в него упаковку
  std::thread T{thread_func,std::ref(Task)};
  // ждем результат
  try
  {
    std::cout<<"Future result: "<<F.get()<<"\n";
    // что-то делаем с результатом
  }
  catch(...)
  {
    std::cout<<"E: Some error in thread.\n";
  }
  T.join();
  return 0;
}

