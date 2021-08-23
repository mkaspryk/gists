#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <sstream>

class HTTPDownloader {
    std::string name;
    std::string api_key;
    std::string url;

public:
    HTTPDownloader();
    ~HTTPDownloader();

    void set(const std::string &name, const std::string &api_key, const std::string& url);

    bool settings(std::string &output_data);

    bool get(const std::string &name, const std::string &api_key, const std::string& url, std::string &output);

    bool deleteGist(const std::string &name, const std::string &api_key, const std::string& url);

    bool addGist(const std::string &name, const std::string &api_key, const std::string& url, const std::string &post_gist);

private:
    void* curl;

};

#endif // HTTPDOWNLOADER_H
