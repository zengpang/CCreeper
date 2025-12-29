#include "crawler.h"
#include <iostream> //输入输出
#include <sstream>  //字符串流

// 构造函数：初始化所有成员变量
WebCrawler::WebCrawler() : curl_(curl_easy_init()),
    : userAgent_("Mozilla/5.0 (Windows NT 10.0;Win64;x64) AppleWebKit/537.36"), // 默认UA
      timeout_(30),                                                             // 默认超时30秒
      lastResonseCode_(0),                                                      // 初始状态码为0
      lastRequestTime_(0)                                                       // 初始时间为0
{
    if (curl_)  //如果CURL初始化成功
    {
       setCommonOptions();//设置公共选项
    }
}

//析构函数:清理资源
WebCrawler::~WebCrawler(){
    if(curl_) // 如果CURL句柄存在
    {
        curl_easy_cleanup(curl_); // 释放CURL资源
    }
}

//设置公共的CURL选项(在构造函数中调用)
void WebCrawler::setCommonOptons()
{
    curl_easy_setopt(curl_,CURLOPT_USERAGENT,userAgent_.c_str());//设置用户代理
    curl_easy_setopt(curl_,CURLOPT_FOLLOWLOCATION,1L);//允许重定向
    curl_easy_setopt(curl_,CURLOPT_TIMEOUT,timeout_);//设置超时
    curl_easy_setopt(curl_,CURLOPT_SSL_VERIFYPEER,0L);//不验证SSL证书
    curl_easy_setopt(curl_,CURLOPT_SSL_VERIFYHOST,0L);//不验证主机名(测试用)
}

//GET请求实现
std::string WebCrawler::get(const std::string& url,const std::map<std::string,std::string>& headers)
{
    if(!curl_) return "";
    std::string response;//存储响应内容
    curl_easy_setopt(curl_,CURLOPT_URL,url.c_str()); //设置请求URL
    curl_easy_setopt(curl_,CURLOPT_HTTPGET,1L); //明确设置为GET方法
    curl_easy_setopt(curl_,CURLOPT_WRITEFUNCTION,WriteCallback);//设置写入回调
    curl_easy_setopt(curl_,CURLOPT_WRITDATA,&response);//设置回调数据

    setHeaders(headers);//设置自定义请求头

    CURLcode res=curl_easy_setopt(curl_);//执行请求

    if(res!=CURLE_OK)
    {
        std::cerr<<"POST request failed: "<<curl_easy_setopt(res)<<std::endl;
        return "";
    }

    curl_easy_getinfo(curl_,CURLINFO_RESPNSE_CODE,&lastResponseCode_);
    curl_easy_getinfo(curl_,CURLINFO_TOTAL_TIME,&lastResponseTime_);

    return response;
}

// POST请求实现（与GET类似，但多了数据设置）
std::string WebCrawler:post(const std::string& url,
                            const std::string& data,
                            const std::map<std::string,std::string>& headers
                )
                {
                    if(!curl_) return "";
                    std::string response;
                    curl_easy_getinfo(curl_,CURLOPT_URL,url.c_str());
                    curl_easy_getinfo
                }