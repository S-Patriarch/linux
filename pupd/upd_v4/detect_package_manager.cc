#include <fstream>
#include <algorithm>
#include "upd.hh"

using namespace std;

namespace upd {
  auto UpDate::detect_package_manager()
    -> pm
  {
    pm res {};

    ifstream file("/etc/os-release");
    if (!file.is_open()) {res=pm::NDEF;}
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

      if (id=="debian" || id=="ubuntu") {res=pm::APT;}
      else if (id=="fedora" || id=="rhel" || id=="centos") {res=pm::DNF_YUM;}
      else if (id=="arch") {res=pm::PACMAN;}
      else if (id=="opensuse") {res=pm::ZYPPER;}
      else {res=pm::NDEF;}
    }

    return res;
  }
}
