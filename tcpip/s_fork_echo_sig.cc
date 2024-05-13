//
// (c) 2024 S-Patriarch
// Параллельный эхо-сервер с уничтожением зомби процессов.
//
#include "tcpip.hh"
//------------------------------------------------------------------------------
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
//------------------------------------------------------------------------------
using SA = struct sockaddr;
//------------------------------------------------------------------------------
static std::uint64_t count {0};
//------------------------------------------------------------------------------
void sig_chld(std::int32_t signo)
   // функция, корректно обрабатывающая сигнал SIGCHLD
{
   std::int32_t stat {};
   pid_t pid {};
   // вызываем функцию waitpid (обработчик завершения дочернего процесса)
   // в цикле, получая состояние любого из дочерних процессов, которые 
   // завершились
   // WNOHANG - параметр, указывающий функции waitpid, что не нужно
   // блокироваться, если существует выполняемые дочерние процессы,
   // которые еще не завершились
   while ((pid = waitpid(-1,&stat,WNOHANG))>0) {
      std::cout << "child " << pid << " terminated\n";
   }
}
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

      tcp.tcp_signal(SIGCHLD,sig_chld);

      std::cout << "The server is running...\n";

      char buff[pl::mr::MAXLINE];
      for (;;) {
         std::int32_t connfd {};
         socklen_t len = sizeof(caddr);
         if ((connfd = accept(listenfd,(SA*)&caddr,&len))<0) {
            if (errno==EINTR) continue; 
            else {
               char errmsg[pl::mr::MAXLINE];
               strcpy(errmsg,"E: Accept error - ");
               char* s = std::strerror(errno);
               throw pl::Exception(strcat(errmsg,s));
            }
         }
         std::cout << '[' << ++count << "] connection from " 
                   << inet_ntop(AF_INET,&caddr.sin_addr,buff,sizeof(buff)) 
                   << '\n';

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

