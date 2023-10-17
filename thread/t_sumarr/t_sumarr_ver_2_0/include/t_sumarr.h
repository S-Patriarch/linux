/*++

    Copyright (c) S-Patriarch, 2023

--*/

#ifndef T_SUMARR_H
#define T_SUMARR_H

#include <vector>
#include <cstdint>

//////////////////////////////////////////////////////////////////////
class SumArray
{
private:
    std::int32_t m_sizeArray {}; // размер массива элементов
    std::int32_t m_nThread {};   // количество потоков
    std::int32_t m_sumResult {}; // результат суммы элементов массива

    std::vector<std::int32_t> m_vector {}; // массив элементов

    // функция потока
    void sumCalculatePart(std::int32_t, std::int32_t, std::int32_t);

public:
    SumArray(std::int32_t, std::int32_t);
    ~SumArray() = default;

    std::int32_t calculate_using_thread();
    std::int32_t calculate_without_thread();
    void print_array();

}; // class SumArray

#endif // T_SUMARR_H
