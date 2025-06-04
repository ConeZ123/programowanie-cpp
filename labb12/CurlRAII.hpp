#pragma once
#include <curl/curl.h>
#include <stdexcept>
#include <string>
#include <vector>

class CurlGlobal {
public:
    CurlGlobal()  { curl_global_init(CURL_GLOBAL_DEFAULT); }
    ~CurlGlobal() { curl_global_cleanup(); }
};


class CurlHandle {
public:
    CurlHandle() {
        handle_ = curl_easy_init();
        if (!handle_)
            throw std::runtime_error("curl_easy_init() failed");
    }
    ~CurlHandle() {
        if (handle_)
            curl_easy_cleanup(handle_);
    }
    
    CurlHandle(const CurlHandle&) = delete;
    CurlHandle& operator=(const CurlHandle&) = delete;
    CurlHandle(CurlHandle&& other) noexcept  : handle_(other.handle_) { other.handle_ = nullptr; }
    CurlHandle& operator=(CurlHandle&& other) noexcept {
        if (this != &other) {
            if (handle_) curl_easy_cleanup(handle_);
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    CURL* get() noexcept { return handle_; }
private:
    CURL* handle_{nullptr};
};


std::string fetch_url(const std::string& url);
