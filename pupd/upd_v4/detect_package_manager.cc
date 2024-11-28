#include <fstream>
#include <algorithm>
#include <stdexcept>
#include "upd.hh"

namespace upd {
  auto UpDate::detect_package_manager()
    -> std::string
  {
    std::string res {};

    std::ifstream file("/etc/os-release");
    if (!file.is_open()) {
      res = "";
    }
    else {
      std::string line {};
      std::string id {};

      while (std::getline(file,line)) {
        if (file.eof()) {break;}
        else {
          if (line.find("ID=")==0) {
            id = line.substr(3);
            id.erase(std::remove(id.begin(),id.end(),'"'), id.end());
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
