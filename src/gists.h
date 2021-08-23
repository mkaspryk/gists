#ifndef GISTS_H
#define GISTS_H

#include <iostream>
#include <string>
#include <vector>

#include "httpdownloader.h"
#include "inputhelper.h"
#include "jsonhelper.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct GistObject {
    std::string url;
    std::string file;
    std::string content;
    std::string description;
    std::string created_at;
    std::string updated_at;
};

class Gists {
    std::vector<GistObject> gistObjects;

    HTTPDownloader *downloader;
    InputHelper *input;
    JsonHelper *jsonHelper;

    std::string name;
    std::string api_key;
    std::string url;

    const std::string url_gists = "https://api.github.com/gists";

public:
    Gists();
    ~Gists();

    void gistsApp();

    bool gistsServiceGet(bool passCorrect);

    void gistsPrint();

    void gistsServiceAdd();

    void gistsServiceDelete();

    void gistsReadJsonParameters(json &j);

    bool getContent(std::string &url, std::string &output);

};

#endif // GISTS_H
