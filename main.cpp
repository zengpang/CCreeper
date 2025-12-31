#include <iostream>
#include "crawler.h"     //包含爬虫类
#include "html_parser.h" // 包含HTML解析器
int main()
{
    // 初始化
    curl_global_init(CURL_GLOBAL_DEFAULT);
    try
    {
        // 异常处理
        WebCrawler crawler; // 创建爬虫实例

        // 设置请求头(模拟游览器)
        std::map<std::string, std::string> headers = {
            {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"},
            {"Accept-Language", "en-US,en;q=0.5"},
            {"Connection", "keep-alive"}};

        // 爬取网页
        std::string url = "http://httpbin.org/html";
        std::string html = crawler.get(url, headers); // 执行GET请求

        if (!html.empty())
        {
            std::cout << "成功获取网页内容(" << html.length() << "字节)" << std::endl;
            std::cout << "响应码：" << crawler.getLastResponseCode() << std::endl;
            std::cout << "请求时间：" << crawler.getLastRequestTime() << std::endl;

            // 解析HTML内容
            std::vector<std::string> links = HTMLParser::extractLinks(html, url);
            std::vector<std::string> images = HTMLParser::extractImages(html);
            std::string text = HTMLParser::extractText(html);

            // 输出结果
            std::cout << "\n找到" << links.size() << " 个链接" << std::endl;
            for (const auto &link : links)
            {
                std::cout << "  -" << link << std::endl;
            }

            std::cout<<"\n找到 "<<images.size()<<" 个图片"
        }
    }
}