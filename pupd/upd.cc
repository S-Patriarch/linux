//
// (c) 2024 S-Patriarch
// Обновление системы GNU/Linux семейства Debian Linux.
//
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
std::int32_t main(int argc, char** argv)
{
   std::vector<std::string> args(argv,argv+argc);
   
   if (args.size()==2) {
      std::string opt {args.at(1)};
      if (opt=="-f" || opt=="--full") {
         std::system("sudo apt update && sudo apt full-upgrade -y");
         std::system("sudo apt autoremove -y");
         std::system("sudo apt autoclean -y");
         std::system("sudo apt clean -y");
      }
      else if (opt=="-u" || opt=="--updating") {
         std::system("sudo apt update && sudo apt full-upgrade -y");
      }
      else if (opt=="-c" || opt=="--cleaning") {
         std::system("sudo apt autoremove -y");
         std::system("sudo apt autoclean -y");
         std::system("sudo apt clean -y");
      }
      else {
         std::cout << "E: Command line option [" << opt << "] unclear.\n\n";
      }
   }
   else if (args.size()!=2) {
      std::cout << "Usage: upd [<options>]\n\n"
                << "upd is a assistand for updating and cleaning the system"
                << "of the family Debian Linux\n"
                << "for people with very little experience in OS GNU/Linux.\n\n"
                << "Options:\n"
                << "  -f  --full      Updating the system to the latest "
                << "version followed by cleaning.\n"
                << "  -u  --updating  Updating the system to the latest "
                << "version.\n"
                << "  -c  --cleaning  System cleaning.\n\n";
   }
   std::exit(EXIT_SUCCESS);
}
