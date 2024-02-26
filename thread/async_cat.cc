//
// (c) 2024 S-Patriarch
//
#include "pl/conio.hh"
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include <memory> // for std::make_shared
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
   // данный код является попыткой реализовать аcинхронно тривиальную ситуацию
   // по выводу с задержкой в 1 секунду строк из указанного файла до момента
   // нажатия пользователем любой клавиши
   // ожидание нажатия любой клавиши реализовано в дополнительном потоке
   // после нажатия пользователем любой клавиши дополнительный поток завершается
   // установив std::future в готовность
{
   if (argc!=2) std::cout << "W: Для работы необходимо указать файл.\n";
   else {
      std::ifstream file(argv[1]);
      if (!file.is_open()) {
         std::cerr << "E: error opening file " << argv[1] << '\n';
         return 1;
      }
      // объект std::promise оборачиваем в std::shared_ptr
      // это необходимо для копирования std::promise в новый поток
      // хотя можно было ее и переместить туда, но, к сожалению lambda не
      // содержит синтаксиса для "перемещающего захвата"
      auto pr = std::make_shared<std::promise<void>>();
      std::future<void> f = pr->get_future();
      auto f_async = std::async(std::launch::async,[pr]() {
         pl::Conio c;
         c.get_ch();
         pr->set_value();
      });
      int it {1};
      while (file.good()) {
         std::string line {};
         std::getline(file,line);
         std::cout << it++ << ' ' << line << '\n';
         if (f.wait_for(std::chrono::milliseconds{0})==std::future_status::ready) {
            f.get();
            std::cout << "W: stop after pressing any key...\n";
            break;
         }
         std::this_thread::sleep_for(std::chrono::seconds{1});
      }
      file.close();
   }
   return 0;
}

