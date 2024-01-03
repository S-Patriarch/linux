/*
   (c) S-Patriarch, 2023
   Пример кода, который имитирует join для отвязанного (detached) потока.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
//------------------------------------------------------------------------------
std::condition_variable g_Condition;
std::mutex g_Mutex;
////////////////////////////////////////////////////////////////////////////////
int main()
{
   auto call=[]()
   {
      std::unique_lock<std::mutex> lock{g_Mutex};
      std::this_thread::sleep_for(std::chrono::seconds(5));
      std::notify_all_at_thread_exit(g_Condition,std::move(lock));
   };
   std::thread callThread{call};
   callThread.detach();
   std::unique_lock<std::mutex> lock{g_Mutex};
   std::cout<<"Я заснул...\n";
   g_Condition.wait(lock);
   std::cout<<"OK\nЯ проснулся.\n";
   return 0;
}

