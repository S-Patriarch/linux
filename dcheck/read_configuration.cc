#include <fstream>
#include <cstring>
#include "dcheck.hh"

namespace dcheck {

    auto DomainChecker::read_configuration()
        -> void
    {
        std::fstream fs;
        fs.open(m_fileconfig, std::ios::in);

        if (fs.is_open()) {
            fs.seekg(0, std::ios::end);
            if (fs.tellg()!=0) {
                fs.seekg(0, std::ios::beg);

                std::string sline {};
                while (std::getline(fs, sline)) {
                    if (fs.eof()) break;
                    else if (sline=="") continue;
                    else {
                        size_t pos {0};
                        char delimiter {'='};
                        while ((pos=sline.find(delimiter)) != std::string::npos) {
                            std::string token = sline.substr(0, pos);
                            sline.erase(0, pos+1);
                            if (token=="resfile") {
                                if (!sline.empty()) m_resfile = std::stoi(sline);
                            }
                        }
                    }
                }
            }
            fs.close();
        }
    }

}
