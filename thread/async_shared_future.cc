//
// (c) 2024 S-Patriarch
//
#include <iostream>
#include <future>
//------------------------------------------------------------------------------
int func_get_int()
{
  int Res;
  std::cout<<"input integer: ";
  std::cin>>Res;
  return Res;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
  std::shared_future<int> F1{async(std::launch::async,func_get_int).share()};
  std::future<int> F2{async(std::launch::async,[&F1]()
  {
    int Res{F1.get()};
    return (Res*Res);
  })};
  std::future<int> F3{async(std::launch::async,[&F1]()
  {
    int Res{F1.get()};
    return (Res/2);
  })};
  std::cout<<"F1: "<<F1.get()<<"\n";
  std::cout<<"F2: "<<F2.get()<<"\n";
  std::cout<<"F3: "<<F3.get()<<"\n";
  return 0;
}

