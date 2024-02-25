//
// (c) 2024 S-Patriarch
//
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
//------------------------------------------------------------------------------
void thread_func(std::promise<int> &P)
{
  std::cout<<"Setting result to promise: 10\n";
  // устанавливаем значение в промис, фьючерс перейдет в готовое состояние
  P.set_value(10);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout<<"Thread finished work.\n";
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
  // объявляем промис и передаем его в поток
  std::promise<int> P;
  std::thread T{thread_func,std::ref(P)};
  // получаем фьючерс из промиса
  std::future<int> F{P.get_future()};
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

