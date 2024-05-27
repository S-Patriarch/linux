//
// (c) 2024 S-Patriarch
// Эхо-клиент с использованием потоков.
//
#include "tcpip.hh"
//------------------------------------------------------------------------------
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
//------------------------------------------------------------------------------
using SA = struct sockaddr;
//------------------------------------------------------------------------------
pl::TCPip tcp;
static std::int32_t sockfd;
//------------------------------------------------------------------------------
void* copyto(void* arg)
   // функция потока
   // отвечает за ввод текста и отправку серверу введенного текста
{
   char sendline[pl::mr::MAXLINE];
   std::memset(&sendline[0],0,sizeof(sendline));
   while (tcp.tcp_fgets(sendline,pl::mr::MAXLINE,stdin)!=NULL)  
      tcp.tcp_writen(sockfd,sendline,std::strlen(sendline));
   tcp.tcp_shutdown(sockfd,SHUT_WR);
   return NULL;
}
////////////////////////////////////////////////////////////////////////////////
std::int32_t main(int argc, char** argv)
{
   std::vector<std::string> args(argv,argv+argc);
   if (args.size()!=2) std::cerr << "W: usage: a.out <IPaddress>\n";
   else {
      try {
         struct sockaddr_in addr;

         sockfd = tcp.tcp_socket(AF_INET,SOCK_STREAM,0);

         std::memset(&addr,0,sizeof(addr));
         addr.sin_family = AF_INET;
         addr.sin_port = htons(pl::mr::SERV_PORT);
         std::string s = args.at(1);
         if (inet_pton(AF_INET,s.c_str(),&addr.sin_addr)<=0) {
            std::cout << "E: inet_pton error for " << s << '\n';
            std::exit(EXIT_SUCCESS);
         }

         tcp.tcp_connect(sockfd,(SA*)&addr,sizeof(addr));
         std::cout << "W: connection to server...\n";

         char recvline[pl::mr::MAXLINE];
         std::memset(&recvline[0],0,sizeof(recvline));
         pthread_t tid;

         // создаем поток для ввода данных и их отправки серверу
         tcp.tcp_pthread_create(&tid,NULL,::copyto,NULL);

         // основной поток занимается чтением поступающих данных
         // от сервера и выводом их в терминал
         while (tcp.tcp_readline(sockfd,recvline,pl::mr::MAXLINE)>0) {
            tcp.tcp_fputs(recvline,stdout);
            std::memset(&recvline[0],0,sizeof(recvline));
         }
      }
      catch (std::exception& ex) {
         std::cout << ex.what() << '\n';
      }
   }
   std::exit(EXIT_SUCCESS);
}
