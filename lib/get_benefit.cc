#include <curl/curl.h>
#include <bits/stdc++.h>

using namespace std;

class HttpConnection {
public:
    HttpConnection() {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_ = curl_easy_init();
    }

    ~HttpConnection() {
        curl_easy_cleanup(curl_);
    }

    bool Post(const std::string& url, const std::string& data, std::string& response) {
        if (!curl_) {
            return false;
        }

    // set params
		// set curl header
		struct curl_slist* header_list = NULL;
		// der_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
		header_list = curl_slist_append(header_list, "Content-Type:application/json; charset = UTF-8");
		curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header_list);    

        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_POST, 1L);
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl_);
        return (res == CURLE_OK);
    }

    bool Get(const std::string& url, std::string& response) {
        if (!curl_) {
            return false;
        }

        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
		    curl_easy_setopt(curl_, CURLOPT_POST, 0L);
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl_);
        return (res == CURLE_OK);
    }

private:
    CURL* curl_ = nullptr;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        size_t realsize = size * nmemb;
        std::string* str = static_cast<std::string*>(userp);
        str->append(static_cast<char*>(contents), realsize);
        return realsize;
    }
};

int main(void)
{
  HttpConnection test;
  
  string benefit = "https://openapi.twse.com.tw/v1/exchangeReport/BWIBBU_ALL";
  // 上市個股日本益比、殖利率及股價淨值比（依代碼查詢）

  string url = benefit;
  string res = "";
  test.Get(url, res);
  cout << res << '\n';
  return 0;
}