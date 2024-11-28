#include <fstream>
#include <algorithm>
#include "upd.hh"

using namespace std;

namespace upd {
  auto UpDate::detect_package_manager()
    -> PackageManager
  {
    PackageManager res {};

    ifstream file("/etc/os-release");
    if (!file.is_open()) {
      res = PackageManager::ndef;
    }
    else {
      string line {};
      string id {};

      while (getline(file,line)) {
        if (file.eof()) {break;}
        else {
          if (line.find("ID=")==0) {
            id = line.substr(3);
            id.erase(remove(id.begin(),id.end(),' '), id.end());
          }
        }
      }
      file.close();

      if (id=="debian" || id=="ubuntu") {
        res = PackageManager::apt;
      }
      else if (id=="fedora" || id=="rhel" || id=="centos") {
        res = PackageManager::dnf_yum;
      }
      else if (id=="arch") {
        res = PackageManager::pacman;
      }
      else if (id=="opensuse") {
        res = PackageManager::zypper;
      }
      else {
        res = PackageManager::ndef;
      }
    }

    return res;
  }
}
