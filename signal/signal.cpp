// signal.cpp -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Обработка полученного сигнала.

#include <iostream>
#include <csignal>
#include <cstdlib>

//////////////////////////////////////////////////////////////////////
//
namespace
  {
    volatile std::sig_atomic_t gSignalStatus;
  }

//////////////////////////////////////////////////////////////////////
//
void signal_handler (int _signal);

//////////////////////////////////////////////////////////////////////
// Точка входа.
//
int
main ()
  {
    // установка обработчика сигнала
    std::signal (SIGINT, signal_handler);

    std::cout << "Для обработки сигнала нажмите Ctrl+C\n"
              << "Спим..."
              << std::endl;

    while (true);

    return 0;
  }

//--------------------------------------------------------------------
// Реализация обработанного сигнала.
//
void
signal_handler (int _signal)
  {
    gSignalStatus = _signal;

    std::cout << "\nПодъем! Труба зовет..."
              << std::endl;

    exit (1);
  }
