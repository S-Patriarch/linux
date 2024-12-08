// (c) 2024 S-Patriarch
// Обновление системы GNU/Linux семейства Debian Linux.

#include <cstdlib>
#include <vector>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   using std::string;
   using std::system;
   using std::cout;
   using std::endl;

   std::vector<string> args(argv,argv+argc);
   
   if (args.size()==2) {
      string opt {args.at(1)};
      if (opt=="-f" || opt=="--full") {
         system("sudo apt update && sudo apt full-upgrade -y");
         system("sudo apt autoremove -y");
         system("sudo apt autoclean -y");
         system("sudo apt clean -y");
      }
      else if (opt=="-u" || opt=="--updating") {
         system("sudo apt update && sudo apt full-upgrade -y");
      }
      else if (opt=="-c" || opt=="--cleaning") {
         system("sudo apt autoremove -y");
         system("sudo apt autoclean -y");
         system("sudo apt clean -y");
      }
      else {
         cout << "E: command line option [" << opt << "] unclear\n" << endl;
      }
   }
   else if (args.size()!=2) {
      cout << "Usage: upd [<options>]\n\n"
           << "upd is a assistand for updating and cleaning the system "
           << "of the family Debian Linux\n"
           << "for people with very little experience in OS GNU/Linux.\n\n"
           << "Options:\n"
           << "  -f  --full      Updating the system to the latest "
           << "version followed by cleaning.\n"
           << "  -u  --updating  Updating the system to the latest "
           << "version.\n"
           << "  -c  --cleaning  System cleaning.\n"
           << endl;
   }
   std::exit(EXIT_SUCCESS);
}
