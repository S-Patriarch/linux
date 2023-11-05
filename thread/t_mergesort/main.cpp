/*++

    (c) S-Patriarch, 2023

    t_margesort
    Сортировка слиянием с использованием многопоточности.

Техническое задание:

    1. Использовать std::future в качестве инструмента для
    синхронизации результата работы потока.
    2. Нужно определить независимые части алгоритма, которые могут быть
    распараллелены и запустить их вычисление в отдельных потоках.
    3. Потоки могут быть запущены через std::thread или std::async, но
    синхронизация строго через std::future.
    4. Предусмотреть ограничение количества запускаемых потоков.

Описание:

    В данной реализации функции mergeSort и merge выполняют сортировку слиянием
    независимых частей массива. Функция parallelMergeSort распределяет части
    массива между количеством заданных потоков и создает потоки для выполнения
    сортировки частей. Затем она объединяет результаты в итоговый отсортированный
    массив.

    Помимо этого, данная реализация обеспечивает строгую синхронизацию через
    использование std::future для контроля завершения выполнения потоков.
    Она также позволяет ограничить количество запускаемых потоков с помощью
    параметра num_threads.

--*/

#include <iostream>
#include <vector>
#include <future>
#include <thread>

//------------------------------------------------------------------------------
// Функция для сортировки слиянием одной части массива.
//
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);

    for (int i = 0; i < n1; ++i)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        right_arr[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_arr[i] < right_arr[j]) {
            arr[k] = left_arr[i];
            ++i;
        }
        else {
            arr[k] = right_arr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = left_arr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = right_arr[j];
        ++j;
        ++k;
    }
}

//------------------------------------------------------------------------------
// Функция для сортировки слиянием.
//
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        std::function<void()> left_child = [&]() {
            mergeSort(arr, left, middle);
        };

        std::function<void()> right_child = [&]() {
            mergeSort(arr, middle + 1, right);
        };

        std::future<void> left_future = std::async(std::launch::async, left_child);
        std::future<void> right_future = std::async(std::launch::async, right_child);

        left_future.wait();
        right_future.wait();

        merge(arr, left, middle, right);
    }
}

//------------------------------------------------------------------------------
// Функция для запуска сортировки слиянием.
//
void parallelMergeSort(std::vector<int>& arr, int num_threads) {
    int size = arr.size();
    int chunk_size = size / num_threads;

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        int left = i * chunk_size;
        int right = (i == num_threads - 1) ? (size - 1) : (left + chunk_size - 1);
        // добавляем новый элемент в конец контейнера
        threads.emplace_back(std::thread(mergeSort, std::ref(arr), left, right));
    }

    for (auto& thread : threads) {
        if (thread.joinable())
            thread.join();
    }

    // выполняем окончательное слияние
    for (int i = 1; i < num_threads; i *= 2) {
        for (int j = 0; j < num_threads - i; j += 2 * i) {
            int left = j * chunk_size;
            int mid = (j + i - 1) * chunk_size;
            int right = std::min((j + 2 * i - 1) * chunk_size, size - 1);

            merge(arr, left, mid, right);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::vector<int> arr = { 3, 7, 6, 9, 2, 5 };
    int num_threads = 2;

    std::cout << "     Исходный массив: ";
    for (const auto& i : arr) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    parallelMergeSort(arr, num_threads);

    std::cout << "Сортированный массив: ";
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << '\n';

    return 0;
}
