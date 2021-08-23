#include "httpdownloader.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {

    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*) stream) << data << std::endl;
    return size * nmemb;
}

HTTPDownloader::HTTPDownloader() {

    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader() {

    curl_easy_cleanup(curl);
}

void HTTPDownloader::set(const std::string &name, const std::string &api_key, const std::string& url) {

    this->name = name;
    this->api_key = api_key;
    this->url = url;
}

bool HTTPDownloader::settings(std::string &output_data) {

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Github Gists Service");
    curl_easy_setopt(curl, CURLOPT_USERNAME, name.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, api_key.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, "Accept: application/vnd.github.v3+json");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    CURLcode res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        std::cout<<"curl_easy_perform() failed: "<<curl_easy_strerror(res)<<std::endl;
        return false;
    }
    output_data=out.str();
    return true;
}

bool HTTPDownloader::get(const std::string &name, const std::string &api_key, const std::string& url, std::string &output) {

    set(name, api_key, url);
    return this->settings(output);
}

bool HTTPDownloader::deleteGist(const std::string &name, const std::string &api_key, const std::string& url) {

    set(name, api_key, url);
    std::string out;
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    return this->settings(out);
}

bool HTTPDownloader::addGist(const std::string &name, const std::string &api_key, const std::string& url, const std::string &post_gist) {

    set(name, api_key, url);
    std::string out;
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_gist.c_str());
    return this->settings(out);
}
