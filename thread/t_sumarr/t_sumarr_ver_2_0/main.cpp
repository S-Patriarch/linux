/*++

    Copyright (c) S-Patriarch, 2023
    Подсчет суммы элементов массива несколькими потоками.
    Версия 2.0

--*/

#include "include/t_sumarr.h"

#include <iostream>
#include <thread>
#include <chrono>

//////////////////////////////////////////////////////////////////////
int main()
{
    const std::int32_t sizeArray_ {10000000};
    const std::int32_t nThread_ {5};

    SumArray sum(sizeArray_, nThread_);

    // подсчет суммы в используемых потоках
    auto t_start_ = std::chrono::system_clock::now();
    std::int32_t s_ = sum.calculate_using_thread();
    auto t_end_ = std::chrono::system_clock::now();
    long diff_ = std::chrono::duration_cast<std::chrono::milliseconds>(t_end_ - t_start_).count();
    std::cout << "SUM (using threads: "
              << nThread_
              << ") is "
              << s_
              << " time (ms): "
              << diff_
              << "\n";

    // подсчет суммы в основном потоке
    t_start_ = std::chrono::system_clock::now();
    s_ = sum.calculate_without_thread();
    t_end_ = std::chrono::system_clock::now();
    diff_ = std::chrono::duration_cast<std::chrono::milliseconds>(t_end_ - t_start_).count();
    std::cout << "SUM (main thread) is "
              << s_
              << " time (ms): "
              << diff_
              << "\n";

    return 0;
}
