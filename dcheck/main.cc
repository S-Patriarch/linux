/*
 * Copyright (C) 2024, S-Patriarch
 * DomainChecker - проверка доступности и отзывчивости доменов.
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include <memory>
#include "pl/pl.conio"
#include "pl/pl.ios"
#include "dcheck.hh"

int main(int argc, char **argv)
{
    using std::cout;
    using std::endl;

    using std::string;

    std::vector<string> args(argv, argv+argc);
    std::size_t argsize {args.size()};

    string arglistfile {};
    string argoption {};

    switch (argsize) {
    case 3:
        arglistfile = args[2];
        argoption   = args[1];
        break;
    case 2:
        if (args[1]=="-h" || args[1]=="-r") {
            arglistfile = "";
            argoption   = args[1];
        }
        else {
            arglistfile = args[1];
            argoption   = "";
        }
        break;
    default:
        arglistfile = "";
        argoption   = "";
        break;
    }

    auto dch = std::make_unique<dcheck::DomainChecker>();

    if ((arglistfile=="" && argoption=="")   ||
        (arglistfile=="" && argoption=="-h") ||
        (arglistfile!="" && argoption=="-h") ||
        (arglistfile=="" && argoption=="-r")) {
        cout << pl::mr::clrscr;
        dch->logo();
        cout << endl;
        dch->help();
    }
    else {
        if (arglistfile!="" && argoption=="-r") {
            dch->m_resfile = 1;
        }

        cout << pl::mr::clrscr;
        dch->logo();
        cout << endl;

        auto ios_ = std::make_unique<pl::ios>();

        std::fstream fs;
        fs.open(arglistfile, std::ios::in);

        string message {};
        if (!fs.is_open()) {
            if (dch->m_locale=="ru") message = "Файл "+arglistfile+" не открыт.";
            if (dch->m_locale=="en") message = arglistfile+" file is not open.";
            ios_->mout(message, 2);
        }
        else {
            fs.seekg(0, std::ios::end);
            if (fs.tellg()!=0) {
                fs.seekg(0, std::ios::beg);

                string sline {};
                string scolor {};
                while (std::getline(fs, sline)) {
                    if (fs.eof()) break;
                    else if (sline=="") continue;
                    else {
                        bool isrescheck = dch->domain_checker(sline.c_str());
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
                if (dch->m_locale=="ru") message = "Файл "+arglistfile+" пуст.";
                if (dch->m_locale=="en") message = arglistfile+" file is empty.";
                ios_->mout(message, 2);
            }
            fs.close();
        }

        if (dch->m_resfile==1) {
            if (dch->m_locale=="ru") message = "Результат работы отписан в файл : ";
            if (dch->m_locale=="en") message = "The result of the work is written to the file : ";
            cout
                << '\n'
                << "W: "
                << message
                << dch->m_fileresult
                << endl;
        }
    }

    cout << endl;
    std::exit(0);
}
