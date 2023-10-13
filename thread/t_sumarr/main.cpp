/*++

    Copyright (c) S-Patriarch, 2023
    Подсчет суммы элементов массива несколькими потоками.

--*/

#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <functional>

//--------------------------------------------------------------------
// Функция, которую будут выполнять потоки для подсчета суммы
//
void sumCalculate(const std::vector<std::uint16_t>& v,
                  std::uint16_t indexStart,
                  std::uint16_t indexEnd,
                  std::uint16_t& sumResult)
{
    // инициализируем сумму для этого потока
    std::uint16_t sumLocal {0};

    // проходим по части массива текущего потока
    for (std::uint16_t i {indexStart}; i < indexEnd; ++i) {
        sumLocal += v[i];
    }

    // добавляем локальную сумму к общей сумме
    sumResult += sumLocal;
}

//////////////////////////////////////////////////////////////////////
int main()
{
    // исходный массив
    const std::vector<std::uint16_t> v {5,3,2,4,8,9,6,1,1,7,9,3,8,2,6,3,5,5,4,7};

    // количество потоков
    const std::uint16_t nThreads {4};

    // разделяем массив на части по количеству потоков
    const std::uint16_t partNumber = v.size() / nThreads;

    // общая сумма массива
    std::uint16_t sumResult {};

    // массив потоков
    std::vector<std::thread> threads {};

    // начальное значение итератора (индекса)
    std::uint16_t indexStart {0};

    // создаем и запускаем потоки
    for (std::uint16_t i {0}; i < nThreads; ++i) {
        std::uint16_t indexEnd =
            (i == nThreads-1) ? v.size() : indexStart + partNumber;

        threads.emplace_back(sumCalculate,
                             std::ref(v),
                             indexStart,
                             indexEnd,
                             std::ref(sumResult));

        indexStart = indexEnd;
    }

    // ожидаем завершения работы всех потоков
    for (auto& i : threads) {
        i.join();
    }

    // выводим результат
    std::cout << "Сумма элементов массива = "
              << sumResult
              << '\n';

    return 0;
}
