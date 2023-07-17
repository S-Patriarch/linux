// upd.cpp -*- C++ -*-

/*
 * Copyright (c) 2023 S-Patriarch
 * Обновление системы Linux семейства Debian.
 */

#include <iostream>
#include <cstdlib>
#include <string>
//////////////////////////////////////////////////////////////////////
auto
main( int argc, char *argv[] ) -> int
  {
  if( argc != 2 )
    {
    std::cout 
      << "upd 2.1\n"
      << "Использование: upd [параметр]\n\n"
      << "upd - помошник проведения обновления и очистки системы "
      << "семейства Debian\n"
      << "для людей с очень маленьким опытом работы в ОС Linux.\n\n"
      << "Основные параметры:\n"
      << "  -f  обновление системы до последней версии с последующей "
      << "очисткой\n"
      << "  -u  обновление системы до последней версии\n"
      << "  -c  очистка системы" 
      << std::endl;

    return 0;
    }

  std::string  _argString{ *( argv + 1 ) };

  if( _argString == "-f" )
    {
    //обновление системы до последней версии
    std::system( "sudo apt update && sudo apt full-upgrade -y" );

    // удаление неиспользуемых программ и ядер
    std::system( "sudo apt autoremove -y" );

    // удаление старых скаченных файлов архивов
    std::system( "sudo apt autoclean -y" );

    // удаление скаченных файлов архивов
    std::system( "sudo apt clean -y" );
    }
  else if( _argString == "-u" )
    {
    // обновление системы до последней версии
    std::system( "sudo apt update && sudo apt full-upgrade -y" );
    }
  else if( _argString == "-c" )
    {
    // удаление неиспользуемых программ и ядер
    std::system( "sudo apt autoremove -y" );

    // удаление старых скаченных файлов архивов
    std::system( "sudo apt autoclean -y" );

    // удаление скаченных файлов архивов
    std::system( "sudo apt clean -y" );
    }
  else
    {
    std::cout 
      << "E: Параметр командной строки [" 
      << _argString 
      << "] непонятен." 
      << std::endl;
    }

  return 0;
  }
