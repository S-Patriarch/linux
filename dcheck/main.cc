/*
 * Copyright (C) 2024, S-Patriarch
 * DomainChecker - проверка доступности и отзывчивости доменов.
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include "pl/pl.conio"
#include "pl/pl.ios"
#include "dcheck.hh"

int main(int argc, char **argv)
{
    using std::cout;
    using std::endl;

    std::vector<std::string> args(argv, argv+argc);
    dcheck::DomainChecker dch;

    if (args.size()>=2) {
        cout << pl::mr::clrscr;
        dch.logo();
        cout << endl;

        if (args.size()==3) {
            std::string argoption {args[2]};
            if (argoption=="-r") dch.m_resfile = 1;
        }

        pl::ios ios_;

        std::fstream fs;
        std::string arglistfile {args[1]};
        fs.open(arglistfile, std::ios::in);

        std::string message {};
        if (!fs.is_open()) {
            if (dch.m_locale=="ru") message = "Файл "+arglistfile+" не открыт.";
            if (dch.m_locale=="en") message = arglistfile+" file is not open.";
            ios_.mout(message, 2);
        }
        else {
            fs.seekg(0, std::ios::end);
            if (fs.tellg()!=0) {
                fs.seekg(0, std::ios::beg);

                std::string sline {};
                std::string scolor {};
                while (std::getline(fs, sline)) {
                    if (fs.eof()) break;
                    else if (sline=="") continue;
                    else {
                        bool isrescheck = dch.domain_checker(sline.c_str());
                        if (isrescheck) scolor = "[  \033[32mOK\033[0m  ]";
                        else scolor = "[\033[31mFAILED\033[0m]";
                        cout
                            << scolor
                            << ' '
                            << sline
                            << endl;
                    }
                }
            }
            else {
                if (dch.m_locale=="ru") message = "Файл "+arglistfile+" пуст.";
                if (dch.m_locale=="en") message = arglistfile+" file is empty.";
                ios_.mout(message, 2);
            }
            fs.close();
        }
    }
    else {
        cout << pl::mr::clrscr;
        dch.logo();
        cout << endl;
        //dch.help();
    }

    cout << endl;
    std::exit(0);
}
