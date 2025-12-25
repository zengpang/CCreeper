#pragma once // 防止头文件被多次包含
#include <string>
#include <map>
#include <curl/curl.h>

class WebCrawler{
    public:
      WebCrawler();
      ~WebCrawler();

      /**
       * HTTP Get 请求方法
       * @param url 请求地址
       * @param headers 可选的请求头
       */
      std::string get(const std::string& url,const std::map<std::string>& headers={});
      
      /**
       * HTTP 
       */
      std::string post(const std::string& url,const std::string& data,const std::map<std::strng,std::string>& headers={});

      //设置代理
      void setProxy(const std::string& proxy);

      //设置超时

}