//
// (c) 2024 S-Patriarch
//
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
//------------------------------------------------------------------------------
bool thread_func()
{
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return true;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
  std::future<bool> F{async(std::launch::async,thread_func)};
  if(F.valid())
    std::cout<<"future : valid"<<"\n";
  else
    std::cout<<"future : invalid"<<"\n";
  std::cout<<"F.wait()\n";
  F.wait();
  if(F.valid())
    std::cout<<"future : valid"<<"\n";
  else
    std::cout<<"future : invalid"<<"\n";
  return 0;
}

