#include "crawler.h"
#include <iostream> //输入输出
#include <sstream>  //字符串流

// 构造函数：初始化所有成员变量
WebCrawler::WebCrawler() : curl_(curl_easy_init()),
                           userAgent_("Mozilla/5.0 (Windows NT 10.0;Win64;x64) AppleWebKit/537.36"), // 默认UA
                           timeout_(30),                                                             // 默认超时30秒
                           lastResponseCode_(0),                                                      // 初始状态码为0
                           lastRequestTime_(0)                                                       // 初始时间为0
{
    if (curl_) // 如果CURL初始化成功
    {
        setCommonOptions(); // 设置公共选项
    }
}

// 析构函数:清理资源
WebCrawler::~WebCrawler()
{
    if (curl_) // 如果CURL句柄存在
    {
        curl_easy_cleanup(curl_); // 释放CURL资源
    }
}

// 设置公共的CURL选项(在构造函数中调用)
void WebCrawler::setCommonOptions()
{
    curl_easy_setopt(curl_, CURLOPT_USERAGENT, userAgent_.c_str()); // 设置用户代理
    curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);            // 允许重定向
    curl_easy_setopt(curl_, CURLOPT_TIMEOUT, timeout_);             // 设置超时
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);            // 不验证SSL证书
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);            // 不验证主机名(测试用)
}

// GET请求实现
std::string WebCrawler::get(const std::string &url, const std::map<std::string, std::string> &headers)
{
    if (!curl_)
        return "";
    std::string response;                                          // 存储响应内容
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());             // 设置请求URL
    curl_easy_setopt(curl_, CURLOPT_HTTPGET, 1L);                  // 明确设置为GET方法
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback); // 设置写入回调
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);          // 设置回调数据

    setHeaders(headers); // 设置自定义请求头

    CURLcode res = curl_easy_setopt(curl_); // 执行请求

    if (res != CURLE_OK)
    {
        std::cerr << "POST request failed: " << curl_easy_setopt(res) << std::endl;
        return "";
    }

    curl_easy_getinfo(curl_, CURLINFO_RESPNSE_CODE, &lastResponseCode_);
    curl_easy_getinfo(curl_, CURLINFO_TOTAL_TIME, &lastResponseTime_);

    return response;
}

// POST请求实现（与GET类似，但多了数据设置）
std::string WebCrawler : post(const std::string &url,
                              const std::string &data,
                              const std::map<std::string, std::string> &headers)
{
    if (!curl_)
        return "";
    std::string response;
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, data.length());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);

    setHeaders(headers);

    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK)
    {
        std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &lastResponseCode_);
    curl_easy_getinfo(curl_, CURLINFO_TOTAL_TIME, &lastResponseCode_);

    return response;
}

// 设置代理服务器
void WebCrawler::setProxy(const std::string &proxy)
{
    proxy_ = proxy;
    if (!proxy_.empty())
    {
        curl_easy_setopt(curl_, CURLOPT_PROXY, proxy_.c_str()); // 设置代理
    }
}

// 设置超时时间
void WebCrawler::setTimeout(long seconds)
{
    timeout_ = seconds;
    curl_easy_setopt(curl_, CURLOPT_TIMEOUT, timeout_); // 设置CURL超时
}

// 设置请求头
void WebCrawler : setHeaders(const std::map<std::string, std::string> &headers)
{
    struct curl_slist *chunk = nullptr;

    // 遍历所有头部键值对
    for (const auto &header : headers)
    {
        std::string headerStr = header.first + ": " + header.second; // 格式化为"Key:Value"
        chunk = curl_slist_append(chunk, headerStr.c_str());         // 添加到链表
    }
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, chunk); // 设置请求头
}
/**
 * size_t 是 C++ 中一个非常重要的无符号整数类型，用于表示对象的大小或数组索引等。
 */
// 静态回调函数(与基础版本相同)
size_t WebCrawler : WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t totalSize = size * nmemb;
    response->append((char *)contents, totalSize);
    return totalSize;
}

// 获取最后一次请求的状态码
long WebCrawler::getLastResponseCode() const
{
    return lastResponseCode_;
}

// 获取最后一次请求的耗时
double WebCrawler::getLastRequestTime() const
{
    return lastRequestTime_;
}