//
// (c) 2024 S-Patriarch
// Типичный параллельный сервер.
// Сервер следует запускать под root, чтобы обрабатывался 13 порт.
//
#include "tcpip.hh"
//------------------------------------------------------------------------------
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <thread>
//------------------------------------------------------------------------------
#define PORT   13 // сервер времени и даты
//------------------------------------------------------------------------------
using SA = struct sockaddr;
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   try {
      pl::TCPip            tcp;
      struct sockaddr_in   saddr;
      struct sockaddr_in   caddr;
   
      std::int32_t listenfd = tcp.tcp_socket(AF_INET,SOCK_STREAM,0);

      std::memset(&saddr,0,sizeof(saddr));
      saddr.sin_family = AF_INET;
      saddr.sin_port = htons(PORT);
      saddr.sin_addr.s_addr = htonl(INADDR_ANY);

      tcp.tcp_bind(listenfd,(SA*)&saddr,sizeof(saddr));
      tcp.tcp_listen(listenfd,pl::mr::LISTENQ);

      std::cout << "The server is running...\n";
 
      char  buff[pl::mr::MAXLINE];
      for (;;) {
         socklen_t   len = sizeof(caddr);
         std::int32_t connfd = tcp.tcp_accept(listenfd,(SA*)&caddr,&len);
         pid_t pid {};
         if ((pid = tcp.tcp_fork())==0) {
            tcp.tcp_close(listenfd); // дочерний процесс закрывает
                                     // прослушиваемый сокет
            std::cout << "connection from " 
                      << inet_ntop(AF_INET,&caddr.sin_addr,buff,sizeof(buff)) 
                      << ", port " 
                      << ntohs(caddr.sin_port)
                      << '\n';
            // иметация выполнения большой работы
            std::this_thread::sleep_for(std::chrono::seconds(20));
            std::time_t ticks = std::time(NULL);
            std::string st = (std::string)std::ctime(&ticks);
            tcp.tcp_write(connfd,st.c_str(),st.size());
            tcp.tcp_close(connfd); // с этим клиентом закончено
            return 0; // дочерний процесс завершен
         }
         tcp.tcp_close(connfd); // родительский процесс закрывает
                                // присоединенный сокет
      }
   }
   catch (std::exception& ex) {
      std::cout << ex.what() << '\n';
   }
   return 0;
}

