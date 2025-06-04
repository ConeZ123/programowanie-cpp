#include "CurlRAII.hpp"
#include <cstring>

namespace {
    
    size_t write_to_vec(char* ptr, size_t size, size_t nmemb, void* userdata)
    {
        auto* buffer = static_cast<std::vector<char>*>(userdata);
        size_t total = size * nmemb;
        buffer->insert(buffer->end(), ptr, ptr + total);
        return total;
    }
} 

std::string fetch_url(const std::string& url)
{
    CurlHandle curl;                
    std::vector<char> buffer;        

    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, write_to_vec);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &buffer);

    if (curl_easy_perform(curl.get()) != CURLE_OK)
        throw std::runtime_error("curl_easy_perform() failed");

    return std::string(buffer.begin(), buffer.end());
}
