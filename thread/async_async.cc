//
// (c) 2024 S-Patriarch
//
// пример работы с std::async в мире асинхронного выполнения кода
// std::async является третьей сущностью поставки значения для future
//
// класс std::future представляет собой обертку, над каким-либо значением или
// объектом, вычисление или получение которого происходи отложено т.е. future 
// предоставляет доступ к некоторому разделяемому состоянию, которое состоит 
// из 2-х частей: данные (здесь лежит значение) и флаг готовности
// future является получателем значения и не может самостоятельно выставлять
// его; роль future пассивна
//
#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
////////////////////////////////////////////////////////////////////////////////
int main()
   // std::async с флагом launch::async является удобной заменой
   // std::packaged_task и прямого использования std::thread
   // т.е. есть смысл всегда использовать ее в тех местах, где нет явной
   // необходимости в использовании std::thread и std::packaged_task
   // например, когда есть необходимость в создании отдельного потока на
   // каждую задачу
   //
   // std::async, с флагом launch::deferred, удобно использовать в случае
   // необходимого отложенного вычисления не требовательного к ресурсам, т.е.
   // того которое может быть быстро вычислено в месте его получения
   // 
   // результат работы данного кода:
   // 1. реализация async выбрала launch::async, как политику по умолчанию
   // 2. первый (async_deferred) async с launch::deferred был выполнен в том
   // же потоке, что и main
   // 3. первый async с launch::deferred был выполнен после того, как 
   // отработал sleep
   // 4. второй (async_deferred_2) async не был выполнен т.к. не была вызвана
   // соответствующая функция ожидания, а следовательно и вызова не будет
   // 5. async с явням переданным флагом launch::async был выполнен в
   // отдельном потоке
{
   std::cout << "идентификатор основного потока id="
             << std::this_thread::get_id() << '\n';

   auto async_default = std::async([]() {
   	std::cout << "асинхронный, по умолчанию, индентификатор потока id="
                << std::this_thread::get_id() << '\n';
   });
   auto async_deferred = std::async(std::launch::deferred,
   	[](const std::string& str) {
      std::cout << "асинхронная отсрочка, индентификатор потока id="
                << std::this_thread::get_id() << ',' << str << '\n';
   },std::string("конец строки"));
   auto async_deferred_2 = std::async(std::launch::deferred,[]() {
      std::cout << "асинхронная отсрочка 2, индентификатор потока id="
                << std::this_thread::get_id() << '\n';
   });
   auto true_async = std::async(std::launch::async,[]() {
      std::cout << "настоящий асинхронный, индентификатор потока id="
                << std::this_thread::get_id() << '\n';
   });

   std::this_thread::sleep_for(std::chrono::seconds{5});
   std::cout << "сон закончился\n";
   async_default.get();
   async_deferred.get();
   true_async.get();
   return 0;
}
