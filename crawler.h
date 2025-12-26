#pragma once // 防止头文件被多次包含
#include <string>
#include <map>
#include <curl/curl.h>

class WebCrawler
{
public:
  WebCrawler();
  ~WebCrawler();

  /**
   * HTTP Get 请求方法
   * @param url 请求地址
   * @param headers 可选的请求头
   */
  std::string get(const std::string &url, const std::map<std::string> &headers = {});

  /**
   * HTTP
   */
  std::string post(const std::string &url, const std::string &data, const std::map<std::strng, std::string> &headers = {});

  // 设置代理
  void setProxy(const std::string &proxy);

  // 设置超时
  void setTimeout(long seconds);

  // 获取最后一次请求的消息
  long getLastResponseCode() const; // 获取http状态码

  double getLastRequestTime() const; // 获取请求耗时
private:
  CURL *curl_;
  std::string userAgent_;  // 用户代理字符串
  std::string proxy_;      // 代理服务器地址
  long timeout_;           // 超时时间(秒)
  long lastResponseCode_;  // 最后一次响应的HTTP状态码
  double lastRequestTime_; // 最后一次请求的耗时

  // 静态回调函数(不能访问非静态成员)
  static size_t WriteCallback(void *content, size_t size, size_t nmemb, std::string *response);
  void setCommonOptions();                                            // 设置公共的CURL选项
  void setHeaders(const std::map<std::string, std::string> &headers); // 设置请求头
};
