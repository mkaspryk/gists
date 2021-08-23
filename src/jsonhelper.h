#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <string>
#include <algorithm>

class JsonHelper {
public:
    bool getJsonContent(std::string &str, std::string &json_content);

    bool getJsonContentOneElement(std::string &str, std::string &json_content);

};

#endif // JSONHELPER_H
