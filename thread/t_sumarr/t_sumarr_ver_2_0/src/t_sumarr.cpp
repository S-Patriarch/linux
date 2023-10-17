/*++

    Copyright (c) S-Patriarch, 2023

--*/

#include "../include/t_sumarr.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

//--------------------------------------------------------------------
SumArray::SumArray(std::int32_t sizeArray_, std::int32_t nThread_)
    : m_sizeArray {sizeArray_}
    , m_nThread {nThread_}
{
    const std::int32_t minValue {0};
    const std::int32_t maxValue {10};

    std::srand(std::time(0));

    for (std::int32_t i {0}; i < m_sizeArray; i++) {
        m_vector.push_back(minValue + std::rand() % (maxValue - minValue + 1));
    }
}

//--------------------------------------------------------------------
void SumArray::print_array()
{
    std::cout << "Array : ";

    for (const auto& i : m_vector) {
        std::cout << i
                  << " ";
    }

    std::cout << "\n\n";
}

//--------------------------------------------------------------------
void SumArray::sumCalculatePart(std::int32_t indexBegin,
                                std::int32_t indexEnd,
                                std::int32_t index)
{
    std::int32_t s_ {0};

    while (indexBegin <= indexEnd) {
        s_ += m_vector[indexBegin++];
    }

    m_sumResult += s_;
}

//--------------------------------------------------------------------
std::int32_t SumArray::calculate_without_thread()
{
    std::int32_t s_ {0};

    for (std::int32_t i {0}; i < m_vector.size(); i++) {
        s_ += m_vector[i];
    }

    return s_;
}

//--------------------------------------------------------------------
std::int32_t SumArray::calculate_using_thread()
{
    std::vector<std::thread> threads;

    std::int32_t indexBegin_ {0};
    std::int32_t indexEnd_   {0};

    std::int32_t countElements = m_sizeArray / m_nThread;

    m_sumResult = 0;

    for (std::int32_t i {0}; i < m_nThread; i++) {
        if (i == m_nThread - 1) {
            indexEnd_ = m_vector.size();
        }
        else {
            indexEnd_ = countElements;
        }

        // создаем поток
        std::thread t(&SumArray::sumCalculatePart,
                      this,
                      indexBegin_,
                      indexEnd_ - 1,
                      i);

        // добавляем созданный поток в вектор потоков,
        // при этом не копируем его а переносим,
        // что значительно ускоряет работу кода
        threads.push_back(std::move(t));

        indexBegin_ += countElements;
    }

    // дожидаемся отработки потоков
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return m_sumResult;
}
