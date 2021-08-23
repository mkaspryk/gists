#include "jsonhelper.h"

bool JsonHelper::getJsonContent(std::string &str, std::string &json_content){

    unsigned int i=0;
    while(str[i]!=EOF){

        if (str[i]=='['){

            json_content = str.substr(i, str.size());
            json_content.erase(std::remove(json_content.begin(), json_content.end(), '\n'),json_content.end());
            return true;
        }
        ++i;
    }

    return false;
}

bool JsonHelper::getJsonContentOneElement(std::string &str, std::string &json_content){

    unsigned int i=0;
    while(str[i]!=EOF){

        if (str[i]=='{'){

            json_content = str.substr(i, str.size());
            json_content.erase(std::remove(json_content.begin(), json_content.end(), '\n'),json_content.end());
            return true;
        }
        ++i;
    }

    return false;
}
