//
// (c) 2024 S-Patriarch
//
// пример работы с std::packaged_task в мире асинхронного выполнения кода
// std::packaged_task является первой сущностью поставки значения для future
//
// класс std::future представляет собой обертку, над каким-либо значением или
// объектом, вычисление или получение которого происходи отложено т.е. future 
// предоставляет доступ к некоторому разделяемому состоянию, которое состоит 
// из 2-х частей: данные (здесь лежит значение) и флаг готовности
// future является получателем значения и не может самостоятельно выставлять
// его; роль future пассивна
//
#include <iostream>
#include <future>
//------------------------------------------------------------------------------
std::future<bool> submit_form(const std::string& form)
   // в этом коде используется std::packaged_task в качестве аргумента thread, 
   // для того, чтобы исполнить задачу в отдельном потоке, т.к. ее исполнение в
   // том же потоке, что и вызов submit_form() уничтожил бы всю ее пользу
{
   auto handle = [](const std::string& form) -> bool {
      std::cout << "Обработка отправленной формы: " << form << '\n';
      return false;
   };
   std::packaged_task<bool(const std::string&)> task(handle);
   auto future = task.get_future();
   std::thread t(std::move(task),form);
   t.detach();
   return std::move(future);
}
////////////////////////////////////////////////////////////////////////////////
int main()
   // std::packaged_task выполняет роль задачи
   // задача является базовым блоком асинхронного программирования
   // программирование на уровне задач является весьма удобным механизмом
   // ускорения отзывчивости софта
   // 
   // хотя здесь использован только один поток с одной задачей никто не мешает 
   // сделать по другому, например очередь из задач, которые исполняются в
   // одном потоке
   // это позволит сэкономить на количестве потоков, если у нас есть 
   // непрерывный поток закач
   // в основном, применение std::packaged_task и заключается в идеоме
   // "один поток и много задач"
   // 
   // std::packaged_task следует использовать в местах, когда необходимо
   // выполнить некую функцию фсинхронно, и получить результат по окончанию ее
   // работы
{
   auto check = submit_form("Моя форма");
   if (check.get())
      std::cout << "Вау, у меня есть паспорт!\n";
   else
      std::cout << "Блин, они снова нашли ошибку!\n";
   return 0;
}