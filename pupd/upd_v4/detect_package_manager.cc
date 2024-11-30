#include <fstream>
#include <algorithm>
#include <stdexcept>
#include "upd.hh"

namespace upd {
  auto UpDate::detect_package_manager()
    -> std::string
  {
    using std::string;
    using std::ifstream;
    using std::getline;
    using std::remove;

    string res {};

    ifstream file("/etc/os-release");
    if (!file.is_open()) {
      res = "";
    }
    else {
      string line {};
      string id {};

      while (getline(file,line)) {
        if (file.eof()) {break;}
        else {
          if (line.find("ID=")==0) {
            id = line.substr(3);
            id.erase(remove(id.begin(),id.end(),'"'), id.end());
          }
        }
      }
      file.close();

      try {
        res = ospm.at(id);
      }
      catch (const std::out_of_range &e) {
        res = "";
      }
    }

    return res;
  }
}
