#include <iostream>
#include <string>
#include <curl/curl.h>

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (curl) {
        printf("CURL initialized successfully!\n");
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
     system("pause");
    return 0;
}