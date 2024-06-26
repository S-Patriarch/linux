//
// (c) 2024 S-Patriarch
// Параллельный эхо-сервер.
//
#include "tcpip.hh"
//------------------------------------------------------------------------------
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdlib>
//------------------------------------------------------------------------------
using SA = struct sockaddr;
//------------------------------------------------------------------------------
static std::uint64_t count {0};
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
      saddr.sin_port = htons(pl::mr::SERV_PORT);
      saddr.sin_addr.s_addr = htonl(INADDR_ANY);

      tcp.tcp_bind(listenfd,(SA*)&saddr,sizeof(saddr));
      tcp.tcp_listen(listenfd,pl::mr::LISTENQ);

      std::cout << "The server is running...\n";
 
      for (;;) {
         socklen_t len = sizeof(caddr);
         std::int32_t connfd = tcp.tcp_accept(listenfd,(SA*)&caddr,&len);
         std::cout << '[' << ++count << "] connect\n";

         pid_t pid {};
         if ((pid = tcp.tcp_fork())==0) {
            tcp.tcp_close(listenfd); 
            std::int32_t n {};  
            char recvline[pl::mr::MAXLINE];
            for (;;) {
               std::memset(&recvline[0],0,sizeof(recvline));
               if ((n = tcp.tcp_read(connfd,recvline,pl::mr::MAXLINE))>0)
                  tcp.tcp_write(connfd,recvline,n);
               else break;
            }
            tcp.tcp_close(connfd); 
            return 0; 
         }

         tcp.tcp_close(connfd); 
      }
   }
   catch (std::exception& ex) {
      std::cout << ex.what() << '\n';
   }
   return 0;
}

