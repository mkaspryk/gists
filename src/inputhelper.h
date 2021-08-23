#ifndef INPUTHELPER_H
#define INPUTHELPER_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

class InputHelper {
public:
    int getch();

    std::string getpass(const std::string &prompt, bool show_asterisk);

};

#endif // INPUTHELPER_H
