#include <iostream>
#include "crawler.h"                               //包含爬虫类
#include "htmlParser/baseHtmlParser/html_parser.h" // 包含HTML解析器
#include "enums.h"                                 // 包含枚举头文件
#include <sstream>
/**
 * 根据 网页类型 获取HTML
 * @param webType 网页类型
 */
std::string getHTMLByWebType(webType : CrawlWebType)
{
    std::string html;
    switch (webType)
    {
    case CrawlWebType::EHENTAI:

        int pageSize = 10;
        std::cout << "请输入爬取页码数量(默认页码:10)\n";
        std::cin >> pageSize;
        for (let i = 0; i < 10; i++)
        {
            html = crawler.get(url, headers); // 执行GET请求
        }
        
        break;

    case CrawlWebType::ORGHTTP:
        html = crawler.get(url, headers); // 执行GET请求
        break;
    default:
        html = crawler.get(url, headers); // 执行GET请求
        break;
    };
    return html;
}
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
        std::string url;  // 默认地址
        int inputWebType; // 爬取网页类型
        std::cout << "请输入序号，以此选择爬取网页地址\n";
        std::cout << "1:E站(需使用VPN,否则无法爬取信息)\n";
        std::cout << "2:原始HTTP测试站\n";
        std::cin >> inputWebType;
        switch (inputWebType)
        {
        case CrawlWebType::EHENTAI:
            std::cout << "请输入漫画搜索词条\n";
            std::string searchStr;
            std::cin >> searchStr;
            if (!searchStr.empty())
            {
                std::stringstream ss;
                ss << "https://e-hentai.org/" << "?" << "f_search=" << searchStr;
            }
            else
            {

                url = "https://e-hentai.org/";
            }
            // https://e-hentai.org/?f_search=tomgirl
            break;

        case CrawlWebType::ORGHTTP:
            url = "http://httpbin.org/html";
            break;
        }
        if (url.empty())
        {
            std::cout << "爬取目标地址不能为空" << std::endl;
            // 清理libcurl全局环境
            curl_global_cleanup();
            system("pause");
            return 0;
        }
        std::cout << "开始爬取中..." << std::endl;
        std::string html;
        switch (inputWebType)
        {
        case CrawlWebType::EHENTAI:

            std::cout << "请输入爬取页码数量\n";
            html = crawler.get(url, headers); // 执行GET请求
            break;

        case CrawlWebType::ORGHTTP:
            html = crawler.get(url, headers); // 执行GET请求
            break;
        }

        std::cout << "爬取完成" << std::endl;
        if (!html.empty())
        {

            std::cout << "网页原始内容" << html << std::endl;
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

            std::cout << "\n找到 " << images.size() << " 个图片:" << std::endl;
            for (const auto &img : images)
            {
                std::cout << " -" << img << std::endl;
            }

            std::cout << "\n提取的文本内容" << std::endl;
        }
        else
        {
            std::cout << "获取不到网页原始内容" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 清理libcurl全局环境
    curl_global_cleanup();
    system("pause");
    return 0;
}