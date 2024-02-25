//
// (c) 2024 S-Patriarch
//
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
////////////////////////////////////////////////////////////////////////////////
int main()
{
  // создаем фьючерс
  std::future<void> F{async(std::launch::async,[]() 
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"thread work"<<"\n";
  })};
  // проверяем готовность фьючерса
  std::cout
    <<"before wait future ready: "
    <<(F.wait_for(std::chrono::seconds(0))==std::future_status::ready)
    <<"\n";
  std::cout
    <<"before wait future valid: "
    <<F.valid()
    <<"\n";
  // ждем завершение потока
  F.wait();
  // проверяем готовность и валидность фьючерса после метода wait()
  std::cout
    <<"before wait future ready: "
    <<(F.wait_for(std::chrono::seconds(0))==std::future_status::ready)
    <<"\n";
  std::cout
    <<"before wait future valid: "
    <<F.valid()
    <<"\n";
  F.get();
  // проверяем валидность фьючерса после метода get()
  std::cout
    <<"after get, future valid: "
    <<F.valid()
    <<"\n";
  return 0;
}

