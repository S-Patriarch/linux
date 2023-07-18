// sysinfo.cpp -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Получение информации о системе.

#include <iostream>
#include <sys/utsname.h>

//////////////////////////////////////////////////////////////////////
// Точка входа.
//
int
main ()
  {
    struct utsname sysinfo;
    uname (&sysinfo);

    std::cout << "Наименование системы : "
              << sysinfo.sysname
              << "\n"
              << "Архитектура          : "
              << sysinfo.machine
              << "\n"
              << "Наименование хоста   : "
              << sysinfo.nodename
              << "\n"
              << "Версия ядра          : "
              << sysinfo.release
              << "\n"
              << "Сборка ядра          : "
              << sysinfo.version
              << "\n"
              << "Доменное имя         : "
              << sysinfo.domainname
              << std::endl;

    return 0;
  }
